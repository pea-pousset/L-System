#include "lsystem.h"
#include <stack>

#include <cstdlib>
#include <iostream>

LSystem::LSystem()
{
    setRules(RandomTree);
    //setRules(Tree1);
    //setRules(KochSnowflake);
}

LSystem::~LSystem()
{
    if (!segments.empty())
        segments.clear();
    if (plusangle)
        delete plusangle;
    if (minusangle)
        delete minusangle;
}

bool LSystem::setRules(Ruleset rules)
{
    this->rules = rules;
    return true;
}

void LSystem::gen(unsigned depth)
{
    if (plusangle)
        delete plusangle;
    if (minusangle)
        delete minusangle;
    plusangle = new RotationMatrix(-rules.angle);
    minusangle = new RotationMatrix(rules.angle);
    segments.clear();
    minx = maxx = miny = maxy = 0.0;
    gen(depth, rules.axiom, static_cast<int>(depth));
}

void LSystem::gen(unsigned depth, std::string str, int maxLineWidth)
{
    std::stack<Segment> stack;
    std::string next;
    Segment segment;
    segment.color = 0;
    segment.direction.y = 1.0;
    segment.lineWidth = maxLineWidth;
    bool pendown = true;

    for (unsigned i = 0; i < str.length(); ++i)
    {
        if (str[i] == 'F' || str[i] == 'X' || str[i] == 'Y' || str[i] == 'A' || str[i] == 'B')
        {
            bool draw = false;
            switch (str[i])
            {
                case 'F': next.append(rules.F); draw = (!depth && !rules.constants.F); break;
                case 'X': next.append(rules.X); draw = (!depth && !rules.constants.X); break;
                case 'Y': next.append(rules.Y); draw = (!depth && !rules.constants.Y); break;
                case 'A': next.append(rules.A); draw = (!depth && !rules.constants.A); break;
                case 'B': next.append(rules.B); draw = (!depth && !rules.constants.B); break;
                default: break;
            }

            if (draw)
            {
                if (pendown)
                    segments.push_back(segment);
                segment.origin += segment.direction;

                if (segment.origin.x > maxx)
                    maxx = segment.origin.x;
                if (segment.origin.x < minx)
                    minx = segment.origin.x;
                if (segment.origin.y > maxy)
                    maxy = segment.origin.y;
                if (segment.origin.y < miny)
                    miny = segment.origin.y;
            }
        }
        else if (str[i] == '[')
        {
            next += '[';
            if (!depth)
                stack.push(segment);
        }
        else if (str[i] == ']')
        {
            next += ']';
            if (!depth)
            {
                segment = stack.top();
                stack.pop();
            }
        }
        else if (str[i] == '>')
        {
            next += '>';
            if (!depth)
                segment.origin += segment.direction;
        }
        else if (str[i] == '+')
        {
            next += '+';
            if (!depth)
            {
                plusangle->transform(segment.direction);
                if (segment.lineWidth > 1)
                    --segment.lineWidth;
            }
        }
        else if (str[i] == '-')
        {
            next += '-';
            if (!depth)
            {
                minusangle->transform(segment.direction);
                if (segment.lineWidth > 1)
                    --segment.lineWidth;
            }
        }
        else if (str[i] == 'v')
        {
            next += 'v';
            if (!depth)
            {
                if (rand() % 2)
                    minusangle->transform(segment.direction);
                else
                    plusangle->transform(segment.direction);
                if (segment.lineWidth > 1)
                    --segment.lineWidth;

            }
        }
        else if (str[i] == 'w')
        {
            next += 'w';
            if (!depth)
            {
                int r = rand() % 3;
                if (r == 2)
                    minusangle->transform(segment.direction);
                else if (r == 1)
                    plusangle->transform(segment.direction);
                else
                {
                    segments.push_back(segment);
                    segment.origin += segment.direction;

                    if (segment.origin.x > maxx)
                        maxx = segment.origin.x;
                    if (segment.origin.x < minx)
                        minx = segment.origin.x;
                    if (segment.origin.y > maxy)
                        maxy = segment.origin.y;
                    if (segment.origin.y < miny)
                        miny = segment.origin.y;
                }

                if (segment.lineWidth > 1)
                    --segment.lineWidth;

            }
        }
        else if (isdigit(str[i]))
        {
            next += str[i];
            segment.color = static_cast<unsigned>(str[i] - '0');
        }
        else
            ; // Ignore
    }

    if (!depth)
        return;

    gen(depth-1, next, maxLineWidth);
}

