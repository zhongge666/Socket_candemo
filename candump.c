#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <net/if.h> 
#include <sys/socket.h>  
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "用法: %s <CAN通道名称>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *ifname = argv[1];
    int can_fd;

    // 创建CAN套接字
    can_fd = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if (can_fd < 0) {
        perror("打开套接字失败");
        return EXIT_FAILURE;
    }

    // 设置CAN套接字选项
    struct ifreq ifr;
    strcpy(ifr.ifr_name, ifname);
    ioctl(can_fd, SIOCGIFINDEX, &ifr);

    // 绑定CAN套接字到指定接口
    struct sockaddr_can addr;
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("绑定套接字失败");
        fprintf(stderr, "请确保 %s 存在并配置正确\n", ifname);
        close(can_fd);
        return EXIT_FAILURE;
    }

    // 准备CAN数据帧
    struct can_frame frame;

    printf("等待接收%s数据...\n", ifname);
    int frame_count = 0;
    while (1) {
        ssize_t nbytes = read(can_fd, &frame, sizeof(struct can_frame));

        if (nbytes < 0) {
            perror("读取数据帧失败");
            break;
        }

        // 获取CAN通道
        // 增加接收数据的计数器
        frame_count++;
        printf("【%d】", frame_count);
        printf(" %s  %X  [%d]  ", ifname, frame.can_id, frame.can_dlc);
        
        for (int i = 0; i < frame.can_dlc; ++i) {
            printf("%02X ", frame.data[i]);
            
        }

        printf("\n\n");
    }

    // 关闭CAN套接字
    close(can_fd);

    return EXIT_SUCCESS;
}
