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
    VALUE findClosestLeft(VALUE value);
    VALUE findClosestRight(VALUE value);
    VALUE findFatherValue(VALUE value);
    bool isExist(KEY key, VALUE value = nullptr);

private:

    template<class T, class S>
    class Node {
    public:
        Node(T key, S value, Node *father) : key(key), value(value),father(father),
                                             left_son(nullptr), right_son(nullptr), bf_value(0),
                                             height(LEAF_HEIGHT), closest_small(nullptr),
                                             closest_big(nullptr), inherit_closest_small(nullptr),
                                             inherit_closest_big(nullptr){}
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
        void setClosestSmall(S other_value){ closest_small = other_value;}
        void setClosestBig(S other_value){ closest_big = other_value;}
        S getClosestSmall(){ return closest_small;}
        S getClosestBig(){ return closest_big;}
        void setInheritClosestSmall(S other_value){ inherit_closest_small = other_value;}
        void setInheritClosestBig(S other_value){ inherit_closest_big = other_value;}
        S getInheritClosestSmall(){ return inherit_closest_small;}
        S getInheritClosestBig(){ return inherit_closest_big;}
//      bool isLeaf() {((right_son == nullptr)&&(left_son == nullptr));}
        T key;
        S value;
        Node* father;
        Node* left_son;
        Node* right_son;
        int bf_value;
        int height;
        S closest_small;
        S closest_big;
        S inherit_closest_small;
        S inherit_closest_big;
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

    void stabilizeTree(Node<KEY, VALUE>* node, bool is_insert=true) {
        int old_height = node->height;
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

        if (node->father == nullptr || (is_insert && old_height == node->height)) { // ||
            return;
        }

        stabilizeTree(node->father, is_insert);
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
        node->father->setFather(father);

        if (father != nullptr) {
            if (father->right_son->key == node->key) {
                father->setRight(node->father);
            }
            else {
                father->setLeft(node->father);
            }
        }

        if (root->key == node->key) {
            root = node->father;
            root->setFather(nullptr);
        }

        node->setHeight(getHeight(node));
        node->setBfValue(getBfValue(node));
        node->father->setHeight(getHeight(node->father));
        node->father->setBfValue(getBfValue(node->father));
    }


    void RRRotation(Node<KEY, VALUE>* node) {
        Node<KEY, VALUE>* left_son_of_right_son = node->right_son->left_son;
        Node<KEY, VALUE>* father = node->father;

        node->setFather(node->right_son);
        node->right_son->setLeft(node);
        node->setRight(left_son_of_right_son);
        node->father->setFather(father);

        if (father != nullptr) {
            if (father->left_son->key == node->key) {
                father->setLeft(node->father);
            }
            else {
                father->setRight(node->father);
            }
        }

        if (root->key == node->key) {
            root = node->father;
            root->setFather(nullptr);
        }

        node->setHeight(getHeight(node));
        node->setBfValue(getBfValue(node));
        node->father->setHeight(getHeight(node->father));
        node->father->setBfValue(getBfValue(node->father));
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

    Node<KEY, VALUE>* findNodeByValue(Node<KEY, VALUE>* current_root, VALUE value_to_find, VALUE close_left, VALUE close_right){
        if (current_root == nullptr) {
            return nullptr;
        }

        VALUE temp = current_root->value;

        if (*temp == *value_to_find){
            current_root->setInheritClosestSmall(close_left);
            current_root->setInheritClosestBig(close_right);
            return current_root;
        }
        if (*temp > *value_to_find) {
            if (close_right == nullptr){
                close_right = temp;
            }
            else{
                if ((*temp - *value_to_find) / (*close_right - *value_to_find)){
                    close_right = temp;
                }
            }
            if (current_root->closest_small == nullptr){
                current_root->closest_small = value_to_find;
            }
            else{
                if ((*value_to_find - *temp) / (*current_root->closest_small - *temp)){
                    current_root->closest_small = value_to_find;
                }
            }
            if (current_root->left_son == nullptr) {
                current_root->setInheritClosestSmall(close_left);
                current_root->setInheritClosestBig(close_right);
                return current_root;
            }
            return findNodeByValue(current_root->left_son, value_to_find, close_left, close_right);
        }
        if (close_left == nullptr){
            close_left = temp;
        }
        else{
            if ((*temp - *value_to_find) / (*close_left - *value_to_find)){
                close_left = temp;
            }
        }
        if (current_root->closest_big == nullptr){
            current_root->closest_big = value_to_find;
        }
        else{
            if ((*value_to_find - *temp) / (*current_root->closest_big - *temp)){
                current_root->closest_big = value_to_find;
            }
        }
        if (current_root->right_son == nullptr) {
            current_root->setInheritClosestSmall(close_left);
            current_root->setInheritClosestBig(close_right);
            return current_root;
        }
        return findNodeByValue(current_root->right_son, value_to_find, close_left, close_right);
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
                root = nullptr;
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
            stabilizeTree(ro->father, false);
            Node<KEY, VALUE>* temp_lefty = nullptr;
            Node<KEY, VALUE>* temp_righty = nullptr;
            if (ro->getClosestSmall() != nullptr) {
                temp_lefty = findNodeByValue(root, ro->getClosestSmall(), nullptr, nullptr);
                temp_lefty->setClosestBig(ro->getClosestBig());
                temp_lefty->setInheritClosestSmall(nullptr);
                temp_lefty->setInheritClosestBig(nullptr);
            }
            if (ro->getClosestBig() != nullptr) {
                temp_righty = findNodeByValue(root, ro->getClosestBig(), nullptr, nullptr);
                temp_righty->setClosestSmall(ro->getClosestSmall());
                temp_righty->setInheritClosestSmall(nullptr);
                temp_righty->setInheritClosestBig(nullptr);
            }
            //log(n) + log(n), maybe a problem with complexity
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
            stabilizeTree(ro->father, false);
            Node<KEY, VALUE>* temp_lefty = findNodeByValue(root, ro->getClosestSmall(), nullptr, nullptr);
            Node<KEY, VALUE>* temp_righty = findNodeByValue(root, ro->getClosestBig(), nullptr, nullptr);
            //log(n) + log(n), maybe a problem with complexity
            temp_lefty->setClosestBig(ro->getClosestBig());
            temp_righty->setClosestSmall(ro->getClosestSmall());
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
            stabilizeTree(ro->father, false);
            Node<KEY, VALUE>* temp_lefty = findNodeByValue(root, ro->getClosestSmall(), nullptr, nullptr);
            Node<KEY, VALUE>* temp_righty = findNodeByValue(root, ro->getClosestBig(), nullptr, nullptr);
            //log(n) + log(n), maybe a problem with complexity
            temp_lefty->setClosestBig(ro->getClosestBig());
            temp_righty->setClosestSmall(ro->getClosestSmall());
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
        VALUE temp_close_lefty = ro->getClosestSmall();
        VALUE temp_close_righty = ro->getClosestBig();
        ro->setKey(nearest->key);
        ro->setValue(nearest->value);
        ro->setClosestSmall(nearest->getClosestSmall());
        ro->setClosestBig(nearest->getClosestBig());
        nearest->setKey(temp_key);
        nearest->setValue(temp_value);
        nearest->setClosestSmall(temp_close_lefty);
        nearest->setClosestBig(temp_close_righty);
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
        // try catch to allocation error?
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
        VALUE closest_small = nullptr;
        VALUE closest_big = nullptr;
        Node<KEY, VALUE>* optional_father = findNodeByValue(root, value, closest_small, closest_big);
        Node<KEY, VALUE>* son = new Node<KEY, VALUE>(key, value, optional_father);
        // try catch to allocation error?
        son->setClosestBig(optional_father->getInheritClosestBig());
        son->setClosestSmall(optional_father->getInheritClosestSmall());
        optional_father->setInheritClosestSmall(nullptr);
        optional_father->setInheritClosestBig(nullptr);
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
    Node<KEY, VALUE> *temp = findNodeByValue(root, value, nullptr, nullptr);
    if (*temp->value != *value)
    {
        return StatusType::FAILURE;
    }
    temp->setInheritClosestSmall(nullptr);
    temp->setInheritClosestBig(nullptr);
    removeNode(temp);
    return StatusType::SUCCESS;
}

template<class KEY, class VALUE>
VALUE Dictionary<KEY, VALUE>::find(KEY key){
    Node<KEY, VALUE>* node = findNodeByKey(root, key);
    if (node == nullptr) {
        return nullptr;
    }
    return findNodeByKey(root, key)->value;
}

template<class KEY, class VALUE>
VALUE Dictionary<KEY, VALUE>::findFatherValue(VALUE value){
    Node<KEY, VALUE>* temp = findNodeByValue(root, value, nullptr, nullptr)->father;
    if (temp == nullptr){
        return nullptr;
    }
    return temp->value;
}

template<class KEY, class VALUE>
bool Dictionary<KEY, VALUE>::isExist(KEY key, VALUE value){
    if (is_sorted_by_key) {
        Node<KEY, VALUE> *temp = findNodeByKey(root, key);
        if (temp->key == key) {
            return true;
        }
        return false;
    }
    Node<KEY, VALUE> *temp = findNodeByValue(root, value, nullptr, nullptr);
    if (temp->key == key){
        return true;
    }
    return false;
}
template<class KEY, class VALUE>
VALUE Dictionary<KEY, VALUE>::findClosestLeft(VALUE value) {
    Node<KEY, VALUE>* temp = findNodeByValue(root, value, nullptr, nullptr);
    return temp->getClosestSmall();
}
template<class KEY, class VALUE>
VALUE Dictionary<KEY, VALUE>::findClosestRight(VALUE value) {
    Node<KEY, VALUE>* temp = findNodeByValue(root, value, nullptr, nullptr);
    return temp->getClosestBig();
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
