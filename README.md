What is ELO Bracket Simulator?

This program runs simulations of tournament brackets with provided (or generated) team lists to estimate result probabilities for teams or evaluate and compare tournament formats.
The program simulates results using an ELO-based approach -- that is, it assumes that a team's performance may be modelled as a random variable with gaussian distribution centered
around their rating and a variance which reflects that teams variability (defined as 200 in ELO). The program takes a list of teams with names, ratings, standard deviations, and
initial seeds, and simulates series (best ofs), systems (e.g. swiss system 16-to-8, double-elimination, etc.), tournaments, or even entire seasons (multiple tournaments,
inter-tournament seeding rules, tiebreakers for qualification at the end of season) for a given number of trials and outputs the results to console or output file in a table or
as a csv. The program is written in C++ using a procedural coding approach and is designed to be extremely fast; running 100,000 trials of a sixteen-team tournament with a 
complex format takes only a couple seconds. 

What tournament formats are supported?

Currently supported formats include round robin, group stage formats, single-elimination, double-elimination, various swiss systems, and the AFL Final Eight system, with more on 
the way. Tournaments formats are supplied by providing a 16-team system, which may be wither 16-to-8 or 16-to-1, and additionally providing an 8-team system in the case of a 
16-to-8 system. 

How can this be used to evaluate and compare formats?

Questions like "What is better at determining the best 4 teams in a league? A split consisting of three tournaments which each use a best-of-5 game-differential Swiss for 16-to-8
and a best-of-7 single-elimination for 8-to-1 using a point system? Or a best-of-7 round robin with a single best-of-7 double-elimination tournament seeded by the round robin?" 
are often debated and are practically impossible to answer when neither format is clearly better, and so debate consists largely of speculation. This program aims to use simulation 
to quantify the performance of different formats when modelling team perfomance using ELO. For example, this program can be used to demonstrate that double-elimination outperforms 
swiss into single elimination when round 1 seeding is ideal, but loses badly to swiss into single elimination when round 1 seeding is poor. This program can therefore be used to 
determine the strengths and weaknesses of different formats to allow tournament designers to be more informed and design more effective tournaments.

Future plans

- finish user interface to allow all existing funcitonality to be utilized
- support more formats and format combinations
- parallelization
- improve GLICKO support
- allow ELO calculation from list of results with various formulas

How to compile:

g++ main.cpp LeagueSimulator.cpp SplitSimulator.cpp TournamentSimulator.cpp SystemSimulator.cpp SeriesSimulator.cpp teams.cpp -o ELO_Bracket_Simulator

How to run:

ELO Bracket Simulator v0.1 [https://github.com/ijezak/ELO_Bracket_Simulator]

Syntax: ./ELO_Bracket_Simulator [OPT]

-i [FILE]   : input file name (see: team_list_example.csv)
-o [FILE]   : output file name
-d [NUM]    : output depth (0 for results of outermost container only, +1 for results of each additional depth level; e.g. tournaments contain systems which contain series)
-f [TEXT]   : output format ('CSV' for comma-separated table, 'FANCY' for fancy formatting)
-t [NUM]    : number of simulation trials
-s [TEXT]   : simulation level (options: SPLIT, TOURNAMENT, SYSTEM)
-a [TEXT]   : final eight system (options: SINGLE_ELIM, AFL_FINAL_EIGHT)
-A [NUM]    : final eight system series length (best of NUM) - must be positive odd number
-b [TEXT]   : final sixteen system (options: ROUND_ROBIN, SINGLE_ELIM, DOUBLE_ELIM, GROUPS, SWISS_GAME_DIF, SWISS_BUCH, SWISS_TRUE)
-B [NUM]    : final sixteen system series length (best of NUM) - must be positive odd number
