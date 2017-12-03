#include "chess.h"


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
int getBestMove(char board[BOARD_SIZE][BOARD_SIZE], char color, Move_List **bestMoves, int originalMaxDepth, int maxDepth, int MinMax, int alpa, int beta, int* isTheWhiteKingMoves, int* isTheWhiteRightRookMoves, int* isTheWhiteLeftRookMoves, int* isTheBlackKingMoves, int* isTheBlackRightRookMoves, int* isTheBlackLeftRookMoves)
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
		return getScore(board, color);  // return the score of the current Board
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
int getBestMove2(char board[BOARD_SIZE][BOARD_SIZE], char color, int* numOfCalls, Move_List **bestMoves, int originalMaxDepth, int maxDepth, int MinMax, int alpa, int beta, int* isTheWhiteKingMoves, int* isTheWhiteRightRookMoves, int* isTheWhiteLeftRookMoves, int* isTheBlackKingMoves, int* isTheBlackRightRookMoves, int* isTheBlackLeftRookMoves)
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
}