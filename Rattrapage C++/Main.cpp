#include <iostream>

#include "Station.h"
#include "FileManager.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout
            << "Usage : programme fichier.txt"
            << std::endl;
        return 1;
    }

    Station station;

    if (!station.loadFromFile(argv[1]))
    {
        std::cout
            << "Erreur lecture fichier"
            << std::endl;
        return 1;
    }

    station.simulate(10);

    // Exemple dans ton Main.cpp (après la simulation)
    std::string inputFilename = argv[1]; // Ex: "input.txt"

    // On extrait le nom pour créer "input_result.txt"
    std::string outputFilename = inputFilename.substr(0, inputFilename.find_last_of('.')) + "_result.txt";

    station.saveResult(outputFilename);
    std::string result =
        FileManager::createOutputName(argv[1]);

    station.saveResult(result);

    return 0;
    std::cout << "argc = " << argc << std::endl;

    if (argc >= 2)
    {
        std::cout << argv[1] << std::endl;
    }
}
