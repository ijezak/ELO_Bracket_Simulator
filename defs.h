#ifndef DEFS_H
#define DEFS_H

enum OutputMode
{
    OUTPUT_INVALID,
    OUTPUT_NONE,
    OUTPUT_CSV,
    OUTPUT_FANCY
};

enum ContainerLevel
{
    LVL_INVALID,
    LVL_SERIES,
    LVL_SYSTEM,
    LVL_TOURNAMENT,
    LVL_SPLIT,
    LVL_SEASON
};

enum SortType
{
    INIT_SEED_ASC,
    RATING_DESC,
    GAME_DIFFERENTIAL_DESC,
    SERIES_DIFFERENTIAL_DESC,
    BUCHHOLZ_SCORE_DESC,
    SPLIT_POINTS_DESC,
    TIEBREAKER_PLACEMENT_ASC,
    SPLIT_TOURNAMENTS_PLACEMENT_ASC
};

enum SixteenSystem
{
    SYS16_INVALID,
    SYS16_SINGLE_ELIM,
    SYS16_DOUBLE_ELIM,
    SYS16_GROUPS,
    SYS16_SWISS_GAME_DIF,
    SYS16_SWISS_BUCHHOLZ,
    SYS16_SWISS_TRUE_RATING
};

enum EightSystem
{
    SYS8_INVALID,
    SYS8_NOT_REQ,
    SYS8_SINGLE_ELIM,
    SYS8_AFL_FINAL_EIGHT
};

enum TiebreakerSystem
{
    TB_SINGLE_ELIM,
    TB_INIT_SEED
};

enum QualificationParameter
{
    POINTS_QUALIFICATION,
    AVG_PLACEMENT_QUALIFICATION
};

enum InterQualifierSeeding
{
    IQS_INIT_SEED,
    IQS_MOST_RECENT_TOURNAMENT_PLACEMENT,
    IQS_SPLIT_POINTS,
    IQS_AVG_PLACEMENT
};

#endif