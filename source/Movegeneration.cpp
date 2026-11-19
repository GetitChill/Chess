
#include "Movegeneration.h"

int bpawn_movement[4] = { 8,16,9,7 };
int knight_movement[8] = { 17,15,-17,-15,-6,10,6,-10 };
int bishop_movement[4] = { 9,7,-9,-7 };
int rook_movement[4] = { 1,8,-1,-8 };

void move_Generation(board* b)
{
	//We want to manipulate the move_list array.
	//This is going to be the index of move_list as we add to it.

	int count = 0;
	for (int i = 0; i < 64; ++i)
	{
		//loop through the specific moves of the specific piece.
		//we'll do black pawn.

		if (b->board_array[i] == BP)
		{
			int current_rank = 8 - (i / 8);
			int current_file = (i % 8);
			bool stop_movement = false;
			//I don't want to have it where the pawn can move over a pawn in +16.
			for (int j = 0; j < 4; ++j)
			{
				int move_rank = 8 - ((i + bpawn_movement[j]) / 8);
				//this represents a regular movement by the pawn

				if ((j == 0) && b->board_array[i + bpawn_movement[j]] == NA)
				{
					//we're storing the index that we move to.
					b->move_list[count] = i + bpawn_movement[j];
					++count;
				}
				//if there's something in the way of +8 movement then we stop
				else if ((j == 0) && !(b->board_array[i + bpawn_movement[j]] == NA))
				{
					stop_movement = true;
				}
				//This stop movement bool should stop the movement of +16 if there's something in the way. This current rank check is for the pawns moving double bug.
				else if ((j == 1) && b->board_array[i + bpawn_movement[j]] == NA && !stop_movement && current_rank == 7)
				{
					//we're storing the index that we move to.
					b->move_list[count] = i + bpawn_movement[j];
					++count;
				}

				//j is an attacking increment index wise. 2 things need to be true. We go down 1 in rank and we attack a white piece.
				//&& (current_rank - move_rank == 1)
				else if ((j == 2 || j == 3) && (b->board_array[i + bpawn_movement[j]] >= 1 && b->board_array[i + bpawn_movement[j]] <= 6) && (current_rank - move_rank == 1))
				{
					b->move_list[count] = i + bpawn_movement[j];
					++count;
				}
			}

		}
		//this is for the black knight and 
		else if (b->board_array[i] == BK)
		{
			int current_rank = 8 - (i / 8);
			int current_file = (i % 8);
			//So it just gives it a stupid fucking value.
			//I want to make sure this shit is in bound

			//We don't need stop movement.
			//We want to loop through all of the possible movements then verify that the index we're moving to doesn't have the same color (black in the case) and that it's a valid move checking file and ran
			//(piece_index_to_move_file - file_current) == 1 && (piece_index_to_move_rank - rank_current == -2)
			for (int j = 0; j < 8; ++j)
			{
				//if we're using the first increment, if it's not a black piece, and the file and rank are good then we can move there.
				int x = i + knight_movement[j];
				int move_rank = 8 - ((i + knight_movement[j]) / 8);
				int move_file = ((i + knight_movement[j]) % 8);
				//7 is the first white piece enum value
				//So I check that this shit is in bounds up here, so that we don't even enter if it's not.
				if (i + knight_movement[j] >= 0 && i + knight_movement[j] <= 63)
				{
					if (j == 0 && b->board_array[i + knight_movement[j]] < 7 && ((move_file - current_file) == 1 && (move_rank - current_rank) == -2))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;

					}
					//THE SAME THING BUT THE J'S ARE DIFFERENT AND SO ARE THE RANK AND FILE DIFFERENCES.
					//+15
					//(piece_index_to_move_file - file_current) == -1 && (piece_index_to_move_rank - rank_current) == -2
					else if (j == 1 && b->board_array[i + knight_movement[j]] < 7 && ((move_file - current_file) == -1 && (move_rank - current_rank) == -2))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;

					}
					//-17
					//(piece_index_to_move_file - file_current) == -1 && (piece_index_to_move_rank - rank_current) == 2)
					//Greater than 0 is for the making sure that the dummy value is not included 
					else if (j == 2 && (b->board_array[i + knight_movement[j]] < 7) && ((move_file - current_file) == -1 && (move_rank - current_rank) == 2))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;

					}
					//-15
					//(piece_index_to_move_file - file_current) == 1 && (piece_index_to_move_rank - rank_current) == 2
					else if (j == 3 && (b->board_array[i + knight_movement[j]] < 7) && ((move_file - current_file) == 1 && (move_rank - current_rank) == 2))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;
						break;
					}
					//-6
					//(piece_index_to_move_file - file_current) == 2 && (piece_index_to_move_rank - rank_current) == 1
					//L top right
					else if (j == 4 && (b->board_array[i + knight_movement[j]] < 7) && ((move_file - current_file) == 2 && (move_rank - current_rank) == 1))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;


					}
					//10
					//(piece_index_to_move_file - file_current) == 2 && (piece_index_to_move_rank - rank_current) == -1
					//L bottom right
					else if (j == 5 && (b->board_array[i + knight_movement[j]] < 7) && ((move_file - current_file) == 2 && (move_rank - current_rank) == -1))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;

					}
					//6
					//(piece_index_to_move_file - file_current) == -2 && (piece_index_to_move_rank - rank_current) == -1
					else if (j == 6 && (b->board_array[i + knight_movement[j]] < 7) && ((move_file - current_file) == -2 && (move_rank - current_rank) == -1))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;
					}
					//-10
					//(piece_index_to_move_file - file_current) == -2 && (piece_index_to_move_rank - rank_current) == 1
					else if (j == 7 && (b->board_array[i + knight_movement[j]] < 7) && ((move_file - current_file) == -2 && (move_rank - current_rank) == 1))
					{
						b->move_list[count] = i + knight_movement[j];
						++count;
					}
				}
			}
			//This marks the beginning of 
			b->move_list[count] = 1000;
			++count;
		}

		else if (b->board_array[i] == BB)
		{




			for (int j = 0; j < 4; ++j)
			{
				int file_base = (i % 8);
				int rank_base = 8 - (i / 8);
				bool good_to_go = true;
				//We need to reset whatever we need to right here.
				int inc_c = 1;
				while (good_to_go)
				{
					//I'm still a little confused on what this reduced shit is doing right here :(.
					int reduced_file_move = (i + bishop_movement[j] * (inc_c - 1)) % 8;
					int reduced_rank_move = 8 - ((i + bishop_movement[j] * (inc_c - 1)) / 8);

					int file_move = (i + bishop_movement[j] * inc_c) % 8;
					int rank_move = 8 - ((i + bishop_movement[j] * inc_c) / 8);

					int movement_index_check = i + bishop_movement[j] * inc_c;


					// + 9
					//Bottom Right
					/* I'm interested in checking why this isn't working.
					if (movement_index_check > 63 || movement_index_check < 0)
					{

					}
					*/

					if ((j == 0 && (file_base == 7) || (rank_base == 1)))
					{
						good_to_go = false;
					}
					else if (j == 0 && !((file_move - reduced_file_move == 1) && (rank_move - reduced_rank_move == -1)) || ((movement_index_check > 63 || movement_index_check < 0) && good_to_go == true)) //I don't like this hard coded value. But whatever.
					{
						good_to_go = false;
					} // + 9
					//We'll try to do j[2]
					//It's where we legit cannot move in that direction + 7
					//Bottom left 
					if ((j == 1 && (file_base == 0) || (rank_base == 1)))
					{
						good_to_go = false;
					}

					else if (j == 1 && !((file_move - reduced_file_move == -1) && (rank_move - reduced_rank_move == -1)) || ((movement_index_check > 63 || movement_index_check < 0) && good_to_go == true))
					{
						good_to_go = false;
					} //+7 DONDA


					//-9
					//Can't I just say if the shit == this to not move? No cause there's an initial value in inc_c that is used. So it takes that possibility out of the cards.
					//File base just checks the initial position.
					//top left.
					if ((j == 2 && (file_base == 0) || (rank_base == 8)))
					{
						good_to_go = false;
					}
					else if (j == 2 && !((file_move - reduced_file_move == -1) && (rank_move - reduced_rank_move == 1)) || ((movement_index_check > 63 || movement_index_check < 0) && good_to_go == true)) //I don't like this hard coded value. But whatever.
					{
						good_to_go = false;
					}
					//-7 top right so we don't to be in rafters or in the cold.
					if ((j == 3 && (file_base == 7) || (rank_base == 8)))
					{
						good_to_go = false;
					}
					else if (j == 3 && !((file_move - reduced_file_move == 1) && (rank_move - reduced_rank_move == 1)) || ((movement_index_check > 63 || movement_index_check < 0) && good_to_go == true)) //I don't like this hard coded value. But whatever.
					{
						good_to_go = false;
					}



					//-7
					else if (b->board_array[i + bishop_movement[j] * inc_c] == NA && good_to_go)
					{
						b->move_list[count] = i + (bishop_movement[j] * inc_c);
						++count;
					}
					//If this shits white add the move because it could be considered a capture.
					else if (b->board_array[i + bishop_movement[j] * inc_c] >= 1 && b->board_array[i + bishop_movement[j] * inc_c] <= 6 && good_to_go)
					{
						b->move_list[count] = i + (bishop_movement[j] * inc_c);
						++count;
						good_to_go = false;
					}

					else if (b->board_array[i + bishop_movement[j] * inc_c] >= 7 && b->board_array[i + bishop_movement[j] * inc_c] <= 12 && good_to_go)
					{
						good_to_go = false;
					}
					++inc_c;



				}
			}
		}
		//Black rook. What are the possible increments for the rook
			//Store them in an array.
		//Then do the same sliding logic that we did for the bishop on the rook.
		/*
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
		*/
		//int rook_movement[4] = { 1,8,-1,-8 };
		else if (b->board_array[i] == BR)
		{

			//This is looping through all of the possible movements for the rook.
			for (int j = 0; j < 4; ++j)
			{
				//so we just want to loop until we hit an enemy 
				bool good_to_go = true;
				int incrementer = 0; //We're going to try this incrementer by starting at zero and doing some if magic to not detect it's own array. 

				while (good_to_go)
				{
					//we move until we hit an enemy ally or the edge. if i + rookindex * inc != i && the spot is NA then we can add it. There's not going to be any bounds but what ever.
					const int movement_index = i + rook_movement[j] * incrementer;
					//We're at the edge we stop
					//The final consideration we need to make is the weird ass movement on the edges of the board that are going to wrap around. And I may just go back to the trusty comparison with the old value. 
					//^ by far the simplest

					const int move_file = movement_index % 8;
					const int move_rank = 8 - (movement_index % 8);

					//Well this method is flawed. Cause with this first increment it's plus 1 so if we're on the left side edge then we should be able to move.

					if (move_file <= 0 || move_file >= 7 || move_rank <= 1 || move_rank >= 8)
					{
						good_to_go = false;
					}
					if (good_to_go)
					{
						if (movement_index != i && b->board_array[movement_index] == NA)
						{
							//Then we want to add it to our movelist array.
							b->move_list[count] = movement_index;
							//Now we also want to increment the count.
							++count;
						}

						//So if we are outside of the original index, and in an index that isn't na.
						else if (movement_index != i && !(b->board_array[movement_index] == NA))
						{
							//If it's white.
							if (b->board_array[movement_index] >= 1 && b->board_array[movement_index] <= 6)
							{
								//We want to take it and add it.
								b->move_list[count] = movement_index;
								//Now we also want to increment the count.
								++count;
								//Then end the loop cause this increment/movement pattern is done.
								good_to_go = false;
							}
							//If it's black.
							else if (b->board_array[movement_index] >= 6 && b->board_array[movement_index] <= 7)
							{
								good_to_go = false;
							}
						}
					}

					++incrementer;
				}
			}
		}
	}
	b->move_list[count] = '\0';
}
