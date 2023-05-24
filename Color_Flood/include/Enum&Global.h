#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <sstream>
#include <string>

using namespace sf;

typedef enum
{
	PLAYER = 0,
	COMPUTER = 1,
	NO_PLAYER = 2
} Turn;

typedef enum
{
	NO_DIFFICULTY = 0,
	EASY = 1,
	MEDIUM = 2,
	HARD = 3

} HardnessLevel;

typedef enum
{
	ORANGE = 0,
	RED = 1,
	BLUE = 2,
	YELLOW = 3,
	PURPLE = 4,
	PINK = 5
} Colors;

const float SIZE_Y = 50;
const float SIZE_X = 205;
const int COLOR_SIZE = 6;
const float WIN_LIMIT = 50;
const float BUTTON_INIT_Y = 5;
const float BUTTON_INIT_X = 60;
const float BUTTON_POS_X = 500;
const int difficultOptions = 3;
const unsigned int SIZE_TXT = 26;
const unsigned int SIZE_BRD = 25;
const unsigned int TITLE_SIZE = 48;
const float BUTTON_COLOR_SIZE = 40;




