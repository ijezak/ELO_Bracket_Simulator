#include "defs.h"
#include "LeagueSimulator.h"

#include <chrono>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>

SixteenSystem getSixteenSystem(const std::string& sys)
{
    if (sys == "SINGLE_ELIM") return SYS16_SINGLE_ELIM;
    if (sys == "DOUBLE_ELIM") return SYS16_DOUBLE_ELIM;
    if (sys == "ROUND_ROBIN") return SYS16_GROUPS;
    if (sys == "SWISS_GAME_DIF") return SYS16_SWISS_GAME_DIF;
    if (sys == "SWISS_BUCH") return SYS16_SWISS_BUCHHOLZ;
    if (sys == "SIWSS_TRUE") return SYS16_SWISS_TRUE_RATING;
    return SYS16_INVALID;
}

EightSystem getEightSystem(const std::string& sys)
{
    if (sys == "SINGLE_ELIM") return SYS8_SINGLE_ELIM;
    if (sys == "AFL_FINAL_EIGHT") return SYS8_AFL_FINAL_EIGHT;
    return SYS8_INVALID;
}

OutputMode getOutputMode(const std::string& mode)
{
    if (mode == "CSV") return OUTPUT_CSV;
    if (mode == "FANCY") return OUTPUT_FANCY;
    return OUTPUT_INVALID;
}

ContainerLevel getContainerLevel(const std::string& lvl)
{
    if (lvl == "SPLIT") return LVL_SPLIT;
    if (lvl == "TOURNAMENT") return LVL_TOURNAMENT;
    return LVL_INVALID;
}

Team* parseTeam(const std::string& line) {
    Team* team = new Team();
    std::istringstream stream(line);
    std::string token;

    if (!std::getline(stream, token, ',')) {
        delete team;
        return nullptr;
    }
    team->name = token;

    if (!std::getline(stream, token, ',')) {
        delete team;
        return nullptr;
    }
    team->abbreviation = token;

    if (!std::getline(stream, token, ',')) {
        delete team;
        return nullptr;
    }
    team->rating = std::stof(token);

    if (!std::getline(stream, token, ',')) {
        delete team;
        return nullptr;
    }
    team->rating_deviation = std::stof(token);

    if (!std::getline(stream, token, ',')) {
        delete team;
        return nullptr;
    }
    team->initial_seed = std::stoi(token);

    return team;
}

bool readTeams(const std::string& filename, Team* teams[], int num_teams)
{
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    int index = 0;
    while (std::getline(infile, line) && index < num_teams)
    {
        Team* team = parseTeam(line);
        if (!team) 
        {
            std::cerr << "Error parsing line: " << line << std::endl;
            // Delete any preexisting teams
            for (int i = 0; i < index; ++i)
            {
                delete teams[i];
            }
            return false;
        }
        teams[index++] = team;
    }

    if (index != num_teams)
    {
        std::cerr << "Error: Expected " << num_teams << " teams, but got " << index << std::endl;
        // Delete all teams
        for (int i = 0; i < index; ++i)
        {
            delete teams[i];
        }
        return false;
    }

    return true;
}

