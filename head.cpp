#include "headers.h"

pieces board::return_corresponding_enum_to_piece(const char a) const
{
	//Pieces is global - this is a bit scary :(
	pieces pi = pieces::NA;
	asciiPieces pieceTypeToMove = asciiPieces::PAWN;

	if (a == 82 || a == 78 || a == 66 || a == 81 || a == 75)
	{
		//so we need to cast this
		pieceTypeToMove = static_cast<asciiPieces>(a);
	}
	//Now we set pi
	if (turn == 0 && pieceTypeToMove == asciiPieces::PAWN)
	{
		return pieces::WP;
	}
	else if (turn == 0 && pieceTypeToMove == asciiPieces::ROOK)
	{
		return pieces::WR;
	}
	else if (turn == 0 && pieceTypeToMove == asciiPieces::KNIGHT)
	{
		return pieces::WK;
	}
	else if (turn == 0 && pieceTypeToMove == asciiPieces::BISHOP)
	{
		return pieces::WB;
	}
	else if (turn == 0 && pieceTypeToMove == asciiPieces::QUEEN)
	{
		return pieces::WQ;
	}
	else if (turn == 0 && pieceTypeToMove == asciiPieces::KING)
	{
		return pieces::WKING;
	}
	//For the black pieces.
	else if (turn == 1 && pieceTypeToMove == asciiPieces::PAWN)
	{
		return pieces::BP;
	}
	else if (turn == 1 && pieceTypeToMove == asciiPieces::ROOK)
	{
		return pieces::BR;
	}
	else if (turn == 1 && pieceTypeToMove == asciiPieces::KNIGHT)
	{
		return pieces::BK;
	}
	else if (turn == 1 && pieceTypeToMove == asciiPieces::BISHOP)
	{
		return pieces::BB;
	}
	else if (turn == 1 && pieceTypeToMove == asciiPieces::QUEEN)
	{
		return pieces::BQ;
	}
	else if (turn == 1 && pieceTypeToMove == asciiPieces::KING)
	{
		return pieces::BKING;
	}
}

piece_to_move::moveStatus board::determineMove()
{
	bool type_is_decided = false;


	p.typeOfMove = piece_to_move::moveStatus::DUMMY;

	size_t string_size = strlen(p.current_Move);

	//strcmp returns a 0
	if (strcmp(p.current_Move, "O-O") == 0)
	{
		p.typeOfMove = piece_to_move::moveStatus::CASTLEKING;
		type_is_decided = true;
	}
	else if (strcmp(p.current_Move, "O-O-O") == 0 && !type_is_decided)
	{
		p.typeOfMove = piece_to_move::moveStatus::CASTLEQUEEN;
		type_is_decided = true;
	}
	else if (p.current_Move[string_size - 1] == '+' && !type_is_decided && p.current_Move[2] != '=')
	{
		p.typeOfMove = piece_to_move::moveStatus::CHECK;
		type_is_decided = true;
	}
	else if (p.current_Move[string_size - 1] == '+' && !type_is_decided && p.current_Move[2] == '=')
	{
		p.typeOfMove = piece_to_move::moveStatus::PROMO;
		type_is_decided = true;
	}
	else if (p.current_Move[string_size - 1] == '#' && !type_is_decided)
	{
		p.typeOfMove = piece_to_move::moveStatus::MATE;
		type_is_decided = true;
	}

	else if (!type_is_decided && (strchr(p.current_Move, 'x') != NULL))
	{

		type_is_decided = true;

		if (type_is_decided && string_size == 4)
		{
			p.typeOfMove = piece_to_move::moveStatus::RATTACK;
		}
		else if (type_is_decided && string_size > 4)
		{
			p.typeOfMove = piece_to_move::moveStatus::AATTACK;
		}
	}

	else if ((p.current_Move[0] == 82 || p.current_Move[0] == 78 || p.current_Move[0] == 66 || p.current_Move[0] == 81 || p.current_Move[0] == 75) && !type_is_decided && string_size == 3)
	{
		p.typeOfMove = piece_to_move::moveStatus::RMOVE;
		type_is_decided = true;
	}
	else if ((p.current_Move[0] == 82 || p.current_Move[0] == 78 || p.current_Move[0] == 66 || p.current_Move[0] == 81 || p.current_Move[0] == 75) && !type_is_decided && !(string_size == 3))
	{
		p.typeOfMove = piece_to_move::moveStatus::AMOVE;
		type_is_decided = true;
	}
	else if (!type_is_decided && p.current_Move[0] >= 'a' && p.current_Move[0] <= 'h' && string_size == 2)
	{
		p.typeOfMove = piece_to_move::moveStatus::RPAWNMOVE;
		type_is_decided = true;
	}

	else
	{
		p.typeOfMove = piece_to_move::moveStatus::APAWNMOVE;
		type_is_decided = true;
	}




	return p.typeOfMove;
}

