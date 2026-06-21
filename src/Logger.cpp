#include "Logger.h"

#include <spdlog/sinks/basic_file_sink.h>

void Log::Setup(const char* pluginName) {
    auto logDir = SKSE::log::log_directory();
    if (!logDir) return;

    auto logFilePath = *logDir / std::format("{}.log", pluginName);
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto logger = std::make_shared<spdlog::logger>(pluginName, std::move(fileSink));

    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::info);
    spdlog::set_default_logger(std::move(logger));
}

void Log::Info(const std::string& msg) {
    SKSE::log::info("{}", msg);
    if (auto console = RE::ConsoleLog::GetSingleton()) {
        console->Print(msg.c_str());
    }
}

void Log::Error(const std::string& msg) {
    SKSE::log::error("{}", msg);
    if (auto console = RE::ConsoleLog::GetSingleton()) {
        console->Print(("ERROR: " + msg).c_str());
    }
}