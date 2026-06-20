#include "Logger.h"

void Enxytemp::Logger::InGameLog(const char* msg) {
    if (RE::ConsoleLog::GetSingleton()) RE::ConsoleLog::GetSingleton()->Print(msg);
}

void Enxytemp::Logger::Info(const std::string& msg) {
    SKSE::log::info(msg);
}

void Enxytemp::Logger::Setup() {
    auto logsFolder = SKSE::log::log_directory();
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);

    std::vector<spdlog::sink_ptr> sinks{
        std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true),
        std::make_shared<spdlog::sinks::msvc_sink_mt>()
    };

    auto logger = std::make_shared<spdlog::logger>(pluginName, sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::info);
    logger->flush_on(spdlog::level::info);
    spdlog::set_default_logger(logger);
}