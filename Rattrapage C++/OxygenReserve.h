#ifndef OXYGENRESERVE_H
#define OXYGENRESERVE_H

#include "Entity.h" // <-- IMPORTANT : Est-ce bien "Entity.h" ou "Entite.h" ?

class Station; // Déclaration anticipée

class OxygenReserve : public Entity { // <-- Si c'est rouge ici, le problème est dans Entity.h
private:
    int concentration;

public:
    OxygenReserve(int x, int y, int c = 2);

    void update(Station& station) override;
    int getConcentration() const;
    void consume();
    char getSymbol() const override;
};

#endif