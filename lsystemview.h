#ifndef LSYSTEMVIEW_H
#define LSYSTEMVIEW_H

#include <QWidget>
#include "lsystem.h"

class LSystemView : public QWidget
{
    Q_OBJECT

public:
    explicit LSystemView(QWidget *parent = nullptr);
    void setLSystem(LSystem* lsystem);
    void setBoldLines(bool boldLines) { this->boldLines = boldLines; }
    void setCorrectTrunks(bool correctTrunks) { this->correctTrunks = correctTrunks; }
    virtual int heightForWidth(int w) const { return w; }

protected:
    virtual void paintEvent(QPaintEvent*);
    virtual void resizeEvent(QResizeEvent*);

private:
    LSystem* lsystem = nullptr;
    QColor colors[10];
    bool boldLines = true;
    bool correctTrunks = true;
};

#endif // LSYSTEMVIEW_H
