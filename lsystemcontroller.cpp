#include "lsystemcontroller.h"

LSystemController::LSystemController(QObject *parent) : QObject(parent)
{
}

void LSystemController::setLSystem(LSystem* lsystem)
{
    this->lsystem = lsystem;
    gen();
}

void LSystemController::setRules(Ruleset rules)
{
    lsystem->setRules(rules);
    gen();
}

void LSystemController::setDepth(int depth)
{
    if (!lsystem)
        return;

    if (depth < 0)
        depth = 0;

    if (this->depth != depth)
    {
        this->depth = static_cast<unsigned>(depth);
        gen();
    }
}

#include <QElapsedTimer>
#include <iostream>
void LSystemController::gen()
{
    QElapsedTimer t;
    t.start();
    lsystem->gen(depth);
    std::cout << t.elapsed() << std::endl;
    emit(lsystemGenerated());
}
