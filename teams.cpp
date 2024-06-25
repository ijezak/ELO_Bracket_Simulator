#include "teams.h"

// FUNCTIONS
void assignTeam(Team* team, std::string name, std::string abbreviation, int initial_league_points, int rating, int rating_deviation)
{
    team->name = name;
    team->abbreviation = abbreviation;
    team->initial_league_points = initial_league_points;
    team->rating = rating;
    team->rating_deviation = rating_deviation;
}

void printTeamOrder(Team* team_list[], int team_list_length)
{
    std::cout << "Team Order:\n";
    for (int i = 0; i < team_list_length; i++)
    {
        std::cout << i + 1 << ". " << team_list[i]->abbreviation << "(" << team_list[i]->split_points << "," << team_list[i]->most_recent_tournament_points << ")\n";
    }
    std::cout << "\n";
}

void printTeamOrderSystem(Team* team_list[], int team_list_length)
{
    std::cout << "Team Order and system information:\n";
    for (int i = 0; i < team_list_length; i++)
    {
        std::cout << i + 1 << ". " << team_list[i]->abbreviation << "(" << team_list[i]->system_series_dif << "," << team_list[i]->system_game_dif << ")\n";
    }
    std::cout << "\n";
}

void stableSortTeams(Team* team_list[], int team_list_length, SortType sort_type)
{
    Team* key;
    int i, j;
    switch (sort_type)
    {
        case INIT_SEED_ASC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->initial_seed > key->initial_seed)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case RATING_DESC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->rating < key->rating)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case GAME_DIFFERENTIAL_DESC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->system_game_dif < key->system_game_dif)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case SERIES_DIFFERENTIAL_DESC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->system_series_dif < key->system_series_dif)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case BUCHHOLZ_SCORE_DESC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->swiss_buchholz_score < key->swiss_buchholz_score)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case SPLIT_POINTS_DESC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->split_points < key->split_points)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case TIEBREAKER_PLACEMENT_ASC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->tiebreaker_system_placement > key->tiebreaker_system_placement)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
        case SPLIT_TOURNAMENTS_PLACEMENT_ASC:
            for (i = 1; i < team_list_length; i++)
            {
                key = team_list[i];
                j = i-1;
                while (j >= 0 && team_list[j]->split_tournaments_placement_weighted_sum > key->split_tournaments_placement_weighted_sum)
                {
                    team_list[j+1] = team_list[j];
                    j--;
                }
                team_list[j+1] = key;
            }
            break;
    }
}

// CLEAR FUNCTIONS
void clearSeriesResults(Team* team)
{
    team->series_game_wins = 0;
    team->series_game_losses = 0;
    team->series_game_dif = 0;
}

void clearSystemResults(Team* team_list[], int team_list_length)
{
    for (int i = 0; i < team_list_length; i++)
    {
        team_list[i]->system_game_wins = 0;
        team_list[i]->system_game_losses = 0;
        team_list[i]->system_game_dif = 0;
        team_list[i]->system_series_wins = 0;
        team_list[i]->system_series_losses = 0;
        team_list[i]->system_series_dif = 0;
    }
}

// LOAD FUNCTIONS
void loadSixteenTeamRealisticDistribution(Team* team_list[16])
{
    assignTeam(team_list[0],  "Team 1",  "T1",  0, 2500, 200);
    assignTeam(team_list[1],  "Team 2",  "T2",  0, 2436, 200);
    assignTeam(team_list[2],  "Team 3",  "T3",  0, 2376, 200);
    assignTeam(team_list[3],  "Team 4",  "T4",  0, 2320, 200);
    assignTeam(team_list[4],  "Team 5",  "T5",  0, 2268, 200);
    assignTeam(team_list[5],  "Team 6",  "T6",  0, 2220, 200);
    assignTeam(team_list[6],  "Team 7",  "T7",  0, 2176, 200);
    assignTeam(team_list[7],  "Team 8",  "T8",  0, 2136, 200);
    assignTeam(team_list[8],  "Team 9",  "T9",  0, 2100, 200);
    assignTeam(team_list[9],  "Team 10", "T10", 0, 2068, 200);
    assignTeam(team_list[10], "Team 11", "T11", 0, 2040, 200);
    assignTeam(team_list[11], "Team 12", "T12", 0, 2016, 200);
    assignTeam(team_list[12], "Team 13", "T13", 0, 1996, 200);
    assignTeam(team_list[13], "Team 14", "T14", 0, 1980, 200);
    assignTeam(team_list[14], "Team 15", "T15", 0, 1968, 200);
    assignTeam(team_list[15], "Team 16", "T16", 0, 1960, 200);
    for (int i = 0; i < 16; i++){team_list[i]->initial_seed = i;}
}

void loadRegDistTeams(Team* team_list[], int team_list_length, float top_rating, float rating_difference)
{
    for (int i = 0; i < team_list_length; i++)
    {
        team_list[i]->name = "Team " + std::to_string(i+1);
        team_list[i]->abbreviation = "T" + std::to_string(i+1);
        team_list[i]->initial_seed = i;
        team_list[i]->initial_league_points = 0;
        team_list[i]->rating = top_rating - i*rating_difference;
        team_list[i]->rating_deviation = 200;
    }
}
