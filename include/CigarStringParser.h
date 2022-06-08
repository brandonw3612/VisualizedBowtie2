//
// Created by Brandon Wong on 2022/6/8.
//

#ifndef VISUALIZEDBOWTIE2_CIGARSTRINGPARSER_H
#define VISUALIZEDBOWTIE2_CIGARSTRINGPARSER_H

#include <string>
#include <tuple>
#include <vector>

class CigarStringParser {
public:
    static std::vector<std::tuple<bool, int, int>> parseCigarString(const std::string& cigar);
};


#endif //VISUALIZEDBOWTIE2_CIGARSTRINGPARSER_H
