#pragma once
#include<iostream>
#include<fstream>
#include <sstream> 
#include<string>
#include<ctime>
using namespace std;
class Node {
public:
	string key;
	Node* left;
	Node* right;
	int height;
	int linenumber;
};
class Avltree {
public:
	Node* node;
	string filenaming;
	ofstream obj;
	Avltree() {
		node = NULL;
	}
	int height(Node* N)
	{
		if (N == NULL)
			return 0;
		return N->height;
	}
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	void readAndWrite(string name)
	{
		filenaming = name;
		obj.open(filenaming, ios::app);
		if (obj.is_open())
		{
			InOrderWrite(node);
			obj.close();
		}
		else
		{
			cout << "File not opened\n";
		}
	}
	void InOrderWrite(Node* root)
	{
		if (root != NULL)
		{
			InOrderWrite(root->left);
			string st = root->key;
			int num = root->linenumber;
			obj << st << '.' << num << '-' << endl;
			InOrderWrite(root->right);
		}
	}
	void InOrderPrint(Node* root)
	{
		if (root != NULL)
		{
			InOrderPrint(root->left);
			cout << root->key << " ";
			InOrderPrint(root->right);
		}
	}
	Node* newNode(string key, int line)
	{
		Node* node = new Node();
		node->key = key;
		node->left = NULL;
		node->right = NULL;
		node->height = 1;
		node->linenumber = line;
		return(node);
	}
	Node* rightRotate(Node* y)
	{
		Node* x = y->left;
		Node* T2 = x->right;

		x->right = y;
		y->left = T2;
 
		y->height = max(height(y->left),
			height(y->right)) + 1;
		x->height = max(height(x->left),
			height(x->right)) + 1;

		return x;
	}
	Node* leftRotate(Node* x)
	{
		Node* y = x->right;
		Node* T2 = y->left;

 
		y->left = x;
		x->right = T2;
 
		x->height = max(height(x->left),
			height(x->right)) + 1;
		y->height = max(height(y->left),
			height(y->right)) + 1;
 
		return y;
	}
	int getBalance(Node* N)
	{
		if (N == NULL)
			return 0;
		return height(N->left) - height(N->right);
	}
	Node* insert(Node* node, string key, int ln)
	{
		if (node == NULL)
			return(newNode(key, ln));

		if (key < node->key)
			node->left = insert(node->left, key, ln);
		else if (key > node->key)
			node->right = insert(node->right, key, ln);
		else 
			return node;


		node->height = 1 + max(height(node->left),
			height(node->right));

		int balance = getBalance(node);
  
		if (balance > 1 && key < node->left->key)
			return rightRotate(node);

		if (balance < -1 && key > node->right->key)
			return leftRotate(node);
  
		if (balance > 1 && key > node->left->key)
		{
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		if (balance < -1 && key < node->right->key)
		{
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}
	Node* minValueNode(Node* node)
	{
		Node* current = node;

		while (current->left != NULL)
			current = current->left;

		return current;
	}
	Node* deleteNode(Node* root, string key)
	{

		if (root == NULL)
			return root;
		if (key < root->key)
			root->left = deleteNode(root->left, key);

			else if (key > root->key)
			root->right = deleteNode(root->right, key);
		else
		{
		  
			if ((root->left == NULL) ||
				(root->right == NULL))
			{
				Node* temp = root->left ?
					root->left :
					root->right;
 
				if (temp == NULL)
				{
					temp = root;
					root = NULL;
				}
				else 
					*root = *temp;  
				free(temp);
			}
			else
			{
		
				Node* temp = minValueNode(root->right);
 
				root->key = temp->key; 
				root->right = deleteNode(root->right,
					temp->key);
			}
		}

		if (root == NULL)
			return root;

		root->height = 1 + max(height(root->left),
			height(root->right));
  
		int balance = getBalance(root);
		if (balance > 1 &&
			getBalance(root->left) >= 0)
			return rightRotate(root);

		if (balance > 1 &&
			getBalance(root->left) < 0)
		{
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
  
		if (balance < -1 &&
			getBalance(root->right) <= 0)
			return leftRotate(root);
  
		if (balance < -1 &&
			getBalance(root->right) > 0)
		{
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}
	void preOrderPrint(Node* root)
	{
		if (root != NULL)
		{
			preOrderPrint(root->left);
			cout << root->key << " "<<"at "<<root->linenumber<<endl;
			preOrderPrint(root->right);
		}
	}
	int preOrderfindline(Node* root, string thatkey) {

		if (root->key == thatkey) {
			cout << "Key is :" << root->key << endl;
			return root->linenumber;
		}
		if (root != NULL) {
			if (thatkey < root->key)
				return preOrderfindline(root->left, thatkey);
			else if (thatkey > root->key)
				return preOrderfindline(root->right, thatkey);
		}


	}
	void deletion(Node *root,string *key,int *lines) {
		int i = 0;
		Inordereaddata(root,key,lines,i);
	}
	void Inordereaddata(Node* root, string* key, int* lines,int &i)
	{
		if (root != NULL)
		{
			Inordereaddata(root->left,key,lines,i);
			string st = root->key;
			int num = root->linenumber;
			key[i] = st;
			lines[i] = num;
			i++;
			Inordereaddata(root->right, key, lines, i);
		}
	}
};