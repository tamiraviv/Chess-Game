#include "chess.h"

void init_board(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;

	//Set Pawns
	for (i = 0; i < BOARD_SIZE; i++)
	{
		board[i][6] = BLACK_P;
		board[i][1] = WHITE_P;
	}

	//Set Rooks
	board[0][0] = board[7][0] = WHITE_R;
	board[0][7] = board[7][7] = BLACK_R;

	//Set Nights
	board[1][0] = board[6][0] = WHITE_N;
	board[1][7] = board[6][7] = BLACK_N;

	//Set Bishops
	board[2][0] = board[5][0] = WHITE_B;
	board[2][7] = board[5][7] = BLACK_B;

	//Set Queens
	board[4][0] = WHITE_K;
	board[4][7] = BLACK_K;

	//Set Kings
	board[3][0] = WHITE_Q;
	board[3][7] = BLACK_Q;

	//Empty rest of the board
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 2; j < BOARD_SIZE - 2; j++)
		{
			board[i][j] = EMPTY;
		}
	}

	initCasteling();
}

void initCasteling()
{
	//White Left ROOK
	initCastlePiece(0, 0, WHITE_R, whitePieceWasMoved, LEFT_ROOK);

	//White Right ROOK
	initCastlePiece(7, 0, WHITE_R, whitePieceWasMoved, RIGHT_ROOK);

	//White King
	initCastlePiece(4, 0, WHITE_K, whitePieceWasMoved, KING);

	//Black Left ROOK
	initCastlePiece(0, 7, BLACK_R, blackPieceWasMoved, LEFT_ROOK);

	//Black Right ROOK
	initCastlePiece(7, 7, BLACK_R, blackPieceWasMoved, RIGHT_ROOK);

	//Black King
	initCastlePiece(4, 7, BLACK_K, blackPieceWasMoved, KING);

	//For debugging[MATAN]: printCurrentCastling() 
}

void initCastlePiece(int x, int y, char pieceType, int* isPieceWasMoved, int isPieceWasMovedType)
{
	if (chess_board[x][y] == pieceType)
	{
		isPieceWasMoved[isPieceWasMovedType] = NO;
	}
	else
	{
		isPieceWasMoved[isPieceWasMovedType] = YES;
	}
}

//For Debugging
void printCurrentCastling()
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		printf("White: %d , res = %d\n", i, whitePieceWasMoved[i]);
		printf("Black: %d , res = %d\n", i, blackPieceWasMoved[i]);
	}
}

void printLine()
{
	int i;
	printf(" |");
	for (i = 1; i < BOARD_SIZE * 4; i++)
	{
		printf("-");
	}
	printf("|\n");
}

void printBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;
	printLine();

	for (j = BOARD_SIZE - 1; j >= 0; j--)
	{
		printf((j < 9 ? "%d" : "%d"), j + 1);
		for (i = 0; i < BOARD_SIZE; i++)
		{
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		printLine();
	}
	printf("  ");

	for (j = 0; j < BOARD_SIZE; j++)
	{
		printf(" %c  ", (char)('a' + j));
	}
	printf("\n");
}

int removePiece(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
	if (x < 0 || x > 7 || y < 0 || y > 7)
	{
		return INVALID_POSITION;
	}

	board[x][y] = EMPTY;

	return 0;
}

int movePiece(char board[BOARD_SIZE][BOARD_SIZE], int src_x, int src_y, int dst_x, int dst_y, char pieceType)
{
	Move* m1;

	if (!isWithinBoardBorders(src_x, src_y) || !isWithinBoardBorders(dst_x, dst_y))
	{
		return INVALID_POSITION;
	}
	else if (board[src_x][src_y] == EMPTY || (next_player == WHITE && isupper(board[src_x][src_y])) || (next_player == BLACK && islower(board[src_x][src_y])))
	{
		return NOT_YOUR_PIECE;
	}
	else if (isLegalMove(board, src_x, src_y, dst_x, dst_y, pieceType) == NO)
	{
		return IILEGAL_MOVE;
	}

	if (pieceType == 0)
	{
		m1 = createNewMove(createNewPos((char)(src_x + 'a'), src_y + 1), createNewPos((char)(dst_x + 'a'), dst_y + 1));
	}
	else if (pieceType >= 97 && pieceType <= 122)
	{
		m1 = createNewMove2(createNewPos((char)(src_x + 'a'), src_y + 1), createNewPos((char)(dst_x + 'a'), dst_y + 1), pieceType);
	}
	else
	{
		m1 = createNewMove2(createNewPos((char)(src_x + 'a'), src_y + 1), createNewPos((char)(dst_x + 'a'), dst_y + 1), (pieceType + 32));
	}


	if (board[src_x][src_y] == WHITE_P || board[src_x][src_y] == WHITE_B || board[src_x][src_y] == WHITE_N || board[src_x][src_y] == WHITE_R || board[src_x][src_y] == WHITE_Q || board[src_x][src_y] == WHITE_K)
	{
		executeMove(board, m1, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK]);
	}
	else
	{
		executeMove(board, m1, &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
	}


	free_Move(m1);
	return 0;
}

int setNextPlayer(char color)
{
	if (color == WHITE || color == BLACK)
	{
		next_player = color;
		return 0;
	}

	return -1;
}

// Remove all pieces from the board
void clearBoard(char board[BOARD_SIZE][BOARD_SIZE])
{
	int i, j;

	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = EMPTY;
		}
	}
}

