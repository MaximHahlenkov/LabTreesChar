#pragma once
#include <string>
struct Node 
{
	char data;
	Node* left;
	Node* right;
		
	Node() : data(' '), left(nullptr), right(nullptr) {}
	Node(char _c) : data(_c), left(nullptr), right(nullptr) {}
	~Node() = default;
};

class Tree
{
	Node* root;

	void Peek(Node* node, std::string& st);

public:
	Tree() : root(new Node) {};
	Tree(char _c) : root(new Node(_c)) {};
	
	void destroyRoot(Node*& node);
	~Tree() { destroyRoot(root); };

	Node* getRoot() { return root; };

	void Insert(char c);
	void Delete(char c);

	Node* deleteNode(Node* node, char c);
	Node* findMin(Node* node);

	void InsertString(std::string st);
	std::string PostOrderString();

};

