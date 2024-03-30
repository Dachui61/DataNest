// #include "cfg.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <fstream>
// #include <memory>

// extern "C"
// {
// #include "cJSON.h"
// #include "make_log.h"
// }

// int get_cfg_value(const char *profile, const char *title, const char *key, char *value)
// {
//     int ret = 0;

//     // 异常处理 阻断NULL和nullptr
//     if (profile == nullptr || title == nullptr || key == nullptr)
//     {
//         return -1;
//     }

//     // 只读打开文件
//     std::ifstream infile(profile);
//     if (!infile.is_open())
//     {
//         perror("ifstream");
//         LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "ifstream err\n");
//         return -1;
//     }

//     infile.seekg(0, std::ios::end); // 光标移动到末尾
//     long size = infile.tellg();     // 获取文件大小
//     infile.seekg(0, std::ios::beg); // 光标移动到开头

//     std::unique_ptr<char[]> buf(new char[size + 1]); // 使用 unique_ptr 来管理内存
//     infile.read(buf.get(), size);
//     buf[size] = '\0'; // 添加字符串结束符

//     // 解析一个json字符串为cJSON对象
//     cJSON *root = cJSON_Parse(buf.get());
//     if (nullptr == root)
//     {
//         LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "root err\n");
//         ret = -1;
//         infile.close();
//         return ret;
//     }

//     // 返回指定字符串对应的json对象
//     cJSON *father = cJSON_GetObjectItem(root, title);
//     if (nullptr == father)
//     {
//         LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "father err\n");
//         ret = -1;
//         infile.close();
//         return ret;
//     }

//     cJSON *son = cJSON_GetObjectItem(father, key);
//     if (nullptr == son)
//     {
//         LOG(CFG_LOG_MODULE, CFG_LOG_PROC, "son err\n");
//         ret = -1;
//         infile.close();
//         return ret;
//     }

//     strcpy(value, son->valuestring); // 拷贝内容

//     cJSON_Delete(root); // 删除json对象

//     infile.close();
//     return ret;
// }

// int get_mysql_info(char *mysql_user, char *mysql_pwd, char *mysql_db)
// {
//     return 0;
// }


