#ifndef OXYGENRESERVE_H
#define OXYGENRESERVE_H

#include "Entity.h" 

class Station; 

class OxygenReserve : public Entity { 
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
