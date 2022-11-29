#ifndef EX1_DICTIONARY_H
#define EX1_DICTIONARY_H

#include "wet1util.h"
#include <iostream>         //just for check

const int LEAF_HEIGHT = 0;
const int LEAF_SON_HEIGHT = -1;

template<class KEY, class VALUE>
class Dictionary {
public:
    Dictionary(bool is_sorted_by_key) : is_sorted_by_key(is_sorted_by_key), root(nullptr),
                                        counter_for_arrays(0), length(0){};

    void print();         //just for check
    StatusType insert(KEY key, VALUE value);
    StatusType remove(KEY key, VALUE value);
    VALUE* inorderNodesByValue();
    KEY* inorderNodesByKey();
    VALUE find(KEY key);
    VALUE findFatherValue(VALUE value);
    bool isExist(KEY key, VALUE value = nullptr);
//    VALUE getFarRight();
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
    int counter_for_arrays;
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

    void stabilizeTree(Node<KEY, VALUE>* node) {
        int old_height = node->height;
        node->setHeight(getHeight(node));
        node->setBfValue(getBfValue(node));
        if (node->bf_value == 2) {
            if (node->left_son->bf_value == -1) {
                LRRotation(node);
            }
            else {
                LLRotation(node);
            }
        }
        else if (node->bf_value == -2) {
            if (node->right_son->bf_value == 1) {
                RLRotation(node);
            }
            else {
                RRRotation(node);
            }
        }
        node->setHeight(getHeight(node));
        node->setBfValue(getBfValue(node));
        if (old_height == node->height || node->father == nullptr) {
            return;
        }

        stabilizeTree(node->father);
    }

    int getBfValue(Node<KEY, VALUE>* node) {
        return getHeight(node->left_son) - getHeight(node->right_son);
    }

    void LLRotation(Node<KEY, VALUE>* node) {
        Node<KEY, VALUE>* right_son_of_left_son = node->left_son->right_son;
        Node<KEY, VALUE>* father = node->father;

        node->setFather(node->left_son);
        node->left_son->setRight(node);
        node->setLeft(right_son_of_left_son);

        if (father != nullptr) {
            if (father->right_son->key == node->key) {
                father->setRight(node->father);
            }
            else {
                father->setLeft(node->father);
                father->left_son->setFather(father);
            }
        }

        if (root->key == node->key) {
            root = node->father;
            root->setFather(nullptr);
        }
    }


    void RRRotation(Node<KEY, VALUE>* node) {
        Node<KEY, VALUE>* left_son_of_right_son = node->right_son->left_son;
        Node<KEY, VALUE>* father = node->father;

        node->setFather(node->right_son);
        node->right_son->setLeft(node);
        node->setRight(left_son_of_right_son);

        if (father != nullptr) {
            if (father->left_son->key == node->key) {
                father->setLeft(node->father);
            }
            else {
                father->setRight(node->father);
                father->right_son->setFather(father);
            }
        }

        if (root->key == node->key) {
            root = node->father;
            root->setFather(nullptr);
        }
    }

    void RLRotation(Node<KEY, VALUE>* node) {
        LLRotation(node->right_son);
        RRRotation(node);
    }

    void LRRotation(Node<KEY, VALUE>* node) {
        RRRotation(node->left_son);
        LLRotation(node);
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

    void getAllNodes(Node<KEY, VALUE>* curr, VALUE* ans){
        if (curr == nullptr){
            return;
        }
        getAllNodes(curr->left_son, ans);
        ans[counter_for_arrays] = curr->value;
        counter_for_arrays += 1;
        getAllNodes(curr->right_son, ans);
    }

    void getAllNodesByKey(Node<KEY, VALUE>* curr, KEY* ans){
        if (curr == nullptr){
            return;
        }
        getAllNodesByKey(curr->left_son, ans);
        ans[counter_for_arrays] = curr->key;
        counter_for_arrays += 1;
        getAllNodesByKey(curr->right_son, ans);
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
            stabilizeTree(ro->father);
            delete ro;
            length -= 1;
            return;
        }
        if (ro->left_son == nullptr) {
            if (ro->father == nullptr){
                ro->right_son->setFather(nullptr);
                root = ro->right_son;
            }
            else {
                if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                    ro->father->setLeft(ro->right_son);
                    ro->right_son->setFather(ro->father);
                } else {
                    ro->father->setRight(ro->right_son);
                    ro->right_son->setFather(ro->father);
                }
            }
            stabilizeTree(ro->father);
            delete ro;
            length -= 1;
            return;
        }
        if (ro->right_son == nullptr){
            if (ro->father == nullptr){
                ro->left_son->setFather(nullptr);
                root = ro->left_son;
            }
            else {
                if ((ro->father->left_son != nullptr) && (ro->father->left_son->key == ro->key)) {
                    ro->father->setLeft(ro->left_son);
                    ro->left_son->setFather(ro->father);
                } else {
                    ro->father->setRight(ro->left_son);
                    ro->left_son->setFather(ro->father);
                }
            }
            stabilizeTree(ro->father);
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
        stabilizeTree(optional_father);
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
        stabilizeTree(optional_father);
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
            length++;
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
    Node<KEY, VALUE>* node = findNodeByKey(root, key);
    if (node == nullptr) {
        return nullptr;
    }
    return findNodeByKey(root, key)->value;
}

template<class KEY, class VALUE>
VALUE Dictionary<KEY, VALUE>::findFatherValue(VALUE value) {
    Node<KEY, VALUE>* temp = findNodeByValue(root, value)->father;
    if (temp == nullptr){
        return nullptr;
    }
    return temp->value;
}

template<class KEY, class VALUE>
bool Dictionary<KEY, VALUE>::isExist(KEY key, VALUE value) {
    if (is_sorted_by_key) {
        Node<KEY, VALUE> *temp = findNodeByKey(root, key);
        if (temp->key == key) {
            return true;
        }
        return false;
    }
    Node<KEY, VALUE> *temp = findNodeByValue(root, value);
    if (temp->key == key){
        return true;
    }
    return false;
}

//template<class KEY, class VALUE>
//VALUE Dictionary<KEY, VALUE>::getFarRight() {
//    Node<KEY, VALUE>* temp = root;
//    if (temp == nullptr){
//        return nullptr;
//    }
//    while (temp->right_son != nullptr){
//        temp = temp->right_son;
//    }
//    return temp->value;
//}

template<class T, class S>
void Dictionary<T, S>::print() {
    printAll(root);
}

template<class T, class S>
S* Dictionary<T, S>::inorderNodesByValue() {
    S* ans = new S[length];
    counter_for_arrays = 0;
    getAllNodes(root, ans);
    return ans;
}

template<class T, class S>
T* Dictionary<T, S>::inorderNodesByKey() {
    T* ans = new T[length];
    counter_for_arrays = 0;
    getAllNodesByKey(root, ans);
    return ans;
}

#endif //EX1_DICTIONARY_H
