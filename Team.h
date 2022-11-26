//
// Created by itayi on 21/11/2022.
//

#ifndef EX1_TEAM_H
#define EX1_TEAM_H

#include "Dictionary.h"
#include "Player.h"

class Team
{
public:
    Team(int teamID, int points = 0);
    StatusType add_player(int playerID, Player* pl);
    StatusType remove_player(int playerID);

    int valueOfTeam() const;   //points + strength
    int getPoints() const;
    int getStrength() const;
    int getID() const;
    void addPoints(int points);
    void addStrength(int strength);
    void addGamesPlayed();
    int numberOfPlayers() const;
    bool isGoalKeeperExists() const;
    bool operator>(const Team& other) const;
    bool operator==(const Team& other) const;
    //StatusType getAllPlayers(* const ouput);
    //Output_t<int> getTopScorer();

    ~Team();

private:
    int teamID;
    int m_points;
    int m_strength;
    int m_games_played;
    int m_number_of_players;
    int m_goalKeeper_exist;
    Dictionary<int, Player*> m_dict_of_players_in_team;
    // Player m_top_scorer;
    // dictionary of players
};
bool operator!=(const Team& v1, const Team& v2);
bool operator<(const Team& v1, const Team& v2);

#endif //EX1_TEAM_H
