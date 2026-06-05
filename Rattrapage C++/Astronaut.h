#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Entity.h" 

class Station;

class Astronaut : public Entity {
private:
    int oxygen;
    int age;

public:
    // Le constructeur prend uniquement x et y
    Astronaut(int x, int y);

    void update(Station& station) override;
    char getSymbol() const override;

    bool isDead() const;
    int getOxygen() const;
    int getAge() const;
};

#endif