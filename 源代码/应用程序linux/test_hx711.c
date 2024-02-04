#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
 
#define IIO_DEVICE "/sys/bus/iio/devices/iio:device0"
static int offset = 8363700;
static float scale = 406.0;
static float weight = 0;
float convert_to_weight(int sensor_data) {
    float weight;
    // 根据校准参数计算重量值
    weight = (float)(sensor_data - offset) / scale;
    return weight;
}
 
int main() {
    int fd;
    char buf[16];
    ssize_t num_read;
 
    // 打开iio设备文件
    fd = open(IIO_DEVICE "/in_voltage0_raw", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open iio device");
        return 1;
    }
 
    // 读取传感器数据
    num_read = read(fd, buf, sizeof(buf) - 1);
    if (num_read < 0) {
        perror("Failed to read sensor data");
        close(fd);
        return 1;
    }
 
    // 关闭设备文件
    close(fd);
 
    // 解析传感器数据
    buf[num_read] = '\0';
    int sensor_data = atoi(buf);
    weight = convert_to_weight(sensor_data);
    printf("Sensor data: %.0f\n", weight);
    return 0;
}