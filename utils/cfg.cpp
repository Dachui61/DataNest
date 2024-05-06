/* -------------------------------------------*/
/**
 * @brief  从配置文件中得到相对应的参数
 *
 * @param profile   配置文件路径
 * @param tile      配置文件title名称[title]
 * @param key       key
 * @param value    (out)  得到的value
 *
 * @returns
 *      0 succ, -1 fail
 */
/* -------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include "jsoncpp/json/json.h"
#include "cfg.h"

void writeFileFromString(const std::string& filename, const std::string& body) {
    std::ofstream ofile(filename);
    ofile << body;
    ofile.close();
}

std::string readFileIntoString(const char* filename) {
    std::ifstream ifile(filename);
    if (!ifile.is_open()) {
        std::cerr << "文件打开错误";
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
        std::cerr << "文件打开错误";
        return Json::Value();
    }
    
    Json::CharReaderBuilder ReaderBuilder;
    ReaderBuilder["emitUTF8"] = true;
    
    Json::Value root;
    std::string strerr;
    bool ok = Json::parseFromStream(ReaderBuilder, ifile, &root, &strerr);
    if (!ok) {
        std::cerr << "json解析错误";
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
        std::cerr << "json解析出错";
        return Json::Value();
    }
    
    return root;
}


int get_cfg_value(const std::string& profile, const std::string& tile, const std::string& key, std::string&value){
    // 使用一个已经有数据的 json 对象
    Json::Value root;
    root = readJsonFile(profile);

    if(root.empty()) return -1;
    
    // 第一种使用方法 get
    value = root[tile][key].asString();
    // std::cout << value << std::endl;
    return 0;
}

//获取数据库用户名、用户密码、数据库标示等信息
int get_mysql_info(std::string& mysql_user, std::string& mysql_pwd, std::string& mysql_db){
    if (-1 == get_cfg_value(CFG_PATH, "mysql", "user", mysql_user))
    {
        // LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "mysql_user err\n");
        return -1;
    }

    if (-1 == get_cfg_value(CFG_PATH, "mysql", "password", mysql_pwd))
    {
        // LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "mysql_pwd err\n");
        return -1;
    }

    if (-1 == get_cfg_value(CFG_PATH, "mysql", "database", mysql_db))
    {
        // LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "mysql_db err\n");
        return -1;
    }

    return 0;
}


/**
 * 测试
*/
// int main() {
//     //mysql 数据库配置信息 用户名， 密码， 数据库名称
//     std::string mysql_user;
//     std::string mysql_pwd;
//     std::string mysql_db;

//     get_mysql_info(mysql_user, mysql_pwd, mysql_db);
//     std::cout << mysql_user << "," << mysql_pwd << "," << mysql_db << std::endl;
//     return 0;
// }

