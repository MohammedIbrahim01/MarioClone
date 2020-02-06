#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
    virtual void Update(float dt, sf::RenderWindow& window) = 0;
};

#endif

