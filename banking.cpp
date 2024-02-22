#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <iomanip>
#include <vector>
#include <random>
#include <unordered_map>

class Account {
public:
    Account(std::string id, std::string password)
        : id(id), password(password), savingsBalance(0.0), checkingBalance(0.0), interestRate(0.03) {}

    bool deposit(double amount, const std::string& accountType) {
        if (accountType == "savings") {
            savingsBalance += amount;
        } else if (accountType == "checking") {
            checkingBalance += amount;
        } else {
            return false;
        }
        return true;
    }

    bool withdraw(double amount, const std::string& accountType) {
        if (accountType == "savings" && savingsBalance >= amount) {
            savingsBalance -= amount;
            return true;
        } else if (accountType == "checking" && checkingBalance >= amount) {
            checkingBalance -= amount;
            return true;
        }
        return false;
    }

    void applyInterest() {
        savingsBalance += savingsBalance * interestRate;
    }

    void displayBalances() const {
        std::cout << "Savings Account Balance: $" << std::fixed << std::setprecision(2) << savingsBalance << std::endl;
        std::cout << "Checking Account Balance: $" << std::fixed << std::setprecision(2) << checkingBalance << std::endl;
    }

    std::string getId() const { return id; }
    bool checkPassword(const std::string& pw) const { return pw == password; }
    
    bool buyStock(const std::string& stockName, double amount) {
        if (savingsBalance >= amount) {
            savingsBalance -= amount;
            portfolio[stockName] += amount;
            return true;
        }
        return false;
    }

    bool sellStock(const std::string& stockName, double amount) {
        if (portfolio.find(stockName) != portfolio.end() && portfolio[stockName] >= amount) {
            savingsBalance += amount;
            portfolio[stockName] -= amount;
            if (portfolio[stockName] == 0) {
                portfolio.erase(stockName);
            }
            return true;
        }
        return false;
    }

    void displayInvestments() const {
        std::cout << "Stock Investments:\n";
        for (const auto& pair : portfolio) {
            std::cout << pair.first << ": $" << std::fixed << std::setprecision(2) << pair.second << std::endl;
        }
    }

private:
    std::string id;
    std::string password;
    double savingsBalance;
    double checkingBalance;
    double interestRate;
    std::unordered_map<std::string, double> portfolio; // Tracks stock investments
};

class Stock {
public:
    Stock(const std::string& name, double price)
        : name(name), price(price) {}

    std::string getName() const { return name; }
    double getPrice() const { return price; }

    void updatePrice() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-0.05, 0.05);
        price += price * dis(gen);
        if (price < 0) price = 0.01;
    }

private:
    std::string name;
    double price;
};


class BankSystem {
public:
    BankSystem() {
        initializeStockMarket();
    }
    
     void buyStock(const std::string& stockName, double investAmount) {
    if (currentAccount && currentAccount->buyStock(stockName, investAmount)) {
        std::cout << "Invested $" << investAmount << " in " << stockName << ".\n";
    } else {
        std::cout << "Investment failed. Check your balance or sign in.\n";
        }
    }

    void sellStock(const std::string& stockName, double sellAmount) {
        if (currentAccount && currentAccount->sellStock(stockName, sellAmount)) {
            std::cout << "Divested $" << sellAmount << " from " << stockName << ".\n";
        } else {
            std::cout << "Divestment failed. Check your investments or sign in.\n";
        }
    }

    void createAccount(const std::string& id, const std::string& password) {
        if (userDatabase.find(id) == userDatabase.end()) {
            userDatabase[id] = password;
            accounts[id] = std::make_unique<Account>(id, password);
            std::cout << "Account successfully created for " << id << ".\n";
        } else {
            std::cout << "An account with this ID already exists.\n";
        }
    }

    bool signIn(const std::string& id, const std::string& password) {
        auto it = userDatabase.find(id);
        if (it != userDatabase.end() && it->second == password) {
            currentAccount = accounts[id].get();
            std::cout << "Successfully signed in as " << id << ".\n";
            return true;
        } else {
            std::cout << "Sign in failed. Incorrect ID or password.\n";
            return false;
        }
    }

    void signOut() {
        if (currentAccount) {
            std::cout << "Signed out.\n";
            currentAccount = nullptr;
        } else {
            std::cout << "No user is currently signed in.\n";
        }
    }

    void deposit(double amount, const std::string& accountType) {
        if (currentAccount) {
            if (currentAccount->deposit(amount, accountType)) {
                std::cout << "Deposited $" << amount << " to your " << accountType << " account.\n";
            } else {
                std::cout << "Deposit failed. Invalid account type.\n";
            }
        } else {
            std::cout << "You must be signed in to deposit money.\n";
        }
    }

