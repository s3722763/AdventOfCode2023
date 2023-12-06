#include <iostream>
#include <fstream>
#include <string>
#include <vector>

import day1;

void run_day1() {
    std::fstream file("input/day1.txt");

    std::vector<std::string> lines;

    for (std::string line; getline(file, line);) {
        lines.emplace_back(line);
    }

    const auto result = run_day1_main(lines);
    std::cout << "Day 1 Result Part 1: " << result[0] << "\t" << "Part 2: " << result[1] << "\n";
}

int main(int argc, char** argv) {
    run_day1();

    return 0;
}