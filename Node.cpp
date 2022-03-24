#include "NodeInterface.h"
#include "Node.h"

Node::Node(int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    height = 0;
}

void Node::setData(int newData) {
    data = newData;
}
void Node::setLeft(Node* newLeft) {
    left = newLeft;
    if (left != nullptr) {
        left->setParent(this);
    }
}
void Node::setRight(Node* newRight) {
    right = newRight;
    if (right != nullptr) {
        right->setParent(this);
    }
}
Node* Node::getLeft() const {
    return left;
}
Node* Node::getRight() const {
    return right;
}
Node*& Node::recurseRight() {
    return right;
}
Node*& Node::recurseLeft() {
    return left;
}

int Node::getData() const {
    return data;
}
NodeInterface* Node::getLeftChild() const {
    return left;
}
NodeInterface* Node::getRightChild() const {
    return right;
}

void Node::setHeight(int newHeight) {
    height = newHeight;
}
int Node::getHeight() {
    return height;
}
void Node::setParent(Node* newParent) {
    parent = newParent;
}
Node* Node::getParent() const {
    return parent;
}
Node*& Node::recurseParent() {
    return parent;
}