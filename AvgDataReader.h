#ifndef SSCOPE_AVGDATAREADER_H
#define SSCOPE_AVGDATAREADER_H

#include "IIRLowpass.h"
#include "DataReader.h"

/* Data reader maintaining an IIR lowpass filtered average for each channel.
   The IIR calculation uses double, so T must be convertible to double. */

template <typename T>
class AvgDataReader: public DataReader<T>
{
  public:
    AvgDataReader(const char* fname, int bufsize, int channels)
        : DataReader<T>(fname, bufsize, channels)
    {
        fIIRLowpass = new IIRLowpass[DataReader<T>::fNChannels];
        for(size_t ch=0; ch<DataReader<T>::fNChannels; ch++) {
            fIIRLowpass[ch].setTau(1000.);
        }
    }
    
    ~AvgDataReader()
        { delete[] fIIRLowpass; }
    
    double avg(size_t ch) const
        { if(ch >= DataReader<T>::fNChannels) return 0.; return fIIRLowpass[ch].output(); }
    
    void setAvgTime(size_t ch, double tau)
        { if(ch < DataReader<T>::fNChannels) fIIRLowpass[ch].setTau(tau); }
    
    virtual void processData(size_t head, size_t n_new_chunks) {
        for(size_t t = (head + 1 - n_new_chunks); t <= head; t++) {
            for(size_t ch=0; ch<DataReader<T>::fNChannels; ch++) {
                fIIRLowpass[ch].input(DataReader<T>::at(t, ch));
            }
        }
    }
    
  private:
    IIRLowpass *fIIRLowpass;
};

#endif
