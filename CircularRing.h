#pragma once
#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include<ctime>
#include"AvlTree.h"
#include"FTtable.h"
#include"Machine.h"
using namespace std;

struct Ringnode {
	Ringnode* next;
	Ringnode* prev;
	Machine* machine;
};
class CircularRing {
	Ringnode* head;
	Ringnode* temp;
	int bit;
	int identifierspace;
	int no_of_machines;
	Machine** gomachine;
	Machine* firstactivenode;
	Machine* lastactivenode;
public:
	CircularRing()
	{
		head = temp = NULL;
		identifierspace = no_of_machines = 0;
		bit = 0;
		gomachine = NULL;
		firstactivenode = NULL;
		lastactivenode = NULL;
	}
	CircularRing(int power) {
		cout << "Power: " << power;
		head = temp = NULL;
		no_of_machines = 0;
		bit = power;
		identifierspace = pow(2, power);

		int size = identifierspace + 1;
		gomachine = new Machine * [size];		//To store adresses of machines for quick search.
		int count = 0;
		for (int i = 0; i < identifierspace; i++) {		// Creating nodes of the ring.
			count++;
			if (head == NULL) {
				temp = new Ringnode;
				temp->machine = new Machine(count);
				gomachine[count] = temp->machine;
				head = temp;
				temp->next = head;
				temp->prev = head;
			}
			else {
				temp = new Ringnode;
				temp->machine = new Machine(count);
				gomachine[count] = temp->machine;
				Ringnode* curr = head;
				while (curr->next != head) {
					curr = curr->next;
				}
				curr->next = temp;
				temp->next = head;
				temp->prev = curr;
			}
		}

	}
	void randomlyactivemachines(int act) {			//It randomly activates required number of machines.
		srand(time(NULL));
		for (int i = 0; i < act; i++)
		{
			int y = (rand() % (identifierspace)) + 1;
			while (gomachine[y]->checkstatus() == 1)
			{
				y = (rand() % (identifierspace)) + 1;
			}
			while (y < 1 && y > identifierspace) {
				while (gomachine[y]->checkstatus() == 1)
				{
					y = (rand() % (identifierspace)) + 1;
				}
			}
			gomachine[y]->setstatus(1);

		}
		setnodes();
		createLookups();			//Maintaining the Ft tables.
		printLookUpTables();
	}
	void setnodes() {
		for (int i = 1; i < identifierspace + 1; i++)
		{
			if (gomachine[i]->checkstatus() == 1)
				lastactivenode = gomachine[i];
		}
		for (int i = 1; i < identifierspace + 1; i++)
		{
			if (gomachine[i]->checkstatus() == 1)
			{
				firstactivenode = gomachine[i];
				break;
			}
		}
	}
	int getbit() {
		return bit;
	}
	void createLookups()					//Maintaining FT Tables
	{
		for (int i = 1; i < identifierspace + 1; i++)
		{
			gomachine[i]->table = NULL;
			gomachine[i]->table = new FTtable();
			for (int j = 1; j <= bit; j++)
			{
				if (gomachine[i]->checkstatus())
				{
					int indexofft = gomachine[i]->getid() + pow(2, j - 1);
					if (indexofft > identifierspace)
					{
						indexofft = indexofft % identifierspace;
					}
					int k = indexofft;
					bool flag = 0;
					for (; k < identifierspace + 1; k++)
					{
						if (gomachine[k]->checkstatus()) {
							flag = 1;
							break;
						}
					}

					if (flag)
						gomachine[i]->table->insert(gomachine[k]->getid());
					else
					{
						Machine* ptr = NULL;
						int l = 1;
						for (; l < identifierspace + 1; l++)
						{
							if (gomachine[l]->checkstatus())
								break;
						}
						ptr = gomachine[l];
						gomachine[i]->table->insert(ptr->getid());
					}

				}
			}
		}
	}

