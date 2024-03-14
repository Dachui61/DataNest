#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

class ConfigParser {
public:
    ConfigParser(const std::string& filename) : filename_(filename) {}

    bool parseConfig() {
        std::ifstream configFile(filename_);
        if (!configFile.is_open()) {
            std::cerr << "Failed to open config file: " << filename_ << std::endl;
            return false;
        }

        try {
            configFile >> config_;
        } catch (const Json::Exception& e) {
            std::cerr << "Error parsing config file: " << e.what() << std::endl;
            configFile.close();
            return false;
        }

        configFile.close();
        return true;
    }

    std::string getRedisIP() const {
        return config_["redis"]["ip"].asString();
    }

    std::string getRedisPort() const {
        return config_["redis"]["port"].asString();
    }

    std::string getMySQLIP() const {
        return config_["mysql"]["ip"].asString();
    }

    std::string getMySQLPort() const {
        return config_["mysql"]["port"].asString();
    }

    std::string getMySQLDatabase() const {
        return config_["mysql"]["database"].asString();
    }

    std::string getMySQLUser() const {
        return config_["mysql"]["user"].asString();
    }

    std::string getMySQLPassword() const {
        return config_["mysql"]["password"].asString();
    }

    std::string getDFSClientConfPath() const {
        return config_["dfs_path"]["client"].asString();
    }

    std::string getWebServerIP() const {
        return config_["web_server"]["ip"].asString();
    }

    std::string getWebServerPort() const {
        return config_["web_server"]["port"].asString();
    }

    std::string getStorageWebServerIP() const {
        return config_["storage_web_server"]["ip"].asString();
    }

    std::string getStorageWebServerPort() const {
        return config_["storage_web_server"]["port"].asString();
    }

private:
    std::string filename_;
    Json::Value config_;
};

int main(){
    ConfigParser parser("../conf/config.json");
    if (!parser.parseConfig()) {
        std::cerr << "Failed to parse config file." << std::endl;
        return 1;
    }
    std::cout << "Redis IP: " << parser.getRedisIP() << std::endl;
    std::cout << "Redis Port: " << parser.getRedisPort() << std::endl;
    std::cout << "MySQL IP: " << parser.getMySQLIP() << std::endl;
    std::cout << "MySQL Port: " << parser.getMySQLPort() << std::endl;
    std::cout << "MySQL Database: " << parser.getMySQLDatabase() << std::endl;
    std::cout << "MySQL User: " << parser.getMySQLUser() << std::endl;
    std::cout << "MySQL Password: " << parser.getMySQLPassword() << std::endl;
    std::cout << "DFS Client Conf Path: " << parser.getDFSClientConfPath() << std::endl;
    std::cout << "Web Server IP: " << parser.getWebServerIP() << std::endl;
    std::cout << "Web Server Port: " << parser.getWebServerPort() << std::endl;
    std::cout << "Storage Web Server IP: " << parser.getStorageWebServerIP() << std::endl;
    std::cout << "Storage Web Server Port: " << parser.getStorageWebServerPort() << std::endl;

    return 0;
}