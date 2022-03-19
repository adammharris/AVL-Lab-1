#pragma once

#include "AVLInterface.h"
#include "Node.h"

class AVL : public AVLInterface {
protected:
    Node* root;
public:
    void erase(Node*& local,const int& data, bool& complete);
    void replace_parent(Node*& old_root, Node*& local_root);

    AVL();
    ~AVL();
    NodeInterface* getRootNode() const;
    bool add(int data);
    bool remove(int data);
    void clear();

    void rotate(Node*& local);
    /*
     * Sets Node*& local to leaf node where child will be added
     * Also sets heights of each node to help with balancing
     * Used in `add` function
     * @return bool to indicate whether node is already present
     */
    void insert(Node*& local, const int& data, bool& complete);
    void adjustHeight(Node*& local);
};