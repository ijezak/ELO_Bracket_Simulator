#include "SystemSimulator.h"

int runSingleElimFinalEight(Team* team_list[8], int series_length, int trials, OutputMode output_mode)
{
    for (int j = 0; j < 8; j++)
    {
        team_list[j]->system_points = 0;
    }
    Team* semi_finalists[4];
    Team* grand_finalists[2];
    for (int j = 0; j < trials; j++)
    {
        // QUARTER FINALS
        for (int i = 0; i < 4; i ++)
        {
            if (runSeriesSimulation(team_list[i], team_list[7-i], 7))
            {
                semi_finalists[i] = team_list[i];
                team_list[7-i]->eight_system_placement_count[7]++;
                team_list[7-i]->eight_system_placement = 7;
                team_list[7-i]->system_points = 0;
            }
            else
            {
                semi_finalists[i] = team_list[7-i];
                team_list[i]->eight_system_placement_count[7]++;
                team_list[i]->eight_system_placement = 7;
                team_list[i]->system_points = 0;
            }
        }
        // SEMI FINALS
        for (int i = 0; i < 2; i ++)
        {
            if (runSeriesSimulation(semi_finalists[i], semi_finalists[3-i], 7))
            {
                grand_finalists[i] = semi_finalists[i];
                semi_finalists[3-i]->eight_system_placement_count[3]++;
                semi_finalists[3-i]->eight_system_placement = 3;
                semi_finalists[3-i]->system_points = 3;
            }
            else
            {
                grand_finalists[i] = semi_finalists[3-i];
                semi_finalists[i]->eight_system_placement_count[3]++;
                semi_finalists[i]->eight_system_placement = 3;
                semi_finalists[i]->system_points = 3;
            }
        }
        // GRAND FINAL
        if (runSeriesSimulation(grand_finalists[0], grand_finalists[1], 7))
        {
            grand_finalists[0]->eight_system_placement_count[0]++;
            grand_finalists[0]->eight_system_placement = 0;
            grand_finalists[0]->system_points = 10;
            grand_finalists[1]->eight_system_placement_count[1]++;
            grand_finalists[1]->eight_system_placement = 1;
            grand_finalists[1]->system_points = 6;
        }
        else
        {
            grand_finalists[1]->eight_system_placement_count[0]++;
            grand_finalists[1]->eight_system_placement = 0;
            grand_finalists[1]->system_points = 10;
            grand_finalists[0]->eight_system_placement_count[1]++;
            grand_finalists[0]->eight_system_placement = 1;
            grand_finalists[0]->system_points = 6;
        }
    }
    return 0;
}

