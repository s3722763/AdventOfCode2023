//
// Created by Daniel on 6/12/2023.
//
#include <array>
#include <bitset>
#include <iostream>
#include <span>
#include <string>
#include <ranges>
#include <vector>

export module day2;

struct Subgame {
    size_t number_red = 0;
    size_t number_green = 0;
    size_t number_blue = 0;
};

struct Game {
    size_t game_number = 0;
    std::vector<Subgame> games;
};

enum class Colour {
    Red,
    Green,
    Blue
};

export int day2_part1(std::span<Game> games) {
    return 0;
}

std::vector<Game> lines_to_games(const std::span<std::string> lines) {
    std::vector<Game> games;
    games.resize(lines.size());

    using std::operator""sv;
    constexpr auto game_delim{":"sv};
    constexpr auto subgame_delim{";"sv};
    constexpr auto ball_delim{","sv};
    size_t game_number = 1;

    for (const auto&line: lines) {
        games[game_number - 1].game_number = game_number;

        const size_t start_game_line = line.find(':', 0);
        const std::string game_details = line.substr(start_game_line + 1, line.size() - start_game_line);

        // std::string d(game_details.begin(), game_details.end());
        std::vector<Subgame> subgames;

        for (const auto&subgame_details: game_details | std::views::split(subgame_delim)) {
            Subgame subgame{};

            // std::string a(subgame_details.begin(), subgame_details.end());

            for (const auto&ball_details: subgame_details | std::views::split(ball_delim)) {
                const std::string details(ball_details.begin(), ball_details.end());

                // Offset of one to avoid first value empty value
                size_t start = details.find_first_not_of(' ', 0);
                size_t end = details.find(' ', start);
                const std::string number = details.substr(start, end - start);

                start = details.find_first_not_of(' ', end);
                end = details.find(' ', start);
                const std::string colour = details.substr(start, end - start);

                if (colour == "blue") {
                    subgame.number_blue = std::stoi(number);
                }
                else if (colour == "red") {
                    subgame.number_red = std::stoi(number);
                }
                else if (colour == "green") {
                    subgame.number_green = std::stoi(number);
                }
            }

            subgames.emplace_back(subgame);
        }

        games[game_number - 1].games = subgames;
        game_number += 1;
    }


    return games;
}

int run_day2_part1(const std::span<Game> games) {
    int result = 0;

    for (const auto& game : games) {
        int exceeded_count = 0;

        for(const auto& subgame : game.games) {
            exceeded_count += subgame.number_blue > 14 || subgame.number_green > 13 || subgame.number_red > 12;
        }

        if (exceeded_count == 0) {
            result += game.game_number;
        }
    }

    return result;
}

int run_day2_part2(const std::span<Game> games) {
    int result = 0;

    for (const auto& game : games) {
        int largest_red = 0;
        int largest_green = 0;
        int largest_blue = 0;

        for (const auto& subgame : game.games) {
            if (subgame.number_blue > largest_blue) {
                largest_blue = subgame.number_blue;
            }

            if (subgame.number_green > largest_green) {
                largest_green = subgame.number_green;
            }

            if (subgame.number_red > largest_red) {
                largest_red = subgame.number_red;
            }
        }

        result += largest_blue * largest_red * largest_green;
    }

    return result;
}

export std::array<int, 2> run_day2_main(const std::span<std::string> lines) {
    auto games = lines_to_games(lines);

    return {run_day2_part1(games), run_day2_part2(games)};
}
