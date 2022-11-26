#include "worldcup23a1.h"

world_cup_t::world_cup_t(): m_dict_of_teams(Dictionary<int, Team*>(true)),
                            m_dict_of_active_teams(Dictionary<int, Team*>(true)),
                            m_dict_of_players_by_value(Dictionary<int, Player*>(false)),
                            m_dict_of_players_by_key(Dictionary<int, Player*>(true)),
                            m_teams_total(0),m_active_teams_total(0), m_players_total(0)
{

}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    if ((teamId <= 0) || (points < 0)){
        return StatusType::INVALID_INPUT;
    }
    try {
        Team *added_team = new Team(teamId, points);
        StatusType ans = m_dict_of_teams.insert(teamId, added_team);
        if (ans == StatusType::SUCCESS){
            m_teams_total += 1;
        }
        else{
            delete added_team;
        }
        return ans;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* curr = m_dict_of_teams.find(teamId);
    if (curr->numberOfPlayers() > 0){
        return StatusType::FAILURE;
    }
    StatusType ans = m_dict_of_teams.remove(teamId, curr);
    if (ans == StatusType::SUCCESS){
        m_teams_total -= 1;
    }
	return ans;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
    if ((playerId <= 0) || (teamId <= 0) || (gamesPlayed < 0) || (goals < 0) || (cards < 0)){
        return StatusType::INVALID_INPUT;
    }
    if ((gamesPlayed == 0) && ((cards > 0) || (goals > 0))){
        return StatusType::INVALID_INPUT;
    }
    try{
        Player* temp_player = new Player(playerId, teamId, goals, cards, gamesPlayed, goalKeeper);
        StatusType ans1 = m_dict_of_players_by_key.insert(playerId, temp_player);
        if (ans1 != StatusType::SUCCESS){
            delete temp_player;
            return ans1;
        }
        ans1 = m_dict_of_players_by_value.insert(playerId, temp_player);
        if (ans1 != StatusType::SUCCESS){
            delete temp_player;
            return ans1;
        }
        Team* temp_team = m_dict_of_teams.find(teamId);
        if (temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        temp_team->add_player(playerId, temp_player);
        if (temp_team->numberOfPlayers() == 1){
            ans1 = m_dict_of_active_teams.insert(teamId, temp_team);
            if (ans1 != StatusType::SUCCESS){
                return ans1;
            }
            m_active_teams_total += 1;
        }
        m_players_total += 1;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Player* temp_player = m_dict_of_players_by_key.find(playerId);
    if (temp_player->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    StatusType ans = m_dict_of_players_by_value.remove(playerId, temp_player);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    Team* temp_team = m_dict_of_active_teams.find(temp_player->getTeamID());
    //Maybe here there's a problem with complexity, but active_teams maybe solves it
    ans = temp_team->remove_player(playerId);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    if (temp_team->numberOfPlayers() == 0){
        m_dict_of_active_teams.remove(temp_team->getID(), temp_team);
        m_active_teams_total -= 1;
    }
    m_players_total -= 1;
    return ans;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
    if ((playerId <= 0) || (gamesPlayed < 0) || (scoredGoals < 0) || (cardsReceived < 0)){
        return StatusType::INVALID_INPUT;
    }
	Player* temp_player = m_dict_of_players_by_key.find(playerId);
    if (temp_player->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    temp_player->addGoals(scoredGoals);
    temp_player->addGamesPlayed(gamesPlayed); // check if the value is zero, then need to set not add
    temp_player->addCards(cardsReceived);
    Team* temp_team = m_dict_of_active_teams.find(temp_player->getTeamID());
    temp_team->addStrength(temp_player->getGoals() - temp_player->getCards());
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	// TODO: Your code goes here
	return 2008;
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
	// TODO: Your code goes here
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

