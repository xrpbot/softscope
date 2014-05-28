#include "HeaderReader.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdint.h>

const uint32_t SSCOPE_HEADER_MAGIC = 0x7FD85250;

int do_read(int fd, char* buf, int len)
{
    if(fd < 0)
        return -1;
    
    fd_set fds;
    struct timeval tv;
    int res;
    
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    
    res = select(fd+1, &fds, NULL, NULL, &tv);
    if(res < 0) {
        perror("select()");
        return -1;
    }
    
    if(!FD_ISSET(fd, &fds))
        return 0;
    
    res = read(fd, buf, len);
    if(res < 0) {
        perror("read()");
        return -1;
    } else if(res == 0) {
        // fHadEOF = true;
    }
    
    return res;
}

HeaderReader::HeaderReader()
{
    reset();
}

void HeaderReader::reset()
{
    fChunkId = 0;
    fLen = 4;
    fFinished = false;
    fLeftover = 0;
    fBufPos = 0;
}

void HeaderReader::readAll(int fd)
{
    fBufPos += do_read(fd, &fBuf[fBufPos], fLen-fBufPos);
    if(fBufPos == fLen) {
        processChunk();
        fBufPos = 0;
    }
}

// State machine to parse the header
void HeaderReader::processChunk()
{
    if(fChunkId == 0) { // Magic
        uint32_t magic = *((uint32_t*)fBuf);
        printf("Magic: %08X\n", magic);
        fLen = 4;
        if(magic != SSCOPE_HEADER_MAGIC) {
            fFinished = true;
            fLeftover = 4;
        }
    } else if(fChunkId == 1) { // Version
        printf("Version: %08X\n", *((uint32_t*)fBuf));
        fLen = 1;
    } else if(fChunkId <= 9) {
        if((fChunkId % 2) == 0) { // String length
            fLen = *((uint8_t*)fBuf);
            printf("Len: %zd\n", fLen);
        } else {
            int ch = (fChunkId-2)/2;
            fBuf[fLen] = 0;
            printf("Channel %d: %s\n", ch, fBuf);
            fChNames[ch] = fBuf;
            fLen = 1;
        }
        
        if(fChunkId == 9)
            fFinished = true;
    } else {
        fFinished = true;
    }
    fChunkId++;
}
