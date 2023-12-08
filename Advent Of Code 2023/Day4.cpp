#include "Utils.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <numeric>
struct Card
{
    int id;
    std::vector<int> winning;
    std::vector<int> your;
};

int ParseCardId(std::string input_string)
{
    std::vector<std::string> space_split = split(input_string, ' ');
    return stoi(space_split[1]);
}

std::vector<int> ParseResults(std::string input_string)
{
    std::vector<int> parsed_results;
    std::vector<std::string> number_list = split(input_string, ' ');

    for (std::string int_string : number_list)
    {

        parsed_results.push_back(stoi(int_string));
    }

    return parsed_results;
};

Card ParseLine(std::string input_string)
{
    Card game_data;
    std::vector<std::string> colon_split = split(input_string, ':');
    game_data.id = ParseCardId(colon_split[0]);
    // game_data.results = ParseResults(colon_split[1]);

    std::vector<std::string> games_results = split(colon_split[1], '|');
    std::string winning_string = games_results[0];
    std::string your_string = games_results[1];
    boost::algorithm::trim(winning_string);
    boost::algorithm::trim(your_string);
    game_data.winning = ParseResults(winning_string);
    game_data.your = ParseResults(your_string);
    return game_data;
};

std::vector<Card> LoadData(std::string data_path)
{
    std::ifstream input_file(data_path);
    std::string current_line;

    std::vector<Card> game_data;
    while (std::getline(input_file, current_line))
    {
        game_data.push_back(ParseLine(current_line));
    }

    return game_data;
}

std::vector<int> FindCommonNumbers(std::vector<int> winning, std::vector<int> your)
{
    std::sort(winning.begin(), winning.end());
    std::sort(your.begin(), your.end());
    std::vector<int> result;
    boost::range::set_intersection(winning, your, std::back_inserter(result));

    return result;
}

int SolvePart1(std::vector<Card> cards)
{
    int total_points = 0;
    for (Card card : cards)
    {
        int card_points = 0;
        std::vector<int> common_numbers = FindCommonNumbers(card.winning, card.your);
        if (common_numbers.size() != 0)
        {
            card_points = 1;
        }
        for (int i = 2; i <= common_numbers.size(); ++i)
        {
            card_points = card_points * 2;
        }
        total_points += card_points;
    }
    return total_points;
}

std::vector<int> CalculateWinningsCards(Card card, int max)
{
    std::vector<int> new_winnings;
    std::vector<int> common_numbers = FindCommonNumbers(card.winning, card.your);
    int commonCount = common_numbers.size();

    if (card.id + commonCount > max)
    {
        for (int i = 0; i < max - card.id; ++i)
        {
            new_winnings.push_back(card.id + i + 1);
        }
    }
    else
    {
        for (int i = 0; i < commonCount; ++i)
        {
            new_winnings.push_back(card.id + i + 1);
        }
    }

    return new_winnings;
}

int SolvePart2(std::vector<Card> cards)
{
    std::vector<int> card_count(cards.size(), 1);

    for (size_t i = 0; i < cards.size(); ++i)
    {
        std::vector<int> common_numbers = FindCommonNumbers(cards[i].winning, cards[i].your);

        for (int win = 1; win <= common_numbers.size(); ++win)
        {
            if (i + win < card_count.size())
            {
                card_count[i + win] += card_count[i];
            }
        }
    }

    int total_cards = std::accumulate(card_count.begin(), card_count.end(), 0);

    for (size_t i = 0; i < card_count.size(); ++i)
    {
        std::cout << "Card " << i + 1 << ": " << card_count[i] << "\n";
    }

    std::cout << "Total cards: " << total_cards << "\n";
    return total_cards;
}

int Day4()
{

    std::vector<Card> data_example = LoadData("Data/Day4-Example.txt");
    std::vector<Card> data_part1 = LoadData("Data/Day4_Part1.txt");

    int result_example = SolvePart1(data_example);
    std::cout << "Day 4 Part 1 Example: " << result_example << "\n";

    int result_part1 = SolvePart1(data_part1);
    std::cout << "Day 4 Part 1: " << result_part1 << "\n";

    int result_part2_example = SolvePart2(data_example);
    std::cout << "Day 4 Part 2 Example: " << result_part2_example << "\n";
    int result_part2 = SolvePart2(data_part1);
    std::cout << "Day 2 Part 2: " << result_part2 << "\n";
    return 0;
}