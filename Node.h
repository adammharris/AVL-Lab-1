#pragma once
#include "NodeInterface.h"

class Node : public NodeInterface {
private:
    Node* right;
    Node* left;
    int height;
    int data;
public:
    Node(const int& data);
    ~Node();

    int getData() const;
    NodeInterface * getLeftChild() const;
    NodeInterface * getRightChild() const;
    int getHeight();

    Node*& getRight();
    Node*& getLeft();
    void setHeight(int height);
};
