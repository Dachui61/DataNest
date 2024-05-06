#include "MyLogger.h"

int main() {
    
    // //设置sink
    // std::vector<spdlog::sink_ptr> sinks;
    // //写文件必须要给权限 sudo
    // auto sink2 = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("./logs/cgi/2024/5/6/log.txt", 1024 * 1024 * 10, 100, false);
    // sink2->set_level(spdlog::level::debug);
    // sinks.push_back(sink2);

    // auto logger = std::make_shared<spdlog::logger>("service", begin(sinks), end(sinks));
    // // logger->set_level(spdlog::level::err);
    // spdlog::register_logger(logger);

    // spdlog::flush_every(std::chrono::seconds(1));
    // spdlog::flush_on(spdlog::level::debug);

    // logger->error("Hello, {}!", "World");
    LOG("TEST","test","这是一个{},我是{}","测试log","liuyu");

    return 0;
}
