#ifndef SSCOPE_HEADERREADER_H
#define SSCOPE_HEADERREADER_H

#include <string>
#include <cstddef>

class HeaderReader
{
  public:
    HeaderReader();
    
    void reset();
    void readAll(int fd);
    void processChunk();
    
    bool finished() const { return fFinished; }
    
    std::string chName(size_t ch) const
        { if(ch >= 4) return std::string(""); return fChNames[ch]; }
    
    // Access to data left over after parsing
    size_t leftoverData() const { return fLeftover; }
    const char* data() const { return fBuf; }
    
  private:
    std::string fChNames[4];
    
    char fBuf[257];
    size_t fBufPos;
    
    size_t fLen;
    bool fFinished;
    int fChunkId;
    size_t fLeftover;
};

#endif
