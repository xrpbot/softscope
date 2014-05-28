#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <string.h>

const uint32_t SSCOPE_HEADER_MAGIC = 0x7FD85250;
const uint32_t SSCOPE_HEADER_VERSION = 0x00000001;

const char* CHANNEL_NAMES[] = { "Sine, 10k, 1/10 rad/div, Füü",
                                "Sine, 5k, 1/8 rad/div",
                                "Sine, 14k, 1/15 rad/div",
                                "Sine, 8k, 1/25 rad/div" };

int main(int argc, char** argv)
{
    int fd;
    fd = open("softscope.fifo", O_WRONLY);
    if(fd < 0) {
        perror("Open softscope.fifo");
        return -1;
    }
    
    if(argc > 1) {
        if(write(fd, &SSCOPE_HEADER_MAGIC, sizeof(SSCOPE_HEADER_MAGIC)) != sizeof(SSCOPE_HEADER_MAGIC)) {
            perror("Write header");
        }
        
        if(write(fd, &SSCOPE_HEADER_VERSION, sizeof(SSCOPE_HEADER_VERSION)) != sizeof(SSCOPE_HEADER_VERSION)) {
            perror("Write header");
        }
        
        for(size_t i=0; i<4; i++) {
            uint8_t len = strlen(CHANNEL_NAMES[i]);
            if(write(fd, &len, sizeof(len)) != sizeof(len)) {
                perror("Write header");
            }
            if(write(fd, CHANNEL_NAMES[i], len) != len) {
                perror("Write header");
            }
        }
    }
    
    float data[4];
    int t;
    while(1) {
        data[0] = ((float) sin((float)t / 10.) * 10000.);
        data[1] = ((float) sin((float)t / 8.) * 5000.);
        data[2] = ((float) sin((float)t / 15.) * 14000.);
        data[3] = ((float) sin((float)t / 25.) * 8000.);
        
        if(write(fd, &data, sizeof(data)) != sizeof(data)) {
            perror("Write to file");
            break;
        }
        t++;
        usleep(10000); // 10 ms
    }
    
    if(close(fd) < 0) {
        perror("Close softscope.fifo");
        return -1;
    }
    
    return 0;
}
