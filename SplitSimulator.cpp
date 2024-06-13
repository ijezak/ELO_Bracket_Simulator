#include "SplitSimulator.h"

int runSplit(Team* team_list[16], int number_of_qualifying_teams, int number_of_tournaments,
    SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, 
    TiebreakerSystem tiebreaker_system, int tiebreaker_system_series_length,
    QualificationParameter qualification_parameter,
    int trials, OutputType output_mode)
{
    Team* major_qualified[4];
    for (int i = 0; i < trials; i++)
    {
        // CLEAR SINGLE-SPLIT VARIABLES
        for (int j = 0; j < 16; j++)
        {
            team_list[j]->split_points = 0;
            team_list[j]->tournament_points = 0;
            team_list[j]->split_tournaments_placement_weighted_sum = 0;
        }

        // SIMULATE SPLITS
        stableSortTeams(team_list, 16, INIT_SEED_ASC);
        for (int j = 0; j < number_of_tournaments; j++)
        {
            runTournament(team_list, sixteen_system, sixteen_system_series_length, eight_system, eight_system_series_length, 1, output_mode);
            for (int k = 0; k < 16; k++)
            {
                team_list[k]->split_points += team_list[k]->tournament_points;
                team_list[k]->tournament_points = 0;
                team_list[k]->split_tournaments_placement_weighted_sum += team_list[k]->tournament_placement;
            }
            switch (qualification_parameter)
            {
                case POINTS_QUALIFICATION:
                    stableSortTeams(team_list, 16, SPLIT_POINTS_DESC);
                    break;
                case AVG_PLACEMENT_QUALIFICATION:
                    stableSortTeams(team_list, 16, SPLIT_TOURNAMENTS_PLACEMENT_ASC);
                    break;
            }
        }

        // TIEBREAKER
        switch (qualification_parameter)
        {
            case POINTS_QUALIFICATION:
                stableSortTeams(team_list, 16, INIT_SEED_ASC);
                stableSortTeams(team_list, 16, SPLIT_POINTS_DESC);
                runTiebreaker(team_list, qualification_parameter, tiebreaker_system_series_length, 4, 1, output_mode);
                stableSortTeams(team_list, 16, TIEBREAKER_PLACEMENT_ASC);
                stableSortTeams(team_list, 16, SPLIT_POINTS_DESC);
                break;
            case AVG_PLACEMENT_QUALIFICATION:
                stableSortTeams(team_list, 16, INIT_SEED_ASC);
                stableSortTeams(team_list, 16, SPLIT_TOURNAMENTS_PLACEMENT_ASC);
                runTiebreaker(team_list, qualification_parameter, tiebreaker_system_series_length, 4, 1, output_mode);
                stableSortTeams(team_list, 16, TIEBREAKER_PLACEMENT_ASC);
                stableSortTeams(team_list, 16, SPLIT_TOURNAMENTS_PLACEMENT_ASC);
                break;
            default:
                break;
        }
        
        // LOG CUMULATIVE RESULTS
        for (int j = 0; j < 16; j++)
        {
            if (j < number_of_qualifying_teams)
            {
                team_list[j]->major1_qualification_count++;
            }
            team_list[j]->cumulative_split_placement_count[j]++;
            team_list[j]->cumulative_split_points += team_list[j]->split_points;
        }
    }
    stableSortTeams(team_list, 16, RATING_DESC);
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            team_list[i]->cumulative_split_placement_weighted_sum += (j + 1)*team_list[i]->cumulative_split_placement_count[j];
        }
    }

    switch (output_mode)
    {
        case NO_OUTPUT:
            break;
        case RAW_OUTPUT:
            stableSortTeams(team_list, 16, RATING_DESC);
            outputSplitResultsRaw(team_list, number_of_qualifying_teams, number_of_tournaments, sixteen_system, sixteen_system_series_length,
            eight_system, eight_system_series_length, tiebreaker_system, tiebreaker_system_series_length, qualification_parameter, trials, output_mode);
            break;
        case FORMATTED_OUTPUT:
            stableSortTeams(team_list, 16, RATING_DESC);
            outputSplitResultsFormatted(team_list, number_of_qualifying_teams, number_of_tournaments, sixteen_system, sixteen_system_series_length,
            eight_system, eight_system_series_length, tiebreaker_system, tiebreaker_system_series_length, qualification_parameter, trials, output_mode);
            break;
        default:
            break;
    }

    return 0;
}

