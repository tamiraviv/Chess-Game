#include "chess.h"

void setPieceCmd(char* userInput)
{
	int x = -1, y = -1;
	int colorInput = -1;
	int res = 0;
	getWord(cmd_arg_1, userInput, 2);
	getWord(cmd_arg_2, userInput, 3);
	getWord(cmd_arg_3, userInput, 4);

	if (correctPositionFormant(cmd_arg_1) == NO)
	{
		printf(WRONG_POSITION);
		return;
	}

	x = (int)cmd_arg_1[1] - 97;  // Minus the value of 'a'
	y = (int)cmd_arg_1[3] - 49; // Minus the value of '1'


	//Parse color
	if (strcmp(cmd_arg_2, "white") == 0)
	{
		colorInput = WHITE;
	}
	else if (strcmp(cmd_arg_2, "black") == 0)
	{
		colorInput = BLACK;
	}
	else
	{
		printf("Invalid piece color!\n");
		return;
	}


	//Parse piece type
	res = setPiece(chess_board, x, y, colorInput, pieceTypeToCharacter(cmd_arg_3));
	if (res == INVALID_POSITION)
	{
		printf(WRONG_POSITION);
	}
	else if (res == INVALID_INITIALIZATION)
	{
		printf(NO_PIECE);
	}

}

void removePieceCmd(char* userInput)
{
	int x = -1, y = -1;

	getWord(cmd_arg_1, userInput, 2);

	if (correctPositionFormant(cmd_arg_1) == NO)
	{
		printf(WRONG_POSITION);
		return;
	}

	x = (int)cmd_arg_1[1] - 97;  // Minus the value of 'a'
	y = (int)cmd_arg_1[3] - 49; // Minus the value of '1'


	if (removePiece(chess_board, x, y) == INVALID_POSITION)
	{
		printf(WRONG_POSITION);
	}
}

void nextPlayerCmd(char* userInput)
{
	int colorInput = -1;

	getWord(cmd_arg_1, userInput, 2);

	if (strcmp(cmd_arg_1, "white") == 0)
	{
		colorInput = WHITE;
	}
	else if (strcmp(cmd_arg_1, "black") == 0)
	{
		colorInput = BLACK;
	}

	if (setNextPlayer(colorInput) < 0)
	{
		printf("Illegal color. Next player color must be black or white.\n");
	}

}

void gameUserColorCmd(char* userInput)
{
	int colorInput = -1;

	if (gameMode == PLAYER_VS_PLAYER_MODE)
	{
		printf(ILLEGAL_COMMAND);
		return;
	}

	getWord(cmd_arg_1, userInput, 2);


	if (strcmp(cmd_arg_1, "white") == 0)
	{
		colorInput = WHITE;
	}
	else if (strcmp(cmd_arg_1, "black") == 0)
	{
		colorInput = BLACK;
	}


	if (setUserColor(colorInput) < 0)
	{
		printf("Illegal user color. User color must be black or white.\n");
	}


}

void gameDifficultyCmd(char* userInput)
{
	int difficultyInput = 0;

	if (gameMode == PLAYER_VS_PLAYER_MODE)
	{
		printf(ILLEGAL_COMMAND);

		return;
	}

	getWord(cmd_arg_1, userInput, 2);

	if (strcmp(cmd_arg_1, "depth") == 0)
	{
		getWord(cmd_arg_2, userInput, 3);
		difficultyInput = (int)strtol(cmd_arg_2, (char **)NULL, 10);

		if (difficultyInput == DIFFICULTY_BEST || setGameDifficulty(difficultyInput) < 0)
		{
			printf(WRONG_MINIMAX_DEPTH);
		}
	}
	else if (strcmp(cmd_arg_1, "best") == 0)
	{
		setGameDifficultyBest();
	}
	else
	{

		printf(WRONG_MINIMAX_DEPTH);
	}


}

void gameModeCmd(char* userInput)
{
	int gameModeInput = 0;

	getWord(cmd_arg_1, userInput, 2);
	gameModeInput = (int)strtol(cmd_arg_1, (char **)NULL, 10);

	if (setGameMode(gameModeInput) < 0)
	{
		printf(WRONG_GAME_MODE);
	}
	else
	{
		if (gameMode == PLAYER_VS_PLAYER_MODE)
		{
			printf(TWO_PLAYERS_GAME_MODE);
		}
		else if (gameMode == PLAYER_VS_COMPUTER_MODE)
		{
			printf(PLAYER_VS_AI_GAME_MODE);
		}
	}
}

void loadGameCmd(char* userInput)
{
	char filePath[10000];

	getWord(filePath, userInput, 2);

	if (xml_LoadGame(filePath) < 0)
	{
		printf(WRONG_FILE_NAME);
	}
	else
	{
		printBoard(chess_board);
	}
}

void saveGameCmd(char* userInput)
{
	char filePath[10000];

	getWord(filePath, userInput, 2);

	if (xml_SaveGame(filePath) < 0)
	{
		printf(WRONG_FILE_NAME);
	}
}

