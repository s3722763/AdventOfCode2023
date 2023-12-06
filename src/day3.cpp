//
// Created by Daniel on 6/12/2023.
//
#include <algorithm>
#include <array>
#include <map>
#include <optional>
#include <span>
#include <string>
#include <vector>

export module day3;

struct Point {
    int x;
    int y;

    bool operator<(const Point& rhs) const {
        if (this->x == rhs.x) {
            return this->y < rhs.y;
        }

        return this->x < rhs.x;
    }

    bool operator==(const Point& rhs) const {
        return this->y == rhs.y && this->x == rhs.x;
    }
};

enum class SymbolType {
    Gear,
    Other
};

struct Symbol {
    SymbolType type;
    Point location;
};

struct EngineComponent {
    int id;
    Point start_point;
};

struct Engine {
    std::vector<EngineComponent> valid_components;
    std::map<Point, std::vector<int>> possible_gears{};
};

bool is_number(const auto& c) {
    return c >= '0' && c <= '9';
}

bool valid_symbol(const auto& c) {
    return !is_number(c) && c != '.' && c != '\0';
}

std::optional<Symbol> get_symbol(const Point& p, const std::span<std::string> schematic, const int length) {
    const auto start_x = std::max(p.x - 1, 0);
    const auto start_y = std::max(p.y - 1, 0);

    const auto x_max = std::min(start_x + length + 1, static_cast<int>(schematic[0].size()) - 1);
    const auto y_max = std::min(p.y + 1, static_cast<int>(schematic.size() - 1));

    for (size_t y = start_y; y <= y_max; y++) {
        for (size_t x = start_x; x <= x_max; x++) {
            const char& c = schematic[y][x];
            if (valid_symbol(c)) {
                if (c == '*') {
                    return std::optional{Symbol{
                        SymbolType::Gear,
                        Point(static_cast<int>(x), static_cast<int>(y))
                    }};
                }

                return std::optional{Symbol{
                    SymbolType::Other,
                    Point(static_cast<int>(x), static_cast<int>(y))
                }};
            }
        }
    }

    return {};
}


Engine find_engine_components(const std::span<std::string> schematic) {
    Engine engine{};
    std::string id;
    Point new_component_point{};
    id.reserve(3);

    int y = 0;
    for (const auto& line : schematic) {
        int x = 0;

        for (const auto c : line) {
            if (is_number(c)) {
                if (id.empty()) {
                    new_component_point = {x, y};
                }

                id.push_back(c);
            } else {
                if (!id.empty()) {
                    const auto symbol = get_symbol(new_component_point, schematic, id.length());
                    if (symbol.has_value()) {
                        EngineComponent new_component{};
                        new_component.id = std::stoi(id);
                        new_component.start_point = new_component_point;

                        engine.valid_components.emplace_back(new_component);

                        if (symbol.value().type == SymbolType::Gear) {
                            engine.possible_gears[symbol->location].emplace_back(new_component.id);
                        }
                    }
                }

                id.clear();
            }

            x += 1;
        }

        if (!id.empty()) {
            const auto symbol = get_symbol(new_component_point, schematic, id.length());
            if (symbol.has_value()) {
                EngineComponent new_component{};
                new_component.id = std::stoi(id);
                new_component.start_point = new_component_point;

                engine.valid_components.emplace_back(new_component);

                if (symbol.value().type == SymbolType::Gear) {
                    engine.possible_gears[symbol->location].emplace_back(new_component.id);
                }
            }
        }

        id.clear();
        y += 1;
    }

    return engine;
}

int run_day3_part1(const Engine& engine) {
    int sum = 0;

    for (const auto& valid_component : engine.valid_components) {
        sum += valid_component.id;
    }

    return sum;
}

int run_day3_part2(const Engine& engine) {
    int sum = 0;

    for (const auto& gear : engine.possible_gears) {
        if (gear.second.size() == 2) {
            sum += gear.second[0] * gear.second[1];
        }
    }

    return sum;
}

export std::array<int, 2> run_day3_main(const std::span<std::string> schematic) {
    const auto engine = find_engine_components(schematic);

    return {run_day3_part1(engine), run_day3_part2(engine)};
}
