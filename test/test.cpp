#include <iostream>
#include <fstream>
#include <string>
#include "jsoncpp/json/json.h"
#include "spdlog/spdlog.h"

void writeFileFromString(const std::string& filename, const std::string& body) {
    std::ofstream ofile(filename);
    ofile << body;
    ofile.close();
}

std::string readFileIntoString(const char* filename) {
    std::ifstream ifile(filename);
    if (!ifile.is_open()) {
        // std::cerr << "文件打开错误";
        spdlog::error("文件打开错误, {}!", "liuyu");
        return "";
    }
    std::ostringstream buf;
    char ch;
    while (buf && ifile.get(ch)) {
        buf.put(ch);
    }
    return buf.str();
}

Json::Value readJsonFile(const std::string& filename) {
    std::ifstream ifile(filename);
    if (!ifile.is_open()) {
        // std::cerr << "文件打开错误";
        spdlog::error("文件打开错误, {}!", "liuyu");
        return Json::Value();
    }
    
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;
    
    Json::Value root;
    std::string strerr;
    bool ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
    if (!ok) {
        // std::cerr << "json解析错误";
        spdlog::error("json解析出错, {}!", "liuyu");
        return Json::Value();
    }
    
    return root;
}

Json::Value readJsonFromString(const std::string& mystr) {
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;
    
    std::unique_ptr<Json::CharReader> charread(ReaderBuilder.newCharReader());
    
    Json::Value root;
    std::string strerr;
    bool isok = charread->parse(mystr.c_str(), mystr.c_str() + mystr.size(), &root, &strerr);
    if (!isok || !strerr.empty()) {
        // std::cerr << "json解析出错";
        spdlog::error("json解析出错, {}!", "liuyu");
        return Json::Value();
    }
    
    return root;
}

int main() {
    // 使用一个已经有数据的 json 对象
    Json::Value root;
    root = readJsonFile("./conf/cofig.json");
    
    // 第一种使用方法 get
    std::string ip = root["mysql"]["ip"].asString();
    std::cout << ip << std::endl;
    
    return 0;
}
