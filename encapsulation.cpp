#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <cstring>
using namespace std;
class PaymentReceipt {
private:
	char* receiptId;
	char* issuedTo;
	unsigned long issuedAt;
	double confirmedAmount;
	bool isPrinted;

public:
	PaymentReceipt(const char* id, const char* to, unsigned long time, double amount) {
		receiptId = new char[strlen(id) + 1];
		strcpy(receiptId, id);

		issuedTo = new char[strlen(to) + 1];
		strcpy(issuedTo, to);

		issuedAt = time;
		confirmedAmount = amount;
		isPrinted = false;
	}

	~PaymentReceipt() {
		delete[] receiptId;
		delete[] issuedTo;
		cout << "Receipt  destroyed" << endl;
	}

	void printReceipt() const {
		cout << "Receipt ID     : " << receiptId << endl;
		cout << "Issued To      : " << issuedTo << endl;
		cout << "Date/Time      : " << issuedAt << endl;
		cout << "Amount         : " << confirmedAmount << " PKR" << endl;
		cout << "Printed        : " << (isPrinted ? "Yes" : "No") << endl;
	}

	void markPrinted() {
		isPrinted = true;
	}
};

class Transaction {
private:
	char* transactionId;
	double totalAmount;
	char* status;
	PaymentReceipt* receipt;   

public:
	Transaction(const char* tId, double amount, const char* customer) {
		transactionId = new char[strlen(tId) + 1];
		strcpy(transactionId, tId);

		totalAmount = amount;

		status = new char[20];
		strcpy(status, "PENDING");

		receipt = new PaymentReceipt(tId, customer, 12334567, amount);
	}

	~Transaction() {
		delete[] transactionId;
		delete[] status;
		if (receipt != nullptr) {
			delete receipt;
		}
		cout << "Transaction destroyed" << endl;
	}

	void complete() {
		strcpy(status, "COMPLETED");
		if (receipt != nullptr) {
			receipt->markPrinted();
		}
		cout << "Transaction COMPLETED" << endl;
	}

	void fail() {
		strcpy(status, "FAILED");
		if (receipt != nullptr) {
			delete receipt;
			receipt = nullptr;      
		}
		cout << "Transaction  FAILED" << endl;
	}

	void display() const {
		cout << "Transaction ID : " << transactionId << endl;
		cout << "Amount         : " << totalAmount << " PKR" << endl;
		cout << "Status         : " << status << endl;

		if (receipt != nullptr) {
			receipt->printReceipt();
		}
		else {
			cout << "Receipt  deleted " << endl;
		}
	}

	const char* getTransactionId() const {
		return transactionId;
	}
};

class TransactionHistory {
private:
	Transaction** history;
	int count;
	int capacity;

public:
	TransactionHistory() {
		capacity = 5;
		count = 0;
		history = new Transaction*[capacity];
	}

	~TransactionHistory() {
		for (int i = 0; i < count; i++) {
			if (history[i] != nullptr) {
				delete history[i];
			}
		}
		delete[] history;
		cout << "TransactionHistory destroyed" << endl;
	}

	void addTransaction(Transaction* t) {
		if (count == capacity) {
			capacity *= 2;
			Transaction** newArr = new Transaction*[capacity];
			for (int i = 0; i < count; i++) {
				newArr[i] = history[i];
			}
			delete[] history;
			history = newArr;
		}
		history[count] = t;
		count++;
	}

	void displayAll() const {
		cout << "-- TRANSACTION HISTORY --" << endl;
		for (int i = 0; i < count; i++) {
			if (history[i] != nullptr) {
				history[i]->display();
			}
		}
	}

	void removeTransaction(int index) {
		if (index >= 0 && index < count && history[index] != nullptr) {
			delete history[index];
			history[index] = nullptr;
			cout << "Transaction removed from history" << endl;
		}
	}
};

int main() {
	Transaction* t1 = new Transaction("a1", 500.0, "saba");
	Transaction* t2 = new Transaction("b2", 500.0, "mehak");
	Transaction* t3 = new Transaction("c3", 600.0, "zaima");

	t1->complete();
	t2->complete();
	t3->fail();

	TransactionHistory hist;
	cout << "--adding--" << endl;
	hist.addTransaction(t1);
	hist.addTransaction(t2);
	hist.addTransaction(t3);

	hist.displayAll();

	hist.removeTransaction(2);
	cout << "--composition--" << endl;
	hist.displayAll();

	// TransactionHistory going out of scope here
	// Its destructor will delete all remaining Transactions
	// Each Transaction will delete its Receipt
/*
	COMPOSITION EXPLANATION:

	1. This is Composition because:
	- Transaction creates PaymentReceipt using 'new' inside its constructor.
	- Transaction deletes PaymentReceipt in its destructor.
	- Receipt cannot exist without Transaction.

	2. If PaymentReceipt was created outside and passed by pointer
	(like Merchant in previous program), it would be Aggregation.

	3. Dangling Pointer Example (Do NOT uncomment):
	t3->fail();           // receipt is deleted and set to nullptr
	// t3->display();     // This would be dangerous if we didn't set receipt = nullptr
	*/
	system("pause");
	return 0;
}