    void withdraw(double amount, const std::string& accountType) {
        if (currentAccount) {
            if (currentAccount->withdraw(amount, accountType)) {
                std::cout << "Withdrew $" << amount << " from your " << accountType << " account.\n";
            } else {
                std::cout << "Withdrawal failed. Insufficient funds or invalid account type.\n";
            }
        } else {
            std::cout << "You must be signed in to withdraw money.\n";
        }
    }

    void applyInterest() {
        if (currentAccount) {
            currentAccount->applyInterest();
            std::cout << "Interest applied to your savings account.\n";
        } else {
            std::cout << "You must be signed in to apply interest.\n";
        }
    }

    void displayBalances() {
        if (currentAccount) {
            currentAccount->displayBalances();
        } else {
            std::cout << "You must be signed in to view account balances.\n";
        }
    }

    void initializeStockMarket() {
        marketStocks.emplace_back("Tesla", 1000.0);
        marketStocks.emplace_back("Google", 1500.0);
        marketStocks.emplace_back("Apple", 120.0);
        marketStocks.emplace_back("Amazon", 2000.0);
        marketStocks.emplace_back("Meta", 250.0);
        marketStocks.emplace_back("Nvidia", 300.0);
        marketStocks.emplace_back("Aramco", 10.0);
        marketStocks.emplace_back("Nike", 110.0);
        marketStocks.emplace_back("Goldman Sachs", 250.0);
        marketStocks.emplace_back("Chase", 130.0);
    }

    void displayStocks() {
        std::cout << "\nAvailable Stocks:\n";
        for (auto& stock : marketStocks) {
            stock.updatePrice();
            std::cout << stock.getName() << " - $" << std::fixed << std::setprecision(2) << stock.getPrice() << "\n";
        }
    }

private:
    std::map<std::string, std::string> userDatabase;
    std::map<std::string, std::unique_ptr<Account>> accounts;
    Account* currentAccount = nullptr;
    std::vector<Stock> marketStocks;
};

void displayMenu() {
    std::cout << "\n*** Bank System Menu ***\n";
    std::cout << "1. Create Account\n";
    std::cout << "2. Sign In\n";
    std::cout << "3. Deposit Money\n";
    std::cout << "4. Withdraw Money\n";
    std::cout << "5. Apply Interest\n";
    std::cout << "6. Display Balances\n";
    std::cout << "7. Sign Out\n";
    std::cout << "8. Display Stocks\n";
    std::cout << "9. Buy Stocks\n";
    std::cout << "10. Sell Stocks\n";
    std::cout << "11. Exit\n";
    std::cout << "Select an option: ";
}

int main() {
    BankSystem bankSystem;
    int choice;
    std::string id, password, accountType;
    double amount;

    while (true) {
        displayMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                std::cout << "Enter ID: ";
                std::cin >> id;
                std::cout << "Enter Password: ";
                std::cin >> password;
                bankSystem.createAccount(id, password);
                break;
            case 2:
                std::cout << "Enter ID: ";
                std::cin >> id;
                std::cout << "Enter Password: ";
                std::cin >> password;
                if (!bankSystem.signIn(id, password)) {
                    std::cout << "Failed to sign in. Please check your credentials.\n";
                }
                break;
            case 3:
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                std::cout << "Enter account type (savings/checking): ";
                std::cin >> accountType;
                bankSystem.deposit(amount, accountType);
                break;
            case 4:
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                std::cout << "Enter account type (savings/checking): ";
                std::cin >> accountType;
                bankSystem.withdraw(amount, accountType);
                break;
            case 5:
                bankSystem.applyInterest();
                break;
            case 6:
                bankSystem.displayBalances();
                break;
            case 7:
                bankSystem.signOut();
                break;
            case 8:
                bankSystem.displayStocks();
                break;
            case 11:
                std::cout << "Exiting the bank system.\n";
                return 0;
            case 9: { 
                std::string stockName;
                double investAmount;
                std::cout << "Enter stock name to invest in: ";
                std::cin >> stockName;
                std::cout << "Enter amount to invest: ";
                std::cin >> investAmount;
                bankSystem.buyStock(stockName, investAmount);
                break;
            }
            case 10: { 
                std::string stockName;
                double sellAmount;
                std::cout << "Enter stock name to divest from: ";
                std::cin >> stockName;
                std::cout << "Enter amount to sell: ";
                std::cin >> sellAmount;
                bankSystem.sellStock(stockName, sellAmount);
                break;
            }
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}

