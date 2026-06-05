#ifndef ENTITY_H
#define ENTITY_H

class Station;

class Entity
{
protected:
    int x;
    int y;

public:
    Entity(int x, int y);
    virtual ~Entity();

    int getX() const;
    int getY() const;

    void setPosition(int newX, int newY);

    virtual void update(Station& station) = 0;
    virtual char getSymbol() const = 0;
};

#endif#pragma once
