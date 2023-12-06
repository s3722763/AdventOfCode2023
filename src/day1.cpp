#include <algorithm>
#include <array>
#include <functional>
#include <optional>
#include <span>
#include <string_view>

export module day1;

struct NumberFoundResult {
    int number;
    size_t pos;
};

export int day1_part_1(const std::string_view line) {
    char msd = '\0';
    char lsd = '\0';

    for (const auto c : line) {
        if (c >= '0' && c <= '9') {
            if (msd == '\0') {
                msd = c;
                lsd = c;
            } else {
                lsd = c;
            }
        }
    }

    return ((msd - '0') * 10) + (lsd - '0');
}

inline std::optional<int> get_number(const char& c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else {
        return {};
    }
}

inline int number_word_to_int(const std::string_view word) {
    if (word == "one") {
        return 1;
    } else if (word == "two") {
        return 2;
    } else if (word == "three") {
        return 3;
    } else if (word == "four") {
        return 4;
    } else if (word == "five") {
        return 5;
    } else if (word == "six") {
        return 6;
    } else if (word == "seven") {
        return 7;
    } else if (word == "eight") {
        return 8;
    } else if (word == "nine") {
        return 9;
    } else {
        return 0;
    }
}

inline std::array<NumberFoundResult, 2> find_first_last_numbers(const std::string_view line) {
    std::array<NumberFoundResult, 2> result{};
    result[0].number = '\0';

    size_t index = 0;

    for (const auto c : line) {
        if (c >= '0' && c <= '9') {
            if (result[0].number  == '\0') {
                result[0].number  = c - '0';
                result[0].pos  = index;

                result[1].number  = c - '0';
                result[1].pos  = index;
            } else {
                result[1].number  = c - '0';
                result[1].pos  = index;
            }
        }

        index += 1;
    }

    return result;
}

inline std::array<NumberFoundResult, 2> find_first_last_number_word(const std::string_view line) {
    constexpr std::array<const std::string_view, 9> number_words = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    std::array<NumberFoundResult, 2> result{};
    result[0].pos = -1;

    for (const auto& number_word : number_words) {
        const std::boyer_moore_searcher searcher(number_word.begin(), number_word.end());
        const auto found_first = std::search(line.begin(), line.end(), searcher);

        if (found_first != line.end()) {
            const auto distance = std::distance(line.begin(), found_first);
            if (distance < result[0].pos) {
                result[0].number = number_word_to_int(number_word);
                result[0].pos = distance;
            }
        }
    }

    for (const auto& number_word : number_words) {
        const std::boyer_moore_searcher searcher(number_word.rbegin(), number_word.rend());
        const auto found_last = std::search(line.rbegin(), line.rend(), searcher);

        if (found_last != line.rend()) {
            const auto distance = line.size() - std::distance(line.rbegin(), found_last) - number_word.size();
            if (distance > result[1].pos) {
                result[1].number = number_word_to_int(number_word);
                result[1].pos = distance;
            }
        }
    }


    return result;
}

export int day1_part_2(const std::string_view line) {
    const auto individual_numbers = find_first_last_numbers(line);
    const auto number_words = find_first_last_number_word(line);

    std::vector<NumberFoundResult> results = {
        individual_numbers[0],
        individual_numbers[1],
        number_words[0],
        number_words[1]
    };

    std::ranges::sort(results, {}, &NumberFoundResult::pos);

    std::erase_if(results, [](const NumberFoundResult r) {
        return r.number == 0;
    });

    const auto first_value = results.begin()[0].number * 10;
    const auto second_value = results.begin()[results.size() - 1].number;

    return first_value + second_value;
}

export std::array<int, 2> run_day1_main(const std::span<std::string> lines) {
    int sum_part1 = 0;

    for (const auto& line : lines) {
        sum_part1 += day1_part_1(line);
    }

    int sum_part2 = 0;

    for (const auto& line : lines) {
        auto value = day1_part_2(line);
        sum_part2 += value;
    }

    return {sum_part1, sum_part2};
}