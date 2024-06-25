#ifndef TOURNAMENTSIMULATOR_H
#define TOURNAMENTSIMULATOR_H

#include "defs.h"
#include "teams.h"
#include "SeriesSimulator.h"
#include "SystemSimulator.h"

int runTournament(Team* team_list[16], SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, int trials, OutputMode output_mode);

void outputTournamentResults(Team* team_list[16], OutputMode output_mode, int output_depth, int trials, 
    SixteenSystem sixteen_system, int sixteen_system_series_length, EightSystem eight_system, int eight_system_series_length);

#endif