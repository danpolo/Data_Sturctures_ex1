#ifndef EX1_DICTIONARY_H
#define EX1_DICTIONARY_H

#include "wet1util.h"
#include <iostream>         //just for check

const int LEAF_HEIGHT = 0;
const int LEAF_SON_HEIGHT = -1;

template<class KEY, class VALUE>
class Dictionary {
public:
    Dictionary(bool is_sorted_by_key) : is_sorted_by_key(is_sorted_by_key),
                                        root(nullptr), length(0){};

    void print();         //just for check
    StatusType insert(KEY key, VALUE value);
    StatusType remove(KEY key, VALUE value);
    VALUE find(KEY key);
private:

    template<class T, class S>
    class Node {
    public:
        Node(T key, S value, Node *father) : key(key), value(value),father(father),
                                             left_son(nullptr), right_son(nullptr), bf_value(0),
                                             height(LEAF_HEIGHT) {}
        Node(const Node& node) = default;
        Node& operator=(const Node& node) = default;
        ~Node() = default;
        void setLeft(Node *left) { left_son = left;}
        void setRight(Node *right) {right_son = right;}
        void setFather(Node *fat) {father = fat;}
        void setKey(T other_key){ key = other_key;}
        void setValue(S other_value){ value = other_value;}
        void setHeight(int new_height) {height = new_height;}
        void setBfValue(int new_bf_value) {bf_value = new_bf_value;}
//      bool isLeaf() {((right_son == nullptr)&&(left_son == nullptr));}
        T key;
        S value;
        Node* father;
        Node* left_son;
        Node* right_son;
        int bf_value;
        int height;
    };

    bool is_sorted_by_key;
    Node<KEY, VALUE>* root;
    int length;

    int getHeight(Node<KEY, VALUE>* node){
        if (node == nullptr) {
            return LEAF_SON_HEIGHT;
        }
        int right_son_height = LEAF_SON_HEIGHT;
        int left_son_height = LEAF_SON_HEIGHT;

        if (node->right_son != nullptr){
            right_son_height = node->right_son->height;
        }
        if (node->left_son != nullptr){
            left_son_height = node->left_son->height;
        }

        if (left_son_height > right_son_height) {
            return left_son_height + 1;
        }
        return right_son_height + 1;
    }

    void updateAncestorsHeight(Node<KEY, VALUE>* node) {
        int old_height = node->height;
        node->setHeight(getHeight(node));
        node->setBfValue(getBfValue(node));

        if (old_height == node->height || node->father == nullptr) {
            return;
        }

        updateAncestorsHeight(node->father);
    }

    int getBfValue(Node<KEY, VALUE>* node) {
        return getHeight(node->left_son) - getHeight(node->right_son);
    }

    Node<KEY, VALUE>* findNodeByKey(Node<KEY, VALUE>* current_root, KEY key_to_find) {
        if (current_root == nullptr) {
            return nullptr;
        }

        KEY temp = current_root->key;

        if (temp == key_to_find) {
            return current_root;
        }

        if (temp > key_to_find) {
            if (current_root->left_son == nullptr) {
                return current_root;
            }
            return findNodeByKey(current_root->left_son, key_to_find);
        }

        if (current_root->right_son == nullptr) {
            return current_root;
        }
        return findNodeByKey(current_root->right_son, key_to_find);

    }

    Node<KEY, VALUE>* findNodeByValue(Node<KEY, VALUE>* current_root, VALUE value_to_find){
        if (current_root == nullptr) {
            return nullptr;
        }

        VALUE temp = current_root->value;

        if (*temp == *value_to_find){
            return current_root;
        }
        if (*temp > *value_to_find) {
            if (current_root->left_son == nullptr) {
                return current_root;
            }
            return findNodeByValue(current_root->left_son, value_to_find);
        }

        if (current_root->right_son == nullptr) {
            return current_root;
        }
        return findNodeByValue(current_root->right_son, value_to_find);
    }


