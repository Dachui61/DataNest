#include "CGIUtil.h"


// 去掉字符串左边的空白字符
std::string ltrim(const std::string &s) {
    auto start = std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    });
    return std::string(start, s.end());
}

// 去掉字符串右边的空白字符
std::string rtrim(const std::string &s) {
    auto end = std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(); //base 方法将反向迭代器转换为正常迭代器
    return std::string(s.begin(), end);
}

/**
 * @brief  去掉一个字符串两边的空白字符
 *
 * @param inbuf确保inbuf可修改
 *
 * @returns   
 *      0  成功
 *      -1 失败
 */
int trim(std::string& inbuf){
    inbuf = ltrim(rtrim(s));
    return 0;
}

/**
 * @brief  在字符串full_data中查找字符串substr第一次出现的位置
 *
 * @param full_data 	源字符串首地址
 * @param full_data_len 源字符串长度
 * @param substr        匹配字符串首地址
 *
 * @returns   
 *      成功: 匹配字符串首地址
 *      失败：NULL
 */
const char* find_substr(const char* full_data, size_t full_data_len, const char* substr){
    if (!full_data || !substr || full_data_len == 0) {
        return NULL;
    }

    size_t substr_len = std::strlen(substr);
    if (substr_len == 0) {
        return full_data;  // 如果匹配字符串为空，返回源字符串首地址
    }

    for (size_t i = 0; i <= full_data_len - substr_len; ++i) {
        if (std::strncmp(full_data + i, substr, substr_len) == 0) {
            return full_data + i;
        }
    }

    return NULL;
}

// 解析URL中参数到map里
std::unordered_map<std::string, std::string> parseQueryString(const std::string &query) {
    std::unordered_map<std::string, std::string> queryMap;
    std::istringstream queryStream(query);
    std::string keyValuePair;

    // 用 '&' 分割
    while (std::getline(queryStream, keyValuePair, '&')) {
        size_t pos = keyValuePair.find('=');
        if (pos != std::string::npos) {
            std::string key = keyValuePair.substr(0, pos);
            std::string value = keyValuePair.substr(pos + 1);
            queryMap[key] = value;
        }
    }

    return queryMap;
}


int getValueFromQuery(const std::string &query, const std::string &key,std::string &value) {
    std::unordered_map<std::string, std::string> queryMap = parseQueryString(query);

    auto it = queryMap.find(key);
    if (it != queryMap.end()) {
        value = it->second;
        return 0;
    } else {
        return -1; // Key not found
    }
}

int getFileSuffix(const std::string &file_name, std::string &suffix)
{
    // 使用 find_last_of('.') 查找文件名中最后一个点的位置
    size_t pos = file_name.find_last_of('.');

    // 如果找不到点（返回 std::string::npos）或者点在字符串的开始或结尾，返回 "null"
    if (pos == std::string::npos || pos == 0 || pos == file_name.length() - 1) {
        suffix = "null"; 
        return -1;
    }

    // 提取后缀
    std::string re = file_name.substr(pos + 1);

    // 检查后缀的有效性
    if (re.empty() || re.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") != std::string::npos) {
        suffix = "null"; // 如果后缀为空，或者后缀包含非字母数字字符，返回 "null"
        return -1;
    }

    suffix = re;
    return 0;
}

std::string replaceAll(std::string strSrc, const std::string &strFind, const std::string &strReplace)
{
    if (strFind.empty()) {
        return strSrc; // If strFind is empty, return the original string
    }

    size_t startPos = 0;
    while ((startPos = strSrc.find(strFind, startPos)) != std::string::npos) {
        strSrc.replace(startPos, strFind.length(), strReplace);
        startPos += strReplace.length(); // Advance position to avoid infinite loop
    }

    return strSrc;
}


