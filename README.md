# C++ Bank System Detailed Overview

## Overview

This C++ project simulates a banking system, designed to emulate real-world financial operations within a console-based application. It allows for user interaction through a menu-driven interface, facilitating account management, financial transactions, interest accrual, and stock market investments.

## Detailed Features

### Enhanced Account Management
- **Unique Account Creation**: Leveraging a map data structure, the system ensures unique IDs for each account, preventing duplicates.
- **Secure Sign-In/Out**: Incorporates a basic authentication system for account access, promoting a fundamental level of security.

### Robust Banking Operations
- **Flexible Deposits and Withdrawals**: Users can seamlessly transfer funds to and from their savings and checking accounts, with real-time balance updates.
- **Automated Interest Application**: A predefined interest rate is applied to savings accounts, compounding the investment over time.

### Stock Market Simulation
- **Dynamic Stock Portfolio**: Users can buy and sell stocks from a predefined list of companies, with prices that fluctuate to simulate market conditions.
- **Investment Strategy Testing**: The simulated environment allows users to practice investment strategies without financial risk.

### Account Balance Inquiry
- **Real-Time Balance Display**: Instantly view the current state of both savings and checking accounts, providing clarity on financial status.

## Setup and Execution

### Environment Setup
Ensure your development environment includes a C++ compiler supporting C++11 standards or higher. This project was tested with GCC and Clang.

### Compilation Command
Compile the source code with the following command to ensure compatibility across platforms:

```bash
g++ -std=c++11 -o BankSystem BankSystem.cpp
```

### Execution
Run the application through the terminal or command prompt:

```bash
./BankSystem
```

## Usage Guide

1. **Navigate the Menu**: Use numerical inputs to navigate through the banking system's menu.
2. **Perform Transactions**: Follow prompts to deposit or withdraw funds, apply for interest, or manage stock investments.
3. **View Balances and Stocks**: Access detailed information on account balances and stock investments at any time.

## System Architecture

### Core Components

- `Account`: Manages account details, financial transactions, and the stock portfolio.
- `Stock`: Represents the fluctuating stock market, allowing for investment simulations.
- `BankSystem`: Coordinates the overall functionality, linking user interactions with backend logic.

### Data Management

- Utilizes `std::map` and `std::unordered_map` for efficient data retrieval and storage, ensuring quick access to account and stock information.

## Advanced Features and Future Enhancements

- **Persistence Layer**: Implementing file I/O operations to save and load user data for persistent usage across sessions.
- **Enhanced Security**: Upgrading the authentication mechanism to include password hashing and encryption for increased data protection.
- **User Interface Improvements**: Introducing a graphical user interface (GUI) for an enriched user experience.
- **Complex Market Simulations**: Incorporating more advanced algorithms for stock price fluctuations, reflecting more realistic market behaviors.
