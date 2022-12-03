//
// Created by itayi on 21/11/2022.
//
#include <windows.h>
#include <vector>

#include "Dictionary.h"
#include "Player.h"
#include "worldcup23a1.h"


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

bool constructorCrush() {
    printFunctionName(__FUNCTION__);
    try {
        world_cup_t game = world_cup_t();
    }
    catch(...){
        return false;
    }
    return true;
}

bool addTeamInvalidInputId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.add_team(0, 1) == StatusType::INVALID_INPUT;
}

bool addTeamInvalidInputPoints() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.add_team(1, -1) == StatusType::INVALID_INPUT;
}

bool addTeamSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.add_team(1, 0) == StatusType::SUCCESS;
}

bool addTeamAlreadyExistingTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.add_team(1, 1) == StatusType::FAILURE;
}

bool removeTeamSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.remove_team(1) == StatusType::SUCCESS;
}

bool removeTeamInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.remove_team(0) == StatusType::INVALID_INPUT;
}

bool removeTeamTeamIdDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    return game.remove_team(2) == StatusType::FAILURE;
}

bool removeTeamNotEmpty() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.remove_team(1) == StatusType::FAILURE;
}

bool removeTeamAfterLastPlayerRemoval() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1, 0);
    game.add_player(1, 1, 1, 1, 1, false);
    game.remove_player(1);
    return game.remove_team(1) == StatusType::SUCCESS;
}

bool addPlayerSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 1, 1, 1, false) == StatusType::SUCCESS;
}

bool addPlayerInvalidPlayerId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(0, 1, 1, 1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidTeamId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 0, 1, 1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidGamesPlayed() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, -1, 1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidGoals() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 1, -1, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidCards() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 1, 1, -1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidCardsWithoutGames() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 0, 0, 1, false) == StatusType::INVALID_INPUT;
}

bool addPlayerInvalidGoalsWithoutGames() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 1, 0, 1, 0, false) == StatusType::INVALID_INPUT;
}

bool addPlayerAlreadyExistsInTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 2, 3, 4, false);
    return game.add_player(1, 1, 1, 1, 1, false) == StatusType::FAILURE;
}

bool addPlayerAlreadyExistsInAnotherTeam() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_team(2,0);
    game.add_player(1, 1, 2, 3, 4, false);
    return game.add_player(1, 2, 1, 1, 1, false) == StatusType::FAILURE;
}

bool addPlayerTeamDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    return game.add_player(1, 2, 1, 1, 1, false) == StatusType::FAILURE;
}

bool removePlayerSuccess() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.remove_player(1) == StatusType::SUCCESS;
}

bool removePlayerInvalidId() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    return game.remove_player(0) == StatusType::INVALID_INPUT;
}

bool removePlayerDoesntExist() {
    printFunctionName(__FUNCTION__);
    world_cup_t game = world_cup_t();
    game.add_team(1,0);
    game.add_player(1, 1, 1, 1, 1, false);
    return game.remove_player(2) == StatusType::FAILURE;
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

int main2() {
    std::cout << "Ignore this (Its for the colors)-> ";
    system(("chcp " + std::to_string(CP_UTF8)).c_str());
    std::cout << std::string(MAX_LINE_LENGTH + 28, '-') << std::endl;

    std::vector<bool(*)()> automatic_tests = {&findInEmptyDictionaryByKey, &findInEmptyDictionaryByValue,
                                              &findInOneElementDictionaryByKey,
                                              &findInOneElementDictionaryByValue,
                                              &findMissingElementInOneElementDictionaryByKey,
                                              &findMissingElementInOneElementDictionaryByValue,
                                              &findElementAfterRemoval, &constructorCrush,
                                              &addTeamInvalidInputId, &addTeamInvalidInputPoints,
                                              &addTeamSuccess, &addTeamAlreadyExistingTeam,
                                              &removeTeamSuccess, &removeTeamInvalidId,
                                              &removeTeamTeamIdDoesntExist, &removeTeamNotEmpty,
                                              &removeTeamAfterLastPlayerRemoval,
                                              &addPlayerSuccess, &addPlayerInvalidPlayerId,
                                              &addPlayerInvalidTeamId,
                                              &addPlayerInvalidGamesPlayed,
                                              &addPlayerInvalidGoals, &addPlayerInvalidCards,
                                              &addPlayerInvalidCardsWithoutGames,
                                              &addPlayerInvalidGoalsWithoutGames,
                                              &addPlayerAlreadyExistsInTeam,
                                              &addPlayerAlreadyExistsInAnotherTeam,
                                              &addPlayerTeamDoesntExist, &removePlayerSuccess,
                                              &removePlayerInvalidId, &removePlayerInvalidId,
                                              &removePlayerDoesntExist};

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
    dict2.remove(v5.getPlayerId(), &v5);
    std::cout << "level 1" << std::endl;
    dict2.print();
}
void generalTest3(){
    std::cout << "Test3" << std::endl;
    world_cup_t game1 = world_cup_t();
    game1.add_team(1, 10);
    game1.add_player(1,1,2,3,5, false);
    game1.add_player(2,1,3,5,2, false);
    game1.add_player(3,1,3,5,3,false);
    game1.add_player(4,1,1,3,5,false);
    game1.add_player(5,1,2,3,7, false);
    game1.getPlayers();
    game1.remove_player(5);
    game1.getPlayers();
}

int main(){
    generalTest3();
}