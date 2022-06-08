//
// Created by Brandon Wong on 2022/6/8.
//

#include "../include/CigarStringParser.h"

std::vector<std::tuple<bool, int, int>> CigarStringParser::parseCigarString(const std::string& cigar) {
    std::vector<std::tuple<bool, int, int>> result;
    int rangeLength = 0, currentRangeStart = 0;

    for (char i : cigar) {
        if (i >= '0' && i <= '9') {
            rangeLength *= 10;
            rangeLength += i - '0';
        }
        else if (i == 'I') {
            result.emplace_back(true, currentRangeStart, rangeLength);
            rangeLength = 0;
        }
        else if (i == 'D') {
            result.emplace_back(false, currentRangeStart, rangeLength);
            currentRangeStart += rangeLength;
            rangeLength = 0;
        }
        else {
            currentRangeStart += rangeLength;
            rangeLength = 0;
        }
    }

    return result;
}