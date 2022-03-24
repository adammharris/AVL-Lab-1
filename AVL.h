#pragma once

#include "AVLInterface.h"
#include "Node.h"

using namespace std;
class AVL : public AVLInterface {
protected:
    Node* root;
    Node* local_node; // used for `find`
    int local_height;
public:
    /*
    * `find` helps find data via recursion
  * @return pointer of node next to or equal to data
  * @return nullptr if BST is empty
    */
    //Node* find(const int& data);
    bool removeFinalNode();
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