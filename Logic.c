
#include "chess.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

//int max_depth = 4;
//char player_color = 'w';

/*
// Struct: Coordinates of a single position on the board
typedef struct
{
	char x;
	int y;
} Pos;


//Struct: A node in a linked list of Positions. The entire list represnts a turn of a player
//indicator: promotion: 'q' = Queen, 'r' = Rook, 'b' = Bishop, 'n' = Knight.
//special move: 'c' = casteling.


typedef struct Move
{
	Pos* startPos;
	Pos* endPos;
	char indicator;
	struct Move *next;
}Move;

// Struct: A node in a linked list of turns. The entire list represts all the possible moves a player can perform in a specific turn
typedef struct Move_List
{
	Move* head;
}Move_List;
*/


// create empty Move_list with head = NULL.
Move_List * createEmptyMoveList()
{
	// Allocating memory
	Move_List * newMoveList = (Move_List *)malloc(sizeof(Move_List));
	if (newMoveList == NULL)
	{
		//perror_message("malloc");
		return NULL;
	}

	//Initializing the fields
	newMoveList->head = NULL;

	return newMoveList;
}

//create Move_list with head as the move we got as a paremeter.
Move_List * createMoveList(Move *move)
{
	/* Allocating memory */
	Move_List * newMoveList = (Move_List *)malloc(sizeof(Move_List));
	if (newMoveList == NULL)
	{
		//perror_message("malloc");
		return NULL;
	}

	/* Initializing the fields */
	newMoveList->head = move;

	return newMoveList;
}

// creat new Position with field: char x and int y
Pos* createNewPos(char x, int y)
{
	Pos * newPos = (Pos *)malloc(sizeof(Pos));
	if (newPos == NULL)
	{
		//perror_message("malloc");
		return NULL;
	}
	if (x < 97 || x > 122 || y < 0 || y>10)
	{
		printf("there is an error");
	}

	newPos->x = x;
	newPos->y = y;

	return newPos;
}


// create new move from position and move that represent the start position of the tool and the order of the move that the tool makes
Move * createNewMove(Pos* start, Pos* end)
{
	/* Allocating memory */
	Move * newMove = (Move *)malloc(sizeof(Move));
	if (newMove == NULL)
	{
		//perror_message("malloc");
		return NULL;
	}

	/* Initializing the fields */
	newMove->startPos = start;
	newMove->endPos = end;
	newMove->indicator = 0;
	newMove->next = NULL;

	return newMove;
}

// create new move from position and move that represent the start position of the tool and the order of the move that the tool makes
// also as a indicator that say if it's a casteling move or promotion move.
Move * createNewMove2(Pos* start, Pos* end, char indicator)
{
	/* Allocating memory */
	Move * newMove = (Move *)malloc(sizeof(Move));
	if (newMove == NULL)
	{
		//perror_message("malloc");
		return NULL;
	}

	/* Initializing the fields */
	newMove->startPos = start;
	newMove->endPos = end;
	newMove->next = NULL;
	newMove->indicator = indicator;

	return newMove;
}


// every Node goes to the head of the list
void appendMoveToMoveList(Move_List * moves, Move * nodeToAppend)
{
	/* Error: Illegal argument */
	if (moves == NULL || nodeToAppend == NULL)
	{
		printf("ERROR in appendTermNode: moves == NULL.");
		return;
	}

	if (moves->head == NULL)
	{
		/* The move list has only one move, making the node the other moves that can be */
		moves->head = nodeToAppend;
	}
	else
	{
		/* Adding the given node before the head node */
		nodeToAppend->next = moves->head;
		moves->head = nodeToAppend;
	}

}

// every Node goes to the tail of the list
void appendMoveToMoveList2(Move_List * moves, Move * nodeToAppend)
{
	Move* preMove = NULL;
	Move* move = NULL;
	/* Error: Illegal argument */
	if (moves == NULL || nodeToAppend == NULL)
	{
		printf("ERROR in appendTermNode: moves == NULL.");
		return;
	}

	if (moves->head == NULL)
	{
		/* The move list has only one move, making the node the other moves that can be */
		moves->head = nodeToAppend;
	}
	else
	{
		preMove = moves->head;
		move = moves->head->next;
		while (move != NULL)
		{
			preMove = move;
			move = move->next;
		}

		/* Adding the given node in the end of the list */
		preMove->next = nodeToAppend;
	}

}


//free allocated memory of Move
int free_Move(Move *move)
{
	if (move != NULL)
	{
		if (move->startPos != NULL)
		{
			free(move->startPos);
		}
		if (move->endPos != NULL)
		{
			free(move->endPos);
		}
		free(move);
		return 1;
	}

	return 0;
}

//free allocated memory of Move_list
int free_Move_List(Move_List *move_list)
{
	Move* move;

	if (move_list == NULL)
	{
		return 0;
	}


	while (move_list->head != NULL)
	{
		move = move_list->head;
		move_list->head = move->next;
		free_Move(move);
	}

	free(move_list);

	return 1;
}


//print a position on the board
void printPosition(Pos* pos)
{
	printf("<%c,%d>", pos->x, pos->y);
}

//print a single move
void printMove(Move* move)
{
	if (move == NULL)
	{
		printf("ERROR: move == NULL.\n");
		return;
	}

	if (move->indicator == 'c') // casteling
	{
		if (move->endPos->x == 'g' && move->endPos->y == 1)
		{
			printf("castle <h,1>");
		}
		if (move->endPos->x == 'g' && move->endPos->y == 8)
		{
			printf("castle <h,8>");
		}
		if (move->endPos->x == 'c' && move->endPos->y == 1)
		{
			printf("castle <a,1>");
		}
		if (move->endPos->x == 'c' && move->endPos->y == 8)
		{
			printf("castle <a,8>");
		}
		printf("\n");
		return;
	}

	if (move->indicator != 0 && move->indicator != 'c') // promotion move
	{

		if (move->indicator == 'b') //  promotion Bishop
		{
			printPosition(move->startPos);
			printf(" to ");
			printPosition(move->endPos);
			printf(" bishop");
		}

		if (move->indicator == 'n') // white promotion Knight
		{
			printPosition(move->startPos);
			printf(" to ");
			printPosition(move->endPos);
			printf(" knight");
		}

		if (move->indicator == 'r') // white promotion Rook
		{
			printPosition(move->startPos);
			printf(" to ");
			printPosition(move->endPos);
			printf(" rook");
		}

		if (move->indicator == 'q') // white promotion Queen
		{
			printPosition(move->startPos);
			printf(" to ");
			printPosition(move->endPos);
			printf(" queen");
		}
		printf("\n");
		return;
	}

	printPosition(move->startPos);
	printf(" to ");
	printPosition(move->endPos);

	printf("\n");
}


//print all the move list
void printMoveList(Move_List* moves)
{
	Move *lastNode;

	if (moves == NULL || moves->head == NULL)
	{
		printf("ERROR: moves == NULL.\n");
		return;
	}

	lastNode = moves->head;

	while (lastNode != NULL)
	{
		printMove(lastNode);
		lastNode = lastNode->next;
	}

}

// given an Original board and a board to copy -> copy the original board.
void copyBoard(char board[BOARD_SIZE][BOARD_SIZE], char new_board[BOARD_SIZE][BOARD_SIZE])
{
	int row, column;

	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			new_board[row][column] = board[row][column];
		}
	}
}

// assumption: get a legal move
// update the board with the new move
void executeMove(char board[BOARD_SIZE][BOARD_SIZE], Move *move, int *isTheKingMoved, int *isTheRightRookMoved, int *isTheLeftRookMoved)
{

	if (move == NULL)
	{
		return;
	}

	if ((move->startPos->y == 1 && move->startPos->x == 'e' && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_K && move->endPos->x == 'g') ||
		(move->startPos->y == 8 && move->startPos->x == 'e' && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_K && move->endPos->x == 'g'))
	{   // right casteling
		board[move->endPos->x - 'a'][move->endPos->y - 1] = board[move->startPos->x - 'a'][move->startPos->y - 1];
		board[move->startPos->x - 'a'][move->startPos->y - 1] = EMPTY;
		board[move->endPos->x - 'a' - 1][move->endPos->y - 1] = board[7][move->startPos->y - 1];
		board[7][move->startPos->y - 1] = EMPTY;
		*isTheKingMoved = 1;
		*isTheRightRookMoved = 1;
		return;
	}


	if ((move->startPos->y == 1 && move->startPos->x == 'e' && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_K && move->endPos->x == 'c') ||
		(move->startPos->y == 8 && move->startPos->x == 'e' && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_K && move->endPos->x == 'c'))
	{   // Left casteling
		board[move->endPos->x - 'a'][move->endPos->y - 1] = board[move->startPos->x - 'a'][move->startPos->y - 1];
		board[move->startPos->x - 'a'][move->startPos->y - 1] = EMPTY;
		board[move->endPos->x - 'a' + 1][move->endPos->y - 1] = board[0][move->startPos->y - 1];
		board[0][move->startPos->y - 1] = EMPTY;
		*isTheKingMoved = 1;
		*isTheLeftRookMoved = 1;
		return;
	}

	if ((move->startPos->y == BOARD_SIZE - 1 && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_P) ||
		(move->startPos->y == 2 && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_P)) // promotion move
	{

		if (move->indicator == 'b' && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_P) // white promotion Bishop
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = WHITE_B;
		}
		if (move->indicator == 'b' && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_P) // black promotion Bishop
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = BLACK_B;
		}
		if (move->indicator == 'n' && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_P) // white promotion Knight
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = WHITE_N;
		}
		if (move->indicator == 'n' && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_P) // black promotion Knight
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = BLACK_N;
		}
		if (move->indicator == 'r' && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_P) // white promotion Rook
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = WHITE_R;
		}
		if (move->indicator == 'r' && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_P) // black promotion Rook
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = BLACK_R;
		}
		if (move->indicator == 'q' && board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_P) // white promotion Queen
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = WHITE_Q;
		}
		if (move->indicator == 'q' && board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_P) // black promotion Queen
		{
			board[move->endPos->x - 'a'][move->endPos->y - 1] = BLACK_Q;
		}

		board[move->startPos->x - 'a'][move->startPos->y - 1] = EMPTY;


		return;
	}

	//regular move
	if (move->startPos->x - 'a' == 0 && (move->startPos->y - 1 == 0 || move->startPos->y - 1 == 7) && (board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_R || board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_R))
	{ // left rook moved
		*isTheLeftRookMoved = 1;
	}
	if (move->startPos->x - 'a' == 7 && (move->startPos->y - 1 == 0 || move->startPos->y - 1 == 7) && (board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_R || board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_R))
	{ // right rook moved
		*isTheRightRookMoved = 1;
	}
	if (move->startPos->x == 'e' && (move->startPos->y - 1 == 0 || move->startPos->y - 1 == 7) && (board[move->startPos->x - 'a'][move->startPos->y - 1] == WHITE_K || board[move->startPos->x - 'a'][move->startPos->y - 1] == BLACK_K))
	{ // king moved
		*isTheKingMoved = 1;
	}
	board[move->endPos->x - 'a'][move->endPos->y - 1] = board[move->startPos->x - 'a'][move->startPos->y - 1];
	board[move->startPos->x - 'a'][move->startPos->y - 1] = EMPTY;

}


