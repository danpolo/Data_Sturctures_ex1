//
// Created by itayi on 21/11/2022.
//
#include <windows.h>
#include "Dictionary.h"
#include "Player.h"
#include <vector>

const int MAX_LINE_LENGTH = 50;

void amendSentence(std::string str) {
    std::string out;
    out += str[0] - 32;
    for (int i = 1; i < str.length(); i++) {
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
    std::cout << "Running test: " << out << std::string(MAX_LINE_LENGTH - out.length(), ' ');
}

bool findInEmptyDictionaryByKey() {
    amendSentence(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    return dict.find(1) == nullptr;
}

bool findInEmptyDictionaryByValue() {
    amendSentence(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    return dict.find(1) == nullptr;
}


bool runTests(const std::vector<bool(*)()>& tests) {
    bool all_tests_passed = true;
    for (auto test : tests) {
        if (test()) {
            std::cout << "\033[1;32m - TEST PASSED\033[0m" << std::endl;
        }
        else {
            all_tests_passed = false;
            std::cout << "\033[1;31m - TEST FAILED\033[0m" << std::endl;
        }
    }
    return all_tests_passed;
}

int main() {
    std::cout << "Ignore this (Its for the colors)-> ";
    system(("chcp " + std::to_string(CP_UTF8)).c_str());
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    std::vector<bool(*)()> tests = {&findInEmptyDictionaryByKey, &findInEmptyDictionaryByValue};
    if (runTests(tests)) {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;32mALL TESTS PASSED!!!\033[0m" << std::endl;
    }
    else {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;31mSome of the tests failed\033[0m" << std::endl;
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