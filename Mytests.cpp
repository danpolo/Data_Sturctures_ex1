//
// Created by itayi on 21/11/2022.
//

#include "Dictionary.h"
#include "Player.h"
#include <vector>

#define PRINT_TEST_NAME(test) std::cout << "Running test: " << #test

std::string amendSentence(std::string str) {
    std::string out;
    for (int i = 0; i < str.length(); i++) {
        if (str[i]>='A' && str[i]<='Z') {
            str[i]=str[i]+32;
            if (i != 0) {
                out += " ";
            }
            out += str[i];
        }
        else {
            out += str[i];
        }
    }
    return out;
}

bool findInEmptyDictionaryByKey() {
    std::cout << "Running test: " << amendSentence(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    return dict.find(1) == nullptr;
}

bool findInEmptyDictionaryByValue() {
    std::cout << "Running test: " << amendSentence(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    return dict.find(1) == nullptr;
}



bool runTests(const std::vector<bool(*)()>& tests) {
    bool all_tests_passed = true;
    for (auto test : tests) {
        if (test()) {
            std::cout << " - TEST PASSED" << std::endl;
        }
        else {
            all_tests_passed = false;
            std::cout << " - TEST FAILED" << std::endl;
        }
    }
    return all_tests_passed;
}

int main()
{
    std::vector<bool(*)()> tests = {&findInEmptyDictionaryByKey, &findInEmptyDictionaryByValue};
    if (runTests(tests)) {
        std::cout << "ALL TESTS PASSED!!!" << std::endl;
    }
    else {
        std::cout << "Some of the tests failed" << std::endl;
    }

    return 0;
}





void generalTest1() {
    std::cout << "Dictionary 1" << std::endl;
    int num[6] = {6,4,8,9,24,3};
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    dict.insert(1,&num[0]);
    dict.insert(2, &num[1]);
    dict.insert(3,&num[2]);
    dict.insert(4,&num[3]);
    dict.insert(5,&num[4]);
    dict.insert(6,&num[5]);
    dict.print();
    dict.remove(3, &num[2]);
    dict.print();
}

void generalTest2() {
    std::cout << "Dictionary 2" << std::endl;
    Player v1 = Player(1, 1, 3, 5, 2, false);
    Player v2 = Player(2,1,5,2,3,false);
    Player v3 = Player(3,1,5,3,3, false);
    Player v4 = Player(4,1,3,5,1, false);
    Player v5 = Player(5,1,3,7,2, false);
    Dictionary<int, Player*> dict2 = Dictionary<int, Player*>(false);
    dict2.insert(v1.getPlayerId(), &v1);
    dict2.insert(v2.getPlayerId(), &v2);
    dict2.insert(v3.getPlayerId(), &v3);
    dict2.insert(v4.getPlayerId(), &v4);
    dict2.insert(v5.getPlayerId(), &v5);
    dict2.print();
    dict2.remove(v4.getPlayerId(), &v4);
    std::cout << "level 1" << std::endl;
    dict2.print();
}