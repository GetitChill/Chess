#include "Display.h"

void drawBoard(const board* b)
{
	for (int i = 1; i <= board::height * board::width; ++i)
	{
		printf("%d ", b->board_array[i - 1]);
		if (i % 8 == 0)
		{
			printf("\n");
		}
	}
}
