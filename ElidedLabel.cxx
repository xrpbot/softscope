#include "ElidedLabel.h"

void ElidedLabel::setText(const QString& text)
{
    fFullText = text;
    updateElidedText();
}

void ElidedLabel::resizeEvent(QResizeEvent* ev)
{
    updateElidedText();
    QLabel::resizeEvent(ev);
}

void ElidedLabel::updateElidedText()
{
    if(fontMetrics().width(fFullText) > width()) {
        QLabel::setText(fontMetrics().elidedText(fFullText, Qt::ElideRight, width()));
        setToolTip(fFullText);
    } else {
        QLabel::setText(fFullText);
        setToolTip(QString());
    }
}
