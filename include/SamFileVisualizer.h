//
// Created by Brandon Wong on 2022/6/6.
//

#ifndef VISUALIZED_BOWTIE2_SAM_FILE_VISUALIZER_H
#define VISUALIZED_BOWTIE2_SAM_FILE_VISUALIZER_H

#include <string>
#include <vector>

#include "SamEntry.h"

class SamFileVisualizer {
private:
    std::string _mainSequence;
    std::vector<SamEntry*> _entries;
    std::vector<std::string> _currentLines;
    int _currentStartingLine;
    int _currentPosition;
    bool _isHelpScreenOn;

public:
    SamFileVisualizer(const std::string&, const std::string&);

public:
    int getCurrentPosition() const { return _currentPosition; }
    int getCurrentLine() const { return _currentStartingLine; }
    int getSequenceLength() const { return (int)_mainSequence.length(); }
    void display(int position);
    void scrollVertically(int line);
    void toggleHelpScreen();

private:
    void addToTable(int, const std::string&, int);
};

#endif //VISUALIZED_BOWTIE2_SAM_FILE_VISUALIZER_H
