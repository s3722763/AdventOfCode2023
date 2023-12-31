#include <iostream>
#include <fstream>
#include <string>
#include <vector>

import day1;
import day2;
import day3;
import day4;

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
    std::cout << "Day 2 Result Part 1: " << result[0] << "\t" << "Part 2: " << result[1] << "\n";
}

void run_day3() {
    std::fstream file("input/day3.txt");

    std::vector<std::string> lines;

    for (std::string line; getline(file, line);) {
        lines.emplace_back(line);
    }

    const auto result = run_day3_main(lines);
    std::cout << "Day 3 Result Part 1: " << result[0] << "\t" << "Part 2: " << result[1] << "\n";
}

void run_day4() {
    std::fstream file("input/day4.txt");

    std::vector<std::string> lines;

    for (std::string line; getline(file, line);) {
        lines.emplace_back(line);
    }

    const auto result = run_day4_main(lines);
    std::cout << "Day 4 Result Part 1: " << result[0] << "\t" << "Part 2: " << result[1] << "\n";
}

int main(int argc, char** argv) {
    run_day1();
    run_day2();
    run_day3();
    run_day4();

    return 0;
}