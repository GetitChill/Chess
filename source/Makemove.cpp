#include "Makemove.h"

void Move(board* b)
{
		b->switch_sides = false;

		for (int i = 0; i < board::width * board::height; ++i)
		{
			if (b->p.piece_to_move_on_board == b->board_array[i])
			{
				if (check_if_we_can_move_to_destination(b, i))
				{
					//Now we know that we can move this thing, it's non ambiguous
					//We are going to set the position of the piece from the string to it's index to move cause it passed
					if (b->p.typeOfMove == CASTLEKING && b->p.piece_to_move_on_board == WKING)
					{
						b->board_array[b->p.index_to_move] = b->p.piece_to_move_on_board;
						b->board_array[61] = WR;
						//Then we set the current index to NA
						b->board_array[i] = NA;
						b->board_array[63] = NA;
						b->switch_sides = true;
						break;
					}
					else if (b->p.typeOfMove == CASTLEKING && b->p.piece_to_move_on_board == BKING)
					{
						b->board_array[b->p.index_to_move] = b->p.piece_to_move_on_board;
						b->board_array[5] = BR;
						//Then we set the current index to NA
						b->board_array[i] = NA;
						b->board_array[7] = NA;
						b->switch_sides = true;
						break;
					}
					else if (b->p.typeOfMove == CASTLEQUEEN && b->p.piece_to_move_on_board == WKING)
					{
						b->board_array[b->p.index_to_move] = b->p.piece_to_move_on_board;
						b->board_array[59] = WR;
						//Then we set the current index to NA
						b->board_array[i] = NA;
						b->board_array[56] = NA;
						b->switch_sides = true;
						break;
					}
					else if (b->p.typeOfMove == CASTLEQUEEN && b->p.piece_to_move_on_board == BKING)
					{
						b->board_array[b->p.index_to_move] = b->p.piece_to_move_on_board;
						b->board_array[3] = BR;
						//Then we set the current index to NA
						b->board_array[i] = NA;
						b->board_array[0] = NA;
						b->switch_sides = true;
						break;
					}
					//So this is going to cause some problems as well - which is a bit unfortunate. 

					b->board_array[b->p.index_to_move] = b->p.piece_to_move_on_board;
					//Then we set the current index to NA
					b->board_array[i] = NA;
					b->switch_sides = true;
					break;

				}
			}
		}


		//change board at the end
		if (b->turn == 1 && b->switch_sides)
		{
			b->turn = 0;
		}
		else if (b->turn == 0 && b->switch_sides)
		{
			b->turn = 1;
		}
		//And we need to reset the char enum and location? 

}
