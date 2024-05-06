#include "MyLogger.h"


int out_put_file(const std::string& path, const std::string& buf)
{
    

    return 0;
}

int make_path(std::string& path, const std::string& module_name, const std::string& proc_name) {
    time_t t;
    struct tm *now = nullptr;
    std::string top_dir = ".";
    std::string second_dir = "./logs";
    std::string third_dir;
    std::string y_dir;
    std::string m_dir;
    std::string d_dir;
    time(&t);
    now = localtime(&t);
    path = "./logs/" + module_name + "/" + std::to_string(now->tm_year + 1900) + "/" +
           std::to_string(now->tm_mon + 1) + "/" + proc_name + "-" + std::to_string(now->tm_mday) + ".log";

    third_dir = second_dir + "/" + module_name;
    y_dir = third_dir + "/" + std::to_string(now->tm_year + 1900) + "/";
    m_dir = y_dir + "/" + std::to_string(now->tm_mon + 1) + "/";
    d_dir = m_dir + "/" + std::to_string(now->tm_mday) + "/";

    // 创建目录
    if(access(top_dir.c_str(), 0) == -1) {
        if(mkdir(top_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "create %s failed!\n", top_dir.c_str());
        } else if(mkdir(second_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", top_dir.c_str(), second_dir.c_str());
        } else if(mkdir(third_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", top_dir.c_str(), third_dir.c_str());
        } else if(mkdir(y_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", top_dir.c_str(), y_dir.c_str());
        } else if(mkdir(m_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", top_dir.c_str(), m_dir.c_str());
        }
    } else if(access(second_dir.c_str(), 0) == -1) {
        if(mkdir(second_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "create %s failed!\n", second_dir.c_str());
        } else if(mkdir(third_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", second_dir.c_str(), third_dir.c_str());
        } else if(mkdir(y_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", second_dir.c_str(), y_dir.c_str());
        } else if(mkdir(m_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", second_dir.c_str(), m_dir.c_str());
        }
    } else if(access(third_dir.c_str(), 0) == -1) {
        if(mkdir(third_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "create %s failed!\n", third_dir.c_str());
        } else if(mkdir(y_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", third_dir.c_str(), y_dir.c_str());
        } else if(mkdir(m_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", third_dir.c_str(), m_dir.c_str());
        } 
    } else if (access(y_dir.c_str(), 0) == -1) {
        if(mkdir(y_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "create %s failed!\n", y_dir.c_str());
        } else if(mkdir(m_dir.c_str(), 0777) == -1) {
            fprintf(stderr, "%s:create %s failed!\n", y_dir.c_str(), m_dir.c_str());
        } 
    } else if (access(m_dir.c_str(), 0) == -1) {
        if(mkdir(m_dir.c_str(), 0777)) {
            fprintf(stderr, "create %s failed!\n", m_dir.c_str());
        } 
    }

    return 0;
}

// 创建目录并写入内容
std::shared_ptr<spdlog::logger> get_logger(const std::string& module_name, const std::string& proc_name, const std::string& filename,
                    int line, const std::string& funcname)
{   

    std::string filepath;

    // 创建目录路径 这里会获取路径信息
    make_path(filepath, module_name, proc_name);

    //设置sink
    std::vector<spdlog::sink_ptr> sinks;
    //写文件必须要给权限 sudo
    auto sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filepath, 1024 * 1024 * 10, 100, false);
    sink->set_level(spdlog::level::err);
    sinks.push_back(sink);

    //设置log名称
    std::ostringstream bufStream;
    std::string buf;
    bufStream << filename << ":" << line ;
    buf = bufStream.str();
    auto logger = std::make_shared<spdlog::logger>(buf, std::begin(sinks), std::end(sinks));
    return logger;
}
