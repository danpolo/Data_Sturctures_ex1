#ifndef EX1_DICTIONARY_H
#define EX1_DICTIONARY_H

#include "Team.h"
#include "wet1util.h"
#include "Player.h"
#include <iostream>         //just for check

template<class KEY, class VALUE>
class Dictionary {
public:
    Dictionary(bool is_sorted_by_key);

    void print();         //just for check
    StatusType insert(KEY key, VALUE value);
    StatusType remove(KEY key, VALUE value);
private:

    template<class T, class S>
    class Node {
    public:
        Node(T key, S value, Node *father) : key(key), value(value),father(father),
                                                                                  left_son(nullptr),
                                                                                  right_son(nullptr){}
        Node(const Node& node) = default;
        Node& operator=(const Node& node) = default;
        ~Node() = default;
        void setLeft(Node *left) { left_son = left;}
        void setRight(Node *right) {right_son = right;}
        void setFather(Node *fat) {father = fat;}
        void setKey(T other_key){ key = other_key;}
        void setValue(S other_value){ value = other_value;}
//        bool isLeaf() {((right_son == nullptr)&&(left_son == nullptr));}
        T key;
        S value;
        Node* father;
        Node* left_son;
        Node* right_son;
    };

    bool is_sorted_by_key;
    Node<KEY, VALUE>* root;
    int length;


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
            if ((ro->father->left_son != nullptr)&&(ro->father->left_son->key == ro->key)){
                ro->father->setLeft(nullptr);
            }
            else{
                ro->father->setRight(nullptr);
            }
            delete ro;
            return;
        }
        if (ro->left_son == nullptr) {
            if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                ro->father->setLeft(ro->right_son);
                ro->right_son->setFather(ro->father);
            } else {
                ro->father->setRight(ro->right_son);
                ro->right_son->setFather(ro->father);
            }
            delete ro;
            return;
        }
        if (ro->right_son == nullptr){
            if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                ro->father->setLeft(ro->left_son);
                ro->left_son->setFather(ro->father);
            } else {
                ro->father->setRight(ro->left_son);
                ro->left_son->setFather(ro->father);
            }
            delete ro;
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
        std::cout << ro->key << std::endl;
        printAll(ro->right_son);
    }
};

template<class KEY, class VALUE>
Dictionary<KEY, VALUE>::Dictionary(bool is_sorted_by_key) : length(0), root(nullptr),
                                    is_sorted_by_key(is_sorted_by_key){
}

template<class KEY, class VALUE>
StatusType Dictionary<KEY, VALUE>::insert(KEY key, VALUE value) {
    try {
        if (root == nullptr) {
            root = new Node<KEY, VALUE>(key, value, nullptr);
            return StatusType::SUCCESS;
        }
        else {
            Node<KEY, VALUE>* current_node = root;
            if (is_sorted_by_key){
                Node<KEY, VALUE>* temp = findNodeByKey(current_node, key);
                Node<KEY, VALUE>* son = new Node<KEY, VALUE>(key, value, temp);
                if (key == temp->key){
                    delete son;
                    return StatusType::FAILURE;
                }
                if (key < temp->key){
                    temp->setLeft(son);
                }
                else{
                    temp->setRight(son);
                }
                return StatusType::SUCCESS;
            }
            else{
                Node<KEY, VALUE>* temp = findNodeByValue(current_node, value);
                Node<KEY, VALUE>* son = new Node<KEY, VALUE>(key, value, temp);
                if (*value < *temp->value){
                    temp->setLeft(son);
                }
                else{
                    temp->setRight(son);
                }
                return StatusType::SUCCESS;
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

template<class T, class S>
void Dictionary<T, S>::print() {
    printAll(root);
}

#endif //EX1_DICTIONARY_H
