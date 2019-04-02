#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <vector>
#include "vector.h"
#include "rotationmatrix.h"

struct Segment
{
    Vector   origin;
    Vector   direction;
    int      lineWidth;
    unsigned color;
};

struct Bounds
{
    double left;
    double bottom;
    double right;
    double top;
};

struct RulesetConsts
{
    bool F;
    bool X;
    bool Y;
    bool A;
    bool B;
};

struct Ruleset
{
    std::string axiom;
    RulesetConsts constants;
    std::string F;
    std::string X;
    std::string Y;
    std::string A;
    std::string B;
    int angle;
};

// circle : A -> A+A
const Ruleset KochSnowflake =
{
    "5+++F++++F++++F",
    { false, false, false, false, false },
    "F--F++++F--F",
    "",
    "",
    "",
    "",
    30
};

const Ruleset Tree1 =
{
    "+X",
    { false, true, false, false, false },
    "FF",
    "1F+[[X]-X]-1F[4-FX]+X",
    "",
    "",
    "",
    25
};

const Ruleset RandomTree =
{
    "X",
    { false, true, false, false, false},
    "FF",
    "1F+[[X]-X]-[3vF[4vFX]][1vF[4vFX]]+X",
    "",
    "",
    "",
    20
};

const Ruleset Tree2 =
{
    "F",
    { false, false, false, false, false },
    "1FF-[2-F+F+F]+[3+F-F-F]",
    "",
    "",
    "",
    "",
    22
};

class LSystem
{
public:
    LSystem();
    virtual ~LSystem();

    bool setRules(Ruleset rules);
    Ruleset getRules()                  { return rules; }
    void gen(unsigned depth);
    std::vector<Segment>& getSegments() { return segments; }
    Bounds getBounds()                  { return { minx, miny, maxx, maxy }; }

private:
    Ruleset rules;
    std::vector<Segment> segments;
    RotationMatrix* plusangle = nullptr;
    RotationMatrix* minusangle = nullptr;
    double minx, maxx, miny, maxy;

    void gen(unsigned depth, std::string str, int maxLineWidth);
};

#endif // LSYSTEM_H
