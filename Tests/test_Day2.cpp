#include "pch.h"

#include "../Advent Of Code 2023/Day2.h"
#include "../Advent Of Code 2023/Day2.cpp"
#include <string>





TEST(Day2, ParseGameId, CheckGameIdIsParsed) {
	EXPECT_EQ(ParseGameId("Game 11: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green"), 11);
};


TEST(Day2, ParseResultString, CheckGameIsParsed) {
	Cubes result = ParseResultString("3 blue, 4 red");
	EXPECT_EQ(result.red, 4);
	EXPECT_EQ(result.blue, 3);
	EXPECT_EQ(result.green, 0);
}

TEST(Day2, SolvePart1, Test1) {
	Game game;
	game.id = 23;
	game.results.push_back(Cubes(1, 2, 3));
	std::vector<Game> games{};
	games.push_back(game);
	EXPECT_EQ(SolvePart1(games), 23);
}