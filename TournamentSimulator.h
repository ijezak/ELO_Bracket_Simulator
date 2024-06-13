#ifndef TOURNAMENTSIMULATOR_H
#define TOURNAMENTSIMULATOR_H

#include "defs.h"
#include "teams.h"
#include "SeriesSimulator.h"
#include "SystemSimulator.h"

int runTournament(Team* team_list[16], SixteenSystem sixteen_system, int sixteen_system_series_length, 
    EightSystem eight_system, int eight_system_series_length, int trials, OutputType output_mode);

void tournamentOutputFormatted(Team* team_list[16], int trials);

void tournamentOutputRaw(Team* team_list[16], int trials);

#endif