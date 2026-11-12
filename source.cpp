#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "headers.h"
/*
* enum pieces {
	NAN = 0, WP = 1, WK = 2, WB = 3, WR = 4, WQ = 5, WKING = 6,
	BP = 7, BK = 8, BB = 9, BR = 10, BQ = 11, BKING = 12
};


enum castleRights { NBC=0, NWC, BQC, BKC,  WQC, WKC};

void getInput(char* move)
{
	int i = 0;

	for (char c = _getch(); c != '\r'; c = _getch(), ++i)
	{
		move[i] = c;
		_putch(c);
	}
	move[i] = '\0';
	_putch('\n');
}
void print(const char* movement)
{
	for (int i = 0;  movement[i] != '\0'; ++i)
	{
		_putch(movement[i]);
	}
	_putch('\n');
}
*/


int main()
{
	board b;
	//drawBoard(&b);
	char m[10];
	//const char* move = "a5";//Qd2
	b.readFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	
	
	const char* string[] = {
	"e4", "e5", "Nf3", "Nc6", "Nc3", "Bc5", "d3", "Nf6",
	"Be2", "d5", "Nxd5", "Nxd5", "exd5", "Nd4", "Nxd4", "Qxd5",
	"Be3", "Bxd4", "c4", "Qxg2", "Bf3", "Bg4", "Bxg2", "Bc3+",
	"Kf1", "Bxb2", "Qxg4", "Bxa1", "Qxg7", "Rf8", "Bc5", "O-O-O",
	"Bxf8", "f6", "Qxf6", "Bd4", "Ke2", "Rd7", "Rc1", "b6",
	"c5", "h6", "cxb6", "Bxb6", "Qxe5", "Bd4", "Qxd4", "a6",
	"Qa4", "Rd8", "Qxa6+", "Kb8", "Rb1#"
		};
	

	////placeholder = 0;regular attack = 1; ambiguos attack = 2; castle king = 3; castle queen = 4; check = 5; mate = 6; regular move = 7; ambiguous move = 8; enpassant = 9

	
	bool a = (b.turn % 2 == 0);
	int d = 0;
	for (int i = 0; string[i] != nullptr; ++i)
	{
		
		strcpy(m, string[i]);
		//getInput(m);
		b.setCurrentMove( m);
		b.determineMove();
		b.parseMove();
		b.Move();
		
		if (a == (b.turn % 2 == 0))
		{
			d = i;
			break;
		}
		else
		{
			a = (b.turn % 2 == 0);
			printf("%d", i);
			
		}

	}
	for (int i = 0; i < d; ++i)
	{
		if (b.turn % 2 == 0)
		{
			printf("It's whites turn\n");
		}
		else if (!(b.turn % 2 == 0))
		{
			printf("It's blacks turn\n");
		}
		strcpy(m, string[i]);
		//getInput(m);
		b.setCurrentMove( m);
		b.determineMove();
		b.parseMove();
		b.Move();

		b.drawBoard();
	}
	
	
	
	return 0;
}