int runAFLFinalEight(Team* team_list[8], int series_length, int trials, OutputMode output_mode)
{
    for (int j = 0; j < 8; j++)
    {
        team_list[j]->system_points = 0;
    }
    Team* semi_finalists[4];
    Team* preliminary_finalists[4];
    Team* grand_finalists[2];
    for (int j = 0; j < trials; j++)
    {
        // Qualifying Final Upper
        if (runSeriesSimulation(team_list[0], team_list[3], series_length)) // 1st vs 4th
        {
            preliminary_finalists[0] = team_list[0];
            semi_finalists[0] = team_list[3];
        }
        else
        {
            preliminary_finalists[0] = team_list[3];
            semi_finalists[0] = team_list[0];
        }
        // Qualifying Final Lower
        if (runSeriesSimulation(team_list[1], team_list[2], series_length)) // 2nd vs 3rd
        {
            preliminary_finalists[2] = team_list[1];
            semi_finalists[2] = team_list[2];
        }
        else
        {
            preliminary_finalists[2] = team_list[2];
            semi_finalists[2] = team_list[1];
        }
        // Elimination Final Upper
        if (runSeriesSimulation(team_list[4], team_list[7], series_length)) // 5th vs 8th
        {
            semi_finalists[1] = team_list[4];
            team_list[7]->eight_system_placement_count[7]++;
            team_list[7]->eight_system_placement = 7;
            team_list[7]->system_points = 0;
        }
        else
        {
            semi_finalists[1] = team_list[7];
            team_list[1]->eight_system_placement_count[7]++;
            team_list[1]->eight_system_placement = 7;
            team_list[1]->system_points = 0;
        }
        // Elimination Final Upper
        if (runSeriesSimulation(team_list[5], team_list[6], series_length)) // 6th vs 7th
        {
            semi_finalists[3] = team_list[5];
            team_list[6]->eight_system_placement_count[7]++;
            team_list[6]->eight_system_placement = 7;
            team_list[6]->system_points = 0;
        }
        else
        {
            semi_finalists[3] = team_list[6];
            team_list[5]->eight_system_placement_count[7]++;
            team_list[5]->eight_system_placement = 7;
            team_list[5]->system_points = 0;
        }
        // Semi Final Upper
        if (runSeriesSimulation(semi_finalists[0], semi_finalists[1], series_length))
        {
            preliminary_finalists[1] = semi_finalists[0];
            semi_finalists[1]->eight_system_placement_count[5]++;
            semi_finalists[1]->eight_system_placement = 5;
            semi_finalists[1]->system_points = 1; //1
        }
        else
        {
            preliminary_finalists[1] = semi_finalists[1];
            semi_finalists[0]->eight_system_placement_count[5]++;
            semi_finalists[0]->eight_system_placement = 5;
            semi_finalists[0]->system_points = 1; //1
        }
        // Semi Final Lower
        if (runSeriesSimulation(semi_finalists[2], semi_finalists[3], series_length))
        {
            preliminary_finalists[3] = semi_finalists[2];
            semi_finalists[3]->eight_system_placement_count[5]++;
            semi_finalists[3]->eight_system_placement = 5;
            semi_finalists[3]->system_points = 1; //1
        }
        else
        {
            preliminary_finalists[3] = semi_finalists[3];
            semi_finalists[2]->eight_system_placement_count[5]++;
            semi_finalists[2]->eight_system_placement = 5;
            semi_finalists[2]->system_points = 1; //1
        }
        // Preliminary Final Upper
        if (runSeriesSimulation(preliminary_finalists[0], preliminary_finalists[1], series_length))
        {
            grand_finalists[0] = preliminary_finalists[0];
            preliminary_finalists[1]->eight_system_placement_count[3]++;
            preliminary_finalists[1]->eight_system_placement = 3;
            preliminary_finalists[1]->system_points = 3;
        }
        else
        {
            grand_finalists[0] = preliminary_finalists[1];
            preliminary_finalists[0]->eight_system_placement_count[3]++;
            preliminary_finalists[0]->eight_system_placement = 3;
            preliminary_finalists[0]->system_points = 3;
        }
        // Preliminary Final Lower
        if (runSeriesSimulation(preliminary_finalists[2], preliminary_finalists[3], series_length))
        {
            grand_finalists[1] = preliminary_finalists[2];
            preliminary_finalists[3]->eight_system_placement_count[3]++;
            preliminary_finalists[3]->eight_system_placement = 3;
            preliminary_finalists[3]->system_points = 3;
        }
        else
        {
            grand_finalists[1] = preliminary_finalists[3];
            preliminary_finalists[2]->eight_system_placement_count[3]++;
            preliminary_finalists[2]->eight_system_placement = 3;
            preliminary_finalists[2]->system_points += 3;
        }
        // Grand Final
        if (runSeriesSimulation(grand_finalists[0], grand_finalists[1], series_length))
        {
            grand_finalists[0]->eight_system_placement_count[0]++;
            grand_finalists[0]->eight_system_placement = 0;
            grand_finalists[0]->system_points += 10;
            grand_finalists[1]->eight_system_placement_count[1]++;
            grand_finalists[1]->eight_system_placement = 1;
            grand_finalists[1]->system_points += 6;
        }
        else
        {
            grand_finalists[1]->eight_system_placement_count[0]++;
            grand_finalists[1]->eight_system_placement = 0;
            grand_finalists[1]->system_points += 10;
            grand_finalists[0]->eight_system_placement_count[1]++;
            grand_finalists[0]->eight_system_placement = 1;
            grand_finalists[0]->system_points += 6;
        }
    }
    return 0;
}

