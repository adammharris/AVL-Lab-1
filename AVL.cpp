#include "AVL.h"
#include <iostream>
AVL::AVL() {
    root = 0;
}
AVL::~AVL() {

}
NodeInterface* AVL::getRootNode() const {
    return root;
}
bool AVL::add(int data) {
    if (root == NULL) {
        root = new Node(data);
        return true;
    }
    return false;
}
bool AVL::remove(int data) {
    Node* toRemove = find(data);
    if (toRemove == NULL) {
        return false;
    }
    return true;
}
void AVL::clear() {
    if (root == NULL)
        return;
    remove(root->getData());
}

Node* AVL::find(const int& data) const {
    if (root == NULL)
        return NULL;
    Node* foundNode = root;
    step_find(foundNode, data);
    return foundNode;
}
void AVL::step_find(Node*& local_root, const int& data) const {
    if (data > local_root->getData()) {
        local_root = local_root->getRight();
        step_find(local_root, data);
    } else if (data < local_root->getData()) {
        local_root = local_root->getLeft();
        step_find(local_root, data);
    }
}