//We'll get input from main
void board::setCurrentMove(const char* input)
{
	strcpy(p.current_Move, input);
}

void board::parseMove()
{
	size_t string_length = strlen(p.current_Move);

	int x_for_index = 0;
	int y_for_index = 0;

	switch (p.typeOfMove)
	{
	case piece_to_move::moveStatus::RATTACK:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p.current_Move[string_length - 1] - 48);
		break;
	case piece_to_move::moveStatus::AATTACK:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p.current_Move[string_length - 1] - 48);
		break;
	case piece_to_move::moveStatus::CASTLEKING:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(75);
		if (p.piece_to_move_on_board == pieces::WKING)
		{
			x_for_index = 'g' - 97;
			y_for_index = 8 - ('1' - 48);
		}
		else if (p.piece_to_move_on_board == pieces::BKING)
		{
			x_for_index = 'g' - 97;
			y_for_index = 8 - ('8' - 48);
		}
		break;
	case piece_to_move::moveStatus::CASTLEQUEEN:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(75);
		if (p.piece_to_move_on_board == pieces::WKING)
		{
			x_for_index = 'c' - 97;
			y_for_index = 8 - ('1' - 48);
		}
		else if (p.piece_to_move_on_board == pieces::BKING)
		{
			x_for_index = 'c' - 97;
			y_for_index = 8 - ('8' - 48);
		}
		break;
	case piece_to_move::moveStatus::CHECK:
		//It could be a pawn 
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[string_length - 3] - 97;
		y_for_index = 8 - (p.current_Move[string_length - 2] - 48);
		break;
	case piece_to_move::moveStatus::MATE:
		//It could be a pawn 
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[string_length - 3] - 97;
		y_for_index = 8 - (p.current_Move[string_length - 2] - 48);
		break;
	case piece_to_move::moveStatus::RMOVE:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p.current_Move[string_length - 1] - 48);
		break;
	case piece_to_move::moveStatus::AMOVE:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p.current_Move[string_length - 1] - 48);
		break;
	case piece_to_move::moveStatus::RPAWNMOVE:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[0] - 97;
		y_for_index = 8 - (p.current_Move[1] - 48);
		break;
	case piece_to_move::moveStatus::APAWNMOVE:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[0] - 97;
		y_for_index = 8 - (p.current_Move[1] - 48);
		break;
	case piece_to_move::moveStatus::PROMO:
		p.piece_to_move_on_board = return_corresponding_enum_to_piece(p.current_Move[0]);
		x_for_index = p.current_Move[0] - 97;
		y_for_index = 8 - (p.current_Move[1] - 48);
		break;
	}
	p.index_to_move = x_for_index + (y_for_index * board::width);
}

