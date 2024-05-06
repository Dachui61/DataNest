#ifndef MYLOGGER_H
#define MYLOGGER_H

#include <string>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdarg>
#include <vector>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/daily_file_sink.h"

//写入内容
int out_put_file(const std::string& path, const std::string& buf);

//创建目录
int make_path(std::string& path, const std::string& module_name, const std::string& proc_name);

//创建目录并写入内容
std::shared_ptr<spdlog::logger> get_logger(const std::string& module_name, const std::string& proc_name, const std::string& filename,
                    int line, const std::string& funcname);

#define LOG(module_name, proc_name, ...) \
        do { \
            std::shared_ptr<spdlog::logger> logger = get_logger(module_name, proc_name, __FILE__, __LINE__, __FUNCTION__); \
            logger->error(__VA_ARGS__); \
        } while(0)

        

#endif
