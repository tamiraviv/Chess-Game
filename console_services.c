#include "chess.h"


int printMoves(char board[BOARD_SIZE][BOARD_SIZE], int x, int y)
{
	Move_List* move_list = NULL;

	if (!isWithinBoardBorders(x, y))
	{
		return INVALID_POSITION;
	}
	else if (board[x][y] == EMPTY || (next_player == WHITE && isupper(board[x][y])) || (next_player == BLACK && islower(board[x][y])))
	{
		return NOT_YOUR_PIECE;
	}

	if (next_player == WHITE)
	{
		move_list = getMoves(board, next_player, whitePieceWasMoved[KING], whitePieceWasMoved[RIGHT_ROOK], whitePieceWasMoved[LEFT_ROOK]);
	}
	else
	{
		move_list = getMoves(board, next_player, blackPieceWasMoved[KING], blackPieceWasMoved[RIGHT_ROOK], blackPieceWasMoved[LEFT_ROOK]);
	}

	printPieceMoves(move_list, x, y);

	free_Move_List(move_list);

	return 0;

}

void printBestMoves(int depth)
{
	Move_List* moves = NULL;
	int maxCalls;
	int WhiteKing = whitePieceWasMoved[KING];
	int WhiteRightRook = whitePieceWasMoved[RIGHT_ROOK];
	int WhiteLeftRook = whitePieceWasMoved[LEFT_ROOK];
	int BlackKing = blackPieceWasMoved[KING];
	int BlackRightRook = blackPieceWasMoved[RIGHT_ROOK];
	int BlackLeftRook = blackPieceWasMoved[LEFT_ROOK];
	if (depth >= 1 && depth <= 4)
	{
		getBestMove(chess_board, next_player, &moves, depth, depth, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
		
		if (moves != NULL)
		{
			printMoveList(moves);
			free_Move_List(moves);
		}
	}
	else if (depth == 5)
	{

		if (getBestMove(chess_board, next_player, &moves, 1, 1, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]) == 1000)
		{
			if (moves != NULL)
			{
				printMoveList(moves);
				free_Move_List(moves);
				return;
			}
		}
		free_Move_List(moves);
		moves = NULL;

		if (getBestMove(chess_board, next_player, &moves, 3, 3, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]) == 1000)
		{
			if (moves != NULL)
			{
				printMoveList(moves);
				free_Move_List(moves);
				return;
			}
		}

		free_Move_List(moves);
		moves = NULL;

		maxCalls = 1000000;

		if (getBestMove2(chess_board, next_player, &maxCalls, &moves, 5, 5, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]) != 7777)
		{
			if (moves != NULL)
			{
				printMoveList(moves);
				free_Move_List(moves);
				return;
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

			getBestMove(chess_board, next_player, &moves, 4, 4, 1, -1001, 1001, &whitePieceWasMoved[KING], &whitePieceWasMoved[RIGHT_ROOK], &whitePieceWasMoved[LEFT_ROOK], &blackPieceWasMoved[KING], &blackPieceWasMoved[RIGHT_ROOK], &blackPieceWasMoved[LEFT_ROOK]);
			if (moves != NULL)
			{
				printMoveList(moves);
				free_Move_List(moves);
				return;
			}



		}

	}
}


//Print only moves of piece on the board out of a moves list
void printPieceMoves(Move_List* moves, int x, int y)
{
	Move *lastNode;

	if (moves == NULL || moves->head == NULL)
	{
		return;
	}

	lastNode = moves->head;

	while (lastNode != NULL)
	{
		//Print only moves of piece on the board
		if (((lastNode->startPos->x) - 'a' == x) && ((lastNode->startPos->y) - 1 == y))
		{
			printMove(lastNode);
		}

		if (x == 0 && y == 0)
		{
			if (lastNode->indicator == 'c' && (lastNode->endPos->x == 'c') && (lastNode->startPos->y == 1))
			{
				printMove(lastNode);
			}
		}

		if (x == 7 && y == 0)
		{
			if (lastNode->indicator == 'c' && (lastNode->endPos->x == 'g') && (lastNode->startPos->y == 1))
			{
				printMove(lastNode);
			}
		}

		if (x == 0 && y == 7)
		{
			if (lastNode->indicator == 'c' && (lastNode->endPos->x == 'c') && (lastNode->startPos->y == 8))
			{
				printMove(lastNode);
			}
		}

		if (x == 7 && y == 7)
		{
			if (lastNode->indicator == 'c' && (lastNode->endPos->x == 'g') && (lastNode->startPos->y == 8))
			{
				printMove(lastNode);
			}
		}

		lastNode = lastNode->next;
	}

}
