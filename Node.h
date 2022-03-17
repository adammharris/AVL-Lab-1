#pragma once
#include <iostream>
#include "NodeInterface.h"

class Node : public NodeInterface {
private:
    int data;
    int height;
    Node* left;
    Node* right;
    NodeInterface* l;
    NodeInterface* r;

public:
    Node(int data);

    void setData(int data);
    void setLeft(Node* newLeft);
    void setRight(Node* newRight);
    Node* getLeft() const;
    Node* getRight() const;
    Node*& recurseRight();
    Node*& recurseLeft();

    int getData() const;
    NodeInterface* getLeftChild() const;
    NodeInterface* getRightChild() const;

    void setHeight(int height);
    int getHeight();
};