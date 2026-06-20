#include "Config.h"

namespace Enxy {  
    void InitializeLogging() {  
        auto path = logger::log_directory();  
        if (!path) {  
            report_and_fail("Unable to lookup standard logging directory");  
        }  
          
        auto& factory = SKSE::log_directory();  
        *path /= std::format("{}.log", Plugin::NAME);  
          
        auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);  
        auto log = std::make_shared<spdlog::logger>("global log", std::move(sink));  
          
        log->set_level(spdlog::level::info);  
        log->flush_on(spdlog::level::info);  
          
        spdlog::set_default_logger(std::move(log));  
        spdlog::info("{} v{}", Plugin::NAME, Plugin::VERSION);  
    }  
}  