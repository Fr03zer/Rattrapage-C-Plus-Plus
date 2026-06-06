#include "FileManager.h"

std::string FileManager::createOutputName(
    const std::string& inputFile)
{
    return inputFile + "_result.txt";
}