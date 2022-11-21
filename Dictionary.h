#ifndef EX1_DICTIONARY_H
#define EX1_DICTIONARY_H

#include "Team.h"
#include "wet1util.h"

template<class KEY, class VALUE>
class Dictionary {
public:
    Dictionary(bool is_sorted_by_key);

    StatusType insert(KEY key, VALUE value);
private:

    template<class T, class S>
    class Node {
    public:
        Node(T key, S value, Node *father) : key(key), value(value),father(father),
                                                                                  left_son(nullptr),
                                                                                  right_son(nullptr){}
        T key;
        S value;
        Node* father;
        Node* left_son;
        Node* right_son;
    };

    bool is_sorted_by_key;
    Node<KEY, VALUE>* root;
    int length;


    Node<KEY, VALUE>* findNode(Node<KEY, VALUE>* current_root, KEY key_to_find = NULL, ) {
        if (current_root == nullptr) {
            return nullptr;
        }

        if (is_sorted_by_key) {
            KEY temp = current_root->key;

            if (temp == key_to_find) {
                return current_root;
            }

            if (temp > key_to_find) {
                if (current_root->left_son == nullptr) {
                    return current_root;
                }
                return findNode(key_to_find, current_root->left_son);
            }

            if (current_root->right_son == nullptr) {
                return current_root;
            }
            return findNode(key_to_find, current_root->right_son);
        }
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
        }
    }
    catch (std::bad_alloc) {
        return StatusType::ALLOCATION_ERROR;
    }
}


#endif //EX1_DICTIONARY_H
