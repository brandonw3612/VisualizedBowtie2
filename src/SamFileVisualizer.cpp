//
// Created by Brandon Wong on 2022/6/6.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sstream>

#include "../include/Helpers.h"
#include "../include/SamFileReader.h"
#include "../include/SamFileVisualizer.h"

SamFileVisualizer::SamFileVisualizer(const std::string& sequenceFilePath, const std::string& resultFilePath) {
    std::ifstream inFile(sequenceFilePath);

    if (!inFile.good()) {
        std::cerr << "The FASTA Sequence (.fa) file could not be found. Make sure you selected the correct path." << std::endl;
        exit(2);
    }

    std::string line;
    std::ostringstream ostr;
    while (std::getline(inFile, line)) {
        if (line[0] != '>') {
            ostr << line;
        }
    }
    _mainSequence = ostr.str();

    inFile.close();

    SamFileReader samFileReader(resultFilePath);
    _entries = samFileReader.read();

    _currentPosition = 0;

    _isHelpScreenOn = false;
}

void SamFileVisualizer::display(int position) {
    winsize size{};
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);

    if (position < 0) position = 0;
    if (position + size.ws_col >= _mainSequence.length() + 10) position = _mainSequence.length() - size.ws_col + 10;

    int endIndex;
    int left = 0, right = _entries.size() - 1, mid;
    while (left < right - 1)
    {
        mid = left + (right - left) / 2;
        if (_entries[mid]->getPosition() > position + size.ws_col) right = mid;
        else left = mid;
    }
    endIndex = left;

    _currentLines.clear();

    for (int iter = 0; iter <= endIndex; iter++) {
        if (_entries[iter]->getEndPosition() < position) continue;
        if (_entries[iter]->getPosition() < position) {
            if (_entries[iter]->getEndPosition() - position + 1 <= size.ws_col) {
                addToTable(size.ws_col, _entries[iter]->getString().substr(position - _entries[iter]->getPosition()), 0);
            }
            else {
                addToTable(size.ws_col, _entries[iter]->getString().substr(position - _entries[iter]->getPosition(), size.ws_col), 0);
            }
        }
        else {
            if (_entries[iter]->getEndPosition() - position > size.ws_col) {
                addToTable(size.ws_col, _entries[iter]->getString().substr(0, size.ws_col + position - _entries[iter]->getPosition()), _entries[iter]->getPosition() - position);
            }
            else {
                addToTable(size.ws_col, _entries[iter]->getString(), _entries[iter]->getPosition() - position);
            }
        }
    }

    _currentPosition = position;

    scrollVertically(0);
}

void SamFileVisualizer::scrollVertically(int line) {
    system("clear");

    winsize size{};
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);

    if (line < 0) line = 0;
    if (line >= _currentLines.size()) line = _currentLines.size() - 1;

    int col = 0;
    while (col < size.ws_col) {
        if ((_currentPosition + col) % 10 != 0) {
            std::cout << " ";
            col++;
        }
        else if (col + Helpers::getDigits(_currentPosition + col) < size.ws_col) {
            std::cout << _currentPosition + col;
            col += Helpers::getDigits(_currentPosition + col);
        }
        else {
            col++;
        }
    }
    std::cout << std::endl;

    std::cout << _mainSequence.substr(_currentPosition, size.ws_col) << std::endl;

    for (int i = line; i < _currentLines.size() && i - line < size.ws_row - 3; i++) {
        if (i != line) std::cout << std::endl;
        for (int j = 0; j < size.ws_col; j++) {
            if (_currentLines[i][j] == _mainSequence[_currentPosition + j]) _currentLines[i][j] = '.';
        }
        std::cout << _currentLines[i];
    }

    _currentStartingLine = line;
}

void SamFileVisualizer::addToTable(int column, const std::string& newString, int relativePosition) {
    for (int i = 0; i < _currentLines.size(); i++) {
        if (_currentLines[i].length() <= relativePosition && relativePosition + newString.length() <= column) {
            if (_currentLines[i].length() < relativePosition) _currentLines[i] += std::string(relativePosition - _currentLines[i].length(), ' ');
            _currentLines[i] += newString;
            if (_currentLines[i].length() + 3 <= column) {
                _currentLines[i] += "   ";
            }
            return;
        }
    }

    std::string newLine = "";
    if (relativePosition > 0) newLine += std::string(relativePosition, ' ');
    newLine += newString;
    _currentLines.push_back(newLine);
    _currentLines[_currentLines.size() - 1].reserve(column);
}

void SamFileVisualizer::toggleHelpScreen() {
    _isHelpScreenOn = !_isHelpScreenOn;
    if (!_isHelpScreenOn)
    {
        display(_currentPosition);
        return;
    }
    system("clear");

    std::cout << "VisualizedBowtie2 - Help" << std::endl << std::endl;
    std::cout << std::endl << "Left / Right Arrow Keys" << std::endl << "Navigates the sequence backward/forward by 20 bits." << std::endl;
    std::cout << std::endl << "Up / Down Arrow Keys" << std::endl << "Scroll the displayed sequences 1 line up/down." << std::endl;
    std::cout << std::endl << "B Key" << std::endl << "Navigates the sequence to the beginning of the sequence." << std::endl;
    std::cout << std::endl << "E Key" << std::endl << "Navigates the sequence to the end of the sequence." << std::endl;
    std::cout << std::endl << "G Key" << std::endl << "Navigates the sequence to any position you input in the sequence." << std::endl;
    std::cout << std::endl << "H Key / ? Key" << std::endl << "Toggles this helper screen on or off." << std::endl;
    std::cout << std::endl << "Q Key" << std::endl << "Exit the program." << std::endl;
}