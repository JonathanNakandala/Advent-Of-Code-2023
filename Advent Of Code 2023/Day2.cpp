// Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
#include <string>
#include "Day2.h"
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp> 
struct Cubes
{
	int red;
    int green;
	int blue;
};

struct Game
{
    int id;
    std::vector<Cubes> results;
};


std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string_view string_view(str);
    size_t pos = 0;

    while (pos < string_view.size()) {
        size_t found = string_view.find(delimiter, pos);
        if (found == std::string_view::npos) {
            result.emplace_back(string_view.substr(pos));
            break;
        }
        result.emplace_back(string_view.substr(pos, found - pos));
        pos = found + 1;
    }

    return result;
}

int ParseGameId(std::string input_string) {
    std::vector<std::string> space_split = split(input_string, ' ');
    return stoi(space_split[1]);

}

Cubes ParseResultString(std::string game_result) {
    // 3 blue, 4 red
    Cubes results{};
    std::vector<std::string> comma_split = split(game_result, ',');
    for (std::string result_string : comma_split) {
        boost::algorithm::trim(result_string);
        std::vector<std::string> result_split = split(result_string, ' ');

        if (result_split[1] == "red") {
            results.red = std::stoi(result_split[0]);
        }
        else if (result_split[1] == "green") {
            results.green = std::stoi(result_split[0]);
        }
        else if (result_split[1] == "blue") {
            results.blue = std::stoi(result_split[0]);
        }
        else {
            std::cout << "Unknown Colour";
        }
    }
    return results;
}

std::vector<Cubes> ParseResults(std::string input_string) {
      // 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    std::vector<Cubes> parsed_results;
    std::vector<std::string> games_results = split(input_string, ';');

    for (std::string result_string : games_results) {
        parsed_results.push_back(ParseResultString(result_string));
    }

    return parsed_results;

};
 
Game ParseLine(std::string input_string) {
    Game game_data;
    std::vector<std::string> colon_split = split(input_string, ':');
    game_data.id = ParseGameId(colon_split[0]);
    game_data.results = ParseResults(colon_split[1]);
    return game_data;

    };

std::vector<Game> LoadData(std::string data_path)
{
    std::ifstream input_file(data_path);
    std::string current_line;

    std::vector<Game> game_data;
    while (std::getline(input_file, current_line))
    {
        game_data.push_back(ParseLine(current_line));
 
    }


    return game_data;
}

int SolvePart1(std::vector<Game> match_data) {
    Cubes bag{ 12,13,14 };
    int id_total = 0;
    
    for (Game match : match_data) {
        bool isValid = true;
        for (Cubes game : match.results) {
            if (!(game.red <= bag.red && game.green <= bag.green && game.blue <= bag.blue)) {
                isValid = false;
            }
        }
        if (isValid) {
            id_total += match.id;
        }
    }
    return id_total;
}

int SolvePart2(std::vector<Game> match_data) {
    int power_total = 0;
    for (Game match : match_data) {
        Cubes min_cubes{ 0,0,0 };
        for (Cubes game : match.results) {

            if (game.red > min_cubes.red) {
                min_cubes.red = game.red;
            }
            if (game.green > min_cubes.green) {
                min_cubes.green = game.green;
            }
            if (game.blue > min_cubes.blue) {
                min_cubes.blue = game.blue;
            }

        }
        power_total += min_cubes.red * min_cubes.green * min_cubes.blue;
    }
    return power_total;
}

int Day2(){

    std::vector<Game> data_example = LoadData("Data/Day2-Example.txt");
    std::vector<Game> data_part1 = LoadData("Data/Day2_Part1.txt");


    int result_example = SolvePart1(data_example);
    std::cout << "Day 2 Part 1 Example: " << result_example << "\n";

    int result_part1 = SolvePart1(data_part1);
    std::cout << "Day 2 Part 1: " << result_part1 << "\n";

    int result_part2_example = SolvePart2(data_example);
    std::cout << "Day 2 Part 2 Example: " << result_part2_example << "\n";

    int result_part2 = SolvePart2(data_part1);
    std::cout << "Day 2 Part 2: " << result_part2 << "\n";
    return 0;
}