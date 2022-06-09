//
// Created by Brandon Wong on 2022/6/6.
//

#include <algorithm>
#include <fstream>
#include <iostream>

#include "../include/SamFileReader.h"

SamFileReader::SamFileReader(const std::string &filePath) { _filePath = filePath; }

std::vector<SamEntry*> SamFileReader::Read() {
    std::ifstream inFile(_filePath);

    if (!inFile.good()) {
        std::cerr << "The SAM file could not be found. Make sure the script has generated needed files correctly." << std::endl;
        exit(2);
    }

    std::string line;

    std::vector<SamEntry *> result;

    for (int i = 0; i < 3; i++) getline(inFile, line);
    while (getline(inFile, line))
    {
        auto newEntry = new SamEntry(line);
        if (newEntry->getPosition() >= 0) result.push_back(newEntry);
    }

    inFile.close();

    std::stable_sort(result.begin(), result.end(), SamEntry::defaultCompare);

    return result;
}