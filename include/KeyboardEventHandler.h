//
// Created by Brandon Wong on 2022/6/6.
//

#ifndef VISUALIZED_BOWTIE2_KEYBOARD_EVENT_HANDLER_H
#define VISUALIZED_BOWTIE2_KEYBOARD_EVENT_HANDLER_H

#include <vector>

#include "SamFileVisualizer.h"

class KeyboardEventHandler {
private:
    std::vector<int> _capturedKeys;
    SamFileVisualizer* _visualizer;

public:
    explicit KeyboardEventHandler(SamFileVisualizer*);
    void (*onLeftKeyPressed)(SamFileVisualizer*);
    void (*onRightKeyPressed)(SamFileVisualizer*);
    void (*onBKeyPressed)(SamFileVisualizer*);
    void (*onEKeyPressed)(SamFileVisualizer*);
    void (*onGKeyPressed)(SamFileVisualizer*);
    void (*onHKeyPressed)(SamFileVisualizer*);
    void (*onQuestionMarkPressed)(SamFileVisualizer*);

public:
    void startCapturing();

private:
    void processKeys();

private:
    const std::vector<int> leftKey { 27, 91, 68 };
    const std::vector<int> rightKey { 27, 91, 67 };
};


#endif //VISUALIZED_BOWTIE2_KEYBOARD_EVENT_HANDLER_H
