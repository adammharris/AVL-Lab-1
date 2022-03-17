#include "Node.h"

Node::Node(const int& data) {
    this->data = data;
    right = 0;
    left = 0;
}
Node::~Node() {}
int Node::getData() const {
    return data;
}
NodeInterface* Node::getLeftChild() const {
    return left;
}
NodeInterface* Node::getRightChild() const {
    return right;
}
int Node::getHeight() {
    return height;
}

Node*& Node::getRight() {
    return right;
}
Node*& Node::getLeft() {
    return left;
}
void Node::setHeight(int height) {
    this->height = height;
}
