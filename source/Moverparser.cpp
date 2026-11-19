#define _CRT_SECURE_NO_WARNINGS
#include "Moverparser.h"

#include <cstring>

enum pieces return_corresponding_enum_to_piece(char a, board* b)
{
	enum pieces pi = NA;
	enum asciiPieces pieceTypeToMove = PAWN;

	if (a == 82 || a == 78 || a == 66 || a == 81 || a == 75)
	{
		//so we need to cast this
		pieceTypeToMove = static_cast<asciiPieces>(a);
	}
	//Now we set pi
	if (b->turn == 0 && pieceTypeToMove == PAWN)
	{
		return WP;
	}
	else if (b->turn == 0 && pieceTypeToMove == ROOK)
	{
		return WR;
	}
	else if (b->turn == 0 && pieceTypeToMove == KNIGHT)
	{
		return WK;
	}
	else if (b->turn == 0 && pieceTypeToMove == BISHOP)
	{
		return WB;
	}
	else if (b->turn == 0 && pieceTypeToMove == QUEEN)
	{
		return WQ;
	}
	else if (b->turn == 0 && pieceTypeToMove == KING)
	{
		return WKING;
	}
	//For the black pieces.
	else if (b->turn == 1 && pieceTypeToMove == PAWN)
	{
		return BP;
	}
	else if (b->turn == 1 && pieceTypeToMove == ROOK)
	{
		return BR;
	}
	else if (b->turn == 1 && pieceTypeToMove == KNIGHT)
	{
		return BK;
	}
	else if (b->turn == 1 && pieceTypeToMove == BISHOP)
	{
		return BB;
	}
	else if (b->turn == 1 && pieceTypeToMove == QUEEN)
	{
		return BQ;
	}
	else if (b->turn == 1 && pieceTypeToMove == KING)
	{
		return BKING;
	}

}

enum moveStatus determineMove(board* b)
{
	bool type_is_decided = false;


	b->p.typeOfMove = DUMMY;

	size_t string_size = strlen(b->p.current_Move);



	//strcmp returns a 0
	if (strcmp(b->p.current_Move, "O-O") == 0)
	{
		b->p.typeOfMove = CASTLEKING;
		type_is_decided = true;
	}
	//Queenside castle
	else if (strcmp(b->p.current_Move, "O-O-O") == 0 && !type_is_decided)
	{
		b->p.typeOfMove = CASTLEQUEEN;
		type_is_decided = true;
	}
	//if the last index (strlen doesn't include the null terminator. So it should return the final char in the array.)
	else if (b->p.current_Move[string_size - 1] == '+' && !type_is_decided && b->p.current_Move[2] != '=')
	{
		b->p.typeOfMove = CHECK;
		type_is_decided = true;
	}
	//this is a promotion of the pawn.
	else if (b->p.current_Move[string_size - 1] == '+' && !type_is_decided && b->p.current_Move[2] == '=')
	{
		b->p.typeOfMove = PROMO;
		type_is_decided = true;
	}
	else if (b->p.current_Move[string_size - 1] == '#' && !type_is_decided)
	{
		b->p.typeOfMove = MATE;
		type_is_decided = true;
	}

	else if (!type_is_decided && (strchr(b->p.current_Move, 'x') != NULL))
	{

		type_is_decided = true;

		if (type_is_decided && string_size == 4)
		{
			b->p.typeOfMove = RATTACK;
		}
		else if (type_is_decided && string_size > 4)
		{
			b->p.typeOfMove = AATTACK;
		}
	}

	//enum moveStatus {DUMMY = 0, RATTACK, AATTACK, CASTLEKING, CASTLEQUEEN, CHECK, MATE, RMOVE, AMOVE, RPAWNMOVE, APAWNMOVE, EP};
	else if ((b->p.current_Move[0] == 82 || b->p.current_Move[0] == 78 || b->p.current_Move[0] == 66 || b->p.current_Move[0] == 81 || b->p.current_Move[0] == 75) && !type_is_decided && string_size == 3)
	{
		b->p.typeOfMove = RMOVE;
		type_is_decided = true;
	}
	//if it's a piece other than pawn in the initial movement, the type isn't assigned yet and the size is not 3 then it's not normal but it's a move and ambiguous cause more specifiers are in the string.
	else if ((b->p.current_Move[0] == 82 || b->p.current_Move[0] == 78 || b->p.current_Move[0] == 66 || b->p.current_Move[0] == 81 || b->p.current_Move[0] == 75) && !type_is_decided && !(string_size == 3))
	{
		b->p.typeOfMove = AMOVE;
		type_is_decided = true;
	}
	//or a pawn move. it's a lowercase first letter, and the size is 2 so just a regular move.
	else if (!type_is_decided && b->p.current_Move[0] >= 'a' && b->p.current_Move[0] <= 'h' && string_size == 2)
	{
		b->p.typeOfMove = RPAWNMOVE;
		type_is_decided = true;
	}
	//this is for promotion of the pawn - FUCK THE PAWNS.

	else
	{
		b->p.typeOfMove = APAWNMOVE;
		type_is_decided = true;
	}




	return b->p.typeOfMove;
}

void setCurrentMove(board* b, const char* input) //We'll get input from main
{
	std::strcpy(b->p.current_Move, input);
}

void parseMove(piece_to_move* p, board* b) //board for turn, we aren't moving board, we're just going to store the value in piece to move.
{
	size_t string_length = strlen(p->current_Move);

	int x_for_index = 0;
	int y_for_index = 0;

	switch (p->typeOfMove)
	{
	case RATTACK:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p->current_Move[string_length - 1] - 48);
		break;
	case AATTACK:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p->current_Move[string_length - 1] - 48);
		break;
	case CASTLEKING:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(75, b);
		if (b->p.piece_to_move_on_board == WKING)
		{
			x_for_index = 'g' - 97;
			y_for_index = 8 - ('1' - 48);
		}
		else if (b->p.piece_to_move_on_board == BKING)
		{
			x_for_index = 'g' - 97;
			y_for_index = 8 - ('8' - 48);
		}
		break;
	case CASTLEQUEEN:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(75, b);
		if (b->p.piece_to_move_on_board == WKING)
		{
			x_for_index = 'c' - 97;
			y_for_index = 8 - ('1' - 48);
		}
		else if (b->p.piece_to_move_on_board == BKING)
		{
			x_for_index = 'c' - 97;
			y_for_index = 8 - ('8' - 48);
		}
		break;
	case CHECK:
		//It could be a pawn 
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[string_length - 3] - 97;
		y_for_index = 8 - (p->current_Move[string_length - 2] - 48);
		break;
	case MATE:
		//It could be a pawn 
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[string_length - 3] - 97;
		y_for_index = 8 - (p->current_Move[string_length - 2] - 48);
		break;
	case RMOVE:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p->current_Move[string_length - 1] - 48);
		break;
	case AMOVE:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[string_length - 2] - 97;
		y_for_index = 8 - (p->current_Move[string_length - 1] - 48);
		break;
	case RPAWNMOVE:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[0] - 97;
		y_for_index = 8 - (p->current_Move[1] - 48);
		break;
	case APAWNMOVE:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[0] - 97;
		y_for_index = 8 - (p->current_Move[1] - 48);
		break;
	case PROMO:
		p->piece_to_move_on_board = return_corresponding_enum_to_piece(p->current_Move[0], b);
		x_for_index = p->current_Move[0] - 97;
		y_for_index = 8 - (p->current_Move[1] - 48);
		break;
	}
	p->index_to_move = x_for_index + (y_for_index * board::width);
}
