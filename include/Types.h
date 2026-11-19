#pragma once

enum pieces {
	NA = 0, WP = 1, WK = 2, WB = 3, WR = 4, WQ = 5, WKING = 6,
	
	BP = 7, BK = 8, BB = 9, BR = 10, BQ = 11, BKING = 12
};

typedef bool castlingOptions;

enum castleRights { BQC, BKC, WQC, WKC };

enum asciiPieces { PAWN = 0, ROOK = 82, KNIGHT = 78, BISHOP = 66, QUEEN = 81, KING = 75 };

enum moveStatus { DUMMY = 0, RATTACK, AATTACK, CASTLEKING, CASTLEQUEEN, CHECK, MATE, RMOVE, AMOVE, RPAWNMOVE, APAWNMOVE, PROMO, EP };
