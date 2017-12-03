#define _CRT_SECURE_NO_WARNINGS

#include "chess.h"

//Copy to dest specific word from a string
void getWord(char* dest, char* src, int wordNum)
{
	int curWord = 1;


	///////////////////////Go to word number <wordNum>
	if (isspace(*src))
	{
		curWord = 0;
	}

	while (curWord < wordNum && *src != '\0')
	{
		src = getNextWord(src);
		curWord++;
	}
	///////////////////////

	//Copy word to dest
	while (!isspace(*src) && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	//Add '\0' at the end of the word
	*dest = 0;
}

//Return a pointer to the next word position
char* getNextWord(char* word)
{
	//Find first white space
	while (!isspace(*word) && *word != '\0')
	{
		word++;
	}

	//Set word after the continuous white space
	while (isspace(*word) && *word != '\0')
	{
		word++;
	}

	return word;
}

int isPieceTypeInRange(char pieceType)
{
	if (pieceType != 'm' && pieceType != 'M' && pieceType != 'b' && pieceType != 'B' && pieceType != 'n' && pieceType != 'N' &&
		pieceType != 'r' && pieceType != 'R' && pieceType != 'q' && pieceType != 'Q' && pieceType != 'k' &&  pieceType != 'K')
	{
		return -1;
	}

	return 0;
}

char pieceTypeToCharacter(char* pieceType)
{
	char pieceChar = 0;

	if (strcmp(pieceType, "king") == 0)
	{
		pieceChar = WHITE_K;
	}
	else if (strcmp(pieceType, "queen") == 0)
	{
		pieceChar = WHITE_Q;
	}
	else if (strcmp(pieceType, "knight") == 0)
	{
		pieceChar = WHITE_N;
	}
	else if (strcmp(pieceType, "rook") == 0)
	{
		pieceChar = WHITE_R;
	}
	else if (strcmp(pieceType, "bishop") == 0)
	{
		pieceChar = WHITE_B;
	}
	else if (strcmp(pieceType, "pawn") == 0)
	{
		pieceChar = WHITE_P;
	}
	else
	{
		return 0;
	}

	return pieceChar;
}

int isWithinBoardBorders(int x, int y)
{
	if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
	{
		return 1;
	}

	return 0;
}

void removeSpaces(char* src)
{
	char* i = src;
	char* j = src;

	while (*j != '\0')
	{
		*i = *j++;
		if (!isspace(*i))
		{
			i++;
		}
	}

	*i = '\0';

}


int isLegalPiecePlacement(char board[BOARD_SIZE][BOARD_SIZE])
{
	if (isLegalPiecePlacementPerPlayer(board, WHITE) == NO
		||
		isLegalPiecePlacementPerPlayer(board, BLACK) == NO)
	{
		return NO;
	}

	return YES;
}

int isLegalPiecePlacementPerPlayer(char board[BOARD_SIZE][BOARD_SIZE], int color)
{
	int pawn = 0, bishop = 0, rook = 0, knight = 0, queen = 0, king = 0;
	int row, column;

	//Count pieces
	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			if (board[row][column] == ((color == WHITE) ? 'm' : 'M'))
			{
				pawn++;
			}
			if (board[row][column] == ((color == WHITE) ? 'b' : 'B'))
			{
				bishop++;
			}
			if (board[row][column] == ((color == WHITE) ? 'r' : 'R'))
			{
				rook++;
			}
			if (board[row][column] == ((color == WHITE) ? 'n' : 'N'))
			{
				knight++;
			}
			if (board[row][column] == ((color == WHITE) ? 'q' : 'Q'))
			{
				queen++;
			}
			if (board[row][column] == ((color == WHITE) ? 'k' : 'K'))
			{
				king++;
			}

		}
	}


	//Check if IILEGAL INITIALIATION
	if (king > 1 || queen > 1 || knight > 2 || rook > 2 || bishop > 2 || pawn > 8)
	{
		return NO;
	}



	return YES;
}

int isBothKingsExist(char board[BOARD_SIZE][BOARD_SIZE])
{
	if (isKingExist(board, WHITE) == NO
		||
		isKingExist(board, BLACK) == NO)
	{
		return NO;
	}

	return YES;
}

int isKingExist(char board[BOARD_SIZE][BOARD_SIZE], int color)
{
	int king = 0;
	int row, column;

	//Count pieces
	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			if (board[row][column] == ((color == WHITE) ? 'k' : 'K'))
			{
				king++;
			}
		}
	}

	//Check if IILEGAL INITIALIATION
	if (king != 1)
	{
		return NO;
	}


	return YES;
}

