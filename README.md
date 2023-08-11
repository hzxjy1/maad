<div align="center">

# Maad

一款基于[Maa项目](https://github.com/MaaAssistantArknights/MaaAssistantArknights)的linux cli客户端
</div>

## 使用方法

1.编译

    cd maad && mkdir build && cd build && cmake .. && make

2.添加配置文件config.json至可执行文件同级文件夹中

    {
    "switch": [
        "StartUp",
        "Fight",
        "Recruit",
        "Infrast",
        "Mall",
        "Award"
    ],
    "option": {
        "Core": ".",
        "UserDir": ".",
        "Resource": "./Resource",
        "device": "your android device",
        "task": "1-7"
    }
}


3.将libMaaCore.so放入/usr/lib内

4.通过参数启动,命令行参数会优先
    
    ./maad -d ${你的安卓设备ip} -t 1-7

## 其他

计划在下个版本添加配置文件，简化编译和启动步骤


