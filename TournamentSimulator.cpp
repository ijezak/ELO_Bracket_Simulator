#include "TournamentSimulator.h"

int runTournament(Team* team_list[16], SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, int trials, OutputMode output_mode)
{
    Team* eight_system_team_list[8];
    for (int i = 0; i < trials; i++)
    {
        // CLEAR TOURNAMENT VARIABLES
        for (int j = 0; j < 16; j++)
        {
            team_list[j]->most_recent_tournament_points = 0;
            team_list[j]->system_points = 0;
        }
        // SIMULATE SIXTEEN SYSTEM
        switch(sixteen_system)
        {
            case SYS16_SINGLE_ELIM:
                break;
            case SYS16_DOUBLE_ELIM:
                break;
            case SYS16_GROUPS:
                break;
            case SYS16_SWISS_GAME_DIF:
                runGameDifSwiss(team_list, eight_system_team_list, sixteen_system_series_length, 1, output_mode);
                break;
            case SYS16_SWISS_BUCHHOLZ:
                runBuchholzSwiss(team_list, eight_system_team_list, sixteen_system_series_length, 1, output_mode);
                break;
            case SYS16_SWISS_TRUE_RATING:
                break;
            default:
                break;
        }
        // UPDATE TOURNAMENT VARIABLES
        for (int j = 0; j < 16; j++)
        {
            team_list[j]->most_recent_tournament_points += team_list[j]->system_points;
            team_list[j]->system_points = 0;
        }
        // SIMULATE EIGHT SYSTEM
        switch(eight_system)
        {
            case SYS8_NOT_REQ:
                break;
            case SYS8_SINGLE_ELIM:
                runSingleElimFinalEight(eight_system_team_list, eight_system_series_length, 1, output_mode);
                break;
            case SYS8_AFL_FINAL_EIGHT:
                runAFLFinalEight(eight_system_team_list, eight_system_series_length, 1, output_mode);
                break;
            default:
                break;
        }
        // UPDATE TOURNAMENT VARIABLES
        for (int j = 0; j < 8; j++)
        {
            eight_system_team_list[j]->most_recent_tournament_points += eight_system_team_list[j]->system_points;
            eight_system_team_list[j]->system_points = 0;
        }
        // UPDATE CUMULATIVES
        if (eight_system == SYS8_NOT_REQ)
        {
            for (int j = 0; j < 16; j++)
            {
                team_list[j]->most_recent_tournament_placement = team_list[j]->sixteen_system_placement;
                team_list[j]->cumulative_tournament_placement_count[team_list[j]->sixteen_system_placement]++;
                team_list[j]->cumulative_tournament_points += team_list[j]->most_recent_tournament_points;
            }
        }
        else
        {
            for (int j = 0; j < 8; j++)
            {
                team_list[j]->most_recent_tournament_placement = team_list[j]->eight_system_placement;
                team_list[j]->cumulative_tournament_placement_count[team_list[j]->eight_system_placement]++;
                team_list[j]->cumulative_tournament_points += team_list[j]->most_recent_tournament_points;
            }
            for (int j = 8; j < 16; j++)
            {
                team_list[j]->most_recent_tournament_placement = team_list[j]->sixteen_system_placement;
                team_list[j]->cumulative_tournament_placement_count[team_list[j]->sixteen_system_placement]++;
                team_list[j]->cumulative_tournament_points += team_list[j]->most_recent_tournament_points;
            }
        }
    }
    // GET WEIGHTED SUMS OF CUMULATIVES
    stableSortTeams(team_list, 16, RATING_DESC);
    for (int i = 0; i < 16; i++)
    {
        team_list[i]->cumulative_tournament_placement_weighted_sum = 0;
        for (int j = 0; j < 16; j++)
        {
            team_list[i]->cumulative_tournament_placement_weighted_sum += (j + 1)*team_list[i]->cumulative_tournament_placement_count[j];
        }
    }
    // OUTPUT
    if (output_mode == OUTPUT_NONE)
    {
        return 0;
    }
    outputTournamentResults(team_list, output_mode, 1, trials, sixteen_system, sixteen_system_series_length, eight_system, eight_system_series_length);
    return 0;
}

void outputTournamentResults(Team* team_list[16], OutputMode output_mode, int output_depth, int trials, 
    SixteenSystem sixteen_system, int sixteen_system_series_length, EightSystem eight_system, int eight_system_series_length)
{
    std::cout << "\nTournament Simulation Complete.\n";
    std::cout << "    Simulation Trials: " << trials << "\n";
    std::cout << "    Final Sixteen System: " << getSixteenSystemName(sixteen_system) << "\n";
    std::cout << "        Series Length: " << sixteen_system_series_length << "\n";
    std::cout << "    Final Eight System: " << getEightSystemName(eight_system) << "\n";
    std::cout << "        Series Length: " << eight_system_series_length << "\n";
    std::cout << "\nResults:\n";

    if (output_mode == OUTPUT_FANCY)
    {
        std::cout << "    |  TEAM  | RATING |  TOP1  |  TOP2  |  TOP4  |  TOP8  |  TOP11  |  TOP14  |  TOP16  | AVG POS | AVG PTS |\n";
        for (int i = 0; i < 16; i++)
        {
            std::cout << "    | " << std::setw(6) << std::fixed << std::setprecision(0) << team_list[i]->abbreviation;
            std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(0) << team_list[i]->rating;
            std::cout << " | " << std::setw(5) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[0]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(5) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[1]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(5) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[3]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(5) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[7]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[10]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[13]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[15]/((double)trials/100) << "%";
            std::cout << " | " << std::setw(7) << std::fixed << std::setprecision(1) << (double)team_list[i]->cumulative_tournament_placement_weighted_sum/(double)trials;
            std::cout << " | " << std::setw(7) << std::fixed << std::setprecision(1) << (double)team_list[i]->cumulative_tournament_points/(double)trials;
            std::cout << " |\n";
        }
    }
    else if (output_mode == OUTPUT_CSV)
    {
        std::cout << "TEAM,RATING,TOP1,TOP2,TOP4,TOP8,TOP11,TOP14,TOP16,AVG POS,AVG PTS\n";
        for (int i = 0; i < 16; i++)
        {
            std::cout << std::setw(6) << std::fixed << std::setprecision(0) << team_list[i]->abbreviation;
            std::cout << "," << std::fixed << std::setprecision(0) << team_list[i]->rating;
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[0]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[1]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[3]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[7]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[10]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[13]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_tournament_placement_count[15]/((double)trials/100) << "%";
            std::cout << "," << std::fixed << std::setprecision(1) << (double)team_list[i]->cumulative_tournament_placement_weighted_sum/(double)trials;
            std::cout << "," << std::fixed << std::setprecision(1) << (double)team_list[i]->cumulative_tournament_points/(double)trials;
            std::cout << "\n";
        }
    }
}