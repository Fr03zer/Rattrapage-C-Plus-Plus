#include "OxygenReserve.h"
#include "Station.h"
#include <vector>

// Constructeur : transmet les coordonnées x et y à la classe de base Entity
OxygenReserve::OxygenReserve(int x, int y, int c)
    : Entity(x, y), concentration(c)
{
}

// Getter pour la concentration
int OxygenReserve::getConcentration() const {
    return concentration;
}

// Consomme la réserve d'oxygène (demandé par le sujet : passe à 0 quand un astronaute est là)
void OxygenReserve::consume() {
    concentration = 0;
}

// Retourne le symbole pour l'affichage de la grille
char OxygenReserve::getSymbol() const {
    return 'O';
}

// Méthode de mise à jour autonome de la réserve à chaque itération
void OxygenReserve::update(Station& station) {
    int currentX = getX();
    int currentY = getY();

    // RÈGLE 1 : Si un astronaute marche dessus, elle est consommée immédiatement et passe à 0
    if (station.hasAstronaut(currentX, currentY)) {
        consume();
        return; // Elle a été vidée, on s'arrête là pour ce tour
    }

    // RÈGLE 2 : Régénération (Si concentration entre 1 et 4 et pas d'astronaute)
    if (concentration > 0 && concentration < 5) {
        concentration++;
    }

    // RÈGLE 3 : Diffusion (Si concentration == 5, diffuse sur une case adjacente vide)
    if (concentration == 5) {
        // Liste des 4 directions possibles (Haut, Bas, Gauche, Droite)
        std::vector<std::pair<int, int>> directions = {
            {currentX - 1, currentY}, // Haut
            {currentX + 1, currentY}, // Bas
            {currentX, currentY - 1}, // Gauche
            {currentX, currentY + 1}  // Droite
        };

        for (const auto& dir : directions) {
            int targetX = dir.first;
            int targetY = dir.second;

            // On vérifie si la case est dans la grille et totalement vide
            if (station.isInside(targetX, targetY) &&
                !station.hasAstronaut(targetX, targetY) &&
                !station.hasReserve(targetX, targetY))
            {
                // On crée une nouvelle réserve de concentration 2 sur cette case vide
                station.createReserveNear(currentX, currentY);
              

                break; 
            }
        }
    }
}