bool board::check_if_impeded_by_ally_piece(int current_index) const
{
	bool good = true;


	int file_current = current_index % 8;
	int rank_current = 8 - (current_index / 8);

	int piece_index_to_move_file = p.index_to_move % 8;
	int piece_index_to_move_rank = 8 - (p.index_to_move / 8);

	int incrementer = 0; //WE NEED TO FIGURE THIS PART OUT

	//This is checking for the knight.
	if (board_array[current_index] == pieces::WK || board_array[current_index] == pieces::BK)
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
		// p.index_to_move == (current_index - 6) || p.index_to_move == (current_index + 10) || p.index_to_move == (current_index + 6) || p.index_to_move == (current_index - 10))
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
	else if (board_array[current_index] == pieces::WP && p.typeOfMove == piece_to_move::moveStatus::RPAWNMOVE)
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
	else if (board_array[current_index] == pieces::WP && p.typeOfMove == piece_to_move::moveStatus::RATTACK)
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

	else if (board_array[current_index] == pieces::BP && p.typeOfMove == piece_to_move::moveStatus::RPAWNMOVE)
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
	else if (board_array[current_index] == pieces::BP && p.typeOfMove == piece_to_move::moveStatus::RATTACK)
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
	else if (board_array[current_index] == pieces::WB || board_array[current_index] == pieces::BB)
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

	else if (board_array[current_index] == pieces::WB || board_array[current_index] == pieces::BB)
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
	else if (board_array[current_index] == pieces::WQ || board_array[current_index] == pieces::BQ || board_array[current_index] == pieces::WKING || board_array[current_index] == pieces::BKING)
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

	while (current_index != p.index_to_move)
	{
		//We don't need/want to check our current index. This is going to involve knowing the piece.
		current_index += incrementer;
		//if it's white.
		if (turn == 0)
		{
			//if the current box has an ally piece in it's path, then we can't move there. We're returning false if a square has an allied piece.
			if (board_array[current_index] == pieces::WP || board_array[current_index] == pieces::WB || board_array[current_index] == pieces::WR || board_array[current_index] == pieces::WK || board_array[current_index] == pieces::WQ || board_array[current_index] == pieces::WKING)
			{
				good = false;
				break;
			}
		}
		//it's blacks turn
		else if (turn == 1)
		{
			if (board_array[current_index] == pieces::BP || board_array[current_index] == pieces::BB || board_array[current_index] == pieces::BR || board_array[current_index] == pieces::BK || board_array[current_index] == pieces::BQ || board_array[current_index] == pieces::BKING)
			{
				good = false;
				break;
			}
		}
	}
	return good;
}

