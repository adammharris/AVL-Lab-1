#include "AVL.h"
#include "Node.h"
#include <iostream>

AVL::AVL() {
    root = nullptr;
}
AVL::~AVL() {
    clear();
}
NodeInterface* AVL::getRootNode() const {
    return root;
}
bool AVL::add(int data) {
    return insert(data, root);
}
bool AVL::insert(const int& data, Node*& local) {
    if (local == nullptr) {
        local = new Node(data);
        return true;
    }
    if (local->getData() == data) {
        return false;
    }
    if (data > local->getData()) {
        bool result = insert(data, local->recurseRight());
        calcHeight(local);
        rotate(local);
        return result;
    }
    if (data < local->getData()) {
        bool result = insert(data, local->recurseLeft());
        calcHeight(local);
        rotate(local);
        return result;
    }
}
bool AVL::remove(int data) {
    return erase(root, data);
}

void AVL::clear() {
    if (root == nullptr)
        return;
    remove(root->getData());
    clear();
}

bool AVL::erase(Node*& local_root,const int& item) {
    if (local_root == nullptr) {
        return false;
    }
    calcHeight(local_root);
    if (item < local_root->getData()) {
        bool result = erase(local_root->recurseLeft(), item);
        calcHeight(local_root);
        rotate(local_root);
        return result;
    }
    if (local_root->getData() < item) {
        bool result = erase(local_root->recurseRight(), item);
        calcHeight(local_root);
        rotate(local_root);
        return result;
    }
    if (local_root->getData() == item) { // Found item
        Node *old_root = local_root;
        if (local_root->getLeft() == nullptr) {
            local_root = local_root->getRight();
        } else if (local_root->getRight() == nullptr) {
            local_root = local_root->getLeft();
        } else {
            replace_parent(old_root, old_root->recurseLeft());
            rotate(local_root);
            return true;
        }
        calcHeight(local_root);
        delete old_root;
        return true;
    }
    calcHeight(local_root);
    rotate(local_root);
}

void AVL::replace_parent(Node*& old_root, Node*& local_root) {
    if (local_root->getRight() != nullptr) {
        replace_parent(old_root, local_root->recurseRight());
        rotate(local_root);
    } else {
        int newData = local_root->getData();
        erase(local_root, local_root->getData());
        old_root->setData(newData);
    }
}
void AVL::rotateLeft(Node*& local) {
    Node* temp = local->getLeft();
    local->setLeft(temp->getRight());
    temp->setRight(local);
    local = temp;
}
void AVL::rotateRight(Node*& local) {
    Node* temp = local->getRight();
    local->setRight(temp->getLeft());
    temp->setLeft(local);
    local = temp;
}
void AVL::rotate(Node*& local) {
    if (local == nullptr) {
        return;
    }
    int leftHeight = getHeight(local->getLeft());
    int rightHeight = getHeight(local->getRight());
    if (leftHeight - rightHeight > 1) {
        int leftSubtreeRightHeight = getHeight(local->getLeft()->getRight());
        int leftSubtreeLeftHeight = getHeight(local->getLeft()->getLeft());
        if (leftSubtreeRightHeight > leftSubtreeLeftHeight) {
            // if left subtree is right heavy, right-rotate left subtree first
            rotateRight(local->recurseLeft());
        }
        rotateLeft(local);
    } else if (rightHeight - leftHeight > 1) {
        int rightSubtreeRightHeight = getHeight(local->getRight()->getRight());
        int rightSubtreeLeftHeight = getHeight(local->getRight()->getLeft());
        if (rightSubtreeLeftHeight > rightSubtreeRightHeight) {
            // if right subtree is left heavy, left rotate right subtree first
            rotateLeft(local->recurseRight());
        }
        rotateRight(local);
    }
    calcHeight(local->recurseLeft());
    calcHeight(local->recurseRight());
    calcHeight(local);
}
int AVL::getHeight(Node* local) {
    if (local == nullptr) {
        return 0;
    }
    return local->getHeight();
}
void AVL::calcHeight(Node* local) {
    if (local == nullptr) {
        return;
    }
    int max = 0;
    if (getHeight(local->getLeft()) > max) {
        max = getHeight(local->getLeft());
    }
    if (getHeight(local->getRight()) > max) {
        max = getHeight(local->getRight());
    }
    local->setHeight(max+1);
}