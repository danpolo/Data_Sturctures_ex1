//
// Created by itayi on 21/11/2022.
//

#include "Team.h"

Team::Team(int teamID, int points) : teamID(teamID), m_points(points), m_games_played(0),
                                m_number_of_players(0), m_goalKeeper_exist(false), m_strength(points),
                                m_dict_of_players_in_team(Dictionary<int, Player*>(true)){}

bool Team::operator>(const Team &other) const {
    return (this->m_strength + this->m_points) > (other.m_strength + other.m_strength);
}

bool Team::operator==(const Team &other) const {
    return (this->m_strength + this->m_points) == (other.m_strength + other.m_strength);
}

int Team::numberOfPlayers() const {
    return m_number_of_players;
}

bool operator!=(const Team& v1, const Team& v2){
    return !(v1 == v2);
}
bool operator<(const Team& v1, const Team& v2){
    return v2 > v1;
}