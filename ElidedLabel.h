#ifndef SSCOPE_ELIDEDLABEL_H
#define SSCOPE_ELIDEDLABEL_H

#include <QString>
#include <QLabel>

class ElidedLabel: public QLabel
{
  public:
    void setText(const QString& text);
    void resizeEvent(QResizeEvent* ev);
  
  private:
    void updateElidedText();
    
    QString fFullText;
};

#endif
