#include <iostream>

#include "../include/KeyboardEventHandler.h"

#include <cstdlib>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char* argv[] ) {
    std::string faFilePath, fqFilePath;

    if (argc == 1) {
        std::cout << "No arguments have been passed to the program." << std::endl;
        std::cout << "Enter the file paths here." << std::endl;
        std::cout << "Main FASTA sequence file path (.fa): ";
        std::getline(std::cin, faFilePath);
        std::cout << "Fastaq file path (.fq): ";
        std::getline(std::cin, fqFilePath);
    }
    else {
        if (argc < 3) {
            std::cout << "Unaccepted usage." << std::endl <<std::endl;
            std::cout << "VisualizedBowtie2 Usage:" << std::endl;
            std::cout << "VisualizedBowtie2 main_fasta_sequence_file_path fastaq_file_path" << std::endl;
            exit(1);
        }
        faFilePath = std::string(argv[1]);
        fqFilePath = std::string(argv[2]);
    }

    std::cout << std::endl << "FASTA file: " << faFilePath << std::endl << "Fastaq file: " << fqFilePath << std::endl << std::endl;

    std::cout << "Executing shell script to analyse the sequences with bowtie2." << std::endl;

    std::string cmd = "bash ./bowtie2.sh " + faFilePath + " reference " + fqFilePath + " result.sam";
    system(cmd.c_str());

    SamFileVisualizer visualizer("/Users/brandon/Downloads/项目6/project6/data/ref.fa", "/Users/brandon/Downloads/result1.sam");
    int position = 0;
    visualizer.display(position);

    KeyboardEventHandler keyboardEventHandler(&visualizer);

    keyboardEventHandler.onLeftKeyPressed = [](SamFileVisualizer* v) { v->display(v->getCurrentPosition() - 20); };
    keyboardEventHandler.onRightKeyPressed = [](SamFileVisualizer* v) { v->display(v->getCurrentPosition() + 20); };
    keyboardEventHandler.onBKeyPressed = [](SamFileVisualizer* v) { v->display(0); };
    keyboardEventHandler.onEKeyPressed = [](SamFileVisualizer* v) { v->display(v->getSequenceLength()); };
    keyboardEventHandler.onHKeyPressed = [](SamFileVisualizer* v) { v->toggleHelpScreen(); };
    keyboardEventHandler.onQuestionMarkPressed = [](SamFileVisualizer* v) { v->toggleHelpScreen(); };

    keyboardEventHandler.onGKeyPressed = [](SamFileVisualizer* v) {
        winsize size{};
        ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
        std::cout << "\033[" << size.ws_row << ";0H" << "Go to position: ";
        int position;
        std::cin >> position;
        v->display(position);
    };
    keyboardEventHandler.startCapturing();
    return 0;
}