void outputSplitResultsRaw(Team* team_list[16],  int number_of_qualifying_teams, int number_of_tournaments,
    SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, 
    TiebreakerSystem tiebreaker_system, int tiebreaker_system_series_length,
    QualificationParameter qualification_parameter,
    int trials, OutputType output_mode)
{
    std::string sixteen_system_name;
    std::string eight_system_name;
    std::string tiebreaker_system_name;
    switch (sixteen_system)
    {
        case SINGLE_ELIM16:
            sixteen_system_name = "SINGLE ELIMINATION 16-to-1";
            break;
        case DOUBLE_ELIM16:
            sixteen_system_name = "DOUBLE ELIMINATION 16-to-1";
            break;
        case GROUPS16:
            sixteen_system_name = "FOUR-GROUP GROUPSTAGE AND ROUND 1 16-to-8";
            break;
        case SWISS_GAME_DIFFERENTIAL16:
            sixteen_system_name = "SWISS WITH GAME DIFFERENTIAL TIEBREAKER 16-to-8";
            break;
        case SWISS_BUCHHOLZ16:
            sixteen_system_name = "SWISS WITH BUCHHOLZ TIEBREAKER 16-to-8";
            break;
        case SWISS_TRUE_RATING16:
            sixteen_system_name = "SWISS WITH TRUE RATING TIEBREAKER 16-to-8";
            break;
    }
    switch (eight_system)
    {
        case NOT_APPLICABLE8:
            eight_system_name = "NOT APPLICABLE";
            break;
        case SINGLE_ELIM8:
            eight_system_name = "SINGLE ELIMINATION";
            break;
        case AFL_FINAL_EIGHT:
            eight_system_name = "AFL FINAL EIGHT SYSTEM";
            break;
    }
    switch (tiebreaker_system)
    {
        case SINGLE_ELIM_TB:
            tiebreaker_system_name = "SINGLE ELIMINATION TOURNAMENT WITH BYES SEEDED BY LATEST RESULTS";
            break;
        case INIT_SEED_TB:
            tiebreaker_system_name = "INITIAL SEED";
            break;
    }

    std::cout << "\nSimulation Complete.\n";
    std::cout << "    Simulation trials: " << trials << "\n";
    std::cout << "    Simulaton type: SPLIT\n";
    std::cout << "    Number of qualifier tournaments: " << number_of_tournaments << "\n";
    std::cout << "    Number of major tournament qualifying teams: " << number_of_qualifying_teams << "\n";
    std::cout << "    Qualifier tournament final sixteen system: " << sixteen_system_name << "\n";
    std::cout << "    Qualifier tournament final eight system: " << eight_system_name << "\n";
    std::cout << "    Final qualification tiebreaker system: " << tiebreaker_system_name << "\n";

    std::cout << "Simulation Results:\n";
    std::cout << "TEAM, RATING, MAJOR1 QUAL, MAJOR1 SEED1, MAJOR1 SEED2, MAJOR1 SEED3, MAJOR1 SEED4, AVG POINTS\n";
    for (int i = 0; i < 16; i++)
    {
        std::cout << std::setw(4) << std::fixed << std::setprecision(0) << team_list[i]->team_abbr;
        std::cout << "," << std::fixed << std::setprecision(0) << team_list[i]->rating_mean;
        std::cout << "," << std::fixed << std::setprecision(6) << (double)team_list[i]->major1_qualification_count/(trials);
        std::cout << "," << std::fixed << std::setprecision(6) << (double)team_list[i]->cumulative_split_placement_count[0]/(trials);
        std::cout << "," << std::fixed << std::setprecision(6) << (double)team_list[i]->cumulative_split_placement_count[1]/(trials);
        std::cout << "," << std::fixed << std::setprecision(6) << (double)team_list[i]->cumulative_split_placement_count[2]/(trials);
        std::cout << "," << std::fixed << std::setprecision(6) << (double)team_list[i]->cumulative_split_placement_count[3]/(trials);
        std::cout << "," << std::fixed << std::setprecision(2) << (double)team_list[i]->cumulative_split_points/trials;
        std::cout << "\n";
    }
}

