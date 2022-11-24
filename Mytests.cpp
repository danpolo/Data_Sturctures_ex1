//
// Created by itayi on 21/11/2022.
//

#include "Dictionary.h"
#include "Player.h"


int main()
{
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

    std::cout << "Dictionary 2" << std::endl;

    Player v1 = Player(1, 3, 5, 2, false);
    Player v2 = Player(2,5,2,3,false);
    Player v3 = Player(3,5,3,3, false);
    Player v4 = Player(4,3,5,1, false);
    Player v5 = Player(5,3,7,2, false);
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