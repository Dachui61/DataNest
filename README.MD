# 一个通用的文件存储管理系统
## 这个之前是想用于空间管理系统，用来保存会议室里监控录制的视频文件，现在想把这个模块抽离出来做一个通用的文件存储管理系统
# 为什么取这个名字呢？
DataNest：结合了 "数据" 和 "巢穴" 的概念，暗示着一个安全、舒适的数据存储空间。


json解析这里使用了jsoncpp，jsoncpp是一个开源的C++库
## jsoncpp安装
ubuntu apt安装比较简单：
'''
sudo apt-get install libjsoncpp-dev
'''

日志管理这里使用了spdlog
https://github.com/gabime/spdlog
