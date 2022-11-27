//
// Created by itayi on 21/11/2022.
//

#include "Team.h"

Team::Team(int teamID, int points) : teamID(teamID), m_points(points), m_games_played(0),
                                m_number_of_players(0), m_goalKeeper_exist(0), m_strength(points),
                                m_dict_of_players_in_team(Dictionary<int, Player*>(true)){}


int Team::valueOfTeam() const {
    return m_strength + m_points;
}

bool Team::operator>(const Team &other) const {
    return (valueOfTeam()) > (other.valueOfTeam());
}

bool Team::operator==(const Team &other) const {
    return (valueOfTeam()) == (other.valueOfTeam());
}

int Team::numberOfPlayers() const {
    return m_number_of_players;
}

void Team::addStrength(int strength) {
    m_strength += strength;
}

int Team::getID() const {
    return teamID;
}

bool Team::isGoalKeeperExists() const {
    if (m_goalKeeper_exist > 0){
        return true;
    }
    return false;
}

StatusType Team::add_player(int playerID, Player *pl) {
    StatusType ans = m_dict_of_players_in_team.insert(playerID, pl);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    m_number_of_players += 1;
    addStrength(pl->getGoals() - pl->getCards());
    if (pl->isGk()){
        m_goalKeeper_exist += 1;
    }
    return ans;
}

StatusType Team::remove_player(int playerID) {
    Player* temp_player = m_dict_of_players_in_team.find(playerID);
    if (temp_player->getPlayerId() != playerID){
        return StatusType::FAILURE;
    }
    int player_strength = temp_player->getCards() - temp_player->getGoals();
    bool is_player_gk = temp_player->isGk();
    StatusType ans = m_dict_of_players_in_team.remove(playerID, temp_player);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    m_number_of_players -= 1;
    addStrength(player_strength);
    if (is_player_gk){
        m_goalKeeper_exist -= 1;
    }
    return ans;
}

bool operator!=(const Team& v1, const Team& v2){
    return !(v1 == v2);
}
bool operator<(const Team& v1, const Team& v2){
    return v2 > v1;
}