int runGameDifSwiss(Team* team_list[16], Team* qualified[8], int series_length, int trials, OutputMode output_mode)
{
    // CLEAR SYSTEM VARIABLES
    for (int i = 0; i < 16; i++)
    {
        team_list[i]->system_series_wins = 0;
        team_list[i]->system_series_losses = 0;
        team_list[i]->system_series_dif = 0;
        team_list[i]->system_game_wins = 0;
        team_list[i]->system_game_losses = 0;
        team_list[i]->system_game_dif = 0;
        team_list[i]->swiss_running_opponent_game_wins = 0;
        team_list[i]->swiss_buchholz_score = 0;
    }
    // ROUND 1
    for (int i = 0; i < 8; i++)
    {
        runSeriesSimulation(team_list[i], team_list[15-i], series_length);
    }
    stableSortTeams(team_list, 16, INIT_SEED_ASC);
    stableSortTeams(team_list, 16, GAME_DIFFERENTIAL_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    // ROUND 2
    for (int i = 0; i < 4; i++)
    {
        runSeriesSimulation(team_list[i], team_list[7-i], series_length);
        runSeriesSimulation(team_list[8+i], team_list[15-i], series_length);
    }
    stableSortTeams(team_list, 16, INIT_SEED_ASC);
    stableSortTeams(team_list, 16, GAME_DIFFERENTIAL_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    // ROUND 3
    for (int i = 0; i < 2; i++)
    {
        runSeriesSimulation(team_list[i], team_list[3-i], series_length);
        runSeriesSimulation(team_list[12+i], team_list[15-i], series_length);
    }
    for (int i = 0; i < 4; i++)
    {
        runSeriesSimulation(team_list[4+i], team_list[11-i], series_length);
    }
    stableSortTeams(team_list, 16, INIT_SEED_ASC);
    stableSortTeams(team_list, 16, GAME_DIFFERENTIAL_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    // ROUND 4
    for (int i = 0; i < 3; i++)
    {
        runSeriesSimulation(team_list[2+i], team_list[7-i], series_length);
        runSeriesSimulation(team_list[8+i], team_list[13-i], series_length);
    }
    stableSortTeams(team_list, 16, INIT_SEED_ASC);
    stableSortTeams(team_list, 16, GAME_DIFFERENTIAL_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    // ROUND 5
    for (int i = 0; i < 3; i++)
    {
        runSeriesSimulation(team_list[5+i], team_list[10-i], series_length);
    }
    stableSortTeams(team_list, 16, INIT_SEED_ASC);
    stableSortTeams(team_list, 16, GAME_DIFFERENTIAL_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    for (int i = 0; i < 2; i++)
    {
        team_list[i]->swiss_3_0_count++;
        team_list[i]->sixteen_system_placement_count[1]; // 1st and 2nd
        team_list[i]->sixteen_system_placement = 1;
        team_list[i]->eight_system_qualification_count++;
        team_list[i]->system_points = 6;
        qualified[i] = team_list[i];
    }
    for (int i = 2; i < 5; i++)
    {
        team_list[i]->swiss_3_1_count++;
        team_list[i]->sixteen_system_placement_count[4]; // 3rd through 5th
        team_list[i]->sixteen_system_placement = 4;
        team_list[i]->eight_system_qualification_count++;
        team_list[i]->system_points = 6;
        qualified[i] = team_list[i];
    }
    for (int i = 5; i < 8; i++)
    {
        team_list[i]->swiss_3_2_count++;
        team_list[i]->sixteen_system_placement_count[7]; // 6th through 8th
        team_list[i]->sixteen_system_placement = 7;
        team_list[i]->eight_system_qualification_count++;
        team_list[i]->system_points = 6;
        qualified[i] = team_list[i];
    }
    for (int i = 8; i < 11; i++)
    {
        team_list[i]->swiss_2_3_count++;
        team_list[i]->sixteen_system_placement_count[10]; // 9th through 11th
        team_list[i]->sixteen_system_placement = 10;
        team_list[i]->system_points = 5;
    }
    for (int i = 11; i < 14; i++)
    {
        team_list[i]->swiss_1_3_count++;
        team_list[i]->sixteen_system_placement_count[13]; // 12th through 14th
        team_list[i]->sixteen_system_placement = 13;
        team_list[i]->system_points = 4;
    }
    for (int i = 14; i < 16; i++)
    {
        team_list[i]->swiss_0_3_count++;
        team_list[i]->sixteen_system_placement_count[15]; // 15th and 16th
        team_list[i]->sixteen_system_placement = 15;
        team_list[i]->system_points = 3;
    }
    return 0;
}

int runBuchholzSwiss(Team* team_list[16], Team* qualified[8], int series_length, int trials, OutputMode output_mode)
{
    // CLEAR SYSTEM VARIABLES
    for (int i = 0; i < 16; i++)
    {
        team_list[i]->system_series_wins = 0;
        team_list[i]->system_series_losses = 0;
        team_list[i]->system_series_dif = 0;
        team_list[i]->system_game_wins = 0;
        team_list[i]->system_game_losses = 0;
        team_list[i]->system_game_dif = 0;
        team_list[i]->swiss_running_opponent_game_wins = 0;
        team_list[i]->swiss_buchholz_score = 0;
    }
    // ROUND 1
    for (int i = 0; i < 8; i++)
    {
        runBuchholzSeries(team_list[i], team_list[15-i], series_length);
    }
    // ROUND 2
    stableSortTeams(team_list, 16, BUCHHOLZ_SCORE_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    for (int i = 0; i < 4; i++)
    {
        runBuchholzSeries(team_list[i], team_list[7-i], series_length);
        runBuchholzSeries(team_list[8+i], team_list[15-i], series_length);
    }
    // ROUND 3
    stableSortTeams(team_list, 16, BUCHHOLZ_SCORE_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    for (int i = 0; i < 2; i++)
    {
        runBuchholzSeries(team_list[i], team_list[3-i], series_length);
        runBuchholzSeries(team_list[12+i], team_list[15-i], series_length);
    }
    for (int i = 0; i < 4; i++)
    {
        runBuchholzSeries(team_list[4+i], team_list[11-i], series_length);
    }
    // ROUND 4
    stableSortTeams(team_list, 16, BUCHHOLZ_SCORE_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    for (int i = 0; i < 3; i++)
    {
        runBuchholzSeries(team_list[2+i], team_list[7-i], series_length);
        runBuchholzSeries(team_list[8+i], team_list[13-i], series_length);
    }
    // ROUND 5
    stableSortTeams(team_list, 16, BUCHHOLZ_SCORE_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    for (int i = 0; i < 3; i++)
    {
        runBuchholzSeries(team_list[5+i], team_list[10-i], series_length);
    }
    // OUTPUT
    stableSortTeams(team_list, 16, BUCHHOLZ_SCORE_DESC);
    stableSortTeams(team_list, 16, SERIES_DIFFERENTIAL_DESC);
    for (int i = 0; i < 2; i++)
    {
        team_list[i]->swiss_3_0_count++;
        team_list[i]->sixteen_system_placement_count[1]; // 1st and 2nd
        team_list[i]->sixteen_system_placement = 1;
        team_list[i]->eight_system_qualification_count++;
        team_list[i]->system_points = 6;
        qualified[i] = team_list[i];
    }
    for (int i = 2; i < 5; i++)
    {
        team_list[i]->swiss_3_1_count++;
        team_list[i]->sixteen_system_placement_count[4]; // 3rd through 5th
        team_list[i]->sixteen_system_placement = 4;
        team_list[i]->eight_system_qualification_count++;
        team_list[i]->system_points = 6;
        qualified[i] = team_list[i];
    }
    for (int i = 5; i < 8; i++)
    {
        team_list[i]->swiss_3_2_count++;
        team_list[i]->sixteen_system_placement_count[7]; // 6th through 8th
        team_list[i]->sixteen_system_placement = 7;
        team_list[i]->eight_system_qualification_count++;
        team_list[i]->system_points = 6;
        qualified[i] = team_list[i];
    }
    for (int i = 8; i < 11; i++)
    {
        team_list[i]->swiss_2_3_count++;
        team_list[i]->sixteen_system_placement_count[10]; // 9th through 11th
        team_list[i]->sixteen_system_placement = 10;
        team_list[i]->system_points = 5;
    }
    for (int i = 11; i < 14; i++)
    {
        team_list[i]->swiss_1_3_count++;
        team_list[i]->sixteen_system_placement_count[13]; // 12th through 14th
        team_list[i]->sixteen_system_placement = 13;
        team_list[i]->system_points = 4;
    }
    for (int i = 14; i < 16; i++)
    {
        team_list[i]->swiss_0_3_count++;
        team_list[i]->sixteen_system_placement_count[15]; // 15th and 16th
        team_list[i]->sixteen_system_placement = 15;
        team_list[i]->system_points = 3;
    }
    return 0;
}

int runBuchholzSeries(Team* upper, Team* lower, int series_length)
{
    runSeriesSimulation(upper, lower, series_length);
    
    upper->swiss_running_opponent_game_wins += lower->series_game_wins;
    upper->swiss_buchholz_score = upper->system_game_wins*upper->swiss_running_opponent_game_wins;

    lower->swiss_running_opponent_game_wins += upper->series_game_wins;
    lower->swiss_buchholz_score = lower->system_game_wins*lower->swiss_running_opponent_game_wins;

    return 0;
}

int runTiebreaker(Team* team_list[16], QualificationParameter qualification_parameter, int series_length, int number_of_teams_to_qualify, int trials, int output_mode)
{
    int tied_teams_count = 0;
    int tied_teams_to_qualify = 0;
    int tie_start = 0;
    int tie_stop = 4;
    
    switch (qualification_parameter)
    {
        case POINTS_QUALIFICATION:
            stableSortTeams(team_list, 16, SPLIT_POINTS_DESC);
            if (team_list[3]->split_points != team_list[4]->split_points)
            {
                return 0;
            }
            while(team_list[tie_start]->split_points != team_list[3]->split_points)
            {
                tie_start++;
            }
            while(team_list[tie_stop]->split_points == team_list[3]->split_points)
            {
                tie_stop++;
            }
            break;
        case AVG_PLACEMENT_QUALIFICATION:
            stableSortTeams(team_list, 16, SPLIT_TOURNAMENTS_PLACEMENT_ASC);
            while(team_list[tie_start]->split_tournaments_placement_weighted_sum != team_list[3]->split_tournaments_placement_weighted_sum)
            {
                tie_start++;
            }
            while(team_list[tie_stop]->split_tournaments_placement_weighted_sum == team_list[3]->split_tournaments_placement_weighted_sum)
            {
                tie_stop++;
            }
            break;
        default:
            break;
    }
    tie_stop--;
    tied_teams_count = tie_stop - tie_start + 1;
    tied_teams_to_qualify = 4 - tie_start;

    // POPULATE SINGLE-ELIM PLAYOFF-STYLE BRACKET WITH TIED TEAMS AND BYES
    Team* tiebreaker_playoff[16];
    Team* tiebreaker_quarter_final[8];
    Team* tiebreaker_semi_final[4];
    Team* tiebreaker_final[2];
    Team* tiebreaker_winner;

    int j = 0;
    for (int i = tie_start; i <= tie_stop; i++)
    {
        tiebreaker_playoff[j] = team_list[i];
        j++;
    }
    for (int i = tied_teams_count; i < 16; i++)
    {
        tiebreaker_playoff[i] = new Team;
        tiebreaker_playoff[i]->abbreviation = "BYE";
        tiebreaker_playoff[i]->rating = -9999;
        tiebreaker_playoff[i]->rating_deviation = 0;
    }
    // SIMULATE BRACKET WITH SPECIFIC SEED-BASED PLACEMENT RESULTS
    // ROUND OF 16
    for (int i = 0; i < 8; i++)
    {
        if (runSeriesSimulation(tiebreaker_playoff[i], tiebreaker_playoff[15-i], 7))
        {
            tiebreaker_quarter_final[i] = tiebreaker_playoff[i];
            tiebreaker_playoff[15-i]->tiebreaker_system_placement = 15-i;
        }
        else
        {
            tiebreaker_quarter_final[i] = tiebreaker_playoff[15-i];
            tiebreaker_playoff[i]->tiebreaker_system_placement = 15-i;
        }
    }
    // QUARTER FINALS
    for (int i = 0; i < 4; i ++)
    {
        if (runSeriesSimulation(tiebreaker_quarter_final[i], tiebreaker_quarter_final[7-i], 7))
        {
            tiebreaker_semi_final[i] = tiebreaker_quarter_final[i];
            tiebreaker_quarter_final[7-i]->tiebreaker_system_placement = 7-i;
        }
        else
        {
            tiebreaker_semi_final[i] = tiebreaker_quarter_final[7-i];
            tiebreaker_quarter_final[i]->tiebreaker_system_placement = 7-i;
        }
    }
    // SEMI FINALS
    for (int i = 0; i < 2; i ++)
    {
        if (runSeriesSimulation(tiebreaker_semi_final[i], tiebreaker_semi_final[3-i], 7))
        {
            tiebreaker_final[i] = tiebreaker_semi_final[i];
            tiebreaker_semi_final[3-i]->tiebreaker_system_placement = 3-i;
        }
        else
        {
            tiebreaker_final[i] = tiebreaker_semi_final[3-i];
            tiebreaker_semi_final[i]->tiebreaker_system_placement = 3-i;
        }
    }
    // GRAND FINAL
    if (runSeriesSimulation(tiebreaker_final[0], tiebreaker_final[1], 7))
    {
        tiebreaker_winner = tiebreaker_final[0];
        tiebreaker_final[0]->tiebreaker_system_placement = 0;
        tiebreaker_final[1]->tiebreaker_system_placement = 1;
    }
    else
    {
        tiebreaker_winner = tiebreaker_final[1];
        tiebreaker_final[1]->tiebreaker_system_placement = 0;
        tiebreaker_final[0]->tiebreaker_system_placement = 1;
    }
    // DELETE BYES
    for (int i = tied_teams_count; i < 16; i++)
    {
        delete tiebreaker_playoff[i];
    }
    
    return tied_teams_count;
}

std::string getEightSystemName(EightSystem sys)
{
    switch (sys)
    {
        case SYS8_NOT_REQ:
            return "NOT REQUIRED";
        case SYS8_SINGLE_ELIM:
            return "SINGLE ELIMINATION";
        case SYS8_AFL_FINAL_EIGHT:
            return "AFL FINAL EIGHT SYSTEM";
        default:
            return "INVALID EIGHT SYSTEM";
    }
}

std::string getSixteenSystemName(SixteenSystem sys)
{
    switch (sys)
    {
        case SYS16_SINGLE_ELIM:
            return "SINGLE ELIMINATION 16-to-1";
        case SYS16_DOUBLE_ELIM:
            return "DOUBLE ELIMINATION 16-to-1";
        case SYS16_GROUPS:
            return "FOUR-GROUP GROUPSTAGE AND ROUND 1 16-to-8";
        case SYS16_SWISS_GAME_DIF:
            return "SWISS WITH GAME DIFFERENTIAL TIEBREAKER 16-to-8";
        case SYS16_SWISS_BUCHHOLZ:
            return "SWISS WITH BUCHHOLZ TIEBREAKER 16-to-8";
        case SYS16_SWISS_TRUE_RATING:
            return "SWISS WITH TRUE RATING TIEBREAKER 16-to-8";
        default:
            return "INVALID SIXTEEN SYSTEM";
    }
}

std::string getTiebreakerSystemName(TiebreakerSystem sys)
{
    switch (sys)
    {
        case TB_SINGLE_ELIM:
            return "SINGLE ELIMINATION TOURNAMENT WITH BYES SEEDED BY LATEST RESULTS";
        case TB_INIT_SEED:
            return "INITIAL SEED";
        default:
            return "INVALID TIEBREAKER SYSTEM";
    }
}