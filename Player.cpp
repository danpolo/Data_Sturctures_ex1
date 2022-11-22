#include "Player.h"

Player::Player(int player_id, int goals, int cards, int games_played, bool is_GK) :
              player_id(player_id),  goals(goals), cards(cards), games_played (games_played),
              is_GK(is_GK){
}

bool Player::operator>(const Player& other) const{
    if (goals != other.goals) {
        return goals > other.goals;
    }
    if (cards != other.cards) {
        return cards < other.cards;
    }
    return player_id > other.player_id;
}

bool Player::operator<(const Player& other) const {     //maybe duplication of code
    if (goals != other.goals) {
        return goals < other.goals;
    }
    if (cards != other.cards) {
        return cards > other.cards;
    }
    return player_id < other.player_id;
}

int Player::getPlayerId() const {
    return player_id;
}

int Player::getGoals() const {
    return goals;
}

int Player::getCards() const {
    return cards;
}

int Player::getGamesPlayed() const {
    return games_played;
}

bool Player::isGk() const {
    return is_GK;
}
bool operator!=(const Player& v1, const Player& v2){
    return ((v1 < v2)||(v1 > v2));
}
bool operator==(const Player& v1, const Player& v2){
    return !(v1 != v2);
}
