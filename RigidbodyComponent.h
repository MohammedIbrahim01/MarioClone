#ifndef RIGIDBODYCOMPONENT_H
#define RIGIDBODYCOMPONENT_H

struct RigidbodyComponent
{
    float speed;
    float jumpHeight;
    bool canJump = false;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

#endif

