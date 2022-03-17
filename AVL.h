#pragma once
#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface {
private:
    Node* root;
public:
    AVL();
    ~AVL();

    NodeInterface * getRootNode() const;
    bool add(int data);
    bool remove(int data);
    void clear();

    Node* find(const int& data) const;
    void step_find(Node*& local_root, const int& data) const;
};
