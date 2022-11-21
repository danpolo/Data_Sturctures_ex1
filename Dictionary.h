#ifndef EX1_DICTIONARY_H
#define EX1_DICTIONARY_H

#include "Team.h"
#include "wet1util.h"

template<class KEY, class VALUE>
class Dictionary {
public:
    Dictionary(bool is_sorted_by_key);

    //StatusType addNode(KEY key, VALUE value);

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
};

template<class KEY, class VALUE>
Dictionary<KEY, VALUE>::Dictionary(bool is_sorted_by_key) : length(0), root(nullptr),
                                    is_sorted_by_key(is_sorted_by_key){
}

#endif //EX1_DICTIONARY_H
