#pragma once
#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include<ctime>
#include"Avltree.h"
using namespace std;

class Machine {
	int machine_id;
	bool status;
	ofstream file;
	ifstream file1;
	Avltree tree;
	int linenumber;
public:
	FTtable* table;
	string nameofFile;
	Machine() {
		machine_id = 0;
		status = 0;
		linenumber = 0;
		table = NULL;
	}
	Machine(int id) {
		machine_id = id;
		status = 0;
		linenumber = 0;
		table = NULL;


	}
	void setstatustozero(bool x) {
		status = x;
		
		string b = ".txt";
		string a = to_string(machine_id);
		string c = a + b;
		ofstream obj;
		obj.open(c);
	}
	bool checkstatus() {
		return status;
	}
	void setstatus(bool what) {
		status = what;
		string b = ".txt";
		string a = to_string(machine_id);
		string c = a + b;
		file.open(c, ios::app);
		file1.open(c, ios::app);
	}
	void createTempFile()
	{
		string macfile = "temp";
		string z = to_string(machine_id);
		macfile += z;
		macfile += ".txt";
		tree.readAndWrite(macfile);
		nameofFile = macfile;
	}
	int getid() {
		return machine_id;
	}
	void setvalues(string k, string d) {
		insertdataintree(k, d);
	}
	void insertdataintree(string key, string data) {	//This function also writes file.
		if (linenumber < 101) {
			linenumber++;
			tree.node = tree.insert(tree.node, key, linenumber);

			file << data << endl;	//Data written on first line and then so on.
		}
	}
	void deletedataintree(string key) {
		//Read data
		int linenum = 0;
		string line;

		file1.clear();
		file1.seekg(0);
		if (file1.is_open()) {
			while (getline(file1, line)) {
				linenum++;
			}
		}
		string* array;
		array = new string[linenum];
		string data = retrivedata(key);
		file1.clear();
		file1.seekg(0);
		int counter = 0;
		if (file1.is_open()) {
			while (getline(file1, line)) {
				if (data != line) {
					array[counter] = line;
				}
				else {
					array[counter] = "-";
				}
				counter++;
			}
		}
		file1.clear();
		file1.seekg(0);
		string b = ".txt";
		string a = to_string(machine_id);
		string c = a + b;


		ofstream temp;
		temp.open(c);
		ofstream temp1;
		temp1.open(c, ios::app);
		for (int i = 0; i < linenum; i++) {
			temp1 << array[i] << "\n";
		}
		tree.node = tree.deleteNode(tree.node, key);
		//cout << "Lines in file is: " << linenum<<endl;
	}
	void printavltree() {
		tree.preOrderPrint(tree.node);	//Displays the avl tree.
	}
	string retrivedata(string key) {
		int line = tree.preOrderfindline(tree.node, key);
		cout << "Data was written on line : " << line << endl;
		string word = "";
		int count = 1;
		file1.clear();
		file1.seekg(0);


		if (file1.is_open()) {
			while (getline(file1, word)) {
				if (line == count) {
					break;
				}
				count++;
			}
			return word;
		}
		file1.close();
	}
	void Dodeletingproces(Machine *mac) {
		string *keyarray=new string [linenumber];
		int *linearray = new int[linenumber];
		tree.deletion(tree.node, keyarray, linearray);
		int loopcount = linenumber;
		for (int j = 0; j < loopcount; j++) {
			mac->setvalues(keyarray[j], retrivedatabylinegiven(linearray[j]));
		}
	}
	void deletethatmachine() {
		setstatustozero(0);
	}
	string retrivedatabylinegiven(int  line) {
		string word = "";
		int count = 1;
		file1.clear();
		file1.seekg(0);


		if (file1.is_open()) {
			while (getline(file1, word)) {
				if (line == count) {
					break;
				}
				count++;
			}
			return word;
		}
		file1.close();
	}
};