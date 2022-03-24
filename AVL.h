#pragma once

#include "AVLInterface.h"
#include "Node.h"

using namespace std;
class AVL : public AVLInterface {
protected:
    Node* root;
public:
    bool erase(Node*& local_root,const int& item);
    void replace_parent(Node*& old_root, Node*& local_root);

    AVL();
    ~AVL();
    NodeInterface* getRootNode() const;
    bool add(int data);
    bool insert(const int& data, Node*& local);
    bool remove(int data);
    void clear();

    void rotate(Node*& local);
    void rotateLeft(Node*& local);
    void rotateRight(Node*& local);
    int getHeight(Node* local);
    void calcHeight(Node* local);
};