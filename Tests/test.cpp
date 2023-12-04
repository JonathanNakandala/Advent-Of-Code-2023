#include "pch.h"

#include "../Advent Of Code 2023/Day1.h"
#include "../Advent Of Code 2023/Day1.cpp"
#include <string>

TEST(FindFirstNumber, Test) {
	EXPECT_EQ(FindFirstNumber("4nineeightseven2"), std::string(1, '4'));

}

TEST(FindFirstNumber, Strange15) {
	EXPECT_EQ(FindFirstNumber("bttrx15qfznmdncnz5"), std::string(1, '1'));

}

TEST(FindFirstNumber, Just3Start) {
	EXPECT_EQ(FindFirstNumber("ppckphrtzhstd3xvthzrxxlrrjtk"), std::string(1, '3'));

}


TEST(FindLastNumber,EndString) {
	EXPECT_EQ(FindLastNumber("two1nine"), std::string(1, '9'));

}

TEST(FindLastNumber, EndInt) {
	EXPECT_EQ(FindLastNumber("4nineeightseven2"), std::string(1, '2'));

}

TEST(FindLastNumber, MiddleString) {
	EXPECT_EQ(FindLastNumber("abcone2threexyz"), std::string(1, '3'));

}

TEST(FindLastNumber, MiddleInt) {
	EXPECT_EQ(FindLastNumber("abcone2xyz"), std::string(1, '2'));

}

TEST(FindLastNumber, Just3End) {
	EXPECT_EQ(FindLastNumber("ppckphrtzhstd3xvthzrxxlrrjtk"), std::string(1, '3'));

}

TEST(FindLastNumber, SevenAtEnd) {
	EXPECT_EQ(FindLastNumber("one7ninefivesevenqvpf5xmccsseven"), std::string(1, '7'));

}