//standard Score
int getScore(char board[BOARD_SIZE][BOARD_SIZE], char color)
{
	//char player_color = getPlayerColor();
	int i, j;
	int score = 0;
	Move_List* movesWhite = NULL;
	Move_List* movesBlack = NULL;

	movesWhite = getMoves(board, 'w', 1, 1, 1);
	if (movesWhite->head == NULL) // there is no move;
	{
		free_Move_List(movesWhite);
		if (thereIsCheck(board, 'w'))
		{
			if (color == 'w')
			{
				return -1000;
			}
			else
			{
				return 1000;
			}
		}
		else
		{
			if (color == 'w')
			{
				return -900;
			}
			else
			{
				return 900;
			}
		}
	}

	free_Move_List(movesWhite);

	movesBlack = getMoves(board, 'b', 1, 1, 1);
	if (movesBlack->head == NULL) // there is no move;
	{
		free_Move_List(movesBlack);
		if (thereIsCheck(board, 'b'))
		{
			if (color == 'w')
			{
				return 1000;
			}
			else
			{
				return -1000;
			}
		}
		else
		{
			if (color == 'w')
			{
				return 900;
			}
			else
			{
				return -900;
			}
		}
	}
	free_Move_List(movesBlack);

	for (i = 0; i < BOARD_SIZE; i++) // add score for White tools and sub score for Black tools
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == WHITE_P)
			{
				score += 1;
			}
			if (board[i][j] == WHITE_B)
			{
				score += 3;
			}
			if (board[i][j] == WHITE_N)
			{
				score += 3;
			}
			if (board[i][j] == WHITE_R)
			{
				score += 5;
			}
			if (board[i][j] == WHITE_K)
			{
				score += 400;
			}
			if (board[i][j] == WHITE_Q)
			{
				score += 9;
			}
			if (board[i][j] == BLACK_P)
			{
				score -= 1;
			}
			if (board[i][j] == BLACK_B)
			{
				score -= 3;
			}
			if (board[i][j] == BLACK_N)
			{
				score -= 3;
			}
			if (board[i][j] == BLACK_R)
			{
				score -= 5;
			}
			if (board[i][j] == BLACK_K)
			{
				score -= 400;
			}
			if (board[i][j] == BLACK_Q)
			{
				score -= 9;
			}
		}
	}


	if (color == 'w') // score according to the White
	{
		return score;
	}
	else
	{
		return (-1 * score); // score according to the Black
	}
}




//My Score for the Best Depth
int getScore2(char board[BOARD_SIZE][BOARD_SIZE], char color)
{
	//char player_color = getPlayerColor();
	int i, j;
	int score = 0;
	Move_List* movesWhite = NULL;
	Move_List* movesBlack = NULL;

	movesWhite = getMoves(board, 'w', 1, 1, 1);
	if (movesWhite->head == NULL) // there is no move;
	{
		free_Move_List(movesWhite);
		if (thereIsCheck(board, 'w'))
		{
			if (color == 'w')
			{
				return -1000;
			}
			else
			{
				return 1000;
			}
		}
		else
		{
			if (color == 'w')
			{
				return -900;
			}
			else
			{
				return 900;
			}
		}
	}
	free_Move_List(movesWhite);

	movesBlack = getMoves(board, 'b', 1, 1, 1);
	if (movesBlack->head == NULL) // there is no move;
	{
		free_Move_List(movesBlack);
		if (thereIsCheck(board, 'b'))
		{
			if (color == 'w')
			{
				return 1000;
			}
			else
			{
				return -1000;
			}
		}
		else
		{
			if (color == 'w')
			{
				return 900;
			}
			else
			{
				return -900;
			}
		}
	}
	free_Move_List(movesBlack);

	for (i = 0; i < BOARD_SIZE; i++) // add score for White tools and sub score for Black tools
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == WHITE_P)
			{
				score += 2;
			}
			if (board[i][j] == WHITE_B)
			{
				score += 7;
			}
			if (board[i][j] == WHITE_N)
			{
				score += 6;
			}
			if (board[i][j] == WHITE_R)
			{
				score += 10;
			}
			if (board[i][j] == WHITE_K)
			{
				score += 400;
			}
			if (board[i][j] == WHITE_Q)
			{
				score += 20;
			}
			if (board[i][j] == BLACK_P)
			{
				score -= 2;
			}
			if (board[i][j] == BLACK_B)
			{
				score -= 7;
			}
			if (board[i][j] == BLACK_N)
			{
				score -= 6;
			}
			if (board[i][j] == BLACK_R)
			{
				score -= 10;
			}
			if (board[i][j] == BLACK_K)
			{
				score -= 400;
			}
			if (board[i][j] == BLACK_Q)
			{
				score -= 20;
			}
		}
	}


	if (color == 'w') // score according to the White
	{
		return score;
	}
	else
	{
		return (-1 * score); // score according to the Black
	}
}




// check if 2 moves represent the same Move ( have the same start position and the order of the move that the tool make);
int equalMove(Move *move1, Move *move2)
{
	if (move1 == NULL || move2 == NULL)
	{
		return 0;
	}

	Move* m1 = move1;
	Move* m2 = move2;


	if (m1 != NULL && m2 != NULL)
	{
		if (m1->startPos->x != m2->startPos->x || m1->startPos->y != m2->startPos->y)
		{
			return 0;
		}

		if (m1->endPos->x != m2->endPos->x || m1->endPos->y != m2->endPos->y)
		{
			return 0;
		}

		if (m1->indicator != m2->indicator)
		{
			return 0;
		}
	}

	return 1;

}

// check if the move is contained in the move list.
int isInMoveList(Move_List* moves, Move *move)
{
	Move* m1 = moves->head;
	while (m1 != NULL)
	{
		if (equalMove(m1, move))
		{
			return 1;
		}
		m1 = m1->next;
	}
	return 0;

}



//this function get a position of a king, and check that there is no enemy king near her.
int nearAKing(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
	/*if (board[x][y] != WHITE_K && board[x][y] != BLACK_K)
	{
		return -1;
	}*/



	if (x - 1 >= 0 && y - 1 >= 0 && (board[x - 1][y - 1] == WHITE_K || board[x - 1][y - 1] == BLACK_K))
	{
		return 1;
	}
	if (y - 1 >= 0 && (board[x][y - 1] == WHITE_K || board[x][y - 1] == BLACK_K))
	{
		return 1;
	}
	if (x + 1 < BOARD_SIZE && y - 1 >= 0 && (board[x + 1][y - 1] == WHITE_K || board[x + 1][y - 1] == BLACK_K))
	{
		return 1;
	}

	if (x - 1 >= 0 && y + 1 < BOARD_SIZE && (board[x - 1][y + 1] == WHITE_K || board[x - 1][y + 1] == BLACK_K))
	{
		return 1;
	}
	if (y + 1 < BOARD_SIZE && (board[x][y + 1] == WHITE_K || board[x][y + 1] == BLACK_K))
	{
		return 1;
	}
	if (x + 1 < BOARD_SIZE && y + 1 < BOARD_SIZE && (board[x + 1][y + 1] == WHITE_K || board[x + 1][y + 1] == BLACK_K))
	{
		return 1;
	}

	if (x + 1 < BOARD_SIZE && (board[x + 1][y] == WHITE_K || board[x + 1][y] == BLACK_K))
	{
		return 1;
	}

	if (x - 1 >= 0 && (board[x - 1][y] == WHITE_K || board[x - 1][y] == BLACK_K))
	{
		return 1;
	}

	return 0;
}





