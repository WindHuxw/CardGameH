#ifndef LEVEL_CONFIG_H
#define LEVEL_CONFIG_H
//还没用上
#include <vector>

struct LevelConfig {
    int levelId;
    int cardCount;
    std::vector<int> cardNumbers;
};

#endif