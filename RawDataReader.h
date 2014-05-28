#ifndef SSCOPE_RAWDATAREADER_H
#define SSCOPE_RAWDATAREADER_H

#include <QFile>
#include "HeaderReader.h"

class RawDataReader {
  public:
    RawDataReader(const char* fname, int bufsize, int chunksize);
    ~RawDataReader();
    inline int head()  { return fHead; }
    inline bool checkAndClearReset()
        { bool ret = fHadReset; fHadReset = false; return ret; }
    void reset(int bufsize = -1);
    bool readAll();
    const char* atRaw(int t) const;
    
    void readHeader();
    const HeaderReader& header() const { return fHeaderReader; }
    
    virtual void processData(size_t, size_t) {}
    
  private:
    int do_read(char* buf, int len);
    
    int fFd;
    char* fBuf;
    int fBufsize;    // total buffer size in bytes
    int fNChunks;    // total buffer size in chunks
    int fChunksize;  // size of one chunk in bytes
    int fBufPos;     // buffer index for next byte to be read
    int fHead;       // id of newest available chunk
    bool fHadEOF;    // true after end-of-file (read() returns 0)
    bool fHadReset;  // true after new data stream has begun
    
    HeaderReader fHeaderReader;
};

#endif
