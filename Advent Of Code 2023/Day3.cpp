#include "Day3.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <set>
#include <algorithm>
std::vector<std::string> LoadData(std::string data_path)
{
    std::vector<std::string> map_data;
    std::ifstream input_file(data_path);
    std::string line;

    while (std::getline(input_file, line))
    {
        map_data.push_back(line);
    }

    std::cout << "Number of Rows: " << map_data.size() << " Number of Columns: " << map_data[0].size() << "\n";
    return map_data;
}

struct Coord
{
    int x;
    int y;
};

struct Bounds
{
    Coord start;
    Coord end;
};

struct Part
{
    int number;
    Bounds position;
};

std::vector<Part> FindNumbers(std::string line, int row_number)
{
    std::vector<Part> parts;
    int i = 0;
    int length = line.length();
    while (i < length)
    {

        if (std::isdigit(line[i]))
        {
            int number_start = i;
            std::string number = "";

            while (i < length && std::isdigit(line[i]))
            {
                number += line[i];
                i++;
            }

            Part part;
            part.number = stoi(number);
            part.position.start = {number_start, row_number};
            part.position.end = {i - 1, row_number};

            parts.push_back(part);
        }
        else
        {
            i++;
        }
    }
    return parts;
}
/**
 * Look for the possible places for the symbols
 */
std::vector<Coord> GetPossibleSymbolLocations(Bounds bounds, Coord max)
{
    std::vector<Coord> locations;

    int start_x = std::max(0, bounds.start.x - 1);
    int end_x = std::min(max.x - 1, bounds.end.x + 1);

    int start_y = std::max(0, bounds.start.y - 1);
    int end_y = std::min(max.y - 1, bounds.start.y + 1);

    for (int x = start_x; x <= end_x; ++x)
    {
        for (int y = start_y; y <= end_y; ++y)
        {
            if (x >= bounds.start.x && x <= bounds.end.x && y == bounds.start.y)
            {
                continue;
            }
            // std::cout <<"(" << x << "," << y << ") \n";
            locations.push_back({x, y});
        }
    }
    return locations;
}


std::vector<Coord> GetPossibleNumberLocations(Bounds bounds, Coord max)
{
    std::vector<Coord> locations;

    int start_x = std::max(0, bounds.start.x - 1);
    int end_x = std::min(max.x - 1, bounds.end.x + 1);

    int start_y = std::max(0, bounds.start.y - 1);
    int end_y = std::min(max.y - 1, bounds.start.y + 1);

    for (int x = start_x; x <= end_x; ++x) {
        for (int y = start_y; y <= end_y; ++y) {
            if (!(x == bounds.start.x && y == bounds.start.y)) { 
                locations.push_back({ x, y });
            }
        }
    }
    return locations;
}


bool HasPartSymbol(std::vector<std::string> map_data, std::vector<Coord> possible_locations)
{
    const std::string kSearchValues = "1234567890.";
    for (Coord location : possible_locations)
    {
        // std::cout << "Location: (" << location.x << "," << location.y << ")\n";
        if (kSearchValues.find(map_data[location.y][location.x]) == std::string::npos)
        {
            return true;
        };
    }

    return false;
}

int SolvePart1(std::vector<std::string> map_data)
{
    Coord max_coords{map_data.size(), map_data[0].size()};
    int parts_total = 0;
    for (size_t i = 0; i < map_data.size(); ++i)
    {
        std::vector<Part> found_numbers = FindNumbers(map_data[i], i);
        // std::cout << map_data[i] << "\n";
        for (Part part : found_numbers)
        {
            std::vector<Coord> possible_locations = GetPossibleSymbolLocations(part.position, max_coords);
            if (HasPartSymbol(map_data, possible_locations))
            {
                // std::cout << "CorrectNumber: " << part.number << "\n";
                parts_total += part.number;
            }
        }
    }
    return parts_total;
}

bool IsAdjacentToGear(const Coord& gear, const Coord& location) {
    int dx = abs(gear.x - location.x);
    int dy = abs(gear.y - location.y);

    return dx <= 1 && dy <= 1 && (dx + dy) > 0;
}


std::vector<Part> FindNumbers2(std::vector<std::string> map_data) {
    std::vector<Part> parts;

    for (int i = 0; i < map_data.size(); ++i) {
        std::string line = map_data[i];
        int j = 0;
        while (j < line.length()) {
            if (std::isdigit(line[j])) {
                int number_start = j;
                std::string number = "";

                while (j < line.length() && std::isdigit(line[j])) {
                    number += line[j];
                    j++;
                }

                Part part;
                part.number = std::stoi(number);
                part.position.start = { number_start, i };
                part.position.end = { j - 1, i };

                parts.push_back(part);
            }
            else {
                j++;
            }
        }
    }
    return parts;
}


int SolvePart2(std::vector<std::string> map_data) {
    int result = 0;
    std::vector<Part> parts = FindNumbers2(map_data);
    std::vector<Coord> gears;

    for (int i = 0; i < map_data.size(); ++i) {
        for (int j = 0; j < map_data[i].length(); ++j) {
            if (map_data[i][j] == '*') {
                gears.push_back({ j, i });
            }
        }
    }

    for (const Coord& gear : gears) {
        std::set<int> adjacent_numbers;
        for (const Part& part : parts) {
            if (IsAdjacentToGear(gear, part.position.start) || IsAdjacentToGear(gear, part.position.end)) {
                adjacent_numbers.insert(part.number);
            }
        }
        if (adjacent_numbers.size() == 2) {
            int product = 1;
            for (int num : adjacent_numbers) {
                product *= num;
            }
            result += product;
        }
    }

    return result;
}


int Day3()
{
    std::vector<std::string> data_example = LoadData("Data/Day3-Example.txt");
    std::vector<std::string> data_part1 = LoadData("Data/Day3_Part1.txt");

    int result_example = SolvePart1(data_example);
    std::cout << "Day 3 Part 1 Example: " << result_example << "\n";

    int result_part1 = SolvePart1(data_part1);
    std::cout << "Day 3 Part 1: " << result_part1 << "\n";

    int result_example2 = SolvePart2(data_example);
    std::cout << "Day 3 Part 2 Example: " << result_example2 << "\n";

    int result_part2 = SolvePart2(data_part1);
    std::cout << "Day 3 Part 2: " << result_part2 << "\n";
    return 0;
}