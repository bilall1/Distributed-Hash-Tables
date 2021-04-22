#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include<ctime>
#include"CircularRing.h"
int main() {
	int power;
	cout << "Enter the identifier space in power of 2: ";
	cin >> power;

	int active;
	cout << "Enter the number of machines to activate : ";
	cin >> active;

	//The identifier space will be 2 power(4).
	CircularRing ring(power);
	ring.randomlyactivemachines(active);

	int choice = -1;
	while (choice != 0) {
		if (choice == -1) {
			cout << "-------------------------------------------------------\n";
			cout << "Press 1 to insert data in the ring\n";
			cout << "Press 2 to search data from any machine\n";
			cout << "Press 3 to delete data from any machines\n";
			cout << "Press 4 to print routing table of any active machine\n";
			cout << "Press 5 to print Avl tree of any active machine\n";
			cout << "Press 6 to activate a new machine in the ring\n";
			cout << "Press 7 to delete a active machine from the ring\n";
			cout << "Press 8 to exit ring\n";
			cout << "-------------------------------------------------------\n";
			cin >> choice;
		}

		if (choice == 1) {
			string key = "", data = "";
			int id = 0;
			cout << "Enter the machine id from which you want to insert data: ";
			cin >> id;
			cout << "Enter the key: ";
			cin >> key;
			cout << "Enter the data: ";
			cin >> data;
			ring.insertdata(id, key, data);
		}
		else if (choice == 2) {
			int id = 0;
			string key = "";
			cout << "Enter the machine id from which you want to search data: ";
			cin >> id;
			cout << "Enter the key you want to search: ";
			cin >> key;
			ring.search(id, key);
		}
		else if (choice == 3) {
			int id = 0;
			string key = "";
			cout << "Enter the machine id from which you want to delete data: ";
			cin >> id;
			cout << "Enter the key you want to delete: ";
			cin >> key;
			ring.deletedata(id, key);
		}
		else if (choice == 4) {
			int id = 0;
			cout << "Enter the machine id to print it's routing table: ";
			cin >> id;
			ring.printFt(id);
		}
		else if (choice == 5) {
			int id = 0;
			cout << "Enter the machine id to print it's Avl Tree: ";
			cin >> id;
			ring.printavl(id);
		}
		else if (choice == 6) {
			ring.activateNewMachine();
		}
		else if (choice == 7) {
			int id = 0;
			cout << "Enter the machine id to delete the machine: ";
			cin >> id;
			ring.deleteamachine(id);
		}
		cout << "-------------------------------------------------------\n";
		cout << "Press 1 to insert data in the ring\n";
		cout << "Press 2 to search data from any machine\n";
		cout << "Press 3 to delete data from any machines\n";
		cout << "Press 4 to print routing table of any active machine\n";
		cout << "Press 5 to print Avl tree of any active machine\n";
		cout << "Press 6 to activate a new machine in the ring\n";
		cout << "Press 7 to delete a active machine from the ring\n";
		cout << "Press 0 to exit ring\n";
		cout << "-------------------------------------------------------\n";
		cin >> choice;
	}

}