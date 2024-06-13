#include "TournamentSimulator.h"

int runTournament(Team* team_list[16], SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, int trials, OutputType output_mode)
{
    Team* eight_system_team_list[8];
    for (int i = 0; i < trials; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            team_list[j]->tournament_points = 0;
            team_list[j]->system_points = 0;
        }
        switch(sixteen_system)
        {
            case SINGLE_ELIM16:
                break;
            case DOUBLE_ELIM16:
                break;
            case GROUPS16:
                break;
            case SWISS_GAME_DIFFERENTIAL16:
                runGameDifSwiss(team_list, eight_system_team_list, sixteen_system_series_length, 1, output_mode);
                break;
            case SWISS_BUCHHOLZ16:
                runBuchholzSwiss(team_list, eight_system_team_list, sixteen_system_series_length, 1, output_mode);
                break;
            case SWISS_TRUE_RATING16:
                break;
            default:
                break;
        }
        for (int j = 0; j < 16; j++)
        {
            team_list[j]->tournament_points += team_list[j]->system_points;
            team_list[j]->system_points = 0;
        }
        //printTeamOrder(team_list, 16);
        switch(eight_system)
        {
            case NOT_APPLICABLE8:
                break;
            case SINGLE_ELIM8:
                runSingleElimFinalEight(eight_system_team_list, eight_system_series_length, 1, output_mode);
                break;
            case AFL_FINAL_EIGHT:
                runAFLFinalEight(eight_system_team_list, eight_system_series_length, 1, output_mode);
                break;
            default:
                break;
        }
        if (eight_system == NOT_APPLICABLE8)
        {
            for (int j = 0; j < 16; j++)
            {
                team_list[j]->tournament_placement = team_list[j]->sixteen_system_placement;
            }
        }
        else
        {
            for (int j = 0; j < 8; j++)
            {
                team_list[j]->tournament_placement = team_list[j]->eight_system_placement;
            }
            for (int j = 8; j < 16; j++)
            {
                team_list[j]->tournament_placement = team_list[j]->sixteen_system_placement;
            }
        }
        for (int j = 0; j< 8; j++)
        {
            eight_system_team_list[j]->tournament_points += eight_system_team_list[j]->system_points;
            eight_system_team_list[j]->system_points = 0;
        }
    }
    return 0;
}

void tournamentOutputFormatted(Team* team_list[16], int trials)
{

}

void tournamentOutputRaw(Team* team_list[16], int trials)
{

}