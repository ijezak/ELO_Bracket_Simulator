#ifndef SERIESSIMULATOR_H
#define SERIESSIMULATOR_H

#include <stdlib.h>
#include <random>
#include <ctime>

#include "teams.h"

bool runSeriesSimulation(Team* team_upper, Team* team_lower, int series_length);

#endif