void movePieceCmd(char* userInput)
{
	int src_x = -1, src_y = -1;
	int dst_x = -1, dst_y = -1;
	char pieceType[10];

	int res = -1;

	getWord(cmd_arg_1, userInput, 2);
	getWord(cmd_arg_2, userInput, 4);
	getWord(pieceType, userInput, 5);

	if (correctPositionFormant(cmd_arg_1) == NO || correctPositionFormant(cmd_arg_2) == NO)
	{
		printf(WRONG_POSITION);
		return;
	}


	src_x = (int)cmd_arg_1[1] - 97;  // Minus the value of 'a'
	src_y = (int)cmd_arg_1[3] - 49; // Minus the value of '1'

	dst_x = (int)cmd_arg_2[1] - 97;  // Minus the value of 'a'
	dst_y = (int)cmd_arg_2[3] - 49; // Minus the value of '1'

	//[Set default promotion only if pieceType=Pawn , Moved to the last line and user didn't specify promotion]
	if ( (correctPositionFormant(cmd_arg_1) && isWithinBoardBorders(src_x, src_y)))
	{
		if (chess_board[src_x][src_y] == 'm' || chess_board[src_x][src_y] == 'M')
		{
			setDefaultPromotion(dst_y, pieceType);
		}
	}

	res = movePiece(chess_board, src_x, src_y, dst_x, dst_y, pieceTypeToCharacter(pieceType));

	if (res == INVALID_POSITION)
	{
		printf(WRONG_POSITION);
	}
	else if (res == NOT_YOUR_PIECE)
	{
		printf(INVALID_POSITION_MESSAGE);
	}
	else if (res == IILEGAL_MOVE)
	{
		printf(ILLEGAL_MOVE_MESSAGE);
	}
	else if (res == 0) //The move was executed successfully -> switch to next player and printGameStatus(TIE/Check/MATE)
	{
		printBoard(chess_board); 
		switchNextPlayerColor();
		printGameStatus(); //(TIE/Check/MATE)
	}
}

void startGameCmd()
{
	if (isBothKingsExist(chess_board))
	{
		startGame_init();
		startGameConsole();
	}
	else
	{
		printf(WROND_BOARD_INITIALIZATION);
	}

}

void getMovesCmd(char* userInput)
{
	int x = -1, y = -1;
	int res = -1;

	getWord(cmd_arg_1, userInput, 2);

	if (correctPositionFormant(cmd_arg_1) == NO)
	{
		printf(WRONG_POSITION);
		return;
	}

	x = (int)cmd_arg_1[1] - 97;  // Minus the value of 'a'
	y = (int)cmd_arg_1[3] - 49; // Minus the value of '1'

	res = printMoves(chess_board, x, y);

	if (res == INVALID_POSITION)
	{
		printf(WRONG_POSITION);
	}
	else if (res == NOT_YOUR_PIECE)
	{
		printf(INVALID_POSITION_MESSAGE);
	}
}

void getBestMovesCmd(char* userInput)
{
	int depth = -1;
	getWord(cmd_arg_1, userInput, 2);

	if ((int)cmd_arg_1[0] >= '1' && (int)cmd_arg_1[0] <= '4')
	{
		depth = (int)cmd_arg_1[0] - '0';
	}
	else
	{
		depth = DIFFICULTY_BEST;
	}

	printBestMoves(depth);
}

void getScoreCmd(char* userInput)
{
	int src_x = -1, src_y = -1;
	int dst_x = -1, dst_y = -1;
	char pieceType[10] = "";
	char moveInput[10];
	char moveType[10];
	int isCastle = 0;

	///////////////////////////////////////////////////////////

	char difficultyInput[10];
	int difficulty = 0;

	//Get difficulty
	getWord(difficultyInput, userInput, 2);
	difficulty = (int)difficultyInput[0] - '0';

	//Difficulty is "best"
	if (difficulty < 1 || difficulty > 4)
	{
		difficulty = DIFFICULTY_BEST;
	}


	getWord(moveType, userInput, 3);
	if (strcmp(moveType, "castle") == 0)
	{
		isCastle = 1;
	}
	else
	{
		isCastle = 0;
	}

	getWord(moveInput, userInput, 4);
	src_x = (int)moveInput[1] - 97;  // Minus the value of 'a'
	src_y = (int)moveInput[3] - 49; // Minus the value of '1'

	//Get destination and piece type
	if (isCastle == 0)
	{
		getWord(moveInput, userInput, 6);
		dst_x = (int)moveInput[1] - 97;  // Minus the value of 'a'
		dst_y = (int)moveInput[3] - 49; // Minus the value of '1'

		getWord(pieceType, userInput, 7);
	}


	//For debugging: //	printf("Debugging: isCastle = %d , difficulty=%d , src=%d,%d , dst=%d,%d, type= %c\n", isCastle, difficulty, src_x, src_y, dst_x, dst_y, pieceTypeToCharacter(pieceType));


	printf("%d\n", getBestScore(chess_board, difficulty, src_x, src_y, dst_x, dst_y, pieceTypeToCharacter(pieceType)));
	//For debugging://printf("%d\n",getScore(isCastle, difficulty, src_x, src_y, dst_x, dst_y, pieceTypeToCharacter(pieceType)));
}

void castleCmd(char* userInput)
{
	int src_x = -1, src_y = -1;
	char moveInput[10];
	int res = 0;

	getWord(moveInput, userInput, 2);
	src_x = (int)moveInput[1] - 97;  // Minus the value of 'a'
	src_y = (int)moveInput[3] - 49; // Minus the value of '1'

	res = castle(chess_board, src_x, src_y);


	if (res == INVALID_POSITION)
	{
		printf(WRONG_POSITION);
	}
	else if (res == NOT_YOUR_PIECE)
	{
		printf(INVALID_POSITION_MESSAGE);
	}
	else if (res == WRONG_ROOK_POSITION_ERROR)
	{
		printf(WRONG_ROOK_POSITION);
	}
	else if (res == IILEGAL_CASLTING_ERROR)
	{
		printf(ILLEGAL_CALTLING_MOVE);
	}
	else if (res == 0)
	{
		printBoard(chess_board);
		switchNextPlayerColor();
		printGameStatus(); //(TIE/Check/MATE)
		
	}
	//getchar();
}