int isLegalMove(char board[BOARD_SIZE][BOARD_SIZE], int src_x, int src_y, int dst_x, int dst_y, char pieceType)
{
	Move* m1;
	Move_List* moves = NULL;
	int legal;

	//printf("Move: src_x = %d , src_y = %d  to  dst_x = %d , dst_y = %d \n", src_x, src_y, dst_x, dst_y); //DELETE
	//printf("next player: %c \n", next_player); //DELETE
	//printf("pieceType : %d \n", pieceType); //DELETE

	//TODO Matan: These lines are not nesscary!! Tamir copied them... Those tests are being performed in a previous function - make sure with TAMIR

	//if (!isWithinBoardBorders(src_x, src_y) || !isWithinBoardBorders(dst_x, dst_y))
	//{
	//	printf("isLegalMove :  INVALID_POSITION \n");
	//	return INVALID_POSITION;
	//}
	//else if (board[src_x][src_y] == EMPTY || (next_player == WHITE && isupper(board[src_x][src_y])) || (next_player == BLACK && islower(board[src_x][src_y])))
	//{
	//	printf("isLegalMove :  NOT_YOUR_PIECE \n");
	//	return NOT_YOUR_PIECE;
	//}

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


	if (src_x == 4 && src_y == 0 && board[src_x][src_y] == WHITE_K && (dst_x == 6 || dst_x == 2))
	{
		m1->indicator = 'c';
	}
	if (src_x == 4 && src_y == 7 && board[src_x][src_y] == BLACK_K && (dst_x == 6 || dst_x == 2))
	{
		m1->indicator = 'c';
	}



	if (board[src_x][src_y] == WHITE_P || board[src_x][src_y] == WHITE_B || board[src_x][src_y] == WHITE_N || board[src_x][src_y] == WHITE_R || board[src_x][src_y] == WHITE_Q || board[src_x][src_y] == WHITE_K)
	{
		moves = getMoves(board, 'w', whitePieceWasMoved[KING], whitePieceWasMoved[RIGHT_ROOK], whitePieceWasMoved[LEFT_ROOK]);
	}
	else
	{
		moves = getMoves(board, 'b', blackPieceWasMoved[KING], blackPieceWasMoved[RIGHT_ROOK], blackPieceWasMoved[LEFT_ROOK]);
	}

	legal = isInMoveList(moves, m1);
	free_Move(m1);
	free_Move_List(moves);
	return legal;

}


int isLegalCastle(char board[BOARD_SIZE][BOARD_SIZE], int src_x, int src_y)
{
	Move* m1 = NULL;
	Move_List* moves = NULL;
	int legal;
	

	if (src_x == 0 && src_y == 0)
	{
		m1 = createNewMove2(createNewPos('e', 1), createNewPos('c', 1), 'c');
	}
	else if (src_x == 7 && src_y == 0)
	{
		m1 = createNewMove2(createNewPos('e', 1), createNewPos('g', 1), 'c');
	}
	else if (src_x == 0 && src_y == 7)
	{
		m1 = createNewMove2(createNewPos('e', 7), createNewPos('c', 7), 'c');
	}
	else if (src_x == 7 && src_y == 7)
	{
		m1 = createNewMove2(createNewPos('e', 7), createNewPos('g', 7), 'c');
	}
	else
	{
		return IILEGAL_CASLTING_ERROR;
	}



	if (board[src_x][src_y] == WHITE_R)
	{
		moves = getMoves(board, 'w', whitePieceWasMoved[KING], whitePieceWasMoved[RIGHT_ROOK], whitePieceWasMoved[LEFT_ROOK]);
	}
	else
	{
		moves = getMoves(board, 'b', blackPieceWasMoved[KING], blackPieceWasMoved[RIGHT_ROOK], blackPieceWasMoved[LEFT_ROOK]);
	}

	legal = isInMoveList(moves, m1);
	free_Move(m1);
	free_Move_List(moves);
	return legal;
}


void switchNextPlayerColor()
{
	if (next_player == WHITE)
	{
		next_player = BLACK;
	}
	else
	{
		next_player = WHITE;
	}
}

void setDefaultPromotion(int dst_y, char *pieceType)
{
	if ((next_player == WHITE && dst_y == 7 && *pieceType == 0) || (next_player == BLACK && dst_y == 0 && *pieceType == 0))
	{
		strcpy(pieceType, "queen");
	}

}

//Only for debugging(MATAN) :
void printGameStatus_tmp()
{
	printf("Game status: \n");
	printf("Chess: %d \n", thereIsCheck(chess_board, next_player));
	printf("Tie: %d \n", isTie(chess_board, next_player));
	printf("Mate: %d \n", isMate(chess_board, next_player));
}

int correctPositionFormant(char* word)
{
	int i = 0;

	for (i = 0; i <= 4; i++)
	{
		if (word[i] == '\0')
			return NO;
	}

	if (word[0] != '<' || word[2] != ',' || word[4] != '>')
		return NO;

	return YES;
}