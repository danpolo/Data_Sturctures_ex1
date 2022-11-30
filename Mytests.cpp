//
// Created by itayi on 21/11/2022.
//
#include <windows.h>
#include "Dictionary.h"
#include "Player.h"
#include <vector>

const int MAX_LINE_LENGTH = 75;

void printFunctionName(std::string str) {
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
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    return dict.find(1) == nullptr;
}

bool findInEmptyDictionaryByValue() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    return dict.find(1) == nullptr;
}

bool findInOneElementDictionaryByKey() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(1) == &element;
}

bool findInOneElementDictionaryByValue() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(1) == &element;
}

bool findMissingElementInOneElementDictionaryByKey() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(0) == &element;
}

bool findMissingElementInOneElementDictionaryByValue() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int element = 1;
    dict.insert(element, &element);
    return dict.find(0) == &element;
}

void testSingleRrRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {1,2,3};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleLlRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {3,2,1};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleRlRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {1,3,2};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleLrRotationByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[3] = {3,1,2};
    for (int i = 0; i < 3; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

void testSingleRrRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {1,2,3};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testSingleLlRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {3,2,1};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testSingleRlRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {1,3,2};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testSingleLrRotationByValue() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(false);
    int elements[3] = {3,1,2};
    for (int i = 1; i <= 3; i++) {
        dict.insert(i, elements + i - 1);
    }
    dict.print();
}

void testMultipleRotationsByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    const int length = 15;
    int elements[length];
    for (int i = 0; i < length; i++) {
        elements[i] = i + 1;
    }
    for (int i = 0; i < length; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.print();
}

bool findElementAfterRemoval() {
    printFunctionName(__FUNCTION__);
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int element = 1;
    dict.insert(element, &element);
    dict.remove(element, &element);
    return dict.find(element) == nullptr;
}

void testSingleRrRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {2,1,3,4};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(1, elements + 1);
    dict.print();
}

void testSingleLlRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {3,4,2,1};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(4, elements + 1);
    dict.print();
}

void testSingleLrRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {3,4,1,2};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(4, elements + 1);
    dict.print();
}

void testSingleRlRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[4] = {2,1,4,3};
    for (int i = 0; i < 4; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(1, elements + 1);
    dict.print();
}

void testRotationAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[5] = {2,1,4,3,5};
    for (int i = 0; i < 5; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(2, elements);
    dict.print();
}

void testMultiplyRotationsAfterRemovalByKey() {
    printFunctionName(__FUNCTION__);
    std::cout << std::endl;
    Dictionary<int, int*> dict = Dictionary<int, int*>(true);
    int elements[12] = {5,2,8,1,4,7,10,6,9,11,3,12};
    for (int i = 0; i < 12; i++) {
        dict.insert(elements[i], elements + i);
    }
    dict.remove(1, elements + 3);
    dict.print();
}

bool runAutomaticTests(const std::vector<bool(*)()>& tests) {
    std::cout << "Running Automatic Tests" << std::endl;
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
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

    std::vector<bool(*)()> automatic_tests = {&findInEmptyDictionaryByKey, &findInEmptyDictionaryByValue,
                                              &findInOneElementDictionaryByKey,
                                              &findInOneElementDictionaryByValue,
                                              &findMissingElementInOneElementDictionaryByKey,
                                              &findMissingElementInOneElementDictionaryByValue,
                                              &findElementAfterRemoval};

    std::vector<void(*)()> manual_tests = {&testSingleRrRotationByKey,
                                           &testSingleLlRotationByKey,
                                           &testSingleRlRotationByKey,
                                           &testSingleLrRotationByKey,
                                           &testSingleLlRotationByValue,
                                           &testSingleLrRotationByValue,
                                           &testSingleRlRotationByValue,
                                           &testSingleRrRotationByValue,
                                           &testMultipleRotationsByKey,
                                           &testSingleRrRotationAfterRemovalByKey,
                                           &testSingleLlRotationAfterRemovalByKey,
                                           &testSingleLrRotationAfterRemovalByKey,
                                           &testSingleRlRotationAfterRemovalByKey,
                                           &testRotationAfterRemovalByKey,
                                           &testMultiplyRotationsAfterRemovalByKey};

    if (runAutomaticTests(automatic_tests)) {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;32mALL TESTS PASSED!!!\033[0m" << std::endl;
    }
    else {
        std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
        std::cout << "\033[1;31mSome of the automatic_tests failed\033[0m" << std::endl;
    }
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;
    std::cout << "Running Manual Tests" << std::endl;
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;

    for (auto test : manual_tests) {
        test();
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