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

    SamFileReader samFileReader(resultFilePath);
    _entries = samFileReader.Read();

    _currentPosition = 0;

    isHelpScreenOn = false;
}

void SamFileVisualizer::display(int position) {
    system("clear");

    winsize size{};
    ioctl(STDIN_FILENO, TIOCGWINSZ, &size);

    if (position < 0) position = 0;
    if (position + size.ws_col >= _mainSequence.length() + 10) position = _mainSequence.length() - size.ws_col + 10;

    int col = 0;
    while (col < size.ws_col) {
        if ((position + col) % 10 != 0) {
            std::cout << " ";
            col++;
        }
        else if (col + Helpers::getDigits(position + col) < size.ws_col) {
            std::cout << position + col;
            col += Helpers::getDigits(position + col);
        }
        else {
            col++;
        }
    }
    std::cout << std::endl;

    std::cout << _mainSequence.substr(position, size.ws_col) << std::endl;

    int endIndex;
    int left = 0, right = _entries.size() - 1, mid;
    while (left < right - 1)
    {
        mid = left + (right - left) / 2;
        if (_entries[mid]->getPosition() > position + size.ws_col) right = mid;
        else left = mid;
    }
    endIndex = mid;

    std::vector<std::string> rows(size.ws_row - 3);

    for (int i = 0; i < size.ws_row - 3; i++) {
        rows[i] = "";
        rows[i].reserve(size.ws_col);
    }

    for (int iter = 0; iter <= endIndex; iter++) {
        if (_entries[iter]->getEndPosition() < position) continue;
        if (_entries[iter]->getPosition() < position) {
            if (_entries[iter]->getEndPosition() - position + 1 <= size.ws_col) {
                addToTable(rows, size.ws_row - 3, size.ws_col, _entries[iter]->getString().substr(position - _entries[iter]->getPosition()), 0);
            }
            else {
                addToTable(rows, size.ws_row - 3, size.ws_col, _entries[iter]->getString().substr(position - _entries[iter]->getPosition(), size.ws_col), 0);
            }
        }
        else {
            if (_entries[iter]->getEndPosition() - position > size.ws_col) {
                addToTable(rows, size.ws_row - 3, size.ws_col, _entries[iter]->getString().substr(0, size.ws_col + position - _entries[iter]->getPosition()), _entries[iter]->getPosition() - position);
            }
            else {
                addToTable(rows, size.ws_row - 3, size.ws_col, _entries[iter]->getString(), _entries[iter]->getPosition() - position);
            }
        }
    }

    _currentPosition = position;

    for (int i = 0; i < size.ws_row - 3; i++) {
        if (rows[i].empty()) return;
        if (i != 0) std::cout << std::endl;
        for (int j = 0; j < size.ws_col; j++) {
            if (rows[i][j] == _mainSequence[position + j]) rows[i][j] = '.';
        }
        std::cout << rows[i];
    }

    rows.clear();
}

void SamFileVisualizer::addToTable(std::vector<std::string>& table, int row, int column, const std::string& newString, int relativePosition) {
    for (int i = 0; i < row; i++) {
        if (table[i].length() <= relativePosition && relativePosition + newString.length() <= column) {
            if (table[i].length() < relativePosition) table[i] += std::string(relativePosition - table[i].length(), ' ');
            table[i] += newString;
            if (table[i].length() + 1 <= column) {
                table[i] += " ";
            }
            return;
        }
    }
}

void SamFileVisualizer::toggleHelpScreen() {
    isHelpScreenOn = !isHelpScreenOn;
    if (!isHelpScreenOn)
    {
        display(_currentPosition);
        return;
    }
    system("clear");

    std::cout << "VisualizedBowtie2 - Help" << std::endl << std::endl;
    std::cout << std::endl << "Left / Right Arrow Keys" << std::endl << "Navigates the sequence backward/forward by 20 bits." << std::endl << std::endl;
    std::cout << std::endl << "B Key" << std::endl << "Navigates the sequence to the beginning of the sequence." << std::endl << std::endl;
    std::cout << std::endl << "E Key" << std::endl << "Navigates the sequence to the end of the sequence." << std::endl << std::endl;
    std::cout << std::endl << "H Key / ? Key" << std::endl << "Toggles this help screen on or off." << std::endl << std::endl;
}