	void insertdata(int machineid, string key, string data) {		//Insertion

		while (machineid <= 0 || machineid > identifierspace || gomachine[machineid]->checkstatus() == 0) {
			cout << "Please enter active machine id :";
			cin >> machineid;
		}
		int ascii = 0;
		for (int i = 0; i < key.length(); i++) {
			ascii += key[i];
		}
		int hashedkey = (ascii % identifierspace) + 1;	//To keep value in size;

		Machine* m1 = gomachine[machineid];				//If hash key maches id to the same machine.
		if (hashedkey == machineid)
		{
			cout << "Machine is " << m1->getid() << endl;
			m1->setvalues(key, data);
		}
		else
		{
			bool checkbig = 0;
			Machine* use = m1;

			while (use->getid() > hashedkey && use->getid() != lastactivenode->getid())
			{
				int help = use->table->head->mac_id;
				if (help <= hashedkey)
					break;
				use = gomachine[help];
			}
			if (hashedkey > lastactivenode->getid())
			{
				use = firstactivenode;
				checkbig = 1;
			}
			else
			{
				while (1)
				{
					FTnode* tem = use->table->head;
					FTnode* prev = NULL;
					bool test = 0;
					while (tem->next != NULL && tem->mac_id < hashedkey)
					{
						test = 1;
						if (tem->mac_id < hashedkey)
						{
							break;
						}

						prev = tem;
						tem = tem->next;
					}
					if (tem)
					{
						prev = tem;
					}
					if (test == 0 || prev == NULL)
						break;

					use = gomachine[prev->mac_id];
					if (use->getid() == hashedkey)
						break;
				}
			}
			if (checkbig == 0)
			{
				int found = use->table->head->mac_id;
				use = gomachine[found];
			}
			cout << "Machine is " << use->getid() << endl;
			use->setvalues(key, data);
		}
	}
	void search(int machineid, string key)
	{
		while (machineid <= 0 || machineid > identifierspace || gomachine[machineid]->checkstatus() == 0) {
			cout << "Please enter active machine id :";
			cin >> machineid;
		}
		int ascii = 0;
		for (int i = 0; i < key.length(); i++) {
			ascii += key[i];
		}
		int hashedkey = (ascii % identifierspace) + 1;	//To keep value in size;

		Machine* m1 = gomachine[machineid];
		if (hashedkey == machineid)
		{
			cout << "Machine is " << m1->getid() << endl;
			cout << "Data is: " << m1->retrivedata(key) << endl;
		}
		else
		{
			bool checkbig = 0;
			Machine* use = m1;

			while (use->getid() > hashedkey && use->getid() != lastactivenode->getid())
			{
				int help = use->table->head->mac_id;
				if (help <= hashedkey)
					break;
				use = gomachine[help];
			}
			if (hashedkey > lastactivenode->getid())
			{
				use = firstactivenode;
				checkbig = 1;
			}
			else
			{
				while (1)
				{
					FTnode* tem = use->table->head;
					FTnode* prev = NULL;
					bool test = 0;
					while (tem->next != NULL && tem->mac_id < hashedkey)
					{
						test = 1;
						if (tem->mac_id < hashedkey)
						{
							break;
						}

						prev = tem;
						tem = tem->next;
					}
					if (tem)
					{
						prev = tem;
					}
					if (test == 0 || prev == NULL)
						break;

					use = gomachine[prev->mac_id];
					if (use->getid() == hashedkey)
						break;
				}
			}
			if (checkbig == 0)
			{
				int found = use->table->head->mac_id;
				use = gomachine[found];
			}
			cout << "Data is: " << use->retrivedata(key) << endl;


		}
	}
	void deletedata(int machineid, string key) {

		//Input validation.
		while (machineid <= 0 || machineid > identifierspace || gomachine[machineid]->checkstatus() == 0) {
			cout << "Please enter active machine id :";
			cin >> machineid;
		}
		int ascii = 0;
		for (int i = 0; i < key.length(); i++) {
			ascii += key[i];
		}
		int hashedkey = (ascii % identifierspace) + 1;	//To keep value in size;

		Machine* m1 = gomachine[machineid];
		if (hashedkey == machineid)
		{
			cout << "Machine is " << m1->getid() << endl;
			m1->deletedataintree(key);
		}
		else
		{
			bool checkbig = 0;
			Machine* use = m1;
			while (use->getid() > hashedkey && use->getid() != lastactivenode->getid())
			{
				int help = use->table->head->mac_id;
				if (help <= hashedkey)
					break;
				use = gomachine[help];
			}
			if (hashedkey > lastactivenode->getid())
			{
				use = firstactivenode;
				checkbig = 1;
			}
			else
			{
				while (1)
				{
					FTnode* tem = use->table->head;
					FTnode* prev = NULL;
					bool test = 0;
					while (tem->next != NULL && tem->mac_id < hashedkey)
					{
						test = 1;
						if (tem->mac_id < hashedkey)
						{
							break;
						}

						prev = tem;
						tem = tem->next;
					}
					if (tem)
					{
						prev = tem;
					}
					if (test == 0 || prev == NULL)
						break;

					use = gomachine[prev->mac_id];
					if (use->getid() == hashedkey)
						break;
				}
			}
			if (checkbig == 0)
			{
				int found = use->table->head->mac_id;
				use = gomachine[found];
			}
			use->deletedataintree(key);
		}
	}

