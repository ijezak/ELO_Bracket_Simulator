#include "LeagueSimulator.h"

int main()
{
    const int trials = 1000000;
    Team* team_list[16];
    for (int i = 0; i < 16; i++)
    {
        team_list[i] = new Team;
    }
    loadSixteenTeamRealisticDistribution(team_list);

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < trials; i++)
    {
        runTournament(team_list, SWISS_GAME_DIFFERENTIAL16, 5, SINGLE_ELIM8, 7, 1, FORMATTED_OUTPUT);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Simulations complete. Execution time: " << duration_ms.count() << "\n";

    //runSplit(team_list, 4, 3, SWISS_GAME_DIFFERENTIAL16, 5, SINGLE_ELIM8, 7, SINGLE_ELIM_TB, 7, POINTS_QUALIFICATION, trials, FORMATTED_OUTPUT);

    /*runSplit(team_list, 4, 3, SWISS_GAME_DIFFERENTIAL16, 5, AFL_FINAL_EIGHT, 7, SINGLE_ELIM_TB, 7, POINTS_QUALIFICATION, trials, FORMATTED_OUTPUT);
    for (int i = 0; i < 16; i++)
    {
        team_list[i]->major1_qualification_count = 0;
        team_list[i]->cumulative_split_points = 0;
        team_list[i]->cumulative_split_placement_weighted_sum = 0;
        for (int j = 0; j < 16; j++)
        {
            team_list[i]->cumulative_split_placement_count[j] = 0;
        }
    }
    runSplit(team_list, 4, 3, SWISS_GAME_DIFFERENTIAL16, 5, AFL_FINAL_EIGHT, 7, SINGLE_ELIM_TB, 7, AVG_PLACEMENT_QUALIFICATION, trials, FORMATTED_OUTPUT);
    */

    return 0;
}