int setUserColor(char color)
{
	if (color == WHITE || color == BLACK)
	{
		user_color = color;
		return 0;
	}

	return -1;
}

int setGameDifficulty(int difficultyInput)
{
	if (difficultyInput >= 1 && difficultyInput <= 5)
	{
		gameDifficulty = difficultyInput;

		return 0;
	}

	return -1;
}

int setGameDifficultyBest()
{
	gameDifficulty = DIFFICULTY_BEST;
	return 0;
}

int setGameMode(int gameModeInput)
{
	if (gameModeInput == 1 || gameModeInput == 2)
	{
		gameMode = gameModeInput;
		return 0;
	}

	return -1;
}

int setPiece(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int pieceColor, char pieceType)
{
	char board_dup[BOARD_SIZE][BOARD_SIZE];

	//Verify position and piece type
	if (x < 0 || x > 7 || y < 0 || y > 7 || isPieceTypeInRange(pieceType) < 0)
	{
		return INVALID_POSITION;
	}

	//Convert piece to Black if nesscary
	if (pieceColor == BLACK)
	{
		pieceType = toupper(pieceType);
	}

	copyBoard(board, board_dup);
	board_dup[x][y] = pieceType;

	//Verify that the number of pieces for each player is legal
	if (isLegalPiecePlacement(board_dup) == NO)
	{
		return INVALID_INITIALIZATION;
	}

	//Set piece on the board
	board[x][y] = pieceType;

	return 0;
}


int getBestScore(char board[BOARD_SIZE][BOARD_SIZE], int difficultyInput, int src_x, int src_y, int dst_x, int dst_y, char pieceType)
{
	Move* m1;
	Move_List* bestMoves = NULL;
	int bestScore;
	char new_board[BOARD_SIZE][BOARD_SIZE];
	if (!isWithinBoardBorders(src_x, src_y) || !isWithinBoardBorders(dst_x, dst_y))
	{
		return INVALID_POSITION;
	}
	else if (board[src_x][src_y] == EMPTY || (next_player == WHITE && isupper(board[src_x][src_y])) || (next_player == BLACK && islower(board[src_x][src_y])))
	{
		return NOT_YOUR_PIECE;
	}
	else if (isLegalMove(board, src_x, src_y, dst_x, dst_y, pieceType) == NO)
	{
		return IILEGAL_MOVE;
	}

	if (pieceType == 0)
	{
		m1 = createNewMove(createNewPos((char)(src_x + 'a'), src_y + 1), createNewPos((char)(dst_x + 'a'), dst_y + 1));
	}
	else if (pieceType >= 97 && pieceType <= 122)
	{
		m1 = createNewMove2(createNewPos((char)(src_x + 'a'), src_y + 1), createNewPos((char)(dst_x + 'a'), dst_y + 1), pieceType);
	}
	else
	{
		m1 = createNewMove2(createNewPos((char)(src_x + 'a'), src_y + 1), createNewPos((char)(dst_x + 'a'), dst_y + 1), (pieceType + 32));
	}

	copyBoard(board, new_board);
	if (board[src_x][src_y] == WHITE_P || board[src_x][src_y] == WHITE_B || board[src_x][src_y] == WHITE_N || board[src_x][src_y] == WHITE_R || board[src_x][src_y] == WHITE_Q || board[src_x][src_y] == WHITE_K)
	{
		executeMove(new_board, m1, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK]);
		bestScore = getBestMove(new_board, 'w', &bestMoves, difficultyInput - 1, difficultyInput - 1, 0, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
		if (bestMoves != NULL)
		{
			free_Move_List(bestMoves);
		}
		free_Move(m1);
		return bestScore;
	}
	else
	{
		executeMove(new_board, m1, &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
		bestScore = getBestMove(new_board, 'b', &bestMoves, difficultyInput - 1, difficultyInput - 1, 0, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
		if (bestMoves != NULL)
		{
			free_Move_List(bestMoves);
		}
		free_Move(m1);
		return bestScore;
	}


}


int castle(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
	Move* m1 = NULL;

	if (!isWithinBoardBorders(x, y))
	{
		return INVALID_POSITION;
	}

	if (board[x][y] == EMPTY || (next_player == WHITE && isupper(board[x][y])) || (next_player == BLACK && islower(board[x][y])))
	{
		return NOT_YOUR_PIECE;
	}

	if (board[x][y] != WHITE_R && board[x][y] != BLACK_R)
	{
		return WRONG_ROOK_POSITION_ERROR;
	}

	if (isLegalCastle(board, x, y) != 1)
	{
		return IILEGAL_CASLTING_ERROR;
	}




	if (x == 0 && y == 0)
	{
		m1 = createNewMove2(createNewPos('e', 1), createNewPos('c', 1), 'c');
	}
	else if (x == 7 && y == 0)
	{
		m1 = createNewMove2(createNewPos('e', 1), createNewPos('g', 1), 'c');
	}
	else if (x == 0 && y == 7)
	{
		m1 = createNewMove2(createNewPos('e', 7), createNewPos('c', 7), 'c');
	}
	else if (x == 7 && y == 7)
	{
		m1 = createNewMove2(createNewPos('e', 7), createNewPos('g', 7), 'c');
	}



	if (board[x][y] == WHITE_R)
	{
		executeMove(board, m1, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK]);
	}
	else
	{
		executeMove(board, m1, &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
	}

	free_Move(m1);





	return 0;


}