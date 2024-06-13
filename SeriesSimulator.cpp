#include "SeriesSimulator.h"

std::mt19937 generator(time(nullptr));

bool runSeriesSimulation(Team* team_upper, Team* team_lower, int series_length)
{
    float team_upper_roll = 0;
    float team_lower_roll = 0;
    int team_upper_wins = 0;
    int team_lower_wins = 0;

    team_upper->series_game_wins = 0;
    team_upper->series_game_losses = 0;
    team_upper->series_game_dif = 0;
    team_lower->series_game_wins = 0;
    team_lower->series_game_losses = 0;
    team_lower->series_game_dif = 0;

    std::normal_distribution<float> distribution1(team_upper->rating_mean, team_upper->rating_deviation);
    std::normal_distribution<float> distribution2(team_lower->rating_mean, team_lower->rating_deviation);

    bool series_complete = false;
    while (!series_complete)
    {
        // Roll:
        team_upper_roll = distribution1(generator);
        team_lower_roll = distribution2(generator);
        
        // Determine winner:
        if (team_upper_roll >= team_lower_roll)
        {
            team_upper_wins++;
            team_upper->series_game_wins++;
            team_upper->series_game_dif++;
            team_upper->system_game_wins++;
            team_upper->system_game_dif++;

            team_lower->series_game_losses++;
            team_lower->series_game_dif--;
            team_lower->system_game_losses++;
            team_lower->system_game_dif--;
        }
        else
        {
            team_lower_wins++;
            team_lower->series_game_wins++;
            team_lower->series_game_dif++;
            team_lower->system_game_wins++;
            team_lower->system_game_dif++;

            team_upper->series_game_losses++;
            team_upper->series_game_dif--;
            team_upper->system_game_losses++;
            team_upper->system_game_dif--;
        }
        // Check if either team has won the series:
        if (team_upper_wins == series_length/2+1)
        {
            team_upper->system_series_wins++;
            team_upper->system_series_dif++;
            team_lower->system_series_losses++;
            team_lower->system_series_dif--;
            return true;
        }
        else if (team_lower_wins == series_length/2+1)
        {
            team_lower->system_series_wins++;
            team_lower->system_series_dif++;
            team_upper->system_series_losses++;
            team_upper->system_series_dif--;
            return false;
        }
    }
    return true;
}
