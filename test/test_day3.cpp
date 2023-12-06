//
// Created by Daniel on 6/12/2023.
//
#include <gtest/gtest.h>

import day3;

TEST(Day3, Part1) {
    std::vector<std::string> engine_schematic = {
         "467..114..",
         "...*......",
         "..35..633.",
         "......#...",
         "617*......",
         ".....+.58.",
         "..592.....",
         "......755.",
         "...$.*....",
         ".664.598.."
    };

    auto result = run_day3_main(engine_schematic);
    ASSERT_EQ(result[0], 4361);
}

TEST(Day3, Part2) {
    std::vector<std::string> engine_schematic = {
        "467..114..",
        "...*......",
        "..35..633.",
        "......#...",
        "617*......",
        ".....+.58.",
        "..592.....",
        "......755.",
        "...$.*....",
        ".664.598.."
   };

    auto result = run_day3_main(engine_schematic);
    ASSERT_EQ(result[1], 467835);
}