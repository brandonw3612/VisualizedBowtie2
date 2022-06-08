//
// Created by Brandon Wong on 2022/6/6.
//

#include "../include/CigarStringParser.h"
#include "../include/SamEntry.h"

#include <algorithm>
#include <vector>
#include <cstdlib>

SamEntry::SamEntry(const std::string &entryId, const int position, const std::string &entryString)
{
    _entryId = entryId;
    _position = position;
    _entryString = entryString;
}

SamEntry::SamEntry(const std::string &lineData)
{
    std::vector<uint32_t> tabPositions;
    for (int i = 0; i < lineData.length(); i++)
    {
        if (lineData[i] == '\t')
            tabPositions.push_back(i);
    }

    _entryId = lineData.substr(0, tabPositions[0]);
    _position = (int)strtol(lineData.substr(tabPositions[2] + 1, tabPositions[3] - tabPositions[2] - 1).c_str(), nullptr, 10) - 1;
    _entryString = lineData.substr(tabPositions[8] + 1, tabPositions[9] - tabPositions[8] - 1);

    auto cigarModifiers = CigarStringParser::parseCigarString(lineData.substr(tabPositions[4] + 1, tabPositions[5] - tabPositions[4] - 1));
    for (auto modifier: cigarModifiers) {
        if (get<0>(modifier)) {
            auto former = get<1>(modifier) > 0 ? _entryString.substr(0, get<1>(modifier) - 1) : "";
            auto latter = _entryString.substr(get<1>(modifier) + get<2>(modifier));
            _entryString = former + latter;
        }
        else {
            _entryString.insert(get<1>(modifier), std::string(get<2>(modifier), '~'));
        }
    }
}

bool SamEntry::defaultCompare(SamEntry* entry1, SamEntry* entry2) {
    return entry1->_position < entry2->_position;
}