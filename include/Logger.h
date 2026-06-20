// Logger.h
#pragma once
#include "PCH.h"

namespace Enxytemp::Logger {
    void InGameLog(const char* msg);
    void Info(const std::string& msg);
    void Setup();
}
