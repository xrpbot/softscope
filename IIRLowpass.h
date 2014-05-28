#ifndef SSCOPE_IIRLOWPASS_H
#define SSCOPE_IIRLOWPASS_H

class IIRLowpass {
  public:
    IIRLowpass() : fAlpha(1.0), fy(0.) {}
    
    void setTau(double tau) { fAlpha = 1./(1. + tau); }
    
    void reset() { fy = 0.; }
    void input(double x) { fy = fAlpha*x + (1.-fAlpha)*fy; }
    double output() { return fy; }
    
  private:
    double fAlpha;
    double fy;
};

#endif
