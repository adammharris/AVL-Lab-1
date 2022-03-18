#include "AVL.h"
#include "Node.h"
#include <iostream>

Node* AVL::find(const int& data) {
    Node* nextNode;
    if (data > local_node->getData()) {
        nextNode = local_node->getRight();
    } else if (data < local_node->getData()) {
        nextNode = local_node->getLeft();
    } else {
        nextNode = nullptr;
    }
    if (nextNode == nullptr) {
        Node* toReturn = local_node;
        local_node = root; // reset local_node
        return toReturn;
    }
    local_node = nextNode;
    local_height++;
    return find(data);
}

AVL::AVL() {
    root = nullptr;
    local_node = nullptr;
}
AVL::~AVL() {
    clear();
}
NodeInterface* AVL::getRootNode() const {
    return root;
}
bool AVL::add(int data) {
    if (root == nullptr) {
        root = new Node(data);
        local_node = root;
        return true;
    }
    Node* closestNode = find(data);
    if (closestNode == nullptr || closestNode->getData() == data) {
        return false;
    }
    Node* newNode = new Node(data);
    if (data > closestNode->getData()) {
        closestNode->setRight(newNode);
    } else {
        closestNode->setLeft(newNode);
    }
    return true;
}
bool AVL::remove(int data) {
    return erase(root, data);
}
bool AVL::removeFinalNode() {
    if (root == nullptr)
        return false;
    delete root;
    root = nullptr;
    local_node = nullptr;
    return true;
}

void AVL::clear() {
    if (root == nullptr)
        return;
    remove(root->getData());
    clear();
}

bool AVL::erase(Node*& local_root,const int& item) {
    if (root->getData() == item) {
        // Three cases:
        // root has no children
        // root has one child
        // root has both children
        if (root->getLeft() == nullptr && root->getRight() == nullptr) {
            return removeFinalNode(); // no children
        }
        if ((root->getLeft() == nullptr) != (root->getRight() == nullptr)) {
            // one child (should make child root)
            Node* onlyChild = (root->getLeft()!=nullptr) ? root->getLeft() : root->getRight();
            delete root;
            root = onlyChild;
            return true;
        }
        if (!(root->getLeft() == nullptr) && !(root->getRight() == nullptr)) {
            // both children (should make closest node root)
            replace_parent(root, root->recurseLeft());
            return true;
        }
    }
    if (local_root == nullptr) {
        return false;
    } else {
        if (item < local_root->getData())
            return erase(local_root->recurseLeft(), item);
        else if (local_root->getData() < item)
            return erase(local_root->recurseRight(), item);
        else { // Found item
            Node* old_root = local_root;
            if (local_root->getLeft() == nullptr) {
                local_root = local_root->getRight();
            } else if (local_root->getRight() == nullptr) {
                local_root = local_root->getLeft();
            } else {
                replace_parent(old_root, old_root->recurseLeft());
                return true;
            }
            delete old_root;
            return true;
        }
    }
}

void AVL::replace_parent(Node*& old_root, Node*& local_root) {
    if (local_root->getRight() != nullptr) {
        replace_parent(old_root, local_root->recurseRight());
    } else {
        int newData = local_root->getData();
        erase(root, local_root->getData());
        old_root->setData(newData);
    }
}
void AVL::rotateLeft() {

}
void AVL::rotateRight() {

}