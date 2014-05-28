#ifndef SSCOPE_SCOPEWIDGET_H
#define SSCOPE_SCOPEWIDGET_H

#include "AvgDataReader.h"
#include "Channel.h"
#include <string>
#include <QWidget>
#include <QPaintEvent>
#include <QTimer>
#include <QPixmap>
#include <QMouseEvent>

class ScopeWidget : public QWidget
{
    Q_OBJECT
    
  public:
    ScopeWidget(const char* sourcename, QWidget *parent = 0, int tperdiv = 1);
    
    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    inline const Channel* channel(int ch) const
      { if(ch < 0 || ch >= N_CHANNELS) return NULL; return &fChannels[ch]; }
    inline Channel* channel(int ch)
      { if(ch < 0 || ch >= N_CHANNELS) return NULL; return &fChannels[ch]; }
    inline bool running()  { return fRunning; }
    
    void chParamsChanged();
    void setRunning(bool running);
    void setTicsPerDiv(int tperdiv);
    
    static const int N_CHANNELS = 4;
    
    std::string channelName(int ch) const { return fReader.header().chName(ch); }
    double channelAvg(int ch) const { return fReader.avg(ch); }
    float channelCurValue(int ch) const { return fReader.at(x2t(fCursorXPos), ch); }
    
    void setChannelAvgTime(int ch, double t) { fReader.setAvgTime(ch, t); }
    
    void mouseMoveEvent(QMouseEvent* ev);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

  public slots:
    void timestep();
    void setCursorEnabled(bool enable);
  
  signals:
    void headerChanged();
    void cursorMoved();
    void newData();

  protected:
    inline int ticsPerDiv() const    { return fTicsPerDiv; }
    inline int ticsPerScreen() const { return 10 * fTicsPerDiv; }
  
    void paintEvent(QPaintEvent* ev);
    void resizeEvent(QResizeEvent* ev);
    void generateGrid();
    void updateDisplay();
    void redrawDisplay();
    void drawRegion(QPainter& painter, int t1, int t2);
    float t2x(int t) const;
    int x2t(float x) const;
    float u2y(float u, float u_per_div, float offset) const;
    
    Channel fChannels[N_CHANNELS];
    QTimer* fTimer;
    bool fRunning;
    int fTicsPerDiv;
    AvgDataReader<float> fReader;
    int fLastHead;
    static const int UPDATE_INTERVAL;
    QPixmap fGridPixmap, fDisplayPixmap;
    
    int fCursorXPos;
    bool fDrawCursor, fCursorEnabled;
};

#endif
