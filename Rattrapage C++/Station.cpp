#include "Station.h"
#include "Astronaut.h"     
#include "OxygenReserve.h" 
#include <fstream>
#include <iostream>
#include <algorithm>       

Station::Station() {
    rows = 0;
    cols = 0;
}

bool Station::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file)
        return false;

    file >> rows >> cols;

    // Gestion robuste : Vérification d'une grille vide ou incohérente
    if (rows <= 0 || cols <= 0)
        return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            char c;
            file >> c;

            if (c == 'S')
                astronauts.push_back(Astronaut(i, j));
            else if (c == 'O')
                reserves.push_back(OxygenReserve(i, j, 2)); // Initialisé à 2 par défaut
        }
    }

    return true;
}

bool Station::isInside(int x, int y) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

bool Station::hasReserve(int x, int y) {
    for (auto& r : reserves)
        if (r.getX() == x && r.getY() == y && r.getConcentration() > 0)
            return true;

    return false;
}

bool Station::hasAstronaut(int x, int y) {
    for (auto& a : astronauts)
        if (a.getX() == x && a.getY() == y)
            return true;

    return false;
}

void Station::consumeReserve(int x, int y) {
    for (auto& r : reserves)
    {
        if (r.getX() == x && r.getY() == y)
            r.consume();
    }
}

// AJUSTEMENT : On crée directement aux coordonnées x, y validées libres
void Station::createAstronautNear(int x, int y) {
    if (isInside(x, y))
        astronauts.push_back(Astronaut(x, y));
}

// AJUSTEMENT : On crée directement la réserve de concentration 2 aux coordonnées x, y libres
void Station::createReserveNear(int x, int y) {
    if (isInside(x, y))
        reserves.push_back(OxygenReserve(x, y, 2));
}

void Station::display() {
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, '0'));

    for (auto& r : reserves)
        if (r.getConcentration() > 0)
            grid[r.getX()][r.getY()] = 'O';

    for (auto& a : astronauts)
        grid[a.getX()][a.getY()] = 'S';

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            std::cout << grid[i][j] << " ";

        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Station::simulate(int iterations) {
    for (int i = 0; i < iterations; i++)
    {
        std::cout << "--- ITERATION " << (i + 1) << " ---" << std::endl;

        // 1. Mise à jour des astronautes
        // Note : On utilise une boucle classique par index car les astronautes 
        // peuvent aussi déclencher des push_back indirects via createAstronautNear
        size_t currentAstronautsCount = astronauts.size();
        for (size_t a = 0; a < currentAstronautsCount; ++a) {
            astronauts[a].update(*this);
        }

        // 2. Mise à jour des réserves d'oxygène
        // On utilise une boucle par index pour éviter l'invalidation des itérateurs en mémoire
        size_t currentReservesCount = reserves.size();
        for (size_t r = 0; r < currentReservesCount; ++r) {
            reserves[r].update(*this);
        }

        // 3. Nettoyage : suppression des astronautes morts
        astronauts.erase(
            std::remove_if(astronauts.begin(), astronauts.end(),
                [](Astronaut& a) { return a.isDead(); }),
            astronauts.end());

        // 4. Nettoyage : suppression des réserves vides (concentration == 0)
        reserves.erase(
            std::remove_if(reserves.begin(), reserves.end(),
                [](OxygenReserve& r) { return r.getConcentration() <= 0; }),
            reserves.end());

        // 5. Affichage (Mode Console exigé à chaque itération)
        display();

        // Condition d'arrêt : si tous les astronautes sont morts
        if (astronauts.empty()) {
            std::cout << "Tous les astronautes sont morts. Arret de la simulation." << std::endl;
            break;
        }
    }
}

// AJUSTEMENT DU MODE FICHIER : Écrit la grille finale complète conforme aux specs
void Station::saveResult(const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return;

    // Écrit d'abord la taille de la grille
    out << rows << " " << cols << "\n";

    // Construit la grille finale
    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols, '0'));

    for (auto& r : reserves)
        if (r.getConcentration() > 0)
            grid[r.getX()][r.getY()] = 'O';

    for (auto& a : astronauts)
        grid[a.getX()][a.getY()] = 'S';

    // Écrit la grille dans le fichier
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            out << grid[i][j];
            if (j < cols - 1) out << " ";
        }
        out << "\n";
    }
}