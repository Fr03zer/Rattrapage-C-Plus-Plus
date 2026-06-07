#include "Astronaut.h"
#include "Station.h"
#include <cstdlib>
#include <vector>

// Constructeur de l'astronaute
Astronaut::Astronaut(int x, int y) : Entity(x, y), oxygen(5), age(0)
{
}

// Vérifie si l'astronaute est mort
bool Astronaut::isDead() const {
    return oxygen <= 0;
}

// Getters
int Astronaut::getOxygen() const {
    return oxygen;
}

int Astronaut::getAge() const {
    return age;
}

char Astronaut::getSymbol() const {
    return 'S';
}

// Logique de mise à jour à chaque tour
void Astronaut::update(Station& station) {
    // 1. Perte d'oxygène au début du tour
    oxygen--;

    // 2. Respiration (si une réserve active est sur la même case)
    if (station.hasReserve(getX(), getY()))
    {
        oxygen += 3;
        station.consumeReserve(getX(), getY());
    }

    // 3. Déplacements aléatoires (Recherche des cases valides dans la grille)
    std::vector<std::pair<int, int>> moves;

    if (station.isInside(getX() - 1, getY())) moves.push_back({ getX() - 1, getY() });
    if (station.isInside(getX() + 1, getY())) moves.push_back({ getX() + 1, getY() });
    if (station.isInside(getX(), getY() - 1)) moves.push_back({ getX(), getY() - 1 });
    if (station.isInside(getX(), getY() + 1)) moves.push_back({ getX(), getY() + 1 });

    if (!moves.empty())
    {
        int r = rand() % moves.size();
        x = moves[r].first;
        y = moves[r].second;
    }

    // 4. Logique de reproduction / division (Âge >= 3 et Oxygène >= 6)
    if (age >= 3 && oxygen >= 6)
    {
        // On cherche une case adjacente TOTALEMENT vide (dans la grille, sans S et sans O)
        std::vector<std::pair<int, int>> emptyAdjacentCells;

        std::vector<std::pair<int, int>> neighbors = {
            {getX() - 1, getY()}, {getX() + 1, getY()},
            {getX(), getY() - 1}, {getX(), getY() + 1}
        };

        for (const auto& cell : neighbors) {
            if (station.isInside(cell.first, cell.second) &&
                !station.hasAstronaut(cell.first, cell.second) &&
                !station.hasReserve(cell.first, cell.second))
            {
                emptyAdjacentCells.push_back(cell);
            }
        }

        // S'il y a au moins une case libre, le bébé naît
        if (!emptyAdjacentCells.empty()) {
            int r = rand() % emptyAdjacentCells.size();

            // On demande à la station de créer l'astronaute sur cette case spécifique
            station.createAstronautNear(getX(), getY());
            

            oxygen -= 4; // Coût en oxygène de la reproduction
        }
    }

    // 5. Vieillissement
    age++;
}
