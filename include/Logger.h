#pragma once
#include <string>

namespace Log {
    void Setup(const char* pluginName);  // Fungsi untuk inisialisasi awal
    void Info(const std::string& msg);
    void Error(const std::string& msg);
}