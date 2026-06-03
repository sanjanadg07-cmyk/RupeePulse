💸 RupeePulse: Smart Portfolio & Budget Tracker
RupeePulse is a lightweight, high-performance fintech command-line application built in C++. It is designed to bridge the gap between basic daily expense tracking and wealth portfolio management, operating entirely with simulated Indian Rupees (Rs.).

 🚀 Core Features

* Income & Expense Logging: Seamlessly add cash inflows and outflows to maintain an accurate, real-time liquid cash balance.
* 🚨 Budget Alert System: Set a strict monthly spending threshold. The moment an added expense pushes your total spending past your limit, the system triggers a flashing security alert.
* 📈 Dynamic Investment Portfolio: Move your liquid cash into simulated assets like Stocks, Mutual Funds, or Gold. 
* 🎲 Live Market Simulation: Every time you open your dashboard, a random mathematical algorithm simulates real-world market volatility, dynamically shifting your asset values up or down so you can track your total net worth and profit/loss margins.

🛠️ Advanced OOP Principles Implemented
This project showcases clean, production-grade Object-Oriented Programming (OOP) concepts required for advanced computer science submissions:

* Inheritance: Created a master abstract `Transaction` base class, which cleanly branches into specialized `Income` and `Expense` child classes.
* Polymorphic Runtime Dispatch: Used virtual methods (`display()`) so the system can loop through your entire transaction history and dynamically format cash inflows (`[+]`) and outflows (`[-]`) on the fly.
* Encapsulation: All sensitive financial calculations, vector logs, and current balances are kept safely inside private class scopes, preventing unauthorized data corruption.
*Composition:Built a multi-layered system where the core `FinanceTracker` engine dynamically holds and updates a portfolio of distinct `Investment` objects.

💻 How to Build and Run the App

If you are evaluating this project or want to test it locally, execute the following command in your terminal/shell:

```bash
cd PersonalFinanceTracker && cmake -B build && cmake --build build && ./build/PersonalFinanceTracker