// given a move list -> return the last move list in the order
/*Move_List* getLastMoveList(Move_List* moves)
{
Move_List* m1;
if (moves == NULL)
{
return NULL;
}
m1 = moves->next;
if (m1 == NULL)
{
return moves;
}
while (m1->next != NULL)
{
m1 = m1->next;
}
return m1;
}*/


//check for a check on the board
//this function finds the position of the king alone
int thereIsCheck(char board[BOARD_SIZE][BOARD_SIZE], char player_color)
{
	int k, l;
	int row, column;
	int kingColum, kingRow;
	if (player_color == 'w') // // check on White
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			for (row = 0; row < BOARD_SIZE; row++)
			{
				if (board[column][row] == WHITE_K)
				{
					kingColum = column;
					kingRow = row;
				}
			}
		}

		// check if near a king
		if (nearAKing(board, kingColum, kingRow))
		{
			return 1;
		}
		// check by a Pawn
		if ((kingColum - 1 >= 0 && kingRow + 1 < BOARD_SIZE - 1 && board[kingColum - 1][kingRow + 1] == BLACK_P) || (kingColum + 1 < BOARD_SIZE && kingRow + 1 < BOARD_SIZE - 1 && board[kingColum + 1][kingRow + 1] == BLACK_P))
		{
			return 1;
		}

		// check by a knight
		if ((kingColum - 2 >= 0 && kingRow - 1 >= 0 && board[kingColum - 2][kingRow - 1] == BLACK_N) || (kingColum - 2 >= 0 && kingRow + 1 < BOARD_SIZE && board[kingColum - 2][kingRow + 1] == BLACK_N) ||
			(kingColum - 1 >= 0 && kingRow - 2 >= 0 && board[kingColum - 1][kingRow - 2] == BLACK_N) || (kingColum - 1 >= 0 && kingRow + 2 < BOARD_SIZE && board[kingColum - 1][kingRow + 2] == BLACK_N) ||
			(kingColum + 2 < BOARD_SIZE && kingRow - 1 >= 0 && board[kingColum + 2][kingRow - 1] == BLACK_N) || (kingColum + 2 < BOARD_SIZE && kingRow + 1 < BOARD_SIZE && board[kingColum + 2][kingRow + 1] == BLACK_N) ||
			(kingColum + 1 < BOARD_SIZE && kingRow - 2 >= 0 && board[kingColum + 1][kingRow - 2] == BLACK_N) || (kingColum + 1 < BOARD_SIZE && kingRow + 2 < BOARD_SIZE && board[kingColum + 1][kingRow + 2] == BLACK_N))
		{
			return 1;
		}

		// check by a Bishop or a Queen (4 diagonals)
		for (k = kingColum + 1, l = kingRow + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // North East Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // North West Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum - 1, l = kingRow - 1; k >= 0 && l >= 0; k--, l--) // South West Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum + 1, l = kingRow - 1; k < BOARD_SIZE && l >= 0; k++, l--) // South East Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


		// check by a Rook or a Queen (4 verticals)
		for (k = kingColum + 1, l = kingRow; k < BOARD_SIZE; k++) // right vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow; k >= 0; k--) // left vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow + 1; l < BOARD_SIZE; l++) // up vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow - 1; l >= 0; l--) // down vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


	}
	else // check on Black
	{
		for (column = 0; column < BOARD_SIZE; column++)
		{
			for (row = 0; row < BOARD_SIZE; row++)
			{
				if (board[column][row] == BLACK_K)
				{
					kingColum = column;
					kingRow = row;
				}
			}
		}
		// check if near a king
		if (nearAKing(board, kingColum, kingRow))
		{
			return 1;
		}
		// check by a Pawn
		if ((kingColum - 1 >= 0 && kingRow - 1 >= 1 && board[kingColum - 1][kingRow - 1] == WHITE_P) || (kingColum + 1 < BOARD_SIZE && kingRow - 1 >= 1 && board[kingColum + 1][kingRow - 1] == WHITE_P))
		{
			return 1;
		}

		// check by a knight
		if ((kingColum - 2 >= 0 && kingRow - 1 >= 0 && board[kingColum - 2][kingRow - 1] == WHITE_N) || (kingColum - 2 >= 0 && kingRow + 1 < BOARD_SIZE && board[kingColum - 2][kingRow + 1] == WHITE_N) ||
			(kingColum - 1 >= 0 && kingRow - 2 >= 0 && board[kingColum - 1][kingRow - 2] == WHITE_N) || (kingColum - 1 >= 0 && kingRow + 2 < BOARD_SIZE && board[kingColum - 1][kingRow + 2] == WHITE_N) ||
			(kingColum + 2 < BOARD_SIZE && kingRow - 1 >= 0 && board[kingColum + 2][kingRow - 1] == WHITE_N) || (kingColum + 2 < BOARD_SIZE && kingRow + 1 < BOARD_SIZE && board[kingColum + 2][kingRow + 1] == WHITE_N) ||
			(kingColum + 1 < BOARD_SIZE && kingRow - 2 >= 0 && board[kingColum + 1][kingRow - 2] == WHITE_N) || (kingColum + 1 < BOARD_SIZE && kingRow + 2 < BOARD_SIZE && board[kingColum + 1][kingRow + 2] == WHITE_N))
		{
			return 1;
		}

		// check by a Bishop or a Queen (4 diagonals)
		for (k = kingColum + 1, l = kingRow + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // North East Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // North West Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum - 1, l = kingRow - 1; k >= 0 && l >= 0; k--, l--) // South West Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum + 1, l = kingRow - 1; k < BOARD_SIZE && l >= 0; k++, l--) // South East Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


		// check by a Rook or a Queen (4 verticals)
		for (k = kingColum + 1, l = kingRow; k < BOARD_SIZE; k++) // right vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow; k >= 0; k--) // left vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow + 1; l < BOARD_SIZE; l++) // up vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow - 1; l >= 0; l--) // down vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


	}


	return 0;

}


