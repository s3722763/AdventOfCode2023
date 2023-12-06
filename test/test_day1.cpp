#include <gtest/gtest.h>
#include <gmock/gmock.h>

import day1;

TEST(Day1, Part1_First) {
    constexpr std::string_view line = "1abc2";

    const auto result = day1_part_1(line);

    ASSERT_EQ(result, 12);
}

TEST(Day1, Part1_Second) {
    constexpr std::string_view line = "pqr3stu8vwx";

    const auto result = day1_part_1(line);

    ASSERT_EQ(result, 38);
}

TEST(Day1, Part1_Third) {
    constexpr std::string_view line = "a1b2c3d4e5f";

    const auto result = day1_part_1(line);

    ASSERT_EQ(result, 15);
}

TEST(Day1, Part1_Forth) {
    constexpr std::string_view line = "treb7uchet";

    const auto result = day1_part_1(line);

    ASSERT_EQ(result, 77);
}

TEST(Day1, Part2_First) {
    constexpr std::string_view line = "two1nine";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 29);
}

TEST(Day1, Part2_Second) {
    constexpr std::string_view line = "eightwothree";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 83);
}

TEST(Day1, Part2_Third) {
    constexpr std::string_view line = "abcone2threexyz";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 13);
}

TEST(Day1, Part2_Forth) {
    constexpr std::string_view line = "xtwone3four";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 24);
}

TEST(Day1, Part2_Fifth) {
    constexpr std::string_view line = "4nineeightseven2";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 42);
}

TEST(Day1, Part2_Sixth) {
    constexpr std::string_view line = "zoneight234";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 14);
}

TEST(Day1, Part2_Seventh) {
    constexpr std::string_view line = "7pqrstsixteen";

    const auto result = day1_part_2(line);

    ASSERT_EQ(result, 76);
}