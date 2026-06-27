#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;
class InsufficientFundsException : public exception {
public:
	double shortfall;
	InsufficientFundsException(double s) : shortfall(s) {}
	const char* what() const noexcept override {
		return "Insufficient funds!";
	}
};

class InvalidAmountException : public exception {
public:
	const char* what() const noexcept override {
		return "Invalid amount! Must be greater than zero.";
	}
};

class AccountNotFoundException : public exception {
public:
	int accNum;
	AccountNotFoundException(int n) : accNum(n) {}
	const char* what() const noexcept override {
		return "Account not found!";
	}
};

class BankAccount {
public:
	int accNum;
	char owner[50];
	double balance;

	BankAccount() : accNum(0), balance(0.0) {
		owner[0] = '\0';
	}

	BankAccount(int num, const char* name, double b) {
		accNum = num;
		balance = b;
		int i = 0;
		while (name[i] != '\0' && i < 49) {
			owner[i] = name[i];
			i++;
		}
		owner[i] = '\0';
	}

	void deposit(double amt) {
		if (amt <= 0) throw InvalidAmountException();
		balance += amt;
	}

	void withdraw(double amt) {
		if (amt <= 0) throw InvalidAmountException();
		if (amt > balance) throw InsufficientFundsException(amt - balance);
		balance -= amt;
	}

	void transfer(BankAccount& target, double amt) {
		if (amt <= 0) throw InvalidAmountException();
		if (amt > balance) throw InsufficientFundsException(amt - balance);
		balance -= amt;
		target.balance += amt;
	}

	void show() {
		cout << "Account: " << accNum<<'\n'
			<< " Owner: " << owner<<'\n'
			<< " Balance: " << balance << endl;
	}
};

string getTime() {
	time_t now = time(0);
	char buf[26];
	ctime_s(buf, sizeof(buf), &now);
	buf[24] = '\0';       
	return string(buf);
}

void logError(const string& msg) {
	ofstream log("errors.log", ios::app);
	log << "[" << getTime() << "] " << msg << endl;
}

int findAcc(BankAccount accs[], int size, int num) {
	for (int i = 0; i < size; i++) {
		if (accs[i].accNum == num)
			return i;
	}
	return -1;
}

int loadAccounts(BankAccount accs[]) {
	ifstream file("accounts.dat", ios::binary);
	if (!file) return 0;

	int count = 0;
	while (file.read((char*)&accs[count], sizeof(BankAccount))) {
		count++;
	}
	file.close();
	return count;
}

void saveAccounts(BankAccount accs[], int size) {
	ofstream file("accounts.dat", ios::binary);
	for (int i = 0; i < size; i++) {
		file.write((char*)&accs[i], sizeof(BankAccount));
	}
	file.close();
}

int main() {
	BankAccount accs[10];
	int count = loadAccounts(accs);

	if (count == 0) {
		cout << "No data file found. Creating default accounts...\n";
		accs[0] = BankAccount(1001, "Ali Khan", 50000.0);
		accs[1] = BankAccount(1002, "Sara Ahmed", 30000.0);
		accs[2] = BankAccount(1003, "Bilal Raza", 20000.0);
		count = 3;
		saveAccounts(accs, count);
	}

	cout << "\n Accounts:\n";
	for (int i = 0; i < count; i++)
		accs[i].show();
	try {
		int i = findAcc(accs, count, 1001);
		if (i == -1) throw AccountNotFoundException(1001);
		accs[i].deposit(50000);
		cout << "T1: Deposited 50000 to 1001. New Bal: " << accs[i].balance << endl;
	}
	catch (const exception& e) {
		cout << "T1 Error: " << e.what() << endl;
		logError("T1 - " + string(e.what()));
	}
	try {
		int i = findAcc(accs, count, 1002);
		if (i == -1) throw AccountNotFoundException(1002);
		accs[i].withdraw(200000);
		cout << "T2: Withdrew 200000 from 1002\n";
	}
	catch (InsufficientFundsException& e) {
		cout << "T2 Error: " << e.what() << " Shortfall: " << e.shortfall << endl;
		logError("T2 - Insufficient Funds. Shortfall: " + to_string(e.shortfall));
	}
	catch (const exception& e) {
		cout << "T2 Error: " << e.what() << endl;
		logError("T2 - " + string(e.what()));
	}

	try {
		int from = findAcc(accs, count, 1001);
		int to = findAcc(accs, count, 9999);
		if (from == -1) throw AccountNotFoundException(1001);
		if (to == -1)   throw AccountNotFoundException(9999);
		accs[from].transfer(accs[to], 10000);
	}
	catch (const exception& e) {
		cout << "T3 Error: " << e.what() << endl;
		logError("T3 - " + string(e.what()));
	}
	try {
		int i = findAcc(accs, count, 1003);
		if (i == -1) throw AccountNotFoundException(1003);
		accs[i].deposit(-500);
	}
	catch (const exception& e) {
		cout << "T4 Error: " << e.what() << endl;
		logError("T4 - " + string(e.what()));
	}
	try {
		int from = findAcc(accs, count, 1001);
		int to = findAcc(accs, count, 1003);
		if (from == -1) throw AccountNotFoundException(1001);
		if (to == -1)   throw AccountNotFoundException(1003);

		accs[from].transfer(accs[to], 5000);
		cout << "T5: Transferred 5000 from 1001 to 1003\n";
		cout << "   1001 Bal: " << accs[from].balance
			<< " | 1003 Bal: " << accs[to].balance << endl;
	}
	catch (const exception& e) {
		cout << "T5 Error: " << e.what() << endl;
		logError("T5 - " + string(e.what()));
	}

	saveAccounts(accs, count);

	cout << "\n Final Accounts:\n";
	for (int i = 0; i < count; i++)
		accs[i].show();
	system("pause");
	return 0;
}