void printUsageGuide()
{
    std::cout << std::endl;
    std::cout << "ELO Bracket Simulator v0.1 [https://github.com/ijezak/ELO_Bracket_Simulator]" << std::endl;
    std::cout << std::endl;
    std::cout << "Syntax: ./ELO_Bracket_Simulator [OPT]" << std::endl;
    std::cout << std::endl;
    std::cout << "-i [FILE]   : input file name (see: team_list_example.csv)" << std::endl;
    std::cout << "-o [FILE]   : output file name" << std::endl;
    std::cout << "-d [NUM]    : output depth (0 for results of outermost container only, +1 for results of each additional depth level; e.g. tournaments contain systems which contain series)" << std::endl;
    std::cout << "-f [TEXT]   : output format ('CSV' for comma-separated values, 'FANCY' for fancy table formatting)" << std::endl;
    std::cout << "-t [NUM]    : number of simulation trials" << std::endl;
    std::cout << "-s [TEXT]   : simulation level (options: SPLIT, TOURNAMENT, SYSTEM)" << std::endl;
    std::cout << "-a [TEXT]   : final eight system (options: SINGLE_ELIM, AFL_FINAL_EIGHT)" << std::endl;
    std::cout << "-A [NUM]    : final eight system series length (best of NUM) - must be positive odd number" << std::endl;
    std::cout << "-b [TEXT]   : final sixteen system (options: ROUND_ROBIN, SINGLE_ELIM, DOUBLE_ELIM, GROUPS, SWISS_GAME_DIF, SWISS_BUCH, SWISS_TRUE)" << std::endl;
    std::cout << "-B [NUM]    : final sixteen system series length (best of NUM) - must be positive odd number" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    const int num_teams = 16;
    Team* teams[num_teams] = {nullptr};

    int opt;
    int trials = 0;
    int output_depth = 0;
    OutputMode output_mode = OUTPUT_INVALID;
    ContainerLevel container_level = LVL_INVALID;
    int eight_system_series_length = 0;
    int sixteen_system_series_length = 0;
    char* input_file = nullptr;
    char* output_file = nullptr;
    EightSystem eight_system = SYS8_INVALID;
    SixteenSystem sixteen_system = SYS16_INVALID;
    bool eight_system_required = false;

    if (argc == 1)
    {
        printUsageGuide();
        return 1;
    }

    // GET OPTIONS
    while ((opt = getopt(argc, argv, "i:o:d:f:t:s:a:A:b:B:")) != -1) 
    {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'd':
                output_depth = std::atoi(optarg);
                break;
            case 'f': {
                std::string mode = optarg;
                output_mode = getOutputMode(mode);
                break;
            }
            case 't':
                trials = std::atoi(optarg);
                break;
            case 's': {
                std::string lvl = optarg;
                container_level = getContainerLevel(lvl);
                break;
            }
            case 'a': {
                std::string sys = optarg;
                eight_system = getEightSystem(sys); 
                break;
            }
            case 'A': {
                eight_system_series_length = atoi(optarg);
                break;
            }
            case 'b': {
                std::string sys = optarg;
                sixteen_system = getSixteenSystem(sys);
                break;
            }
            case 'B': {
                sixteen_system_series_length = atoi(optarg);
                break;
            }
            default:
                printUsageGuide();
                return 1;
        }
    }
    
    // CHECK OPTIONS
    {
        if (sixteen_system == SYS16_GROUPS || sixteen_system == SYS16_SWISS_GAME_DIF || sixteen_system == SYS16_SWISS_BUCHHOLZ || sixteen_system == SYS16_SWISS_TRUE_RATING)
        {
            eight_system_required = true;
        }
        if (trials < 1)
        {
            std::cerr << "Error: trials must be positive number" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (output_depth < 0)
        {
            std::cerr << "Error: output depth must be nonnegative number" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (output_mode == OUTPUT_INVALID)
        {
            std::cerr << "Error: invalid output mode" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (container_level == LVL_INVALID)
        {
            std::cerr << "Error: invalid container level" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (eight_system_required && eight_system == SYS8_INVALID) 
        {
            std::cerr << "Error: invalid eight system" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (eight_system_required && (eight_system_series_length < 1 || eight_system_series_length%2 == 0))
        {
            std::cerr << "Error: eight system series length must be positive odd number" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (sixteen_system == SYS16_INVALID) 
        {
            std::cerr << "Error: invalid sixteen system" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
        if (sixteen_system_series_length < 1 || sixteen_system_series_length%2 == 0)
        {
            std::cerr << "Error: sixteen system series length must be positive odd number" << std::endl;
            std::cerr << "For help, run with no options" << std::endl;
            return 1;
        }
    }

    // GET TEAMS FROM INPUT FILE
    if (!readTeams(input_file, teams, 16))
    {
        std::cerr << "Error reading teams." << std::endl;
        return 1;
    }

    // RUN SIMULATIONS
    auto start = std::chrono::high_resolution_clock::now();

    if (container_level == LVL_TOURNAMENT)
    {
        runTournament(teams, sixteen_system, sixteen_system_series_length, eight_system, eight_system_series_length, trials, output_mode);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Execution time: " << duration_ms.count() << " ms\n";

    return 0;
}
