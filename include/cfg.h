#ifndef _CFG_H_
#define _CFG_H_

#define CFG_PATH    "./conf/config.json" //配置文件路径

#define CFG_LOG_MODULE "cgi"
#define CFG_LOG_PROC   "cfg"

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
// extern int get_cfg_value(const char *profile, char *tile, char *key, char *value);
extern int get_cfg_value(const std::string& profile, const std::string& tile, const std::string& key, std::string&value);

//获取数据库用户名、用户密码、数据库标示等信息
// extern int get_mysql_info(char *mysql_user, char *mysql_pwd, char *mysql_db);
extern int get_mysql_info(std::string& mysql_user, std::string& mysql_pwd, std::string& mysql_db);


#endif
