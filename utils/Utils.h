// ---------------------------
// utils/Logger.h
// ---------------------------
#pragma once
#include "cocos2d.h"

namespace utils {
    class Logger {
    public:
        static void log(const std::string& message);
        static void error(const std::string& message);
    };
}