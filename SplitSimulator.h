#ifndef SPLITSIMULATOR_H
#define SPLITSIMULATOR_H

#include "defs.h"
#include "teams.h"
#include "SeriesSimulator.h"
#include "SystemSimulator.h"
#include "TournamentSimulator.h"

#include <iomanip>

int runSplit(Team* team_list[16],  int number_of_qualifying_teams, int number_of_tournaments,
    SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, 
    TiebreakerSystem tiebreaker_system, int tiebreaker_system_series_length,
    QualificationParameter qualification_parameter,
    int trials, OutputMode output_mode);

void outputSplitResultsRaw(Team* team_list[16],  int number_of_qualifying_teams, int number_of_tournaments,
    SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, 
    TiebreakerSystem tiebreaker_system, int tiebreaker_system_series_length,
    QualificationParameter qualification_parameter,
    int trials, OutputMode output_mode);

void outputSplitResultsFormatted(Team* team_list[16],  int number_of_qualifying_teams, int number_of_tournaments,
    SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, 
    TiebreakerSystem tiebreaker_system, int tiebreaker_system_series_length,
    QualificationParameter qualification_parameter,
    int trials, OutputMode output_mode);

#endif