bool board::check_if_we_can_move_to_destination(const int current_index) 
{
	if (p.piece_to_move_on_board == pieces::WK || p.piece_to_move_on_board == pieces::BK)
	{
		if (p.index_to_move == (current_index + 15) || p.index_to_move == (current_index + 17) || p.index_to_move == (current_index - 15) || p.index_to_move == (current_index - 17) || p.index_to_move == (current_index - 6) || p.index_to_move == (current_index + 10) || p.index_to_move == (current_index + 6) || p.index_to_move == (current_index - 10))
		{

			if (check_if_impeded_by_ally_piece( current_index))
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
	else if (p.piece_to_move_on_board == pieces::WP)
	{
		//Add the piece in the way checker thingy.
		//40 - 48 = -8;

		int val = p.index_to_move - current_index;

		if (p.index_to_move - current_index == -8 || p.index_to_move - current_index == -16 && p.typeOfMove == piece_to_move::moveStatus::RPAWNMOVE)
		{
			if (check_if_impeded_by_ally_piece( current_index))
			{
				return true;
			}
		}
		//this is for attack 
		else if ((p.index_to_move - current_index == -9 || p.index_to_move - current_index == -7) && p.typeOfMove == piece_to_move::moveStatus::RATTACK)
		{
			if (check_if_impeded_by_ally_piece( current_index))
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
	else if (p.piece_to_move_on_board == pieces::BP)
	{
		//Add the piece in the way checker thingy.
		if (p.index_to_move - current_index == 8 || p.index_to_move - current_index == 16 && p.typeOfMove == piece_to_move::moveStatus::RPAWNMOVE)
		{
			if (check_if_impeded_by_ally_piece( current_index))
			{
				return true;
			}
		}
		else if ((p.index_to_move - current_index == 9 || p.index_to_move - current_index == 7) && p.typeOfMove == piece_to_move::moveStatus::RATTACK)
		{
			if (check_if_impeded_by_ally_piece( current_index))
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
	else if (p.piece_to_move_on_board == pieces::WB || p.piece_to_move_on_board == pieces::BB)
	{
		if ((p.index_to_move - current_index) % 9 == 0 || (p.index_to_move - current_index) % 7 == 0)
		{
			if (check_if_impeded_by_ally_piece( current_index))
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

	else if (p.piece_to_move_on_board == pieces::WR || p.piece_to_move_on_board == pieces::BR)
	{
		int left_side_remainder = current_index - (current_index % 8);

		if ((p.index_to_move - current_index) % 8 == 0 || ((p.index_to_move >= left_side_remainder) && (p.index_to_move <= current_index + (8 - (current_index % 8) - 1))))
		{
			if (check_if_impeded_by_ally_piece( current_index))
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else if (p.piece_to_move_on_board == pieces::BKING || p.piece_to_move_on_board == pieces::WKING)
	{
		//This if below me is legit saying, from my current piece, is my index to move around my circle of squares? There's no mod so it's literal.
		if ((p.index_to_move - current_index == -1 || (p.index_to_move - current_index) == -9 || p.index_to_move - current_index == -8 || p.index_to_move - current_index == -7 || p.index_to_move - current_index == 1 || (p.index_to_move - current_index) == 9 || p.index_to_move - current_index == 8 || p.index_to_move - current_index == 7))
		{
			if (check_if_impeded_by_ally_piece( current_index))
			{
				if (p.piece_to_move_on_board == pieces::WKING)
				{
					castle_array[static_cast<int>(castleRights::WQC)] = false;
					castle_array[static_cast<int>(castleRights::WKC)] = false;
				}
				return true;
			}
		}
		else if (check_if_impeded_by_ally_piece( current_index) && (p.typeOfMove == piece_to_move::moveStatus::CASTLEQUEEN || p.typeOfMove == piece_to_move::moveStatus::CASTLEKING))
		{
			//And we need to check for the flags
			//in move we're going to assign the indecies after we check this bull shit.
			if (p.piece_to_move_on_board == pieces::WKING)
			{
				if (p.typeOfMove == piece_to_move::moveStatus::CASTLEKING && castle_array[static_cast<int>(castleRights::WKC)])
				{
					return true;
				}
				else if (p.typeOfMove == piece_to_move::moveStatus::CASTLEQUEEN && castle_array[static_cast<int>(castleRights::WQC)])
				{
					return true;
				}
			}
			else if (p.piece_to_move_on_board == pieces::BKING)
			{
				if (p.typeOfMove == piece_to_move::moveStatus::CASTLEKING && castle_array[static_cast<int>(castleRights::BKC)])
				{
					return true;
				}
				if (p.typeOfMove == piece_to_move::moveStatus::CASTLEQUEEN && castle_array[static_cast<int>(castleRights::BQC)])
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
	else if (p.piece_to_move_on_board == pieces::BQ || p.piece_to_move_on_board == pieces::WQ)
	{
		//Just mix the bishop and rook tests. Just make sure there's an or between them, cause the queen can move like either of them.
		if (/*Bishop*/((p.index_to_move - current_index) % 9 == 0 || (p.index_to_move - current_index) % 7 == 0) ||
			/*Rook*/ ((p.index_to_move - current_index) % 8 == 0 ||
				((p.index_to_move >= (current_index - (current_index % 8))) && (p.index_to_move <= current_index + (8 - (current_index % 8) - 1)))))
		{
			if (check_if_impeded_by_ally_piece( current_index))
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
void board::Move()
{
	switch_sides = false;

	for (int i = 0; i < board::width * board::height; ++i)
	{
		if (p.piece_to_move_on_board == board_array[i])
		{
			if (check_if_we_can_move_to_destination(i))
			{
				
				if (p.typeOfMove == piece_to_move::moveStatus::CASTLEKING && p.piece_to_move_on_board == pieces::WKING)
				{
					board_array[p.index_to_move] = p.piece_to_move_on_board;
					board_array[61] = pieces::WR;

					board_array[i] = pieces::NA;
					board_array[63] = pieces::NA;
					switch_sides = true;
					break;
				}
				else if (p.typeOfMove == piece_to_move::moveStatus::CASTLEKING && p.piece_to_move_on_board == pieces::BKING)
				{
					board_array[p.index_to_move] = p.piece_to_move_on_board;
					board_array[5] = pieces::BR;
					//Then we set the current index to pieces::NA
					board_array[i] = pieces::NA;
					board_array[7] = pieces::NA;
					switch_sides = true;
					break;
				}
				else if (p.typeOfMove == piece_to_move::moveStatus::CASTLEQUEEN && p.piece_to_move_on_board == pieces::WKING)
				{
					board_array[p.index_to_move] = p.piece_to_move_on_board;
					board_array[59] = pieces::WR;
					//Then we set the current index to pieces::NA
					board_array[i] = pieces::NA;
					board_array[56] = pieces::NA;
					switch_sides = true;
					break;
				}
				else if (p.typeOfMove == piece_to_move::moveStatus::CASTLEQUEEN && p.piece_to_move_on_board == pieces::BKING)
				{
					board_array[p.index_to_move] = p.piece_to_move_on_board;
					board_array[3] = pieces::BR;
					//Then we set the current index to pieces::NA
					board_array[i] = pieces::NA;
					board_array[0] = pieces::NA;
					switch_sides = true;
					break;
				}
				//So this is going to cause some problems as well - which is a bit unfortunate. 

				board_array[p.index_to_move] = p.piece_to_move_on_board;
				//Then we set the current index to pieces::NA
				board_array[i] = pieces::NA;
				switch_sides = true;
				break;

			}
		}
	}

	if (turn == 1 && switch_sides)
	{
		turn = 0;
	}
	else if (turn == 0 && switch_sides)
	{
		turn = 1;
	}
}
void board::drawBoard()
{
	for (int i = 1; i <= board::height * board::width; ++i)
	{
		printf("%d ", board_array[i - 1]);
		if (i % 8 == 0)
		{
			printf("\n");
		}
	}
}

void board::readFEN(const char* fenstring)
{
	int val = 0;
	int space_counter = 0;
	int castle_first_dash_check_index = 0;



	for (int count = 0; fenstring[count] != '\0';)
	{

		if (space_counter == 0)
		{
			switch (fenstring[count])
			{

			case 'r': board_array[val] = pieces::BR; count += 1; val += 1; break;
			case 'R': board_array[val] = pieces::WR; count += 1; val += 1; break;
			case 'n': board_array[val] = pieces::BK; count += 1; val += 1; break;
			case 'N': board_array[val] = pieces::WK; count += 1; val += 1; break;
			case 'b': board_array[val] = pieces::BB; count += 1; val += 1; break;
			case 'B': board_array[val] = pieces::WB; count += 1; val += 1; break;
			case 'q': board_array[val] = pieces::BQ; count += 1; val += 1; break;
			case 'Q': board_array[val] = pieces::WQ; count += 1; val += 1; break;
			case 'k': board_array[val] = pieces::BKING; count += 1; val += 1; break;
			case 'K': board_array[val] = pieces::WKING; count += 1; val += 1;  break;
			case 'p': board_array[val] = pieces::BP; count += 1; val += 1;  break;
			case 'P': board_array[val] = pieces::WP; count += 1; val += 1;  break;
			case '/': count += 1; break;
			case ' ': ++space_counter; count += 1; break; //We just want to skip kinda like the 
			default:
				int v = fenstring[count] - '0';
				for (int i = 0; i < v; ++val, ++i)
				{
					board_array[val] = pieces::NA;
				}
				++count;
				break;
			}
		}

		else if (space_counter == 1)
		{
			//I do this count++ thing in the cases cause I find that I need to do some stuff after and it messes with that.
			switch (fenstring[count])
			{
			case ' ': ++space_counter; count += 1; castle_first_dash_check_index = count; break;
			case 'w': turn = 0; count += 1; break;
			default: turn = 1; count += 1; break;
			}
		}

		else if (space_counter == 2)
		{
			switch (fenstring[count])
			{
			case 'K': castle_array[static_cast<int>(castleRights::WKC)] = true;  count += 1; break;
			case 'Q': castle_array[static_cast<int>(castleRights::WQC)] = true; count += 1; break;
			case 'k': castle_array[static_cast<int>(castleRights::BKC)] = true; count += 1; break;
			case 'q': castle_array[static_cast<int>(castleRights::WQC)] = true; count += 1; break;

				//This will check if we move onto the next portion of the string
			case ' ': ++space_counter; count += 1; break;
				//We know that this would reference the second - cause we check for the first in the first if, and increment the string;
			case '-': count += 1; break;
			}
		}
		//r4k1r/2p2ppp/3q4/1P3n2/Bbbn4/5P2/NBPQ2PP/R3R1K1 b - 23
		else if (space_counter == 3)
		{
			//Here is where we hit the dash
			char a = fenstring[count];
			switch (fenstring[count])
			{
			case '-': count += 1; break;
			case ' ':++space_counter; count += 1; break;
			default: count += 1; break;
			}
		}
		else if (space_counter == 4)
		{
			
			int number_of_digits = 0;
			for (int j = count; (fenstring[j] != ' '); ++j)
			{
				++number_of_digits;
			}
			plays_since_pawn[number_of_digits] = '\0';

			//(fenstring[count] != ' ') ||
			for (int i = 0; (plays_since_pawn[i] != '\0'); count += 1, ++i)
			{
				plays_since_pawn[i] = fenstring[count];
			}
			switch (fenstring[count])
			{
			case '-': count += 1; break;
			case ' ':++space_counter; count += 1; break;
			default: count += 1; break;
			}
		}
		else if (space_counter == 5)
		{
			int i = 0;
			for (; fenstring[count] != '\0'; count += 1, ++i)
			{
				full_move_number[i] = fenstring[count];
			}
			full_move_number[i] = '\0';
		}
	}
}

