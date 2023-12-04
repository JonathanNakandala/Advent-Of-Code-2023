#include <iostream>
#include <string>
#include "Day1.h"
#include <fstream>
#include <vector>
#include <map>
#include <optional>

const std::string kSearchValues = "123456789";
struct NumberData
{
	size_t position;
	std::string number;
};

int CalculatePart1Line(std::string input_string)
{
	size_t first_num_pos = input_string.find_first_of(kSearchValues);
	size_t last_num_pos = input_string.find_last_of(kSearchValues);

	std::string number_string = std::string(1, input_string[first_num_pos]) + std::string(1, input_string[last_num_pos]);

	return stoi(number_string);
}

std::optional<NumberData> GetNumber(std::string string_to_search, bool from_start = true)
{
	std::vector<NumberData> matched_numbers;

	std::map<std::string, std::string> numbers_map;

	numbers_map["one"] = "1";
	numbers_map["two"] = "2";
	numbers_map["three"] = "3";
	numbers_map["four"] = "4";
	numbers_map["five"] = "5";
	numbers_map["six"] = "6";
	numbers_map["seven"] = "7";
	numbers_map["eight"] = "8";
	numbers_map["nine"] = "9";

	for (auto &[word, number] : numbers_map)
	{
		size_t found_position = string_to_search.find(word);
		while (found_position != std::string::npos)
		{
			NumberData number_data;
			number_data.position = found_position;
			number_data.number = number;
			matched_numbers.push_back(number_data);

			found_position = string_to_search.find(word, found_position + 1);
		}
	}

	std::map<std::string, std::string>::iterator it;
	for (it = numbers_map.begin(); it != numbers_map.end(); ++it)
	{
		size_t found_position = string_to_search.find(it->first);
		if (found_position != std::string::npos)
		{
			NumberData number_data;
			number_data.position = found_position;
			number_data.number = it->second;
			matched_numbers.push_back(number_data);
		}
	};

	if (matched_numbers.size() == 1)
	{
		return matched_numbers[0];
	}
	else if (matched_numbers.size() > 1)
	{
		size_t position = from_start ? std::numeric_limits<size_t>::max() : std::numeric_limits<size_t>::min();
		size_t matched_index = 0;

		for (size_t i = 0; i < matched_numbers.size(); ++i)
		{
			if (from_start)
			{
				if (matched_numbers[i].position < position)
				{
					position = matched_numbers[i].position;
					matched_index = i;
				}
			}
			else
			{
				if (matched_numbers[i].position > position)
				{
					position = matched_numbers[i].position;
					matched_index = i;
				}
			}
		}
		return matched_numbers[matched_index];
	}

	return std::nullopt;
}

std::string FindFirstNumber(std::string input_string)
{
	size_t first_num_pos = input_string.find_first_of(kSearchValues);
	if (first_num_pos == 0)
	{
		return std::string(1, input_string[first_num_pos]);
	}
	if (first_num_pos == std::string::npos)
	{

		std::optional<NumberData> first_string = GetNumber(input_string);

		if (first_string.has_value())
		{

			NumberData first_number_string = first_string.value();
			return first_number_string.number;
		}
	}
	else
	{
		std::string string_upto_first_int = input_string.substr(0, first_num_pos);
		std::optional<NumberData> first_result = GetNumber(string_upto_first_int);
		if (first_result.has_value())
		{

			NumberData first_number_string = first_result.value();
			if (first_num_pos < first_number_string.position)
			{
				return std::string(1, string_upto_first_int[first_num_pos]);
			}
			else
			{
				return first_number_string.number;
			}
		}
	}

	return std::string(1, input_string[first_num_pos]);
}

std::string FindLastNumber(std::string input_string)
{
	size_t last_num_pos = input_string.find_last_of(kSearchValues);
	if (last_num_pos == input_string.length() - 1)
	{
		return std::string(1, input_string[last_num_pos]);
	}
	std::optional<NumberData> last_result = GetNumber(input_string, false);
	if (last_num_pos == std::string::npos)
	{

		std::optional<NumberData> first_string = GetNumber(input_string, false);

		if (first_string.has_value())
		{

			NumberData first_number_string = first_string.value();
			return first_number_string.number;
		}
	}
	else
	{
		std::string string_upto_first_int = input_string.substr(last_num_pos, input_string.length());
		std::optional<NumberData> last_result = GetNumber(input_string, false);
		if (last_result.has_value())
		{

			NumberData last_number_string = last_result.value();
			if (last_num_pos > last_number_string.position)
			{
				return std::string(1, input_string[last_num_pos]);
			}
			else
			{
				return last_number_string.number;
			}
		}
	}
	return std::string(1, input_string[last_num_pos]);
	;
}

int CalculatePart2Line(std::string input_string)
{
	std::string first_number = FindFirstNumber(input_string);
	std::string last_number = FindLastNumber(input_string);

	std::cout << "Line: " << input_string << " First Number: " << first_number << " Last Number: " << last_number << "\n";
	return stoi(first_number + last_number);
}

int SolvePart(std::string data_path, bool part_2 = false)
{
	std::ifstream input_file(data_path);
	std::string current_line;

	std::vector<int> line_values;
	while (std::getline(input_file, current_line))
	{
		if (part_2)
		{
			line_values.push_back(CalculatePart2Line(current_line));
		}
		else
		{

			line_values.push_back(CalculatePart1Line(current_line));
		}
	}
	int total = 0;
	for (int &x : line_values)
	{
		total += x;
	};

	return total;
}

int Day1()
{

	int part_1_example_answer = SolvePart("Data/Day1_Part1-Example.txt");
	std::cout << "Part 1 Example: " << part_1_example_answer << "\n";
	int part_1_answer = SolvePart("Data/Day1_Part1.txt");
	std::cout << "Part 1: " << part_1_answer << "\n";

	int part_2_example_answer = SolvePart("Data/Day1_Part2-Example.txt", true);
	std::cout << "Part 2 Example: " << part_2_example_answer << "\n";

	int part_2_answer = SolvePart("Data/Day1_Part1.txt", true);
	std::cout << "Part 2: " << part_2_answer << "\n";
	return 0;
}