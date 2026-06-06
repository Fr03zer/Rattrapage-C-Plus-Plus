#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class FileManager
{
public:
    static std::string createOutputName(
        const std::string& inputFile
    );
};

#endif