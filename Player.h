#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include <string>


class Player {
public:
    Player(int player_id, int goals, int cards, int games_played, bool is_GK);
    ~Player() = default;

    bool operator>(Player& other) const;

private:
    int player_id;
public:
    int getPlayerId() const;

    int getGoals() const;

    int getCards() const;

    int getGamesPlayed() const;

    bool isGk() const;

private:
    int goals;
    int cards;
    int games_played;
    bool is_GK;

};


#endif //EX1_PLAYER_H
