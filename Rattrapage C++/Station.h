#ifndef STATION_H
#define STATION_H

#include <vector>
#include <string>

#include "Astronaut.h"
#include "OxygenReserve.h"

class Station
{
private:
    int rows;
    int cols;

    std::vector<Astronaut> astronauts;
    std::vector<OxygenReserve> reserves;

public:
    Station();

    bool loadFromFile(const std::string& filename);

    void simulate(int iterations);

    void display();

    void saveResult(const std::string& filename);

    bool isInside(int x, int y);

    bool hasReserve(int x, int y);

    bool hasAstronaut(int x, int y);

    void consumeReserve(int x, int y);

    void createAstronautNear(int x, int y);

    void createReserveNear(int x, int y);
};

#endif
