#include "fen.h"


void readFEN(const char* fenstring, board* b)
{
	//Count is used to traverse the string, and val is used to hold the index of the array we're writing to.

	int val = 0;
	int space_counter = 0;
	int castle_first_dash_check_index = 0;



	for (int count = 0; fenstring[count] != '\0';)
	{
		//This is just for debugging.
		//char a = fenstring[count];

		//Think about making this whole thing around the fact that if(space_counter == 0)
		//We will divide the entire fen string and treat each division as it's own part.

		if (space_counter == 0)
		{
			switch (fenstring[count])
			{

			case 'r': b->board_array[val] = BR; count += 1; val += 1; break;
			case 'R': b->board_array[val] = WR; count += 1; val += 1; break;
			case 'n': b->board_array[val] = BK; count += 1; val += 1; break;
			case 'N': b->board_array[val] = WK; count += 1; val += 1; break;
			case 'b': b->board_array[val] = BB; count += 1; val += 1; break;
			case 'B': b->board_array[val] = WB; count += 1; val += 1; break;
			case 'q': b->board_array[val] = BQ; count += 1; val += 1; break;
			case 'Q': b->board_array[val] = WQ; count += 1; val += 1; break;
			case 'k': b->board_array[val] = BKING; count += 1; val += 1; break;
			case 'K': b->board_array[val] = WKING; count += 1; val += 1;  break;
			case 'p': b->board_array[val] = BP; count += 1; val += 1;  break;
			case 'P': b->board_array[val] = WP; count += 1; val += 1;  break;
			case '/': count += 1; break;
			case ' ': ++space_counter; count += 1; break; //We just want to skip kinda like the 
			default:
				int v = fenstring[count] - '0';
				for (int i = 0; i < v; ++val, ++i)
				{
					b->board_array[val] = NA;
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
			case 'w': b->turn = 0; count += 1; break;
			default: b->turn = 1; count += 1; break;
			}
		}

		else if (space_counter == 2)
		{
			switch (fenstring[count])
			{
			case 'K': b->castle_array[WKC] = true;  count += 1; break;
			case 'Q': b->castle_array[WQC] = true; count += 1; break;
			case 'k': b->castle_array[BKC] = true; count += 1; break;
			case 'q': b->castle_array[BQC] = true; count += 1; break;

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
			//We need to get the number of digits to add the null terminator in the right place.
			int number_of_digits = 0;
			for (int j = count; (fenstring[j] != ' '); ++j)
			{
				++number_of_digits;
			}
			b->plays_since_pawn[number_of_digits] = '\0';

			//(fenstring[count] != ' ') ||
			for (int i = 0; (b->plays_since_pawn[i] != '\0'); count += 1, ++i)
			{
				b->plays_since_pawn[i] = fenstring[count];
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
			//(fenstring[count] != ' ') ||
			int i = 0;
			for (; fenstring[count] != '\0'; count += 1, ++i)
			{
				b->full_move_number[i] = fenstring[count];
			}
			b->full_move_number[i] = '\0';
		}
	}
}
