#include "Movevalidation.h"


bool check_if_impeded_by_ally_piece(board* b, int current_index) 


{
	bool good = true;
	

	int file_current = current_index % 8; // this get's us the x 0-7. This is 0 indexed REMEMBER.
	int rank_current = 8 - (current_index / 8); // this is inverted. When looking from the white side. We calculate from top right, but count bottom up, so we need to translate this.

	int piece_index_to_move_file = b->p.index_to_move % 8;
	int piece_index_to_move_rank = 8 - (b->p.index_to_move / 8);

	int incrementer = 0; //WE NEED TO FIGURE THIS PART OUT

	//This is checking for the knight.
	//17,15,-17,-15,-6,10,6,-10
	if (b->board_array[current_index] == WK || b->board_array[current_index] == BK)
	{
		//Bottom Right Movement.
		if ((piece_index_to_move_file - file_current) == 1 && (piece_index_to_move_rank - rank_current == -2))
		{
			incrementer = 17;
		}
		//Bottom Left Movement.
		else if ((piece_index_to_move_file - file_current) == -1 && (piece_index_to_move_rank - rank_current) == -2)
		{
			incrementer = 15;
		}
		//Top Left Movement.
		else if ((piece_index_to_move_file - file_current) == -1 && (piece_index_to_move_rank - rank_current) == 2)
		{
			incrementer = -17;
		}
		//Top Right Movement.
		else if ((piece_index_to_move_file - file_current) == 1 && (piece_index_to_move_rank - rank_current) == 2)
		{
			incrementer = -15;
		}
		// b->p.index_to_move == (current_index - 6) || b->p.index_to_move == (current_index + 10) || b->p.index_to_move == (current_index + 6) || b->p.index_to_move == (current_index - 10))
		//L right top
		else if ((piece_index_to_move_file - file_current) == 2 && (piece_index_to_move_rank - rank_current) == 1)
		{
			incrementer = -6;
		}
		else if ((piece_index_to_move_file - file_current) == 2 && (piece_index_to_move_rank - rank_current) == -1)
		{
			incrementer = 10;
		}
		//L bottom left
		else if ((piece_index_to_move_file - file_current) == -2 && (piece_index_to_move_rank - rank_current) == -1)
		{
			incrementer = 6;
		}
		else if ((piece_index_to_move_file - file_current) == -2 && (piece_index_to_move_rank - rank_current) == 1)
		{
			incrementer = -10;
		}
	}
	else if (b->board_array[current_index] == WP && b->p.typeOfMove == RPAWNMOVE)
	{
		if (piece_index_to_move_rank - rank_current == 1)
		{
			incrementer = -8;
		}
		else if (piece_index_to_move_rank - rank_current == 2)
		{
			incrementer = -16;
		}
	}
	else if (b->board_array[current_index] == WP && b->p.typeOfMove == RATTACK)
	{
		//Up and left
		if (piece_index_to_move_rank - rank_current == 1 && piece_index_to_move_file - file_current == -1)
		{
			incrementer = -9;
		}
		//Up and right
		if (piece_index_to_move_rank - rank_current == 1 && piece_index_to_move_file - file_current == 1)
		{
			incrementer = -7;
		}
	}

	else if (b->board_array[current_index] == BP && b->p.typeOfMove == RPAWNMOVE)
	{
		if (piece_index_to_move_rank - rank_current == -1)
		{
			incrementer = 8;
		}
		else if (piece_index_to_move_rank - rank_current == -2)
		{
			incrementer = 16;
		}
	}
	else if (b->board_array[current_index] == BP && b->p.typeOfMove == RATTACK)
	{
		//Up and left
		if (piece_index_to_move_rank - rank_current == -1 && piece_index_to_move_file - file_current == -1)
		{
			incrementer = 7;
		}
		//Up and right
		if (piece_index_to_move_rank - rank_current == -1 && piece_index_to_move_file - file_current == 1)
		{
			incrementer = 9;
		}
	}
	//Bishop
	else if (b->board_array[current_index] == WB || b->board_array[current_index] == BB)
	{
		//bottom right
		if (piece_index_to_move_file > file_current && piece_index_to_move_rank < rank_current)
		{
			incrementer = 9;
		}
		//bottom left
		else if (piece_index_to_move_file < file_current && piece_index_to_move_rank < rank_current)
		{
			incrementer = 7;
		}
		//top left
		else if (piece_index_to_move_file < file_current && piece_index_to_move_rank > rank_current)
		{
			incrementer = -9;
		}
		else if (piece_index_to_move_file > file_current && piece_index_to_move_rank > rank_current)
		{
			incrementer = -7;
		}
	}


	//Rook

	else if (b->board_array[current_index] == WR || b->board_array[current_index] == BR)
	{
		//Straight up. Same file different rank above current
		if (piece_index_to_move_file == file_current && piece_index_to_move_rank > rank_current)
		{
			incrementer = -8;
		}
		//Right - same rank different file. File is greater.
		else if (piece_index_to_move_file > file_current && piece_index_to_move_rank == rank_current)
		{
			incrementer = 1;
		}
		//bottom same file, ideal is less than in rank
		else if (piece_index_to_move_file == file_current && piece_index_to_move_rank < rank_current)
		{
			incrementer = 8;
		}
		//left rank is same file is less
		else if (piece_index_to_move_file < file_current && piece_index_to_move_rank == rank_current)
		{
			incrementer = -1;
		}
	}

	//Queen and Kind have the same moves, and it's stopped in the while loop and checks in check_if_we_can_move_to_destination
	else if (b->board_array[current_index] == WQ || b->board_array[current_index] == BQ || b->board_array[current_index] == WKING || b->board_array[current_index] == BKING)
	{
		//Just combine the bishop and rook.
		//Bishop
		//bottom right
		if (piece_index_to_move_file > file_current && piece_index_to_move_rank < rank_current)
		{
			incrementer = 9;
		}
		//bottom left
		else if (piece_index_to_move_file < file_current && piece_index_to_move_rank < rank_current)
		{
			incrementer = 7;
		}
		//top left
		else if (piece_index_to_move_file < file_current && piece_index_to_move_rank > rank_current)
		{
			incrementer = -9;
		}
		else if (piece_index_to_move_file > file_current && piece_index_to_move_rank > rank_current)
		{
			incrementer = -7;
		}
		//Straight up. Same file different rank above current
		else if (piece_index_to_move_file == file_current && piece_index_to_move_rank > rank_current)
		{
			incrementer = -8;
		}
		//Right - same rank different file. File is greater.
		else if (piece_index_to_move_file > file_current && piece_index_to_move_rank == rank_current)
		{
			incrementer = 1;
		}
		//bottom same file, ideal is less than in rank
		else if (piece_index_to_move_file == file_current && piece_index_to_move_rank < rank_current)
		{
			incrementer = 8;
		}
		//left rank is same file is less
		else if (piece_index_to_move_file < file_current && piece_index_to_move_rank == rank_current)
		{
			incrementer = -1;
		}
	}

	while (current_index != b->p.index_to_move)
	{
		//We don't need/want to check our current index. This is going to involve knowing the piece.
		current_index += incrementer;
		//if it's white.
		if (b->turn == 0)
		{
			//if the current box has an ally piece in it's path, then we can't move there. We're returning false if a square has an allied piece.
			if (b->board_array[current_index] == WP || b->board_array[current_index] == WB || b->board_array[current_index] == WR || b->board_array[current_index] == WK || b->board_array[current_index] == WQ || b->board_array[current_index] == WKING)
			{
				good = false;
				break;
			}
		}
		//it's blacks turn
		else if (b->turn == 1)
		{
			if (b->board_array[current_index] == BP || b->board_array[current_index] == BB || b->board_array[current_index] == BR || b->board_array[current_index] == BK || b->board_array[current_index] == BQ || b->board_array[current_index] == BKING)
			{
				good = false;
				break;
			}
		}
	}
	return good;

}
//Piece && target destination are in the board class, 
bool check_if_we_can_move_to_destination(board* b, int current_index)
/*enum pieces {NA = 0, WP = 1, WK = 2, WB = 3, WR = 4, WQ = 5, WKING = 6, BP = 7, BK = 8, BB = 9, BR = 10, BQ = 11, BKING = 12};*/
{
	if (b->p.piece_to_move_on_board == WK || b->p.piece_to_move_on_board == BK)
	{
		if (b->p.index_to_move == (current_index + 15) || b->p.index_to_move == (current_index + 17) || b->p.index_to_move == (current_index - 15) || b->p.index_to_move == (current_index - 17) || b->p.index_to_move == (current_index - 6) || b->p.index_to_move == (current_index + 10) || b->p.index_to_move == (current_index + 6) || b->p.index_to_move == (current_index - 10))
		{

			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	//White pawn
	else if (b->p.piece_to_move_on_board == WP)
	{
		//Add the piece in the way checker thingy.
		//40 - 48 = -8;

		int val = b->p.index_to_move - current_index;

		if (b->p.index_to_move - current_index == -8 || b->p.index_to_move - current_index == -16 && b->p.typeOfMove == RPAWNMOVE)
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		//this is for attack 
		else if ((b->p.index_to_move - current_index == -9 || b->p.index_to_move - current_index == -7) && b->p.typeOfMove == RATTACK)
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		else
		{
			return false;

		}
	}
	//Black Pawn
	else if (b->p.piece_to_move_on_board == BP)
	{
		//Add the piece in the way checker thingy.
		if (b->p.index_to_move - current_index == 8 || b->p.index_to_move - current_index == 16 && b->p.typeOfMove == RPAWNMOVE)
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		else if ((b->p.index_to_move - current_index == 9 || b->p.index_to_move - current_index == 7) && b->p.typeOfMove == RATTACK)
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		else
		{
			return false;

		}
	}
	//We want to do it for the rest. BISHOP
	else if (b->p.piece_to_move_on_board == WB || b->p.piece_to_move_on_board == BB)
	{
		if ((b->p.index_to_move - current_index) % 9 == 0 || (b->p.index_to_move - current_index) % 7 == 0)
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	//ROOK

	else if (b->p.piece_to_move_on_board == WR || b->p.piece_to_move_on_board == BR)
	{
		int left_side_remainder = current_index - (current_index % 8);

		if ((b->p.index_to_move - current_index) % 8 == 0 || ((b->p.index_to_move >= left_side_remainder) && (b->p.index_to_move <= current_index + (8 - (current_index % 8) - 1))))
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else if (b->p.piece_to_move_on_board == BKING || b->p.piece_to_move_on_board == WKING)
	{
		//This if below me is legit saying, from my current piece, is my index to move around my circle of squares? There's no mod so it's literal.
		if ((b->p.index_to_move - current_index == -1 || (b->p.index_to_move - current_index) == -9 || b->p.index_to_move - current_index == -8 || b->p.index_to_move - current_index == -7 || b->p.index_to_move - current_index == 1 || (b->p.index_to_move - current_index) == 9 || b->p.index_to_move - current_index == 8 || b->p.index_to_move - current_index == 7))
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				if (b->p.piece_to_move_on_board == WKING)
				{
					b->castle_array[WQC] = false;
					b->castle_array[WKC] = false;
				}
				return true;
			}
		}
		else if (check_if_impeded_by_ally_piece(b, current_index) && (b->p.typeOfMove == CASTLEQUEEN || b->p.typeOfMove == CASTLEKING))
		{
			//And we need to check for the flags
			//in move we're going to assign the indecies after we check this bull shit.
			if (b->p.piece_to_move_on_board == WKING)
			{
				if (b->p.typeOfMove == CASTLEKING && b->castle_array[WKC])
				{
					return true;
				}
				else if (b->p.typeOfMove == CASTLEQUEEN && b->castle_array[WQC])
				{
					return true;
				}
			}
			else if (b->p.piece_to_move_on_board == BKING)
			{
				if (b->p.typeOfMove == CASTLEKING && b->castle_array[BKC])
				{
					return true;
				}
				if (b->p.typeOfMove == CASTLEQUEEN && b->castle_array[BQC])
				{
					return true;
				}
			}
		}
		else
		{
			return false;
		}
	}
	else if (b->p.piece_to_move_on_board == BQ || b->p.piece_to_move_on_board == WQ)
	{
		//Just mix the bishop and rook tests. Just make sure there's an or between them, cause the queen can move like either of them.
		if (/*Bishop*/((b->p.index_to_move - current_index) % 9 == 0 || (b->p.index_to_move - current_index) % 7 == 0) ||
			/*Rook*/ ((b->p.index_to_move - current_index) % 8 == 0 ||
				((b->p.index_to_move >= (current_index - (current_index % 8))) && (b->p.index_to_move <= current_index + (8 - (current_index % 8) - 1)))))
		{
			if (check_if_impeded_by_ally_piece(b, current_index))
			{
				return true;
			}

		}
		else
		{
			return false;
		}
	}
	return false;
}
