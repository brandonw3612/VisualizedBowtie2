//
// Created by Brandon Wong on 2022/6/6.
//

#include <algorithm>
#include <iostream>

#include "../include/Helpers.h"
#include "../include/KeyboardEventHandler.h"

KeyboardEventHandler::KeyboardEventHandler(SamFileVisualizer* visualizer) {
    _visualizer = visualizer;
}

void KeyboardEventHandler::startCapturing() {
    while (true) {
        int key = Helpers::scanKeyboard();
        if (key != -1) {
            _capturedKeys.push_back(key);
            processKeys();
        }
    }
}

void KeyboardEventHandler::processKeys() {
    if (_capturedKeys.size() == 3) {
        // determine if left key is pressed
        bool matched = true;
        for (int i = 0; i < 3; i++) {
            if (_capturedKeys[i] != leftKey[i]) {
                matched = false;
                break;
            }
        }
        if (matched) {
            onLeftKeyPressed(_visualizer);
            _capturedKeys.clear();
            return;
        }

        // determine if right key is pressed
        matched = true;
        for (int i = 0; i < 3; i++) {
            if (_capturedKeys[i] != rightKey[i]) {
                matched = false;
                break;
            }
        }
        if (matched) {
            onRightKeyPressed(_visualizer);
            _capturedKeys.clear();
            return;
        }

        // determine if up key is pressed
        matched = true;
        for (int i = 0; i < 3; i++) {
            if (_capturedKeys[i] != upKey[i]) {
                matched = false;
                break;
            }
        }
        if (matched) {
            onUpKeyPressed(_visualizer);
            _capturedKeys.clear();
            return;
        }

        // determine if down key is pressed
        matched = true;
        for (int i = 0; i < 3; i++) {
            if (_capturedKeys[i] != downKey[i]) {
                matched = false;
                break;
            }
        }
        if (matched) {
            onDownKeyPressed(_visualizer);
            _capturedKeys.clear();
            return;
        }
    }
    else if (_capturedKeys.size() == 1) {
        if (_capturedKeys[0] == 'b') {
            onBKeyPressed(_visualizer);
        }
        else if (_capturedKeys[0] == 'e') {
            onEKeyPressed(_visualizer);
        }
        else if (_capturedKeys[0] == 'g') {
            onGKeyPressed(_visualizer);
        }
        else if (_capturedKeys[0] == 'q') {
            exit(0);
        }
        else if (_capturedKeys[0] == 'h') {
            onHKeyPressed(_visualizer);
        }
        else if (_capturedKeys[0] == '?') {
            onQuestionMarkPressed(_visualizer);
        }
        if (_capturedKeys[0] != 27) {
            _capturedKeys.clear();
        }
    }

    if (_capturedKeys.size() >= 3) _capturedKeys.clear();
}