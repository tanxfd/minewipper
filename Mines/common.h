#ifndef COMMON_H
#define COMMON_H

class COMMON
{
public:
    enum DIFFICULTY
    {
        LOW_DIFF = 0,
        MEDIUM_DIFF = 1,
        HIGH_DIFF = 2,
        CUSTOM_DIFF = 3
    };

    enum LOW_DIFF
    {
        LOW_ROW_COL = 9,
        LOW_MINENUMS = 10
    };

    enum MEDIUM_DIFF
    {
        MEDIUM_ROW_COL = 16,
        MEDIUM_MINENUMS = 40

    };

    enum HIGH_DIFF
    {
        HIGH_ROW = 16,
        HIGH_COL = 30,
        HIGH_MINENUMS = 99
    };

    enum MAPSET
    {
        MAPWIDTH = 25,
        MAPHEIGHT = 25
    };
};

#endif // COMMON_H
