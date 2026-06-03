#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib> 

using namespace std;
class Transaction {
protected:
    string description;
    double amount;

public:
    Transaction(string desc, double amt) : description(desc), amount(amt) {}
    virtual void display() const = 0; 
    virtual double getAmount() const = 0;
    virtual ~Transaction() {} 
class Income : public Transaction {
public:
    Income(string desc, double amt) : Transaction(desc, amt) {}
    void display() const override {
        cout << "[+] Income      | " << setw(20) << left << description 
             << " | Rs. " << fixed << setprecision(2) << amount << endl;
    }
    double getAmount() const override { return amount; }
};

class Expense : public Transaction {
public:
    Expense(string desc, double amt) : Transaction(desc, amt) {}
    void display() const override {
        cout << "[-] Expense     | " << setw(20) << left << description 
             << " | Rs. -" << fixed << setprecision(2) << amount << endl;
    }
    double getAmount() const override { return -amount; }
};

class Investment {
private:
    string assetName;
    double principalAmount;
    double currentPrice;

public:
    Investment(string name, double amt) : assetName(name), principalAmount(amt), currentPrice(amt) {}

   
    void updateMarketValue() {
        double changePercent = ((rand() % 16) - 5) / 100.0; 
        currentPrice += currentPrice * changePercent;
    }

    void displayInvestment() const {
        double profitLoss = currentPrice - principalAmount;
        cout << "[*] " << setw(11) << left << assetName 
             << " | Invested: Rs. " << setw(9) << fixed << setprecision(2) << principalAmount 
             << " | Current Val: Rs. " << setw(9) << currentPrice;
        if (profitLoss >= 0)
            cout << " ( Profit: +Rs. " << profitLoss << " )" << endl;
        else
            cout << " ( Loss: Rs. " << profitLoss << " )" << endl;
    }

    double getCurrentValue() const { return currentPrice; }
};

class FinanceTracker {
private:
    double liquidBalance;
    double expenseBudget;     
    double totalExpensesLimit; 
    vector<Transaction*> history; 
    vector<Investment> portfolio; 

public:
    FinanceTracker() : liquidBalance(0.0), expenseBudget(0.0), totalExpensesLimit(0.0) {}

    
    ~FinanceTracker() {
        for (auto t : history) delete t;
    }

    void setBudget(double budget) {
        expenseBudget = budget;
        cout << "\n>>> Success: Total Expense Budget set to Rs. " << fixed << setprecision(2) << expenseBudget << "!\n";
    }

    void addIncome(const string& desc, double amt) {
        history.push_back(new Income(desc, amt));
        liquidBalance += amt;
        cout << "\n>>> Success: Income added to balance!\n";
    }

    void addExpense(const string& desc, double amt) {
        if (amt > liquidBalance) {
            cout << "\n[!] Warning: Expense exceeds your liquid balance!\n";
        }
    
        totalExpensesLimit += amt;
        if (expenseBudget > 0.0 && totalExpensesLimit > expenseBudget) {
            cout << "\n🚨🚨 BUDGET ALERT WARNING 🚨🚨\n";
            cout << "[!] You have exceeded your budget limit of Rs. " << fixed << setprecision(2) << expenseBudget << "!\n";
            cout << "[!] Total Expenses logged so far: Rs. " << totalExpensesLimit << "\n";
            cout << "-----------------------------------\n";
        }

        history.push_back(new Expense(desc, amt));
        liquidBalance -= amt;
        cout << "\n>>> Success: Expense recorded!\n";
    }

    void buyAsset(const string& asset, double amt) {
        if (amt > liquidBalance) {
            cout << "\n[!] Error: Insufficient cash balance to invest Rs. " << amt << endl;
            return;
        }
        liquidBalance -= amt;
        portfolio.push_back(Investment(asset, amt));
        history.push_back(new Expense("Invested in " + asset, amt));
        cout << "\n>>> Success: Asset purchased successfully!\n";
    }

    void showDashboard() {
        double totalAssetValue = 0;
        for (auto& inv : portfolio) {
            inv.updateMarketValue();
            totalAssetValue += inv.getCurrentValue();
        }

        cout << "\n=========================================================================" << endl;
        cout << "                      FINANCE & INVESTMENT DASHBOARD                      " << endl;
        cout << "=========================================================================" << endl;
        cout << " Cash Balance: Rs. " << fixed << setprecision(2) << liquidBalance;
        cout << " | Total Invested Value: Rs. " << totalAssetValue << endl;
        cout << " Net Worth (Cash + Assets): Rs. " << (liquidBalance + totalAssetValue) << endl;
        if (expenseBudget > 0.0) {
            cout << " Expense Budget Set: Rs. " << expenseBudget << " | Total Spent: Rs. " << totalExpensesLimit << endl;
        }
        cout << "-------------------------------------------------------------------------" << endl;
        
        cout << " INVESTMENT HOLDINGS:" << endl;
        if (portfolio.empty()) cout << "   No active investments." << endl;
        for (const auto& inv : portfolio) inv.displayInvestment();
        
        cout << "-------------------------------------------------------------------------" << endl;
        cout << " TRANSACTION HISTORY:\n" << endl;
        if (history.empty()) cout << "   No transaction logs." << endl;
        for (const auto& t : history) t->display();
        
        cout << "=========================================================================" << endl;
    }
};

int main() {
    FinanceTracker myTracker;
    int choice;
    double amount;
    string description;

    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Add Income" << endl;
        cout << "2. Add Expense" << endl;
        cout << "3. Invest in Assets (Stocks/Mutual Funds/Gold)" << endl;
        cout << "4. Set Expense Budget Limit" << endl; 
        cout << "5. View Live Dashboard & Statements" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter choice (1-6): ";
        cin >> choice;

        if (choice == 1 || choice == 2 || choice == 3) {
            cout << "Enter Description / Asset Name: ";
            cin.ignore();
            getline(cin, description);
            cout << "Enter Amount: Rs. ";
            cin >> amount;
        } else if (choice == 4) {
            cout << "Enter your total Expense Budget Limit: Rs. ";
            cin >> amount;
        }

        switch (choice) {
            case 1: myTracker.addIncome(description, amount); break;
            case 2: myTracker.addExpense(description, amount); break;
            case 3: myTracker.buyAsset(description, amount); break;
            case 4: myTracker.setBudget(amount); break;
            case 5: myTracker.showDashboard(); break;
            case 6: cout << "\nExiting System. Keep growing your wealth!" << endl; break;
            default: cout << "\n[!] Invalid entry. Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
