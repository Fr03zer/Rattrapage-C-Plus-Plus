#include "Entity.h"

Entity::Entity(int x, int y)
    : x(x), y(y)
{
}

Entity::~Entity()
{
}

int Entity::getX() const
{
    return x;
}

int Entity::getY() const
{
    return y;
}

void Entity::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}