	void activateNewMachine()
	{
		int y = (rand() % (identifierspace)) + 1;
		while (gomachine[y]->checkstatus() == 1)
		{
			y = (rand() % (identifierspace)) + 1;
		}
		while (y < 1 && y > identifierspace) {
			while (gomachine[y]->checkstatus() == 1)
			{
				y = (rand() % (identifierspace)) + 1;
			}
		}
		gomachine[y]->setstatus(1);
		for (int i = 1; i < identifierspace + 1; i++)
		{
			gomachine[i]->table = NULL;
		}
		createLookups();
		setnodes();
		int headInd = gomachine[y]->table->head->mac_id;
		Machine* MacNext = gomachine[headInd];
		MacNext->createTempFile();
		string openingname = MacNext->nameofFile;
		ifstream Iobj(openingname, ios::app);
		if (Iobj.is_open())
		{
			string lining = "";
			while (getline(Iobj, lining)) {
				string st1 = "";
				string numb = "";
				int counter = 0;
				while (lining[counter] != '.')
				{
					st1 += lining[counter];
					counter++;
				}
				counter++;
				while (lining[counter] != '-')
				{
					numb += lining[counter];
					counter++;
				}
				int lineNum = stoi(numb);
				int ascii = 0;
				for (int i = 0; i < st1.length(); i++) {
					ascii += st1[i];
				}
				int index = (ascii % identifierspace) + 1;
				if (index <= gomachine[y]->getid() || index > MacNext->getid())
				{
					string store = MacNext->retrivedata(st1);
					cout << "Before deletion!!!" << endl;
					deletedatabefore(MacNext, st1);
					cout << "Afterrrr deletion!!!" << endl;
					gomachine[y]->setvalues(st1, store);
				}

			}
			Iobj.close();
			ofstream temp;
			temp.open(openingname);
			temp.close();
		}
		else
		{
			cout << "File not opened\n";
		}
		cout << "Routing Table after inserting a new machine in the ring";
		printLookUpTables();

	}
	void printLookUpTables() {
		cout << endl;
		cout << "These machines are activated randomly:\n";
		for (int i = 0; i < identifierspace; i++) {

			if (gomachine[i + 1]->checkstatus() == 1) {
				cout << gomachine[i + 1]->getid() << ":";
				gomachine[i + 1]->table->display();
				cout << endl;

			}
		}
	}

	void deletedatabefore(Machine* mac, string key) {
		mac->deletedataintree(key);
	}
	void deleteamachine(int id) {
		while (id <= 0 || id > identifierspace || gomachine[id]->checkstatus() == 0) {
			cout << "Please enter active machine id :";
			cin >> id;
		}


		cout << "Requested machine to delete was: " << id;
		bool notfound = false;
		int i;
		for (i = id + 1; i <= identifierspace; i++) {
			if (gomachine[i]->checkstatus()) {
				notfound = true;
				break;
			}
		}
		if (notfound == 0) {
			for (i = 1; i <= identifierspace; i++) {
				if (gomachine[i]->checkstatus()) {
					break;
				}
			}
		}
		cout << "Machine id to which data is transferred: " << gomachine[i]->getid() << endl;
		gomachine[id]->Dodeletingproces(gomachine[i]);
		gomachine[id]->deletethatmachine();
		createLookups();

		cout << "Routing Table after deletion of requested machine: ";
		printLookUpTables();
	}
	void printavl(int machine_id) {

		while (machine_id <= 0 || machine_id > identifierspace || gomachine[machine_id]->checkstatus() == 0) {
			cout << "Please enter active machine id :";
			cin >> machine_id;
		}

		cout << "\n-------------------------------------------\n";
		gomachine[machine_id]->printavltree();
		cout << "\n-------------------------------------------\n";
	}
	void printFt(int machine_id) {

		while (machine_id <= 0 || machine_id > identifierspace || gomachine[machine_id]->checkstatus() == 0) {
			cout << "Please enter active machine id :";
			cin >> machine_id;
		}

		gomachine[machine_id]->table->display();
	}

};