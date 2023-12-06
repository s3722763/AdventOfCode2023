//
// Created by Daniel on 6/12/2023.
//
#include <array>
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include <ranges>

export module day4;

struct Round {
    std::vector<int> chosen_numbers;
    std::vector<int> winning_numbers;
    int card_number;
};

int run_day4_part1(const std::span<Round> rounds) {
    int sum = 0;

    for (const auto& round : rounds) {
        int count = 0;

        for (const auto& picked_number : round.chosen_numbers) {
            if (std::find(round.winning_numbers.begin(), round.winning_numbers.end(), picked_number) != round.winning_numbers.end()) {
                count += 1;
            }
        }

        if (count > 0) {
            sum += 1 << (count - 1);
        }
    }

    return sum;
}

int run_day4_part2(const std::span<Round> rounds) {
    int sum = 0;

    std::vector<int> number_winning_cards{};
    std::vector<int> number_times_won{};
    number_winning_cards.resize(rounds.size());
    number_times_won.resize(rounds.size());

    for (const auto& round : rounds) {
        int count = 0;

        for (const auto& picked_number : round.chosen_numbers) {
            if (std::find(round.winning_numbers.begin(), round.winning_numbers.end(), picked_number) != round.winning_numbers.end()) {
                count += 1;
            }
        }

        number_winning_cards[round.card_number - 1] = count;
    }

    for (const auto& round : rounds) {
        // Plus one because you always have atleast one card
        number_times_won[round.card_number - 1] += 1;
        const int start = round.card_number;
        const size_t maximum_card_index = std::min(start + number_winning_cards[round.card_number - 1], static_cast<int>(rounds.size()));

        for (size_t i = start; i < maximum_card_index; i++) {
            number_times_won[i] +=  number_times_won[round.card_number - 1];
        }

        sum += number_times_won[round.card_number - 1];
    }

    return sum;
}

std::vector<Round> create_rounds(const std::span<std::string> lines) {
    std::vector<Round> rounds;
    rounds.resize(lines.size());

    using std::operator""sv;
    constexpr auto round_delim{":"sv};
    constexpr auto winning_chosen_delim{" | "sv};
    size_t card_number = 1;

    for (const auto& line: lines) {
        rounds[card_number - 1].card_number = card_number;

        const size_t start_round_line = line.find(round_delim, 0);
        const std::string round_details = line.substr(start_round_line + 1, line.size() - start_round_line);

        // Offset of one to avoid first value empty value
        size_t start = round_details.find_first_not_of(winning_chosen_delim, 0);
        size_t end = round_details.find(winning_chosen_delim, start);
        const std::string winning_numbers = round_details.substr(start, end - start);

        start = round_details.find_first_not_of(winning_chosen_delim, end);
        end = round_details.find(winning_chosen_delim, start);
        const std::string chosen_numbers = round_details.substr(start, end - start);

        for (const auto& number : winning_numbers | std::views::split(' ')) {
            const auto number_str = std::string(number.begin(), number.end());
            if (!number_str.empty()) {
                rounds[card_number - 1].winning_numbers.emplace_back(std::stoi(number_str));
            }
        }

        for (const auto& number : chosen_numbers | std::views::split(' ')) {
            const auto number_str = std::string(number.begin(), number.end());
            if (!number_str.empty()) {
                rounds[card_number - 1].chosen_numbers.emplace_back(std::stoi(number_str));
            }
        }

        card_number += 1;
    }

    return rounds;
}

export std::array<int, 2> run_day4_main(const std::span<std::string> input) {
    auto rounds = create_rounds(input);
    return {run_day4_part1(rounds), run_day4_part2(rounds)};
}
