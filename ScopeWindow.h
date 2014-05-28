#ifndef SSCOPE_SCOPEWINDOW_H
#define SSCOPE_SCOPEWINDOW_H

#include <QWidget>
#include <QSignalMapper>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include "ScopeWidget.h"

class ScopeWindow : public QWidget
{
  Q_OBJECT
  
  public:
    ScopeWindow(const char* sourcename);
  
  public slots:
    void channelEnableChanged(int ch);
    void channelScaleChanged(int ch);
    void channelOffsetChanged(int ch);
    void channelAvgTimeChanged(int id);
    void runPauseButton();
    void timeScaleChanged();
    
    void channelNamesChanged();
    void channelAvgChanged();
    void channelCurValueChanged();
  
  private:
    void makeChannelCfg(QGridLayout* l, int ch, QSignalMapper* enableMapper, QSignalMapper *scaleMapper, QSignalMapper* offsetMapper, QSignalMapper* avgTimeMapper);
    void makeTimeCfg(QGridLayout* l, int col);
    
    static const int U_PER_DIV_CHOICES[];
    static const int U_PER_DIV_DEFAULT, U_PER_DIV_WIDTH;
    static const int T_PER_DIV_CHOICES[];
    static const int T_PER_DIV_DEFAULT, T_PER_DIV_WIDTH;
    static const double AVG_TIME_CHOICES[];
    
    ScopeWidget *fScopeWidget;
    QCheckBox* fEnableWidgets[ScopeWidget::N_CHANNELS];
    QComboBox* fScaleWidgets[ScopeWidget::N_CHANNELS];
    QSpinBox* fOffsetWidgets[ScopeWidget::N_CHANNELS];
    QLabel* fChNameWidgets[ScopeWidget::N_CHANNELS];
    QLabel* fChAvgWidgets[ScopeWidget::N_CHANNELS];
    QLabel* fChCurWidgets[ScopeWidget::N_CHANNELS];
    QPushButton* fRunPauseButton;
    QComboBox* fTimeScaleWidget;
    QTimer* fTimer;
};

#endif
