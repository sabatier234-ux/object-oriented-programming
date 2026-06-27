#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Merchant {
private:
	char* merchantName;
	char* merchantId;
	double totalRevenue;
	int transactionCount;

public:
	Merchant(const char* name, const char* id) {
		merchantName = new char[strlen(name) + 1];
		strcpy(merchantName, name);

		merchantId = new char[strlen(id) + 1];
		strcpy(merchantId, id);

		totalRevenue = 0.0;
		transactionCount = 0;
	}

	~Merchant() {
		delete[] merchantName;
		delete[] merchantId;
		cout << "Merchant  destroyed" << endl;
	}

	void receivePayment(double amount) {
		totalRevenue += amount;
		transactionCount++;
	}

	void display() const {
		cout << "Merchant ID   : " << merchantId << endl;
		cout << "Merchant Name : " << merchantName << endl;
		cout << "Total Revenue : " << totalRevenue << " PKR" << endl;
		cout << "Transactions  : " << transactionCount << endl;
	}

	const char* getMerchantId() const {
		return merchantId;
	}
};
class PaymentGateway {
private:
	char* gatewayName;
	Merchant** merchants;    
	int merchantCount;
	int capacity;

public:
	PaymentGateway(const char* name) {
		gatewayName = new char[strlen(name) + 1];
		strcpy(gatewayName, name);

		capacity = 5;
		merchantCount = 0;
		merchants = new Merchant*[capacity];   
	}

	~PaymentGateway() {
		delete[] gatewayName;
		delete[] merchants;                   
		cout << "PaymentGateway destroyed" << endl;
		
	}

	void registerMerchant(Merchant* m) {
		if (merchantCount == capacity) {
			capacity *= 2;
			Merchant** newArray = new Merchant*[capacity];

			for (int i = 0; i < merchantCount; i++) {
				newArray[i] = merchants[i];
			}
			delete[] merchants;
			merchants = newArray;
			cout << "Gateway capacity increased to " << capacity << endl;
		}
		merchants[merchantCount] = m;
		merchantCount++;
	}

	void routePayment(const char* merchantId, double amount) {
		for (int i = 0; i < merchantCount; i++) {
			if (strcmp(merchants[i]->getMerchantId(), merchantId) == 0) {
				merchants[i]->receivePayment(amount);
				return;
			}
		}
		cout << "Merchant not found" << endl;
	}

	void displayAll() const {
		cout << "PAYMENT GATEWAY: " << gatewayName  << endl;
		cout << "Total Merchants: " << merchantCount << endl;

		for (int i = 0; i < merchantCount; i++) {
			merchants[i]->display();
		}
	}
};

int main() {

	Merchant* a = new Merchant("saba", "hj8");
	Merchant* b = new Merchant("mehak", "M2");
	Merchant* c = new Merchant("khadija", "M3");

	PaymentGateway* gateway = new PaymentGateway("FAST");

	cout << "--merchant one--" << endl;
	gateway->registerMerchant(a);
	cout << "--merchant two--" << endl;
	gateway->registerMerchant(b);
	cout << "--merchant three--" << endl;
	gateway->registerMerchant(c);
	cout << "routing :" << endl;
	gateway->routePayment("12", 89.0);
	gateway->routePayment("32", 12.0);
	gateway->routePayment("43", 34.0);
	gateway->routePayment("91", 56.0);

	cout << "all merchants:" << endl;
	gateway->displayAll();

	delete gateway;    

	cout << "--aggregation--" << endl;
	a->display();
	b->display();
	c->display();

	delete a;
	delete b;
	delete c;
	system("pause");
	return 0;
}
// (a) Destructor Responsibilities:
	//     - PaymentGateway destructor: frees only gatewayName and the merchants[] pointer array
	//     - Merchant destructor: frees merchantName and merchantId

	// (b) Why merchants survive after deleting gateway?
	//     This is AGGREGATION. Gateway only holds POINTERS to merchants.
	//     Merchants are created and owned outside the gateway (in main).

	// (c) How it would be different in Composition?
	//     In Composition, gateway would create merchants itself (not take pointers).
	//     Then its destructor would delete the Merchant objects automatically.
