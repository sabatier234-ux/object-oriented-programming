#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
class Payment {
private:
	char* ownerName;
	double amount;
	unsigned int paymentId;
	char* currency;

public:
	Payment(const char* name, double amt, unsigned int id, const char* curr) {
		ownerName = new char[strlen(name) + 1];
		strcpy(ownerName, name);

		amount = amt;
		paymentId = id;

		currency = new char[strlen(curr) + 1];
		strcpy(currency, curr);
	}
	~Payment() {
		delete[] ownerName;
		delete[] currency;
		cout << "Payment " << paymentId << " destroyed" << endl;
	}
	void display() const {
		cout << "Payment ID: " << paymentId << endl;
		cout << "Owner: " << ownerName << endl;
		cout << "Amount: " << amount << " " << currency << endl;
	}
	double getAmount() const { return amount; }
	unsigned int getPaymentId() const { return paymentId; }
	const char* getOwnerName() const { return ownerName; }
	const char* getCurrency() const { return currency; }

	void setOwnerName(const char* name) {
		ownerName = new char[strlen(name) + 1];
		strcpy(ownerName, name);
	}
	void setAmount(double amt) { amount = amt; }
	void setPaymentId(unsigned int id) { paymentId = id; }
	void setCurrency(const char* curr) {
		currency = new char[strlen(curr) + 1];
		strcpy(currency, curr);
	}
};

class OnlinePayment : public Payment {
private:
	char* platform;
	char* transactionRef;
	bool isVerified;

public:
	OnlinePayment(const char* name, double amt, unsigned int id, const char* curr,
		const char* plat, const char* trans)
		: Payment(name, amt, id, curr) {

		platform = new char[strlen(plat) + 1];
		strcpy(platform, plat);

		transactionRef = new char[strlen(trans) + 1];
		strcpy(transactionRef, trans);

		isVerified = false;
	}

	~OnlinePayment() {
		delete[] platform;
		delete[] transactionRef;
	}

	void verify() {
		isVerified = true;
		cout << "Payment has been verified successfully!" << endl;
	}

	void display() const {
		Payment::display();  
		cout << "Platform: " << platform << endl;
		cout << "Transaction Ref: " << transactionRef << endl;
		cout << "Verified: " << (isVerified ? "Yes" : "No") << endl;
	}
};

class CardPayment : public OnlinePayment {
private:
	char* maskedCardNumber;
	char* cardType;
	int expiryYear;
	int expiryMonth;

public:
	CardPayment(const char* name, double amt, unsigned int id, const char* curr,
		const char* plat, const char* trans,
		const char* cardNum, const char* cType, int eYear, int eMonth)
		: OnlinePayment(name, amt, id, curr, plat, trans) {

		maskedCardNumber = new char[strlen(cardNum) + 1];
		strcpy(maskedCardNumber, cardNum);

		cardType = new char[strlen(cType) + 1];
		strcpy(cardType, cType);

		expiryYear = eYear;
		expiryMonth = eMonth;
	}


	~CardPayment() {
		delete[] maskedCardNumber;
		delete[] cardType;
	
	}

	bool isExpired(int currentYear, int currentMonth) const {
		if (currentYear > expiryYear) return true;
		if (currentYear == expiryYear && currentMonth > expiryMonth) return true;
		return false;
	}

	void display() const {
		OnlinePayment::display();  
		cout << "Card Type: " << cardType << endl;
		cout << "Masked Card: " << maskedCardNumber << endl;
		cout << "Expiry: " << expiryMonth << "/" << expiryYear << endl;
	}
};

int main() {
	CardPayment* cp = new CardPayment("SABA", 200.50, 891, "PKR",
		"JazzCash", "T987",
		"1234", "VISA", 2000, 9);

	cout << "--CardPayment --" << endl;
	cp->display();

	cout << "--Verifying payment--" << endl;
	cp->verify();

	cout << "--expiry--" << endl;
	if (cp->isExpired(2026, 3)) {
		cout << "Card is EXPIRED" << endl;
	}
	else {
		cout << "Card is NOT expired" << endl;
	}
	Payment* basePtr = cp;  
	basePtr->display();
	// Only Payment::display() is called because display() is not virtual.
	// This is static (early) binding. If we used 'virtual' keyword in base class,
	// it would call the most derived version (CardPayment::display()) - dynamic binding.

	delete cp;
	system("pause");
	return 0;
}
