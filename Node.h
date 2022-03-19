#pragma once
#include "NodeInterface.h"

class Node : public NodeInterface {
private:
    int data;
    int height;
    Node* left;
    Node* right;
    Node* parent;

public:
    Node(int data);

    void setData(int i);
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
    void setParent(Node* parent);
    Node* getParent() const;
    Node*& recurseParent();
};