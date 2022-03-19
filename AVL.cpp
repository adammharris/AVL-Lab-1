#include "AVL.h"

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
    if (root == nullptr) {
        root = new Node(data);
        return true;
    }
    bool successful = false;
    Node* temp = root;
    insert(temp, data, successful);
    return successful;
}
bool AVL::remove(int data) {
    return erase(root, data);
}

void AVL::clear() {
    if (root == nullptr) {
        return;
    }
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
            // no children
            if (root == nullptr) {
                return false;
            }
            delete root;
            root = nullptr;
            return true;
        }
        if ((root->getLeft() == nullptr) != (root->getRight() == nullptr)) {
            // one child (should make child root)
            Node* onlyChild = (root->getLeft()!=nullptr) ? root->getLeft() : root->getRight();
            delete root;
            root = onlyChild;
            return true;
        }
        if (root->getLeft() != nullptr && root->getRight() != nullptr) {
            // both children (should make closest node root)
            replace_parent(root, root->recurseLeft());
            //adjustHeight(root);
            return true;
        }
    }
    if (local_root == nullptr) {
        return false;
    }
    if (item < local_root->getData()) {
        //local_root = local_root->getLeft();
        return erase(local_root->recurseLeft(), item);
    }
    if (local_root->getData() < item) {
        //local_root = local_root->getRight();
        return erase(local_root->recurseRight(), item);
    }
    // Found item
    Node* old_root = local_root;
    if (local_root->getLeft() == nullptr) {
        local_root = local_root->getRight();
    } else if (local_root->getRight() == nullptr) {
        local_root = local_root->getLeft();
    } else {
        //Node* old_root_left = old_root->getLeft();
        replace_parent(old_root, old_root->recurseLeft());
        return true;
    }
    delete old_root;
    return true;
}

void AVL::replace_parent(Node*& old_root, Node*& local_root) {
    if (local_root->getRight() != nullptr) {
        //local_root = local_root->getRight();
        replace_parent(old_root, local_root->recurseRight());
    } else {
        int newData = local_root->getData();
        erase(root, local_root->getData());
        old_root->setData(newData);
    }
}
void AVL::insert(Node*& local, const int& data, bool& complete) {
    if (data == local->getData())
        return;
    if (complete) {
        if (local->getLeft() == nullptr && local->getRight() == nullptr) {
            if (data > local->getData()) {
                local->setRight(new Node(data));
            } else if (data < local->getData()) {
                local->setLeft(new Node(data));
            }
            adjustHeight(local);
        }
        if (local != root) {
            adjustHeight(local->recurseParent());
            rotate(local);
            local = local->getParent();
            insert(local, data, complete);
        } else {
            rotate(local);
            return;
        }
    } else if (data > local->getData()) {
        if (local->getRight() == nullptr) {
            local->setRight(new Node(data));
            local->getRight()->setParent(local);
            adjustHeight(local->recurseRight());
            complete = local->getData() != data;
            if (local != root) {
                insert(local, data, complete);
            }
        } else {
            local->getRight()->setParent(local);
            local = local->getRight();
            insert(local, data, complete);
        }

    } else if (data < local->getData()) {
        if (local->getLeft() == nullptr) {
            local->setLeft(new Node(data));
            local->getLeft()->setParent(local);
            adjustHeight(local->recurseLeft());
            complete = local->getData() != data;
            if (local != root) {
                insert(local, data, complete);
            }
        } else {
            local->getLeft()->setParent(local);
            local = local->getLeft();
            insert(local, data, complete);
        }
    }
}
void AVL::rotate(Node*& local) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (local->getLeft() != nullptr) {
        leftHeight = local->getLeft()->getHeight();
    }
    if (local->getRight() != nullptr) {
        rightHeight = local->getRight()->getHeight();
    }
    int balance = rightHeight - leftHeight;
    if (balance > 1) { // right heavy (left rotation)
        Node* tempL = local->getRight()->getLeft();
        if (local != root) {
            Node* parentNode = local->getParent();
            if (parentNode->getRight() == local) {
                parentNode->setRight(local->getRight());
            } else {
                parentNode->setLeft(local->getRight());
            }
        } else {
            root = local->getRight();
            root->setParent(nullptr);
        }
        local->getRight()->setLeft(local);
        local->setRight(tempL);
        if (local->getLeft() != nullptr) {
            adjustHeight(local->recurseLeft());
        } else {
            adjustHeight(local);
        }
    } else if (balance < -1) { // left heavy
        Node* tempR = local->getLeft()->getRight();
        if (local != root) {
            Node* parentNode = local->getParent();
            if (parentNode->getLeft() == local) {
                parentNode->setLeft(local->getLeft());
            } else {
                parentNode->setRight(local->getLeft());
            }
        } else {
            root = local->getLeft();
            root->setParent(nullptr);
        }
        local->getLeft()->setRight(local);
        local->setLeft(tempR);
        if (local->getLeft() != nullptr) {
            adjustHeight(local->recurseLeft());
        } else {
            adjustHeight(local);
        }

    }
}
void AVL::adjustHeight(Node*& local) {
    int leftVal = 0;
    int rightVal = 0;
    if (local->getLeft() != nullptr) {
        leftVal = local->getLeft()->getHeight();
    }
    if (local->getRight() != nullptr) {
        rightVal = local->getRight()->getHeight();
    }
    int newHeight = (leftVal > rightVal) ? ++leftVal : ++rightVal;
    local->setHeight(newHeight);
    if (local->getParent() != nullptr) {
        adjustHeight(local->recurseParent());
    }
}