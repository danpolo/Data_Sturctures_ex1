#include "worldcup23a1.h"

world_cup_t::world_cup_t(): m_dict_of_teams(Dictionary<int, Team*>(true)),
                            m_dict_of_active_teams(Dictionary<int, Team*>(true)),
                            m_dict_of_players_by_value(Dictionary<int, Player*>(false)),
                            m_dict_of_players_by_key(Dictionary<int, Player*>(true)),
                            m_top_scorer(nullptr),
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
    if ((curr->getID() != teamId) || (curr->numberOfPlayers() > 0)){
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
        Player* temp_player_left = m_dict_of_players_by_value.findClosestLeft(temp_player);
        Player* temp_player_right = m_dict_of_players_by_value.findClosestRight(temp_player);
        temp_player->setClosestLeft(temp_player_left);
        temp_player->setClosestRight(temp_player_right);
        if (temp_player_left != nullptr) {
            temp_player_left->setClosestRight(temp_player);
        }
        if (temp_player_right != nullptr) {
            temp_player_right->setClosestLeft(temp_player);
        }
        if (ans1 != StatusType::SUCCESS){
            delete temp_player;
            return ans1;
        }
        Team* temp_team = m_dict_of_teams.find(teamId);
        if (temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        temp_team->add_player_in_team(playerId, temp_player);
        if (temp_team->numberOfPlayers() == 1){
            ans1 = m_dict_of_active_teams.insert(teamId, temp_team);
            if (ans1 != StatusType::SUCCESS){
                return ans1;
            }
            m_active_teams_total += 1;
        }
        if (m_top_scorer == nullptr){
            m_top_scorer = temp_player;
        }
        else{
            if (*m_top_scorer < *temp_player){
                m_top_scorer = temp_player;
            }
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
    if (temp_player == nullptr || temp_player->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    if (temp_player == m_top_scorer){
        m_top_scorer = m_dict_of_players_by_value.findFatherValue(m_top_scorer);
    }
    int player_team_id = temp_player->getTeamID();
    StatusType ans = m_dict_of_players_by_value.remove(playerId, temp_player);
    if (ans != StatusType::SUCCESS){
        return ans;
    }
    Player* temp_player_left = temp_player->getClosestLeft();
    Player* temp_player_right = temp_player->getClosestRight();
    temp_player->setClosestLeft(nullptr);
    temp_player->setClosestRight(nullptr);
    if (temp_player_left != nullptr) {
        temp_player_left->setClosestRight(temp_player_right);
    }
    if (temp_player_right != nullptr) {
        temp_player_right->setClosestLeft(temp_player_left);
    }
    StatusType ans2 = m_dict_of_players_by_key.remove(playerId, temp_player);
    if (ans2 != StatusType::SUCCESS){
        return ans2;
    }
    Team* temp_team = m_dict_of_active_teams.find(player_team_id);
    //Maybe here there's a problem with complexity, but active_teams maybe solves it
    ans = temp_team->remove_player_in_team(playerId, temp_player);
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
    Team* temp_team = m_dict_of_active_teams.find(temp_player->getTeamID());
    temp_team->remove_player_in_team(playerId, temp_player);
    m_dict_of_players_by_value.remove(playerId, temp_player);
    temp_player->addGoals(scoredGoals);
    temp_player->addGamesPlayed(gamesPlayed); // check if the value is zero, then need to set not add
    temp_player->addCards(cardsReceived);
    temp_team->add_player_in_team(playerId, temp_player);
    m_dict_of_players_by_value.insert(playerId, temp_player);
//    temp_team->addStrength(temp_player->getGoals() - temp_player->getCards());
//    if (*temp_player > *m_top_scorer){
//        m_top_scorer = temp_player;
//    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
	if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2)){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = m_dict_of_teams.find(teamId1);
    Team* team2 = m_dict_of_teams.find(teamId2);
    if ((team1->getID() != teamId1) || (team2->getID() != teamId2) || (!(team2->isValidTeam())) || (!(team1->isValidTeam()))){
        return StatusType::FAILURE;
    }
    if (*team1 < *team2){
        team2->addPoints(3);
    }
    else{
        if (*team1 > *team2){
            team1->addPoints(3);
        }
        else{
            team1->addPoints(1);
            team2->addPoints(1);
        }
    }
    team1->addGamesPlayed(1);
    team2->addGamesPlayed(1);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Player* pl = m_dict_of_players_by_key.find(playerId);
    if (pl->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    int number_of_games_in_team = m_dict_of_active_teams.find(pl->getTeamID())->getGamesPlayed();
    //maybe there's a problem here with complexity
	return number_of_games_in_team + pl->getGamesPlayed();
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0){
        return StatusType::INVALID_INPUT;
    }
    Team* team_curr = m_dict_of_teams.find(teamId);
    if (team_curr->getID() != teamId){
        return StatusType::FAILURE;
    }
	return team_curr->getPoints();
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
	if ((teamId1 <= 0) || (teamId2 <= 0) || (teamId1 == teamId2) || (newTeamId <= 0)){
        return StatusType::INVALID_INPUT;
    }
    Team* team1 = m_dict_of_teams.find(teamId1);
    Team* team2 = m_dict_of_teams.find(teamId2);
    if ((team1->getID() != teamId1) || (team2->getID() != teamId2)){
        return StatusType::FAILURE;
    }
    Team* temp_team = m_dict_of_teams.find(newTeamId);
    if (temp_team->getID() == newTeamId){
        if (teamId1 == newTeamId){
            team1->move_all_players(team2);
            if (m_dict_of_active_teams.isExist(teamId2)){
                m_dict_of_active_teams.remove(teamId2, team2);
                m_active_teams_total -= 1;
            }
            m_dict_of_teams.remove(teamId2, team2);
            m_teams_total -= 1;
        }
        else{
            if (teamId2 == newTeamId){
                team2->move_all_players(team1);
                if (m_dict_of_active_teams.isExist(teamId1)){
                    m_dict_of_active_teams.remove(teamId1, team1);
                    m_active_teams_total -= 1;
                }
                m_dict_of_teams.remove(teamId1, team1);
                m_teams_total -= 1;
            }
            else{
                return StatusType::FAILURE;
            }
        }
        return StatusType::SUCCESS;
    }
    try {
        Team *added_team = new Team(newTeamId, team1->getPoints()+team2->getPoints());
        StatusType ans = m_dict_of_teams.insert(newTeamId, added_team);
        if (ans == StatusType::SUCCESS){
            m_teams_total += 1;
        }
        else{
            delete added_team;
            return ans;
        }
        added_team->move_all_players(team1);
        added_team->move_all_players(team2);
        if (added_team->numberOfPlayers() > 0){
            StatusType ans2 = m_dict_of_active_teams.insert(newTeamId, added_team);
            if (ans2 != StatusType::SUCCESS){
                return ans2;
            }
            m_active_teams_total += 1;
        }
        if (m_dict_of_active_teams.isExist(teamId1)){
            m_dict_of_active_teams.remove(teamId1, team1);
            m_active_teams_total -= 1;
        }
        if (m_dict_of_active_teams.isExist(teamId2)){
            m_dict_of_active_teams.remove(teamId2, team2);
            m_active_teams_total -= 1;
        }
        m_dict_of_teams.remove(teamId1, team1);
        m_dict_of_teams.remove(teamId2, team2);
        m_teams_total -= 2;
    }
    catch (std::bad_alloc&){
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
	if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0){
        Team* temp_team = m_dict_of_active_teams.find(teamId);
        if (temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        return temp_team->getTopScorerInTeam();
    }
    if (m_players_total == 0){
        return StatusType::FAILURE;
    }
	return m_top_scorer->getPlayerId();
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
	if (teamId == 0){
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0){
        Team* temp_team = m_dict_of_teams.find(teamId);
        if (temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        return temp_team->numberOfPlayers();
    }
    return m_players_total;
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if ((output == nullptr) || (teamId == 0)){
        return StatusType::INVALID_INPUT;
    }
    if (teamId > 0){
        Team* temp_team = m_dict_of_active_teams.find(teamId);
        if (temp_team->getID() != teamId){
            return StatusType::FAILURE;
        }
        int* answer = temp_team->getAllPlayersInTeam();
        int num_of_players = temp_team->numberOfPlayers();
        int i = 0;
        while (i < num_of_players){
            output[i] = answer[i];
            i++;
        }
    }
    else{
        if (m_players_total == 0){
            return StatusType::FAILURE;
        }
        int* answer = m_dict_of_players_by_value.inorderNodesByKey();
        int i = 0;
        while (i < m_players_total){
            output[i] = answer[i];
            i++;
        }
    }
	return StatusType::SUCCESS;
    //maybe need to catch an allocation error
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if ((playerId <= 0) || (teamId <= 0)){
        return StatusType::INVALID_INPUT;
    }
    if (m_players_total == 1){
        return StatusType::FAILURE;
    }
	Team* curr_team = m_dict_of_active_teams.find(teamId);
    Player* curr_player = curr_team->findPlayerByKey(playerId);
    if (curr_player->getPlayerId() != playerId){
        return StatusType::FAILURE;
    }
    if ((*curr_player->getClosestLeft() - *curr_player) / (*curr_player->getClosestRight() - *curr_player)){
        return curr_player->getClosestLeft()->getPlayerId();
    }
	return curr_player->getClosestRight()->getPlayerId();
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

void world_cup_t::getPlayers(){
    m_dict_of_players_by_value.print();
}
