#include "Tree.h"

void Tree::destroyRoot(Node*& node)
{
    if (!node) return;

    destroyRoot(node->left);
    destroyRoot(node->right);

    delete node;
    node = nullptr;
}

void Tree::Insert(char c) {
    if (!root) {
        root = new Node(c); 
        return;
    }

    if (root->data == ' ') 
    {
        root = new Node(c);
        return;
    }

    Node* temp = root;
    Node* parent = nullptr;

    while (temp) {
        parent = temp;
        if (c <= temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    
    if (c <= parent->data)
        parent->left = new Node(c);
    else
        parent->right = new Node(c);
}

void Tree::Delete(char c) {
    root = deleteNode(root, c);
}

Node* Tree::findMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

Node* Tree::deleteNode(Node* node, char c) {
    if (!node) return nullptr;

    // Поиск узла
    if (c < node->data) {
        node->left = deleteNode(node->left, c);
    }
    else if (c > node->data) {
        node->right = deleteNode(node->right, c);
    }
    else {
        // Узел найден
        // Случай 1: Узел — лист
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }

        // Случай 2: Один дочерний узел
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Случай 3: Два дочерних узла
        Node* successor = findMin(node->right); // Поиск минимального в правом поддереве
        node->data = successor->data; // Замена значений
        node->right = deleteNode(node->right, successor->data); // Удаляем преемника
    }
    return node;
}

void Tree::InsertString(std::string st) 
{
    for (auto it : st) 
    { 
        Insert(it); 
    };
}

void Tree::Peek(Node* node, std::string& st)
{
    if (node == nullptr) return;

    Peek(node->left, st);
    Peek(node->right, st);
    st += node->data;
}

std::string Tree::PostOrderString() 
{
    if (!root) return "";
    
    std::string ans;
    Peek(root, ans);
    
    return ans;
}
