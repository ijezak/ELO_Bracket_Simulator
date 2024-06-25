#ifndef TEAMS_H
#define TEAMS_H

#include <string>
#include <iostream>

#include "defs.h"

struct Team
{
    // INNATE
    std::string abbreviation = "";
    std::string name = "";
    float rating = 0;
    float rating_deviation = 0;
    int initial_seed = 0;
    int initial_league_points = 0;

    // SERIES - GENERIC
    unsigned int series_game_wins = 0;
    unsigned int series_game_losses = 0;
    int series_game_dif = 0;

    // SYSTEM - GENERIC
    unsigned int system_game_wins = 0;
    unsigned int system_game_losses = 0;
    int system_game_dif = 0;
    unsigned int system_series_wins = 0;
    unsigned int system_series_losses = 0;
    int system_series_dif = 0;

    unsigned int sixteen_system_placement = 0;
    unsigned int sixteen_system_placement_count[16] = {0};
    unsigned int eight_system_qualification_count = {0};
    unsigned int eight_system_placement = 0;
    unsigned int eight_system_placement_count[8] = {0};
    unsigned int tiebreaker_system_placement = 0;
    unsigned int system_points = 0;

    // TOURNAMENT - GENERIC
    unsigned int most_recent_tournament_placement = 0;
    unsigned int most_recent_tournament_points = 0;

    unsigned int cumulative_tournament_placement_count[16] = {0};
    unsigned int cumulative_tournament_placement_weighted_sum = 0;
    unsigned int cumulative_tournament_points = 0;

    // SPLIT - GENERIC
    unsigned int split_placement_weighted_sum = 0;
    unsigned int cumulative_split_placement_count[16] = {0};
    unsigned int cumulative_split_placement_weighted_sum = 0;
    unsigned int split_points = 0;
    unsigned int cumulative_split_points = 0;
    unsigned int split_tournaments_placement_weighted_sum = 0;

    // LEAGUE - GENERIC
    unsigned int league_placement_count[16] = {0};
    unsigned int league_points = 0;
    unsigned int major1_qualification_count = 0;
    unsigned int major2_qualification_count = 0;
    unsigned int world_championship_qualification_count = 0;

    // SYSTEM - SWISS
    unsigned int swiss_3_0_count = 0;
    unsigned int swiss_3_1_count = 0;
    unsigned int swiss_3_2_count = 0;
    unsigned int swiss_2_3_count = 0;
    unsigned int swiss_1_3_count = 0;
    unsigned int swiss_0_3_count = 0;

    // SYSTEM - SWISS - BUCHHOLZ
    unsigned int swiss_running_opponent_game_wins = 0;
    unsigned int swiss_buchholz_score = 0;

    // SYSTEM - ROUND ROBIN
    unsigned int rr_head_to_head[16] = {0};
    unsigned int rr_final_record[16] = {0};
    unsigned int rr_final_placement[16] = {0};
};

// FUNCTIONS
void assignTeam(Team* team, std::string name, std::string abbreviation, int league_points, int rating, int rating_deviation);

void printTeamOrder(Team* team_list[], int team_list_length);

void printTeamOrderSystem(Team* team_list[], int team_list_length);

void stableSortTeams(Team* team_list[], int team_list_length, SortType sort_type);

// CLEAR FUNCTIONS
void clearSeriesResults(Team* team);

void clearSystemResults(Team* team_list[], int team_list_length);

// LOAD FUNCTIONS
void loadSixteenTeamRealisticDistribution(Team* team_list[16]);

void loadRegDistTeams(Team* team_list[], int team_list_length, float top_rating, float rating_difference);

#endif