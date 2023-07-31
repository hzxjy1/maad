<div align="center">

# Maad

一款基于[Maa项目](https://github.com/MaaAssistantArknights/MaaAssistantArknights)的linux客户端

通过命令行对Maacore的调用，一键完成全部日常任务！

</div>

## 使用方法

~~应该没出错吧~~

1.编译

    cd maad && mkdir build && cd build && cmake .. && make

0.11版本需要在Asst.cpp中指定目录,Maacore会在此目录寻找resource/文件夹

    std::string Path ="/usr/share/maa-assistant-arknights-bin"; // 0.1.1请在此填写资源路径

并确保libMaaCore.so在/usr/lib内

2.通过参数启动
    
    maad -d ${你的安卓设备ip} -t 1-7

## 其他

计划在下个版本添加配置文件，简化编译和启动步骤


