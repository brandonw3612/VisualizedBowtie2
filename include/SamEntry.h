//
// Created by Brandon Wong on 2022/6/6.
//

#ifndef VISUALIZED_BOWTIE2_SAM_ENTRY_H
#define VISUALIZED_BOWTIE2_SAM_ENTRY_H

#include "string"

class SamEntry {
private:
    std::string _entryId;
    int _position;
    std::string _entryString;

public:
    SamEntry(const std::string& entryId, int position, const std::string& entryString);
    explicit SamEntry(const std::string& lineData);

public:
    std::string getId() const { return _entryId; }
    int getPosition() const { return _position; }
    std::string getString() const { return _entryString; }

public:
    int getEndPosition() const { return _position + (int)_entryString.length() - 1; }
    int getLength() const { return (int)_entryString.length(); };

public:
    static bool defaultCompare(SamEntry* entry1, SamEntry* entry2);
};


#endif //VISUALIZED_BOWTIE2_SAM_ENTRY_H