void outputSplitResultsFormatted(Team* team_list[16],  int number_of_qualifying_teams, int number_of_tournaments,
    SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, 
    TiebreakerSystem tiebreaker_system, int tiebreaker_system_series_length,
    QualificationParameter qualification_parameter,
    int trials, OutputType output_mode)
{
    std::string sixteen_system_name;
    std::string eight_system_name;
    std::string tiebreaker_system_name;
    switch (sixteen_system)
    {
        case SINGLE_ELIM16:
            sixteen_system_name = "SINGLE ELIMINATION 16-to-1";
            break;
        case DOUBLE_ELIM16:
            sixteen_system_name = "DOUBLE ELIMINATION 16-to-1";
            break;
        case GROUPS16:
            sixteen_system_name = "FOUR-GROUP GROUPSTAGE AND ROUND 1 16-to-8";
            break;
        case SWISS_GAME_DIFFERENTIAL16:
            sixteen_system_name = "SWISS WITH GAME DIFFERENTIAL TIEBREAKER 16-to-8";
            break;
        case SWISS_BUCHHOLZ16:
            sixteen_system_name = "SWISS WITH BUCHHOLZ TIEBREAKER 16-to-8";
            break;
        case SWISS_TRUE_RATING16:
            sixteen_system_name = "SWISS WITH TRUE RATING TIEBREAKER 16-to-8";
            break;
    }
    switch (eight_system)
    {
        case NOT_APPLICABLE8:
            eight_system_name = "NOT APPLICABLE";
            break;
        case SINGLE_ELIM8:
            eight_system_name = "SINGLE ELIMINATION";
            break;
        case AFL_FINAL_EIGHT:
            eight_system_name = "AFL FINAL EIGHT SYSTEM";
            break;
    }
    switch (tiebreaker_system)
    {
        case SINGLE_ELIM_TB:
            tiebreaker_system_name = "SINGLE ELIMINATION TOURNAMENT WITH BYES SEEDED BY LATEST RESULTS";
            break;
        case INIT_SEED_TB:
            tiebreaker_system_name = "INITIAL SEED";
            break;
    }

    std::cout << "\nSimulation Complete.\n";
    std::cout << "    Simulation trials: " << trials << "\n";
    std::cout << "    Simulaton type: SPLIT\n";
    std::cout << "        Number of qualifier tournaments: " << number_of_tournaments << "\n";
    std::cout << "        Number of major tournament qualifying teams: " << number_of_qualifying_teams << "\n";
    std::cout << "        Inter-qualifier seeding method: SPLIT POINTS\n";
    std::cout << "        Qualifier tournament final sixteen system: " << sixteen_system_name << "\n";
    std::cout << "            Series length: " << sixteen_system_series_length << "\n";
    std::cout << "        Qualifier tournament final eight system: " << eight_system_name << "\n";
    std::cout << "            Series length: " << eight_system_series_length << "\n";
    std::cout << "        Final qualification tiebreaker system: " << tiebreaker_system_name << "\n";
    std::cout << "            Series length: " << tiebreaker_system_series_length << "\n";

    std::cout << "Simulation team Results:\n";
    //std::cout << "    | TEAM | RATING | MAJOR1 QUAL | MAJOR1 SEED1 | MAJOR1 SEED2 | MAJOR1 SEED3 | MAJOR1 SEED4 | AVG POINTS |\n";
    std::cout << "    | TEAM | RATING | QUALIFIED |   1st   |   2nd   |   3rd   |   4th   |   5th   |   6th   | POINTS | PLACEMENT |\n";
    for (int i = 0; i < 16; i++)
    {
        std::cout << "    | " << std::setw(4) << std::fixed << std::setprecision(0) << team_list[i]->team_abbr;
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(0) << team_list[i]->rating_mean;
        std::cout << " | " << std::setw(8) << std::fixed << std::setprecision(3) << (double)team_list[i]->major1_qualification_count/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(3) << (double)team_list[i]->cumulative_split_placement_count[0]/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(3) << (double)team_list[i]->cumulative_split_placement_count[1]/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(3) << (double)team_list[i]->cumulative_split_placement_count[2]/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(3) << (double)team_list[i]->cumulative_split_placement_count[3]/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(3) << (double)team_list[i]->cumulative_split_placement_count[4]/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(3) << (double)team_list[i]->cumulative_split_placement_count[5]/(trials/100) << "%";
        std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(1) << (double)team_list[i]->cumulative_split_points/trials;
        std::cout << " | " << std::setw(9) << std::fixed << std::setprecision(1) << (double)team_list[i]->cumulative_split_placement_weighted_sum/(double)trials;

        std::cout << " |\n";
    }

    /*int major1_qual_sumcheck = 0;
    int major1_seed1_sumcheck = 0;
    int major1_seed2_sumcheck = 0;
    int major1_seed3_sumcheck = 0;
    int major1_seed4_sumcheck = 0;
    int cumulative_split_points_sumcheck = 0;
    for (int i = 0; i < 16; i++)
    {
        major1_qual_sumcheck += team_list[i]->major1_qualification_count;
        major1_seed1_sumcheck += team_list[i]->split_placement_count[0];
        major1_seed2_sumcheck += team_list[i]->split_placement_count[1];
        major1_seed3_sumcheck += team_list[i]->split_placement_count[2];
        major1_seed4_sumcheck += team_list[i]->split_placement_count[3];
        cumulative_split_points_sumcheck += team_list[i]->cumulative_split_points;
    }
    std::cout << "    | " << std::setw(4) << std::fixed << std::setprecision(0) << "SUM";
    std::cout << " | " << std::setw(6) << std::fixed << std::setprecision(0) << " ";
    std::cout << " | " << std::setw(9) << std::fixed << std::setprecision(3) << (double)major1_qual_sumcheck/(trials/100) << " %";
    std::cout << " | " << std::setw(10) << std::fixed << std::setprecision(3) << (double)major1_seed1_sumcheck/(trials/100) << " %";
    std::cout << " | " << std::setw(10) << std::fixed << std::setprecision(3) << (double)major1_seed2_sumcheck/(trials/100) << " %";
    std::cout << " | " << std::setw(10) << std::fixed << std::setprecision(3) << (double)major1_seed3_sumcheck/(trials/100) << " %";
    std::cout << " | " << std::setw(10) << std::fixed << std::setprecision(3) << (double)major1_seed4_sumcheck/(trials/100) << " %";
    std::cout << " | " << std::setw(10) << std::fixed << std::setprecision(1) << (double)cumulative_split_points_sumcheck/trials;
    std::cout << " |\n";*/

    std::cout << "Additional Simulation Results:\n";
}

