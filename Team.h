//
// Created by itayi on 21/11/2022.
//

#ifndef EX1_TEAM_H
#define EX1_TEAM_H


class Team
{
public:
    Team(int teamID);

    // StatusType add_player(int playerID, int games_played, int goals, int cards, bool goalKeeper)
    // StatusType remove_player()

    int valueOfTeam() const;   //points + strength
    int getPoints() const;
    int getStrength() const;
    void addPoints(int points);
    void addStrength(int strength);
    void addGamesPlayed();
    int numberOfPlayers() const;
    //StatusType getAllPlayers(* const ouput);
    //Output_t<int> getTopScorer();

    ~Team();

private:
    int teamID;
    int m_points;
    int m_strength;
    int m_games_played;
    int m_number_of_players;
    bool m_goalKeeper_exist;
    // Player m_top_scorer;
    // dictionary of players
};


#endif //EX1_TEAM_H
