#include "AVL.h"
#include "Node.h"
#include <iostream>

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
void AVL::rotateLeft(Node*& local) {
    Node* temp = local->getLeft();
    local->setLeft(temp->getRight());
    temp->setRight(local);
    local = temp;
    calcHeight(local->recurseLeft());
    calcHeight(local->recurseRight());
    calcHeight(local);
}
void AVL::rotateRight(Node*& local) {
    Node* temp = local->getRight();
    local->setRight(temp->getLeft());
    temp->setLeft(local);
    local = temp;
    calcHeight(local->recurseLeft());
    calcHeight(local->recurseRight());
    calcHeight(local);
}
void AVL::rotate(Node*& local) {
    int leftHeight;
    int rightHeight;
    if (local->getLeft()) {
        leftHeight = local->getLeft()->getHeight();
    } else {
        leftHeight = 0;
    }
    if (local->getRight()) {
        rightHeight = local->getRight()->getHeight();
    } else {
        rightHeight = 0;
    }
    if (leftHeight - rightHeight > 1) {
        rotateLeft(local);
    } else if (rightHeight - leftHeight > 1) {
        rotateRight(local);
    }
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