    void removeNode(Node<KEY, VALUE>* ro){
        if (ro == nullptr){
            return;
        }
        if ((ro->left_son == nullptr)&&(ro->right_son == nullptr)){
            if (ro->father == nullptr) {
                delete ro;
                length -= 1;
                return;
            }
            if ((ro->father->left_son != nullptr)&&(ro->father->left_son->key == ro->key)){
                ro->father->setLeft(nullptr);
            }
            else{
                ro->father->setRight(nullptr);
            }
            updateAncestorsHeight(ro->father);
            delete ro;
            length -= 1;
            return;
        }
        if (ro->left_son == nullptr) {
            if (ro->father == nullptr) {
                root = ro->right_son;
                delete ro;
                length -= 1;
                return;
            }
            if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                ro->father->setLeft(ro->right_son);
                ro->right_son->setFather(ro->father);
            } else {
                ro->father->setRight(ro->right_son);
                ro->right_son->setFather(ro->father);
            }
            updateAncestorsHeight(ro->father);
            delete ro;
            length -= 1;
            return;
        }
        if (ro->right_son == nullptr){
            if (ro->father == nullptr) {
                root = ro->left_son;
                delete ro;
                length -= 1;
                return;
            }
            if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                ro->father->setLeft(ro->left_son);
                ro->left_son->setFather(ro->father);
            } else {
                ro->father->setRight(ro->left_son);
                ro->left_son->setFather(ro->father);
            }
            updateAncestorsHeight(ro->father);
            delete ro;
            length -= 1;
            return;
        }
        Node<KEY, VALUE>* nearest = ro->right_son;
        while (nearest->left_son != nullptr){
            nearest = nearest->left_son;
        }
        KEY temp_key = ro->key;
        VALUE temp_value = ro->value;
        ro->setKey(nearest->key);
        ro->setValue(nearest->value);
        nearest->setKey(temp_key);
        nearest->setValue(temp_value);
        removeNode(nearest);
    }

    void printAll(Node<KEY, VALUE>* ro){             //Just for check
        if (ro == nullptr)
        {
            return;
        }
        printAll(ro->left_son);
        std::cout << "Key: " << ro->key << ", Height: " << ro->height << ", BF: " << ro->bf_value <<
        std::endl;
        printAll(ro->right_son);
    }


    StatusType insertKey(KEY key, VALUE value){
        Node<KEY, VALUE>* optional_father = findNodeByKey(root, key);
        if (key == optional_father->key){
            return StatusType::FAILURE;
        }
        Node<KEY, VALUE>* son = new Node<KEY, VALUE>(key, value, optional_father);
        if (key < optional_father->key){
            optional_father->setLeft(son);
        }
        else{
            optional_father->setRight(son);
        }
        updateAncestorsHeight(optional_father);
        length += 1;
        return StatusType::SUCCESS;
    }

    StatusType insertValue(KEY key, VALUE value){
        Node<KEY, VALUE>* optional_father = findNodeByValue(root, value);
        Node<KEY, VALUE>* son = new Node<KEY, VALUE>(key, value, optional_father);
        if (*value < *optional_father->value){
            optional_father->setLeft(son);
        }
        else{
            optional_father->setRight(son);
        }
        updateAncestorsHeight(optional_father);
        length += 1;
        return StatusType::SUCCESS;
    }
};

//template<class KEY, class VALUE>
//Dictionary<KEY, VALUE>::Dictionary(bool is_sorted_by_key) : is_sorted_by_key(is_sorted_by_key),
//                                                            root(nullptr), length(0){}

template<class KEY, class VALUE>
StatusType Dictionary<KEY, VALUE>::insert(KEY key, VALUE value) {
    try {
        if (root == nullptr) {
            root = new Node<KEY, VALUE>(key, value, nullptr);
            return StatusType::SUCCESS;
        }
        else {
            if (is_sorted_by_key){
                return insertKey(key, value);
            }
            else{
                return insertValue(key, value);
            }
        }
    }
    catch (std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
}


template<class KEY, class VALUE>
StatusType Dictionary<KEY, VALUE>::remove(KEY key, VALUE value) {
    if (is_sorted_by_key) {
        Node<KEY, VALUE> *temp = findNodeByKey(root, key);
        if (temp->key != key) {
            return StatusType::FAILURE;
        }
        removeNode(temp);
        return StatusType::SUCCESS;
    }
    Node<KEY, VALUE> *temp = findNodeByValue(root, value);
    if (*temp->value != *value)
    {
        return StatusType::FAILURE;
    }
    removeNode(temp);
    return StatusType::SUCCESS;
}

template<class KEY, class VALUE>
VALUE Dictionary<KEY, VALUE>::find(KEY key) {
    return findNodeByKey(root, key)->value;
}

template<class T, class S>
void Dictionary<T, S>::print() {
    printAll(root);
}

#endif //EX1_DICTIONARY_H
