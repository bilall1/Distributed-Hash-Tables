#pragma once
#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include<ctime>
using namespace std;
class FTnode {
public:
	FTnode* next;
	FTnode* prev;
	int mac_id;
};
class FTtable {
public:
	FTnode* head;
	FTnode* temp;
public:
	FTtable() {
		head = temp = NULL;
	}
	void insert(int m) {
		if (head == NULL) {
			temp = new FTnode;

			temp->mac_id = m;
			temp->next = NULL;
			temp->prev = NULL;
			head = temp;
		}
		else
		{
			temp = new FTnode;
			temp->mac_id = m;

			FTnode* curr = head;
			while (curr->next != NULL) {
				curr = curr->next;
			}
			curr->next = temp;
			temp->next = NULL;
			temp->prev = curr;
		}
	}
	void display() {
		if (head != NULL)
		{
			FTnode* curr = head;
			cout << "\nTable is : \n";
			while (curr->next != NULL) {
				cout << curr->mac_id << " ";
				curr = curr->next;
				cout << endl;
			}
			cout << curr->mac_id << " \n";
		}

	}

};