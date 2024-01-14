# Socket_candemo
SocketCAN 数据收发Demo，帮助你二次开发，代码简单易懂


1. SocketCAN Demo

该仓库包含用于发送和接收 CAN 数据帧的简单 SocketCAN 示例程序。在使用这些程序之前，请确保已安装 libsocketcan-dev 库。

2. 安装

要安装 libsocketcan-dev，请在终端中运行以下命令：

sudo apt-get update
sudo apt-get install libsocketcan-dev

3. 编译

使用以下命令编译示例程序：

make

这将生成名为 cansend 和 candump 的可执行文件。

4. 使用

   4.1. 发送数据帧

   使用以下命令发送 CAN 数据帧：

   ./cansend <CAN通道> <标识符> <数据>

   例如：

   ./cansend can0 123 1122334455667788

   4.2. 接收数据帧

   使用以下命令接收 CAN 数据帧：

   ./candump <CAN通道>

   例如：

   ./candump can0

5. 清理

要清理生成的可执行文件，使用以下命令：

make clean
