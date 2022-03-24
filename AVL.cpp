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
    if (data == root->getData()) { // When deleting root, no AVL stuff is involved
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
            root->setParent(nullptr);
            return true;
        }
        if (root->getLeft() != nullptr && root->getRight() != nullptr) {
            // both children (should make closest node root)
            replace_parent(root, root->recurseLeft());
            return true;
        }
    }
    bool complete = false;
    Node* root_aid = root;
    erase(root_aid, data, complete);
    return complete;
}

void AVL::clear() {
    if (root == nullptr) {
        return;
    }
    remove(root->getData());
    clear();
}
void AVL::erase(Node*& local, const int& data, bool& complete) {
    if (local == nullptr) {
        return;
    }
    if (complete) {
        if (data == local->getData()) {
            Node* toDelete = local;
            local = local->getParent();
            delete toDelete;
        } else {
            local = local->getParent();
        }
        if (local->getParent() != nullptr) {
            adjustHeight(local);
            rotate(local);
        }
        if (local != root) {
            erase(local, data, complete);
        }
        return;
    }
    if (data == local->getData()) { // Found thing to delete
        // One, two, or no children?
        Node* saveLocal = local;
        if (local->getLeft() != nullptr && local->getRight() != nullptr) { // both children
            replace_parent(local, local->recurseLeft());
        } else if ((local->getLeft() == nullptr) != (local->getRight() == nullptr)) { // one child
            // detach node from parent and child, attach parent to child
            Node* onlyChild = (local->getRight() == nullptr) ? local->getLeft() : local->getRight();
            if (local->getParent() != nullptr) {
                onlyChild->setParent(local->getParent());
                if (local->getParent()->getRight() == local) {
                    local->getParent()->setRight(onlyChild);
                } else if (local->getParent()->getLeft() == local){
                    local->getParent()->setLeft(onlyChild);
                }
            }
        } else if (local->getLeft() == nullptr && local->getRight() == nullptr) { // no children
            // remove reference to node from parent
            if (local->getParent() != nullptr) {
                if (local->getParent()->getRight() == local) {
                    local->getParent()->setRight(nullptr);
                } else if (local->getParent()->getLeft() == local){
                    local->getParent()->setLeft(nullptr);
                }
            }
        }
        complete = true;
        erase(saveLocal, data, complete);
    } else if (data > local->getData()) {
        erase(local->recurseRight(), data, complete);
    } else if (data < local->getData()) {
        erase(local->recurseLeft(), data, complete);
    }
}

void AVL::replace_parent(Node*& old_root, Node*& local_root) {
    if (local_root->getRight() != nullptr) {
        //local_root = local_root->getRight();
        replace_parent(old_root, local_root->recurseRight());
    } else {
        int newData = local_root->getData();
        bool complete = false;
        erase(local_root, local_root->getData(),complete);
        old_root->setData(newData);
        adjustHeight(old_root);
        rotate(old_root);
    }
}
void AVL::insert(Node* local, const int& data, bool& complete) {
    if (data == local->getData()) {
        return;
    }
    if (complete) {
        if (local->getLeft() == nullptr && local->getRight() == nullptr) {
            if (data > local->getData()) {
                local->setRight(new Node(data));
                local->getRight()->setParent(local);
            } else if (data < local->getData()) {
                local->setLeft(new Node(data));
                local->getLeft()->setParent(local);
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
void AVL::rotate(Node* local) {
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
        if (local->getParent() != nullptr) {
            Node* parentNode = local->getParent();
            if (parentNode->getRight() == local) {
                parentNode->setRight(local->getRight());
                //parentNode->getRight()->setParent(parentNode);
            } else {
                parentNode->setLeft(local->getRight());
                //parentNode->getLeft()->setParent(parentNode);
            }
        } else {
            root = local->getRight();
            root->setParent(nullptr);
            local->setParent(root);
        }
        local->getRight()->setLeft(local);
        local->setRight(tempL);
        adjustHeight(tempL);
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
            local->setParent(local->getLeft());
        }
        local->getLeft()->setRight(local);
        local->setLeft(tempR);
        if (local->getLeft() != nullptr) {
            adjustHeight(local->recurseLeft());
        } else {
            adjustHeight(local);
        }
        if (tempR != nullptr) {
            adjustHeight(tempR);
        }
    }
}
void AVL::adjustHeight(Node*& local) {
    if (local == nullptr) {
        return;
    }
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