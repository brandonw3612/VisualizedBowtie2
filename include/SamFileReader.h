//
// Created by Brandon Wong on 2022/6/6.
//

#ifndef VISUALIZED_BOWTIE2_SAM_FILE_READER_H
#define VISUALIZED_BOWTIE2_SAM_FILE_READER_H

#include <string>
#include <vector>

#include "SamEntry.h"

class SamFileReader {
private:
    std::string _filePath;

public:
    explicit SamFileReader(const std::string& filePath);

public:
    std::vector<SamEntry*> read();
};

#endif //VISUALIZED_BOWTIE2_SAM_FILE_READER_H