//check for a check on the board
//this function gets the position of the king
int thereIsCheck2(char board[BOARD_SIZE][BOARD_SIZE], char player_color, int kingColum, int kingRow)
{
	int k, l;
	if (player_color == 'w') // // check on White
	{
				// check if near a king
		if (nearAKing(board, kingColum, kingRow))
		{
			return 1;
		}
		// check by a Pawn
		if ((kingColum - 1 >= 0 && kingRow + 1 < BOARD_SIZE - 1 && board[kingColum - 1][kingRow + 1] == BLACK_P) || (kingColum + 1 < BOARD_SIZE && kingRow + 1 < BOARD_SIZE - 1 && board[kingColum + 1][kingRow + 1] == BLACK_P))
		{
			return 1;
		}

		// check by a knight
		if ((kingColum - 2 >= 0 && kingRow - 1 >= 0 && board[kingColum - 2][kingRow - 1] == BLACK_N) || (kingColum - 2 >= 0 && kingRow + 1 < BOARD_SIZE && board[kingColum - 2][kingRow + 1] == BLACK_N) ||
			(kingColum - 1 >= 0 && kingRow - 2 >= 0 && board[kingColum - 1][kingRow - 2] == BLACK_N) || (kingColum - 1 >= 0 && kingRow + 2 < BOARD_SIZE && board[kingColum - 1][kingRow + 2] == BLACK_N) ||
			(kingColum + 2 < BOARD_SIZE && kingRow - 1 >= 0 && board[kingColum + 2][kingRow - 1] == BLACK_N) || (kingColum + 2 < BOARD_SIZE && kingRow + 1 < BOARD_SIZE && board[kingColum + 2][kingRow + 1] == BLACK_N) ||
			(kingColum + 1 < BOARD_SIZE && kingRow - 2 >= 0 && board[kingColum + 1][kingRow - 2] == BLACK_N) || (kingColum + 1 < BOARD_SIZE && kingRow + 2 < BOARD_SIZE && board[kingColum + 1][kingRow + 2] == BLACK_N))
		{
			return 1;
		}

		// check by a Bishop or a Queen (4 diagonals)
		for (k = kingColum + 1, l = kingRow + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // North East Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // North West Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum - 1, l = kingRow - 1; k >= 0 && l >= 0; k--, l--) // South West Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum + 1, l = kingRow - 1; k < BOARD_SIZE && l >= 0; k++, l--) // South East Take move
		{
			if (board[k][l] == BLACK_B || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


		// check by a Rook or a Queen (4 verticals)
		for (k = kingColum + 1, l = kingRow; k < BOARD_SIZE; k++) // right vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow; k >= 0; k--) // left vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow + 1; l < BOARD_SIZE; l++) // up vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow - 1; l >= 0; l--) // down vertical
		{
			if (board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


	}
	else // check on Black
	{
		
		// check if near a king
		if (nearAKing(board, kingColum, kingRow))
		{
			return 1;
		}
		// check by a Pawn
		if ((kingColum - 1 >= 0 && kingRow - 1 >= 1 && board[kingColum - 1][kingRow - 1] == WHITE_P) || (kingColum + 1 < BOARD_SIZE && kingRow - 1 >= 1 && board[kingColum + 1][kingRow - 1] == WHITE_P))
		{
			return 1;
		}

		// check by a knight
		if ((kingColum - 2 >= 0 && kingRow - 1 >= 0 && board[kingColum - 2][kingRow - 1] == WHITE_N) || (kingColum - 2 >= 0 && kingRow + 1 < BOARD_SIZE && board[kingColum - 2][kingRow + 1] == WHITE_N) ||
			(kingColum - 1 >= 0 && kingRow - 2 >= 0 && board[kingColum - 1][kingRow - 2] == WHITE_N) || (kingColum - 1 >= 0 && kingRow + 2 < BOARD_SIZE && board[kingColum - 1][kingRow + 2] == WHITE_N) ||
			(kingColum + 2 < BOARD_SIZE && kingRow - 1 >= 0 && board[kingColum + 2][kingRow - 1] == WHITE_N) || (kingColum + 2 < BOARD_SIZE && kingRow + 1 < BOARD_SIZE && board[kingColum + 2][kingRow + 1] == WHITE_N) ||
			(kingColum + 1 < BOARD_SIZE && kingRow - 2 >= 0 && board[kingColum + 1][kingRow - 2] == WHITE_N) || (kingColum + 1 < BOARD_SIZE && kingRow + 2 < BOARD_SIZE && board[kingColum + 1][kingRow + 2] == WHITE_N))
		{
			return 1;
		}

		// check by a Bishop or a Queen (4 diagonals)
		for (k = kingColum + 1, l = kingRow + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // North East Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // North West Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum - 1, l = kingRow - 1; k >= 0 && l >= 0; k--, l--) // South West Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}

		}

		for (k = kingColum + 1, l = kingRow - 1; k < BOARD_SIZE && l >= 0; k++, l--) // South East Take move
		{
			if (board[k][l] == WHITE_B || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


		// check by a Rook or a Queen (4 verticals)
		for (k = kingColum + 1, l = kingRow; k < BOARD_SIZE; k++) // right vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum - 1, l = kingRow; k >= 0; k--) // left vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow + 1; l < BOARD_SIZE; l++) // up vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}

		for (k = kingColum, l = kingRow - 1; l >= 0; l--) // down vertical
		{
			if (board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
			{
				return 1;
			}
			else if (board[k][l] == EMPTY)
			{
				continue;
			}
			else
			{
				break;
			}
		}


	}


	return 0;

}



// check if we can add any casteling move, if we can, add to moves.
void casteling(Move_List* moves, char board[BOARD_SIZE][BOARD_SIZE], char playerColor, int isTheKingMoved, int isTheRightRookMoved, int isTheLeftRookMoved)
{
	Move* move;
	Pos* curPosition;
	Pos* movePosition;
	char new_board[BOARD_SIZE][BOARD_SIZE];
	char new_board2[BOARD_SIZE][BOARD_SIZE];
	if (playerColor == 'w')
	{
		if (isTheKingMoved == 0 && isTheRightRookMoved == 0)
		{
			if (board[5][0] == EMPTY && board[6][0] == EMPTY)
			{
				curPosition = createNewPos('e', 1);
				movePosition = createNewPos('f', 1);
				move = createNewMove(curPosition, movePosition);
				copyBoard(board, new_board);
				executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
				isTheKingMoved = 0;
				if (!thereIsCheck2(new_board, playerColor,5,0))
				{
					free_Move(move);
					curPosition = createNewPos('f', 1);
					movePosition = createNewPos('g', 1);
					move = createNewMove(curPosition, movePosition);
					copyBoard(new_board, new_board2);
					executeMove(new_board2, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
					isTheKingMoved = 0;
					if (!thereIsCheck2(new_board2, playerColor,6,0))
					{
						free_Move(move);
						curPosition = createNewPos('e', 1);
						movePosition = createNewPos('g', 1);
						move = createNewMove2(curPosition, movePosition, 'c');
						appendMoveToMoveList(moves, move);
					}
					else
					{
						free_Move(move);
					}

				}
				else
				{
					free_Move(move);
				}
			}



		}


		if (isTheKingMoved == 0 && isTheLeftRookMoved == 0)
		{
			if (board[3][0] == EMPTY && board[2][0] == EMPTY && board[1][0] == EMPTY)
			{
				curPosition = createNewPos('e', 1);
				movePosition = createNewPos('d', 1);
				move = createNewMove(curPosition, movePosition);
				copyBoard(board, new_board);
				executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
				if (!thereIsCheck2(new_board, playerColor,3,0))
				{
					free_Move(move);

					curPosition = createNewPos('d', 1);
					movePosition = createNewPos('c', 1);
					move = createNewMove(curPosition, movePosition);
					copyBoard(new_board, new_board2);
					executeMove(new_board2, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
					if (!thereIsCheck2(new_board2, playerColor,2,0))
					{
						free_Move(move);

						curPosition = createNewPos('e', 1);
						movePosition = createNewPos('c', 1);
						move = createNewMove2(curPosition, movePosition, 'c');
						appendMoveToMoveList(moves, move);
					}
					else
					{
						free_Move(move);

					}

				}
				else
				{
					free_Move(move);

				}
			}
		}
	}
	else //black move
	{
		if (isTheKingMoved == 0 && isTheRightRookMoved == 0)
		{
			if (board[5][7] == EMPTY && board[6][7] == EMPTY)
			{
				curPosition = createNewPos('e', 8);
				movePosition = createNewPos('f', 8);
				move = createNewMove(curPosition, movePosition);
				copyBoard(board, new_board);
				executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
				isTheKingMoved = 0;
				if (!thereIsCheck2(new_board, playerColor,5,7))
				{
					free_Move(move);
					curPosition = createNewPos('f', 8);
					movePosition = createNewPos('g', 8);
					move = createNewMove(curPosition, movePosition);
					copyBoard(new_board, new_board2);
					executeMove(new_board2, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
					isTheKingMoved = 0;
					if (!thereIsCheck2(new_board2, playerColor,6,7))
					{
						free_Move(move);
						curPosition = createNewPos('e', 8);
						movePosition = createNewPos('g', 8);
						move = createNewMove2(curPosition, movePosition, 'c');
						appendMoveToMoveList(moves, move);
					}
					else
					{
						free_Move(move);

					}

				}
				else
				{
					free_Move(move);

				}
			}

		}


		if (isTheKingMoved == 0 && isTheLeftRookMoved == 0)
		{
			if (board[3][7] == EMPTY && board[2][7] == EMPTY && board[1][7] == EMPTY)
			{
				curPosition = createNewPos('e', 8);
				movePosition = createNewPos('d', 8);
				move = createNewMove(curPosition, movePosition);
				copyBoard(board, new_board);
				executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
				if (!thereIsCheck2(new_board, playerColor,3,7))
				{
					free_Move(move);
					curPosition = createNewPos('d', 8);
					movePosition = createNewPos('c', 8);
					move = createNewMove(curPosition, movePosition);
					copyBoard(new_board, new_board2);
					executeMove(new_board2, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
					if (!thereIsCheck2(new_board2, playerColor,2,7))
					{
						free_Move(move);
						curPosition = createNewPos('e', 8);
						movePosition = createNewPos('c', 8);
						move = createNewMove2(curPosition, movePosition, 'c');
						appendMoveToMoveList(moves, move);
					}
					else
					{
						free_Move(move);
					}

				}
				else
				{
					free_Move(move);
				}
			}
		}
	}

}




// get all the possiable move of a given player
Move_List* getMoves(char board[BOARD_SIZE][BOARD_SIZE], char playerColor, int isTheKingMoved, int isTheRightRookMoved, int isTheLeftRookMoved)
{
	int i, j, k, l, column,row;
	Move_List* moves = createEmptyMoveList();
	Pos* curPosition;
	Pos* movePosition;
	Move* move;
	char new_board[BOARD_SIZE][BOARD_SIZE];
	int kingColum, kingRow;
	if (((isTheKingMoved == 0 && isTheRightRookMoved == 0) || (isTheKingMoved == 0 && isTheLeftRookMoved == 0)) && !thereIsCheck(board, playerColor))
	{
		casteling(moves, board, playerColor, isTheKingMoved, isTheRightRookMoved, isTheLeftRookMoved);
	}


	if (playerColor == 'w') 
	{
		for (column = 0; column < BOARD_SIZE; column++) // we are finding the position of the king in the board
		{
			for (row = 0; row < BOARD_SIZE; row++)
			{
				if (board[column][row] == WHITE_K)
				{
					kingColum = column;
					kingRow = row;
				}
			}
		}


		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == WHITE_K)
				{

					if (i + 1 < BOARD_SIZE && j - 1 >= 0 && (board[i + 1][j - 1] == EMPTY || board[i + 1][j - 1] == BLACK_P || board[i + 1][j - 1] == BLACK_B || board[i + 1][j - 1] == BLACK_N || board[i + 1][j - 1] == BLACK_R || board[i + 1][j - 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum + 1, kingRow - 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && (board[i + 1][j] == EMPTY || board[i + 1][j] == BLACK_P || board[i + 1][j] == BLACK_B || board[i + 1][j] == BLACK_N || board[i + 1][j] == BLACK_R || board[i + 1][j] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), j + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum + 1, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE && (board[i + 1][j + 1] == EMPTY || board[i + 1][j + 1] == BLACK_P || board[i + 1][j + 1] == BLACK_B || board[i + 1][j + 1] == BLACK_N || board[i + 1][j + 1] == BLACK_R || board[i + 1][j + 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum + 1, kingRow + 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (j - 1 >= 0 && (board[i][j - 1] == EMPTY || board[i][j - 1] == BLACK_P || board[i][j - 1] == BLACK_B || board[i][j - 1] == BLACK_N || board[i][j - 1] == BLACK_R || board[i][j - 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow - 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (j + 1 < BOARD_SIZE && (board[i][j + 1] == EMPTY || board[i][j + 1] == BLACK_P || board[i][j + 1] == BLACK_B || board[i][j + 1] == BLACK_N || board[i][j + 1] == BLACK_R || board[i][j + 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow + 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j - 1 >= 0 && (board[i - 1][j - 1] == EMPTY || board[i - 1][j - 1] == BLACK_P || board[i - 1][j - 1] == BLACK_B || board[i - 1][j - 1] == BLACK_N || board[i - 1][j - 1] == BLACK_R || board[i - 1][j - 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum - 1, kingRow - 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && (board[i - 1][j] == EMPTY || board[i - 1][j] == BLACK_P || board[i - 1][j] == BLACK_B || board[i - 1][j] == BLACK_N || board[i - 1][j] == BLACK_R || board[i - 1][j] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), j + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum - 1, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j + 1 < BOARD_SIZE && (board[i - 1][j + 1] == EMPTY || board[i - 1][j + 1] == BLACK_P || board[i - 1][j + 1] == BLACK_B || board[i - 1][j + 1] == BLACK_N || board[i - 1][j + 1] == BLACK_R || board[i - 1][j + 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum - 1, kingRow + 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

				}


				if (board[i][j] == WHITE_P) // a pawn move
				{
					//regular move
					if (j + 1 < BOARD_SIZE && board[i][j + 1] == EMPTY)
					{
						if (j + 1 == BOARD_SIZE - 1) // promotion pawn
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 'a'), (j + 1) + 1);
							move = createNewMove2(curPosition, movePosition, 'b');
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor,kingColum,kingRow))
							{
								appendMoveToMoveList(moves, move);
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 'a'), (j + 1) + 1), 'r'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 'a'), (j + 1) + 1), 'n'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 'a'), (j + 1) + 1), 'q'));
							}
							else
							{
								free_Move(move);
							}
						}
						else
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 'a'), (j + 1) + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}

							/*if (j == 1 && board[i][j + 2] == EMPTY)
							{
								curPosition = createNewPos((char)(i + 'a'), j + 1);
								movePosition = createNewPos((char)(i + 'a'), (j + 1) + 2);
								move = createNewMove(curPosition, movePosition);
								copyBoard(board, new_board);
								executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
								if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
								{
									appendMoveToMoveList(moves, move);
								}
								else
								{
									free_Move(move);
								}

							}*/
						}

					}

					//a take moves:

					//take the Right piece:
					if (i + 1 < BOARD_SIZE &&  j + 1 < BOARD_SIZE && (board[i + 1][j + 1] == BLACK_P || board[i + 1][j + 1] == BLACK_B || board[i + 1][j + 1] == BLACK_N || board[i + 1][j + 1] == BLACK_R || board[i + 1][j + 1] == BLACK_Q))
					{
						if (j + 1 == BOARD_SIZE - 1) // promotion pawn
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 1 + 'a'), (j + 1) + 1);
							move = createNewMove2(curPosition, movePosition, 'b');
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 1 + 'a'), (j + 1) + 1), 'r'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 1 + 'a'), (j + 1) + 1), 'n'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 1 + 'a'), (j + 1) + 1), 'q'));
							}
							else
							{
								free_Move(move);
							}
						}


						else
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 1 + 'a'), (j + 1) + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}

						}
					}

					//take the Left piece:
					if (i - 1 >= 0 && j + 1 < BOARD_SIZE && (board[i - 1][j + 1] == BLACK_P || board[i - 1][j + 1] == BLACK_B || board[i - 1][j + 1] == BLACK_N || board[i - 1][j + 1] == BLACK_R || board[i - 1][j + 1] == BLACK_Q))
					{
						if (j + 1 == BOARD_SIZE - 1) // promotion pawn
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i - 1 + 'a'), (j + 1) + 1);
							move = createNewMove2(curPosition, movePosition, 'b');
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i - 1 + 'a'), (j + 1) + 1), 'r'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i - 1 + 'a'), (j + 1) + 1), 'n'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i - 1 + 'a'), (j + 1) + 1), 'q'));
							}
							else
							{
								free_Move(move);
							}
						}


						else
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i - 1 + 'a'), (j + 1) + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}

						}
					}

				}

				if (board[i][j] == WHITE_N)
				{
					if (i - 2 >= 0 && j - 1 >= 0 && (board[i - 2][j - 1] == EMPTY || board[i - 2][j - 1] == BLACK_P || board[i - 2][j - 1] == BLACK_N || board[i - 2][j - 1] == BLACK_B || board[i - 2][j - 1] == BLACK_R || board[i - 2][j - 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 2 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 2 >= 0 && j + 1 < BOARD_SIZE && (board[i - 2][j + 1] == EMPTY || board[i - 2][j + 1] == BLACK_P || board[i - 2][j + 1] == BLACK_N || board[i - 2][j + 1] == BLACK_B || board[i - 2][j + 1] == BLACK_R || board[i - 2][j + 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 2 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j - 2 >= 0 && (board[i - 1][j - 2] == EMPTY || board[i - 1][j - 2] == BLACK_P || board[i - 1][j - 2] == BLACK_N || board[i - 1][j - 2] == BLACK_B || board[i - 1][j - 2] == BLACK_R || board[i - 1][j - 2] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j - 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j + 2 < BOARD_SIZE && (board[i - 1][j + 2] == EMPTY || board[i - 1][j + 2] == BLACK_P || board[i - 1][j + 2] == BLACK_N || board[i - 1][j + 2] == BLACK_B || board[i - 1][j + 2] == BLACK_R || board[i - 1][j + 2] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j + 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 2 < BOARD_SIZE && j - 1 >= 0 && (board[i + 2][j - 1] == EMPTY || board[i + 2][j - 1] == BLACK_P || board[i + 2][j - 1] == BLACK_N || board[i + 2][j - 1] == BLACK_B || board[i + 2][j - 1] == BLACK_R || board[i + 2][j - 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 2 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 2 < BOARD_SIZE && j + 1 < BOARD_SIZE && (board[i + 2][j + 1] == EMPTY || board[i + 2][j + 1] == BLACK_P || board[i + 2][j + 1] == BLACK_N || board[i + 2][j + 1] == BLACK_B || board[i + 2][j + 1] == BLACK_R || board[i + 2][j + 1] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 2 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && j - 2 >= 0 && (board[i + 1][j - 2] == EMPTY || board[i + 1][j - 2] == BLACK_P || board[i + 1][j - 2] == BLACK_N || board[i + 1][j - 2] == BLACK_B || board[i + 1][j - 2] == BLACK_R || board[i + 1][j - 2] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j - 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && j + 2 < BOARD_SIZE && (board[i + 1][j + 2] == EMPTY || board[i + 1][j + 2] == BLACK_P || board[i + 1][j + 2] == BLACK_N || board[i + 1][j + 2] == BLACK_B || board[i + 1][j + 2] == BLACK_R || board[i + 1][j + 2] == BLACK_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j + 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}


				}

				if (board[i][j] == WHITE_B)
				{

					for (k = i + 1, l = j + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // All  moves to North East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // All moves to North West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--)  // All  moves to South West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i + 1, l = j - 1; k < BOARD_SIZE && l >= 0; k++, l--) // All  moves to South East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

				}

				if (board[i][j] == WHITE_R)
				{
					for (k = i + 1, l = j; k < BOARD_SIZE; k++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);

							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);

							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i - 1, l = j; k >= 0; k--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j + 1; l < BOARD_SIZE; l++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j - 1; l >= 0; l--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}




				}

				if (board[i][j] == WHITE_Q)
				{

					for (k = i + 1, l = j + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // All  moves to North East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // All moves to North West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--)  // All  moves to South West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i + 1, l = j - 1; k < BOARD_SIZE && l >= 0; k++, l--) // All  moves to South East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i + 1, l = j; k < BOARD_SIZE; k++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i - 1, l = j; k >= 0; k--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j + 1; l < BOARD_SIZE; l++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j - 1; l >= 0; l--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == BLACK_P || board[k][l] == BLACK_B || board[k][l] == BLACK_N || board[k][l] == BLACK_R || board[k][l] == BLACK_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

				}

				

			}

		}

	}
	else // black move
	{
		for (column = 0; column < BOARD_SIZE; column++)// we are finding the position of the king in the board
		{
			for (row = 0; row < BOARD_SIZE; row++)
			{
				if (board[column][row] == BLACK_K)
				{
					kingColum = column;
					kingRow = row;
				}
			}
		}



		for (i = 0; i < BOARD_SIZE; i++)
		{
			for (j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j] == BLACK_K) 
				{

					if (i + 1 < BOARD_SIZE && j - 1 >= 0 && (board[i + 1][j - 1] == EMPTY || board[i + 1][j - 1] == WHITE_P || board[i + 1][j - 1] == WHITE_B || board[i + 1][j - 1] == WHITE_N || board[i + 1][j - 1] == WHITE_R || board[i + 1][j - 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum + 1, kingRow - 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && (board[i + 1][j] == EMPTY || board[i + 1][j] == WHITE_P || board[i + 1][j] == WHITE_B || board[i + 1][j] == WHITE_N || board[i + 1][j] == WHITE_R || board[i + 1][j] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), j + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum + 1, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE && (board[i + 1][j + 1] == EMPTY || board[i + 1][j + 1] == WHITE_P || board[i + 1][j + 1] == WHITE_B || board[i + 1][j + 1] == WHITE_N || board[i + 1][j + 1] == WHITE_R || board[i + 1][j + 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum + 1, kingRow + 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (j - 1 >= 0 && (board[i][j - 1] == EMPTY || board[i][j - 1] == WHITE_P || board[i][j - 1] == WHITE_B || board[i][j - 1] == WHITE_N || board[i][j - 1] == WHITE_R || board[i][j - 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow - 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (j + 1 < BOARD_SIZE && (board[i][j + 1] == EMPTY || board[i][j + 1] == WHITE_P || board[i][j + 1] == WHITE_B || board[i][j + 1] == WHITE_N || board[i][j + 1] == WHITE_R || board[i][j + 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow + 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j - 1 >= 0 && (board[i - 1][j - 1] == EMPTY || board[i - 1][j - 1] == WHITE_P || board[i - 1][j - 1] == WHITE_B || board[i - 1][j - 1] == WHITE_N || board[i - 1][j - 1] == WHITE_R || board[i - 1][j - 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum - 1, kingRow - 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && (board[i - 1][j] == EMPTY || board[i - 1][j] == WHITE_P || board[i - 1][j] == WHITE_B || board[i - 1][j] == WHITE_N || board[i - 1][j] == WHITE_R || board[i - 1][j] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), j + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum - 1, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j + 1 < BOARD_SIZE && (board[i - 1][j + 1] == EMPTY || board[i - 1][j + 1] == WHITE_P || board[i - 1][j + 1] == WHITE_B || board[i - 1][j + 1] == WHITE_N || board[i - 1][j + 1] == WHITE_R || board[i - 1][j + 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum - 1, kingRow + 1))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

				}



				if (board[i][j] == BLACK_P) // a pawn move
				{
					//regular move
					if (j - 1 >= 0 && board[i][j - 1] == EMPTY)
					{
						if (j - 1 == 0) // promotion pawn
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 'a'), (j - 1) + 1);
							move = createNewMove2(curPosition, movePosition, 'b');
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 'a'), (j - 1) + 1), 'r'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 'a'), (j - 1) + 1), 'n'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 'a'), (j - 1) + 1), 'q'));
							}
							else
							{
								free_Move(move);
							}
						}
						else
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 'a'), (j - 1) + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						/*	if (j == BOARD_SIZE - 2 && board[i][j - 2] == EMPTY)
							{
								curPosition = createNewPos((char)(i + 'a'), j + 1);
								movePosition = createNewPos((char)(i + 'a'), (j - 2) + 1);
								move = createNewMove(curPosition, movePosition);
								copyBoard(board, new_board);
								executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
								if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
								{
									appendMoveToMoveList(moves, move);
								}
								else
								{
								free_Move(move);
								}

							}*/
						}

					}

					//a take moves:

					//take the Right piece:
					if (i + 1 < BOARD_SIZE &&  j - 1 >= 0 && (board[i + 1][j - 1] == WHITE_P || board[i + 1][j - 1] == WHITE_B || board[i + 1][j - 1] == WHITE_N || board[i + 1][j - 1] == WHITE_R || board[i + 1][j - 1] == WHITE_Q))
					{
						if (j - 1 == 0) // promotion pawn
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 1 + 'a'), (j - 1) + 1);
							move = createNewMove2(curPosition, movePosition, 'b');
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 1 + 'a'), (j - 1) + 1), 'r'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 1 + 'a'), (j - 1) + 1), 'n'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i + 1 + 'a'), (j - 1) + 1), 'q'));
							}
							else
							{
								free_Move(move);
							}
						}
						else
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i + 1 + 'a'), (j - 1) + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}

						}
					}

					//take the Left piece:
					if (i - 1 >= 0 && j - 1 >= 0 && (board[i - 1][j - 1] == WHITE_P || board[i - 1][j - 1] == WHITE_B || board[i - 1][j - 1] == WHITE_N || board[i - 1][j - 1] == WHITE_R || board[i - 1][j - 1] == WHITE_Q))
					{
						if (j - 1 == 0) // promotion pawn
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i - 1 + 'a'), (j - 1) + 1);
							move = createNewMove2(curPosition, movePosition, 'b');
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i - 1 + 'a'), (j - 1) + 1), 'r'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i - 1 + 'a'), (j - 1) + 1), 'n'));
								appendMoveToMoveList(moves, createNewMove2(createNewPos((char)(i + 'a'), j + 1), createNewPos((char)(i - 1 + 'a'), (j - 1) + 1), 'q'));
							}
							else
							{
								free_Move(move);
							}
						}


						else
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(i - 1 + 'a'), (j - 1) + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}

						}
					}

				}

				if (board[i][j] == BLACK_N)
				{
					if (i - 2 >= 0 && j - 1 >= 0 && (board[i - 2][j - 1] == EMPTY || board[i - 2][j - 1] == WHITE_P || board[i - 2][j - 1] == WHITE_N || board[i - 2][j - 1] == WHITE_B || board[i - 2][j - 1] == WHITE_R || board[i - 2][j - 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 2 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 2 >= 0 && j + 1 < BOARD_SIZE && (board[i - 2][j + 1] == EMPTY || board[i - 2][j + 1] == WHITE_P || board[i - 2][j + 1] == WHITE_N || board[i - 2][j + 1] == WHITE_B || board[i - 2][j + 1] == WHITE_R || board[i - 2][j + 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 2 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j - 2 >= 0 && (board[i - 1][j - 2] == EMPTY || board[i - 1][j - 2] == WHITE_P || board[i - 1][j - 2] == WHITE_N || board[i - 1][j - 2] == WHITE_B || board[i - 1][j - 2] == WHITE_R || board[i - 1][j - 2] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j - 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i - 1 >= 0 && j + 2 < BOARD_SIZE && (board[i - 1][j + 2] == EMPTY || board[i - 1][j + 2] == WHITE_P || board[i - 1][j + 2] == WHITE_N || board[i - 1][j + 2] == WHITE_B || board[i - 1][j + 2] == WHITE_R || board[i - 1][j + 2] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i - 1 + 'a'), (j + 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 2 < BOARD_SIZE && j - 1 >= 0 && (board[i + 2][j - 1] == EMPTY || board[i + 2][j - 1] == WHITE_P || board[i + 2][j - 1] == WHITE_N || board[i + 2][j - 1] == WHITE_B || board[i + 2][j - 1] == WHITE_R || board[i + 2][j - 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 2 + 'a'), (j - 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 2 < BOARD_SIZE && j + 1 < BOARD_SIZE && (board[i + 2][j + 1] == EMPTY || board[i + 2][j + 1] == WHITE_P || board[i + 2][j + 1] == WHITE_N || board[i + 2][j + 1] == WHITE_B || board[i + 2][j + 1] == WHITE_R || board[i + 2][j + 1] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 2 + 'a'), (j + 1) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && j - 2 >= 0 && (board[i + 1][j - 2] == EMPTY || board[i + 1][j - 2] == WHITE_P || board[i + 1][j - 2] == WHITE_N || board[i + 1][j - 2] == WHITE_B || board[i + 1][j - 2] == WHITE_R || board[i + 1][j - 2] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j - 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}

					if (i + 1 < BOARD_SIZE && j + 2 < BOARD_SIZE && (board[i + 1][j + 2] == EMPTY || board[i + 1][j + 2] == WHITE_P || board[i + 1][j + 2] == WHITE_N || board[i + 1][j + 2] == WHITE_B || board[i + 1][j + 2] == WHITE_R || board[i + 1][j + 2] == WHITE_Q))
					{
						curPosition = createNewPos((char)(i + 'a'), j + 1);
						movePosition = createNewPos((char)(i + 1 + 'a'), (j + 2) + 1);
						move = createNewMove(curPosition, movePosition);
						copyBoard(board, new_board);
						executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
						if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
						{
							appendMoveToMoveList(moves, move);
						}
						else
						{
							free_Move(move);
						}
					}


				}

				if (board[i][j] == BLACK_B)
				{

					for (k = i + 1, l = j + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // All  moves to North East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // All moves to North West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--)  // All  moves to South West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i + 1, l = j - 1; k < BOARD_SIZE && l >= 0; k++, l--) // All  moves to South East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

				}

				if (board[i][j] == BLACK_R)
				{
					for (k = i + 1, l = j; k < BOARD_SIZE; k++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);

							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i - 1, l = j; k >= 0; k--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j + 1; l < BOARD_SIZE; l++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j - 1; l >= 0; l--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}




				}

				if (board[i][j] == BLACK_Q)
				{

					for (k = i + 1, l = j + 1; k < BOARD_SIZE && l < BOARD_SIZE; k++, l++) // All  moves to North East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j + 1; k >= 0 && l < BOARD_SIZE; k--, l++) // All moves to North West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i - 1, l = j - 1; k >= 0 && l >= 0; k--, l--)  // All  moves to South West
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i + 1, l = j - 1; k < BOARD_SIZE && l >= 0; k++, l--) // All  moves to South East
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}

					}

					for (k = i + 1, l = j; k < BOARD_SIZE; k++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i - 1, l = j; k >= 0; k--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j + 1; l < BOARD_SIZE; l++) // right vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

					for (k = i, l = j - 1; l >= 0; l--) // left vertical
					{
						if (board[k][l] == EMPTY)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
						}
						else if (board[k][l] == WHITE_P || board[k][l] == WHITE_B || board[k][l] == WHITE_N || board[k][l] == WHITE_R || board[k][l] == WHITE_Q)
						{
							curPosition = createNewPos((char)(i + 'a'), j + 1);
							movePosition = createNewPos((char)(k + 'a'), l + 1);
							move = createNewMove(curPosition, movePosition);
							copyBoard(board, new_board);
							executeMove(new_board, move, &isTheKingMoved, &isTheRightRookMoved, &isTheLeftRookMoved);
							if (!thereIsCheck2(new_board, playerColor, kingColum, kingRow))
							{
								appendMoveToMoveList(moves, move);
							}
							else
							{
								free_Move(move);
							}
							break;
						}
						else
						{
							break;
						}
					}

				}

				

			}

		}
	}


	return moves;

}


//get a move and return a copy of it
Move* copyMove(Move* toCopy)
{
	Move* newMoveHead;

	if (toCopy == NULL)  //Got empty move
	{
		return NULL;
	}

	newMoveHead = createNewMove2(createNewPos(toCopy->startPos->x, toCopy->startPos->y), createNewPos(toCopy->endPos->x, toCopy->endPos->y), toCopy->indicator);

	return newMoveHead;
}

//check if there is a mate on the board
int isMate(char board[BOARD_SIZE][BOARD_SIZE], char player_color)
{
	Move_List* moves;

	moves = getMoves(board, player_color, 1, 1, 1);
	if (moves->head == NULL) // there is no move;
	{
		free_Move_List(moves);
		return thereIsCheck(board, player_color);
	}
	free_Move_List(moves);

	return 0;
}

//check if there is a tie on the board
int isTie(char board[BOARD_SIZE][BOARD_SIZE], char player_color)
{
	Move_List* moves;

	moves = getMoves(board, player_color, 1, 1, 1);
	if (moves->head == NULL) // there is no move;
	{
		free_Move_List(moves);
		return !thereIsCheck(board, player_color);
	}
	free_Move_List(moves);

	return 0;
}

/*
* MinMax function
* Input: Board ,color, a pointer for the bestMove result , the originalMaxDepth, the "current" maxDepth , MinMax (that represent if we trying to maximize or minimize) , and a pointers for the casteling moves. 
* Every call:
* 1. Create a list for possible moves for the current player(Computer or User) using getMove function
* 2. For every move in the list, create a copy of "board"  , execute that move on that board, calls getBestMove on the new board and compare the return values
*	 with the other return values
* 3. Stop condition: maxDepth=0 -> then calculate return the score of the current board
* 4. bestMove pointer will be changed only when originalMaxDepth=maxDepth , meaning only the first call will change it
* 5. we need to perform malloc and free only on "**bestMove" when in level originalMaxDepth
* Uses color in order to decide how to getMoves and how to calculate the score
*/
/*int getBestMove(char board[BOARD_SIZE][BOARD_SIZE],char color, Move_List **bestMoves, int originalMaxDepth, int maxDepth, int MinMax, int alpa, int beta, int* isTheWhiteKingMoves, int* isTheWhiteRightRookMoves, int* isTheWhiteLeftRookMoves, int* isTheBlackKingMoves, int* isTheBlackRightRookMoves, int* isTheBlackLeftRookMoves)
{
	Move_List* move_list;
	Move *cur_move;
	int WhiteKing = *isTheWhiteKingMoves;
	int WhiteRightRook = *isTheWhiteRightRookMoves;
	int WhiteLeftRook = *isTheWhiteLeftRookMoves;
	int BlackKing = *isTheBlackKingMoves;
	int BlackRightRook = *isTheBlackRightRookMoves;
	int BlackLeftRook = *isTheBlackLeftRookMoves;

	char new_board[BOARD_SIZE][BOARD_SIZE];

	int cur_score;
	int res_score;


	if (maxDepth == 0)  // recursion STOP condition
	{	
		return getScore(board,color);  // return the score of the current Board
	}

	//Get all the possible moves

	if (MinMax == 1)  // We need to get the computer optional moves
	{
		//Check what is the computer color , and get all of the computer possible moves
		if (color == 'w')
		{
			move_list = getMoves(board, color, *isTheWhiteKingMoves, *isTheWhiteRightRookMoves, *isTheWhiteLeftRookMoves);
		}
		else
		{
			move_list = getMoves(board, color, *isTheBlackKingMoves, *isTheBlackRightRookMoves, *isTheBlackLeftRookMoves);
		}

		cur_score = -1001; // Initialize the lowest possible score
	}
	else // We need to get the user optional moves
	{
		if (color == 'w')
		{
			move_list = getMoves(board, 'b', *isTheBlackKingMoves, *isTheBlackRightRookMoves, *isTheBlackLeftRookMoves);
		}
		else
		{
			move_list = getMoves(board, 'w', *isTheWhiteKingMoves, *isTheWhiteRightRookMoves, *isTheWhiteLeftRookMoves);
		}

		cur_score = 1001; // Initialize the highest possible score
	}

	cur_move = move_list->head;

	//Walk through all the possible moves
	while (cur_move != NULL)  // move_list->move != NULL to make sure player isn't stuck
	{
		copyBoard(board, new_board);
		if (board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_P || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_N || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_B || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_R || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_Q || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_K)
		{
			executeMove(new_board, cur_move, isTheWhiteKingMoves, isTheWhiteRightRookMoves, isTheWhiteLeftRookMoves);
		}
		else
		{
			executeMove(new_board, cur_move, isTheBlackKingMoves, isTheBlackRightRookMoves, isTheBlackLeftRookMoves);
		}

		

		if (MinMax == 1)
		{
			res_score = getBestMove(new_board, color, NULL, originalMaxDepth, maxDepth - 1, 0, alpa, beta, isTheWhiteKingMoves, isTheWhiteRightRookMoves, isTheWhiteLeftRookMoves, isTheBlackKingMoves, isTheBlackRightRookMoves, isTheBlackLeftRookMoves);

		}
		else
		{
			res_score = getBestMove(new_board, color, NULL, originalMaxDepth, maxDepth - 1, 1, alpa, beta, isTheWhiteKingMoves, isTheWhiteRightRookMoves, isTheWhiteLeftRookMoves, isTheBlackKingMoves, isTheBlackRightRookMoves, isTheBlackLeftRookMoves);

		}


		//back to normal:
		*isTheWhiteKingMoves = WhiteKing;
		*isTheWhiteRightRookMoves = WhiteRightRook;
		*isTheWhiteLeftRookMoves = WhiteLeftRook;
		*isTheBlackKingMoves = BlackKing;
		*isTheBlackRightRookMoves = BlackRightRook;
		*isTheBlackLeftRookMoves = BlackLeftRook;

		if (res_score == cur_score)
		{
			if (originalMaxDepth == maxDepth && bestMoves!=NULL)   // The final move we return is always from the first level
			{
				appendMoveToMoveList2(*bestMoves, copyMove(cur_move));
				
			}
		}


		//Get Maximum score or Minimum score according to "MinMax" value
		if ((MinMax == 1 && res_score > cur_score) || (MinMax == 0 && res_score < cur_score))
		{
			cur_score = res_score;
			if (originalMaxDepth == maxDepth)   // The final move we return is always from the first level
			{
				free_Move_List(*bestMoves);
				*bestMoves = createEmptyMoveList();
				appendMoveToMoveList2(*bestMoves, copyMove(cur_move));
				//(*bestMoves)->head = cur_move;
			}

			
		}

		if (MinMax == 0 && cur_score < beta)
		{
			beta = cur_score;
		}
		if (MinMax == 1 && cur_score > alpa)
		{
			alpa = cur_score;
		}

		if (beta <= alpa)
		{
			break;
		}

		

		cur_move = cur_move->next;	//continue to the next move
	}

	if (move_list != NULL && move_list->head == NULL)  //No moves!
	{
		if (MinMax == 1)
		{
			if (thereIsCheck(board, color))
			{
				cur_score = -1000;
			}
			else
			{
				cur_score = -900;
			}
		}
		else
		{
			if (color == 'w')
			{
				if (thereIsCheck(board, 'b'))
				{
					cur_score = 1000;
				}
				else
				{
					cur_score = 900;
				}
			}
			else
			{
				if (thereIsCheck(board, 'w'))
				{
					cur_score = 1000;
				}
				else
				{
					cur_score = 900;
				}
			}
		}
	}


	//if (originalMaxDepth == maxDepth) //Change the move that we return
	//{
	//	if (bestMove != NULL && *bestMove != NULL && move_list != NULL)
	//	{
	//		remove_from_list(&move_list, *bestMove);    // Remove bestMove from move_list so it wouldn't be freed cause we need to return it and use it later!
	//	}
	//}


	free_Move_List(move_list);		  //Free Memory
	//printf("%d\n", cur_score);
	return cur_score;
}*/



/*
* MinMax function
* Input: Board ,color, a pointer for the bestMove result , the originalMaxDepth, the "current" maxDepth , MinMax (that represent if we trying to maximize or minimize) , and a pointers for the casteling moves.
* Every call:
* 1. Create a list for possible moves for the current player(Computer or User) using getMove function
* 2. For every move in the list, create a copy of "board"  , execute that move on that board, calls getBestMove on the new board and compare the return values
*	 with the other return values
* 3. Stop condition: maxDepth=0 -> then calculate return the score of the current board
* 4. bestMove pointer will be changed only when originalMaxDepth=maxDepth , meaning only the first call will change it
* 5. we need to perform malloc and free only on "**bestMove" when in level originalMaxDepth
* Uses color in order to decide how to getMoves and how to calculate the score
*/
/*int getBestMove2(char board[BOARD_SIZE][BOARD_SIZE], char color, int* numOfCalls, Move_List **bestMoves, int originalMaxDepth, int maxDepth, int MinMax, int alpa, int beta, int* isTheWhiteKingMoves, int* isTheWhiteRightRookMoves, int* isTheWhiteLeftRookMoves, int* isTheBlackKingMoves, int* isTheBlackRightRookMoves, int* isTheBlackLeftRookMoves)
{
	if (*numOfCalls == 0)
	{
		return 7777;
	}
	else
	{
		*numOfCalls = *numOfCalls - 1;
	}



	Move_List* move_list;
	Move *cur_move;
	int WhiteKing = *isTheWhiteKingMoves;
	int WhiteRightRook = *isTheWhiteRightRookMoves;
	int WhiteLeftRook = *isTheWhiteLeftRookMoves;
	int BlackKing = *isTheBlackKingMoves;
	int BlackRightRook = *isTheBlackRightRookMoves;
	int BlackLeftRook = *isTheBlackLeftRookMoves;

	char new_board[BOARD_SIZE][BOARD_SIZE];

	int cur_score;
	int res_score;


	if (maxDepth == 0)  // recursion STOP condition
	{
		return getScore2(board, color);  // return the score of the current Board
	}

	//Get all the possible moves

	if (MinMax == 1)  // We need to get the computer optional moves
	{
		//Check what is the computer color , and get all of the computer possible moves
		if (color == 'w')
		{
			move_list = getMoves(board, color, *isTheWhiteKingMoves, *isTheWhiteRightRookMoves, *isTheWhiteLeftRookMoves);
		}
		else
		{
			move_list = getMoves(board, color, *isTheBlackKingMoves, *isTheBlackRightRookMoves, *isTheBlackLeftRookMoves);
		}

		cur_score = -1001; // Initialize the lowest possible score
	}
	else // We need to get the user optional moves
	{
		if (color == 'w')
		{
			move_list = getMoves(board, 'b', *isTheBlackKingMoves, *isTheBlackRightRookMoves, *isTheBlackLeftRookMoves);
		}
		else
		{
			move_list = getMoves(board, 'w', *isTheWhiteKingMoves, *isTheWhiteRightRookMoves, *isTheWhiteLeftRookMoves);
		}

		cur_score = 1001; // Initialize the highest possible score
	}

	cur_move = move_list->head;

	//Walk through all the possible moves
	while (cur_move != NULL)  // move_list->move != NULL to make sure player isn't stuck
	{
		copyBoard(board, new_board);
		if (board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_P || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_N || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_B || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_R || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_Q || board[cur_move->startPos->x - 'a'][cur_move->startPos->y - 1] == WHITE_K)
		{
			executeMove(new_board, cur_move, isTheWhiteKingMoves, isTheWhiteRightRookMoves, isTheWhiteLeftRookMoves);
		}
		else
		{
			executeMove(new_board, cur_move, isTheBlackKingMoves, isTheBlackRightRookMoves, isTheBlackLeftRookMoves);
		}



		if (MinMax == 1)
		{
			res_score = getBestMove2(new_board, color, numOfCalls, NULL, originalMaxDepth, maxDepth - 1, 0, alpa, beta, isTheWhiteKingMoves, isTheWhiteRightRookMoves, isTheWhiteLeftRookMoves, isTheBlackKingMoves, isTheBlackRightRookMoves, isTheBlackLeftRookMoves);

		}
		else
		{
			res_score = getBestMove2(new_board, color, numOfCalls, NULL, originalMaxDepth, maxDepth - 1, 1, alpa, beta, isTheWhiteKingMoves, isTheWhiteRightRookMoves, isTheWhiteLeftRookMoves, isTheBlackKingMoves, isTheBlackRightRookMoves, isTheBlackLeftRookMoves);

		}

		if (res_score == 7777)
		{
			free_Move_List(move_list);
			return 7777;
		}


		//back to normal:
		*isTheWhiteKingMoves = WhiteKing;
		*isTheWhiteRightRookMoves = WhiteRightRook;
		*isTheWhiteLeftRookMoves = WhiteLeftRook;
		*isTheBlackKingMoves = BlackKing;
		*isTheBlackRightRookMoves = BlackRightRook;
		*isTheBlackLeftRookMoves = BlackLeftRook;

		if (res_score == cur_score)
		{
			if (originalMaxDepth == maxDepth && bestMoves != NULL)   // The final move we return is always from the first level
			{
				appendMoveToMoveList2(*bestMoves, copyMove(cur_move));

			}
		}


		//Get Maximum score or Minimum score according to "MinMax" value
		if ((MinMax == 1 && res_score > cur_score) || (MinMax == 0 && res_score < cur_score))
		{
			cur_score = res_score;
			if (originalMaxDepth == maxDepth)   // The final move we return is always from the first level
			{
				free_Move_List(*bestMoves);
				*bestMoves = createEmptyMoveList();
				appendMoveToMoveList2(*bestMoves, copyMove(cur_move));
				//(*bestMoves)->head = cur_move;
			}


		}

		if (MinMax == 0 && cur_score < beta)
		{
			beta = cur_score;
		}
		if (MinMax == 1 && cur_score > alpa)
		{
			alpa = cur_score;
		}

		if (beta <= alpa)
		{
			break;
		}



		cur_move = cur_move->next;	//continue to the next move
	}

	if (move_list != NULL && move_list->head == NULL)  //No moves!
	{
		if (MinMax == 1)
		{
			if (thereIsCheck(board, color))
			{
				cur_score = -1000;
			}
			else
			{
				cur_score = -900;
			}
		}
		else
		{
			if (color == 'w')
			{
				if (thereIsCheck(board, 'b'))
				{
					cur_score = 1000;
				}
				else
				{
					cur_score = 900;
				}
			}
			else
			{
				if (thereIsCheck(board, 'w'))
				{
					cur_score = 1000;
				}
				else
				{
					cur_score = 900;
				}
			}
		}
	}


	//if (originalMaxDepth == maxDepth) //Change the move that we return
	//{
	//	if (bestMove != NULL && *bestMove != NULL && move_list != NULL)
	//	{
	//		remove_from_list(&move_list, *bestMove);    // Remove bestMove from move_list so it wouldn't be freed cause we need to return it and use it later!
	//	}
	//}


	free_Move_List(move_list);		  //Free Memory
	//printf("%d\n", cur_score);
	return cur_score;
}*/






// get one of the best moves possiable for a given player.
Move* tip(char board[BOARD_SIZE][BOARD_SIZE], int difficultyInput, char color)
{
	Move_List* moves = NULL;
	Move* move = NULL;
	int maxCalls;
	int WhiteKing = whitePieceWasMoved[KING];
	int WhiteRightRook = whitePieceWasMoved[RIGHT_ROOK];
	int WhiteLeftRook = whitePieceWasMoved[LEFT_ROOK];
	int BlackKing = blackPieceWasMoved[KING];
	int BlackRightRook = blackPieceWasMoved[RIGHT_ROOK];
	int BlackLeftRook = blackPieceWasMoved[LEFT_ROOK];

	if (difficultyInput >= 1 && difficultyInput <= 4)
	{
		getBestMove(board, color, &moves, difficultyInput, difficultyInput, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
		if (moves != NULL)
		{
			move = copyMove(moves->head);
			free_Move_List(moves);
			return move;
		}

	}
	else if (difficultyInput == 5)
	{

		if (getBestMove(board, color, &moves, 1, 1, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]) == 1000)
		{
			if (moves != NULL)
			{
				move = copyMove(moves->head);
				free_Move_List(moves);
				return move;
			}
		}

		free_Move_List(moves);
		moves = NULL;

		if (getBestMove(board, color, &moves, 3, 3, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]) == 1000)
		{
			if (moves != NULL)
			{
				move = copyMove(moves->head);
				free_Move_List(moves);
				return move;
			}
		}

		free_Move_List(moves);
		moves = NULL;
		maxCalls = 1000000;

		if (getBestMove2(board, color, &maxCalls, &moves, 5, 5, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]) != 7777)
		{
			if (moves != NULL)
			{
				move = copyMove(moves->head);
				free_Move_List(moves);
				return move;
			}
		}
		else
		{

			whitePieceWasMoved[KING] = WhiteKing;
			whitePieceWasMoved[RIGHT_ROOK] = WhiteRightRook;
			whitePieceWasMoved[LEFT_ROOK] = WhiteLeftRook;
			blackPieceWasMoved[KING] = BlackKing;
			blackPieceWasMoved[RIGHT_ROOK] = BlackRightRook;
			blackPieceWasMoved[LEFT_ROOK] = BlackLeftRook;
			free_Move_List(moves);
			moves = NULL;

			getBestMove(board, color, &moves, 4, 4, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
			if (moves != NULL)
			{
				move = copyMove(moves->head);
				free_Move_List(moves);
				return move;
			}



		}

	}




	return NULL;
}


