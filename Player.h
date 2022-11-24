#ifndef EX1_PLAYER_H
#define EX1_PLAYER_H

#include <string>


class Player {
public:
    Player(int player_id, int goals, int cards, int games_played, bool is_GK);
    ~Player() = default;
    Player& operator=(const Player& other) = default;
    int getPlayerId() const;

    int getGoals() const;

    int getCards() const;

    int getGamesPlayed() const;

    bool isGk() const;

    bool operator>(const Player& other) const;
    bool operator<(const Player& other) const;

private:
    int player_id;
    int goals;
    int cards;
    int games_played;
    bool is_GK;

};
bool operator!=(const Player& v1, const Player& v2);
bool operator==(const Player& v1, const Player& v2);


#endif //EX1_PLAYER_H
