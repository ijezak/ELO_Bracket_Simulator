#ifndef SYSTEMSIMULATOR_H
#define SYSTEMSIMULATOR_H

#include "defs.h"
#include "teams.h"
#include "SeriesSimulator.h"

#include <iomanip>

int runSingleElimFinalEight(Team* team_list[8], int series_length, int trials, OutputMode output_mode);

int runAFLFinalEight(Team* team_list[8], int series_length, int trials, OutputMode output_mode);

int runGameDifSwiss(Team* team_list[16], Team* qualified[8], int series_length, int trials, OutputMode output_mode);

int runBuchholzSwiss(Team* team_list[16], Team* qualified[8], int series_length, int trials, OutputMode output_mode);

int runBuchholzSeries(Team* upper, Team* lower, int series_length);

int runTiebreaker(Team* team_list[16], QualificationParameter qualification_parameter, int series_length, 
    int number_of_teams_to_qualify, int trials, int output_mode);

std::string getEightSystemName(EightSystem sys);

std::string getSixteenSystemName(SixteenSystem sys);

std::string getTiebreakerSystemName(TiebreakerSystem sys);


#endif