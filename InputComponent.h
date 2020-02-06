#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

enum Direction {NONE, RIGHT, LEFT, UP, DOWN, SPACE};

struct InputComponent
{
    Direction dir;
    Direction parallelDir;
};

#endif

