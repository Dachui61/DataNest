#使用的编译器
CC=g++

#预处理参数
CPPFLAGS=-I./include	\
		-I/usr/include/fastdfs	\
		-I/usr/include/fastcommon	\
		-I/usr/local/include/hiredis/  \
		-I/usr/include/mysql/

#选项
CFLAGS=-Wall

# 需要链接的动态库
LIBS=-lfdfsclient	\
	 -lfastcommon	\
	 -lhiredis		\
	 -lfcgi         \
	 -lm            \
	 -lmysqlclient  \
	 -ljsoncpp

# 目录路径
TEST_PATH=test
COMMON_PATH=utils
CGI_BIN_PATH=bin
CGI_SRC_PATH=src


# 项目用
login=$(CGI_BIN_PATH)/login
reg=$(CGI_BIN_PATH)/reg

# 最终目标
target=$(login)	\
		$(reg)


ALL:$(target)

# =====================================================================
#							项目程序规则
# 登录
$(login):	$(CGI_SRC_PATH)/login_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o \
			$(COMMON_PATH)/util_cgi.o \
			$(COMMON_PATH)/des.o \
			$(COMMON_PATH)/base64.o \
			$(COMMON_PATH)/md5.o
	$(CC) $^ -o $@ $(LIBS)

# 注册
$(reg):	$(CGI_SRC_PATH)/reg_cgi.o \
			$(COMMON_PATH)/make_log.o  \
			$(COMMON_PATH)/cJSON.o \
			$(COMMON_PATH)/deal_mysql.o \
			$(COMMON_PATH)/redis_op.o  \
			$(COMMON_PATH)/cfg.o \
			$(COMMON_PATH)/util_cgi.o 
	$(CC) $^ -o $@ $(LIBS)
# =====================================================================



#######################################################################
#                         所有程序都需要的规则
# 生成所有的.o 文件
%.o:%.c
	$(CC) -c $< -o $@ $(CPPFLAGS) $(CFLAGS)

# 项目清除
clean:
	-rm -rf *.o $(target) $(TEST_PATH)/*.o $(CGI_SRC_PATH)/*.o $(COMMON_PATH)/*.o

# 声明伪文件
.PHONY:clean ALL
#######################################################################
