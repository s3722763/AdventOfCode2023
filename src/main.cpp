#include <iostream>
#include <fstream>
#include <string>
#include <vector>

import day1;
import day2;

void run_day1() {
    std::fstream file("input/day1.txt");

    std::vector<std::string> lines;

    for (std::string line; getline(file, line);) {
        lines.emplace_back(line);
    }

    const auto result = run_day1_main(lines);
    std::cout << "Day 1 Result Part 1: " << result[0] << "\t" << "Part 2: " << result[1] << "\n";
}

void run_day2() {
    std::fstream file("input/day2.txt");

    std::vector<std::string> lines;

    for (std::string line; getline(file, line);) {
        lines.emplace_back(line);
    }

    const auto result = run_day2_main(lines);
    std::cout << "Day 2 Result Part 2: " << result[0] << "\t" << "Part 2: " << result[1] << "\n";
}


int main(int argc, char** argv) {
    run_day1();
    run_day2();

    return 0;
}