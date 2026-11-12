#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstring> //this is for strcpy to board current move from the input in main
#include <string.h>
#include <array>
#include <vector>
#include <stdio.h>
//I may want to put this in a class.

enum class pieces {
	NA = 0, WP = 1, WK = 2, WB = 3, WR = 4, WQ = 5, WKING = 6,
	BP = 7, BK = 8, BB = 9, BR = 10, BQ = 11, BKING = 12
};

