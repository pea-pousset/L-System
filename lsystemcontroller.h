#ifndef LSYSTEMCONTROLLER_H
#define LSYSTEMCONTROLLER_H

#include <QObject>
#include "lsystem.h"

class LSystemController : public QObject
{
    Q_OBJECT
public:
    explicit LSystemController(QObject *parent = nullptr);
    void setLSystem(LSystem* lsystem);
    void setRules(Ruleset rules);

signals:
    void lsystemGenerated();

public slots:
    // - set F rule
    // - set X rule
    // - set axiom ?
    // - set angle
    // - set size
    void setDepth(int depth);

private:
    LSystem* lsystem = nullptr;
    unsigned depth = 0;
    void gen();
};

#endif // LSYSTEMCONTROLLER_H
