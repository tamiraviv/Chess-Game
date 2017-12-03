#include "chess.h"

char chess_board[BOARD_SIZE][BOARD_SIZE];
int programState = SETTINGS_STATE;
char user_color = WHITE;
int gameMode = PLAYER_VS_PLAYER_MODE;
int gameDifficulty = DIFFICULTY_DEFAULT;
char next_player = WHITE;

//Castling
int blackPieceWasMoved[3];
int whitePieceWasMoved[3];

char cmd_arg_1[MAX_INPUT_LENGTH];
char cmd_arg_2[MAX_INPUT_LENGTH];
char cmd_arg_3[MAX_INPUT_LENGTH];
char cmd_arg_4[MAX_INPUT_LENGTH];


int main(int argc, char *argv[])
{
	init_board(chess_board);
	//completeTest(); //Delete

	if ((argc == 1) || ((argc == 2) && (strcmp(argv[1], "console") == 0)))
	{
		//runGUIMode();
		runConsoleMode();
	}
	else if (argc == 2 && strcmp(argv[1], "gui") == 0)
	{
		runGUIMode();
	}
	else
	{
		printf("Wrong number of arguments or wrong parameters!!!");
	}

	//getchar();
	return 0;
}

//Assumptions: Maximum user input is 50 Characters
void runConsoleMode()
{
	printBoard(chess_board);
	setGameSettings();
}

void setGameSettings()
{
	char userInput[MAX_INPUT_LENGTH];
	char cmd[MAX_INPUT_LENGTH];

	while (programState == SETTINGS_STATE)
	{
		printf(ENTER_SETTINGS);
		fgets(userInput, MAX_INPUT_LENGTH, stdin);  //fgets: input -> new line(10) -> null(0)
		getWord(cmd, userInput, 1);

		if (strcmp(cmd, "game_mode") == 0)  //Set game_mode
		{
			gameModeCmd(userInput);
		}
		else if (strcmp(cmd, "difficulty") == 0)  //Set Game difficulty
		{
			gameDifficultyCmd(userInput);
		}
		else if (strcmp(cmd, "user_color") == 0)  //Set User Color
		{
			gameUserColorCmd(userInput);
		}
		else if (strcmp(cmd, "next_player") == 0)  //Set The player which start the game
		{
			nextPlayerCmd(userInput);
		}
		else if (strcmp(cmd, "rm") == 0)  // Remove a piece from the board
		{
			removePieceCmd(userInput);
		}
		else if (strcmp(cmd, "set") == 0)  // Set a piece on the board                   ==============   Need to add a fuction for board validity
		{
			setPieceCmd(userInput);
		}
		else if (strcmp(cmd, "clear") == 0)  // Remove all pieces from the board
		{
			clearBoard(chess_board);
		}
		else if (strcmp(cmd, "print") == 0)  // Remove all pieces from the board
		{
			printBoard(chess_board);
		}
		else if (strcmp(cmd, "load") == 0)  // Remove all pieces from the board
		{
			loadGameCmd(userInput);
		}
		else if (strcmp(cmd, "start") == 0)  // Remove all pieces from the board
		{
			startGameCmd();
		}
		else if (strcmp(cmd, "quit") == 0)  // Remove all pieces from the board
		{
			quitGame();
		}
		else
		{
			printf(ILLEGAL_COMMAND);
		}

	}

	//getchar();
}

void quitGame()
{
	exit(0);
}

void executeComputerTurn()
{
	Move* move;
	move = tip(chess_board, gameDifficulty, next_player);

	if (move != NULL)
	{
		if (movePiece(chess_board, move->startPos->x - 'a', move->startPos->y - 1, move->endPos->x - 'a', move->endPos->y - 1, move->indicator) == 0)
		{
			if (next_player == WHITE)
				setNextPlayer(BLACK);
			else
				setNextPlayer(WHITE);
		}

		printf("Computer: move ");
		printMove(move);
		printBoard(chess_board);

		free_Move(move);

	}
	else
	{
		printf("executeComputerTurn() - Computer has no moves!\n");
		quitGame();
	}
}

void printGameStatus()
{

	if (isMate(chess_board, next_player))
	{
		printf("Mate! ");
		if (next_player == BLACK)
		{
			printf("White ");
		}
		else
		{
			printf("Black ");
		}

		printf("player wins the game\n");

		//getchar();  
		quitGame();
	}
	else if (thereIsCheck(chess_board, next_player))
	{
		printf("Check!\n");
	}
	else if (isTie(chess_board, next_player))
	{
		printf(TIE);
		//getchar();  
		quitGame();
	}

}

void startGameConsole()
{
	char userInput[MAX_INPUT_LENGTH];
	char cmd[MAX_INPUT_LENGTH];

	programState = GAME_STATE;

	printGameStatus(); //(TIE/Check/MATE)

	while (programState == GAME_STATE)
	{
		if (gameMode == PLAYER_VS_PLAYER_MODE)
		{
			printEnterMove(); //Prints "Enter moves..... "
		}
		else if (gameMode == PLAYER_VS_COMPUTER_MODE)
		{
			if (next_player != user_color) //Computer's Turn
			{
				executeComputerTurn(); //Execute computer turn
				printGameStatus(); //(TIE/Check/MATE)
			}

			printEnterMove(); //Prints "Enter moves..... "
		}

		fgets(userInput, MAX_INPUT_LENGTH, stdin);
		getWord(cmd, userInput, 1);

		if (strcmp(cmd, "print") == 0)
		{
			printBoard(chess_board);
		}
		else if (strcmp(cmd, "move") == 0)
		{
			movePieceCmd(userInput);
		}
		else if (strcmp(cmd, "get_moves") == 0)
		{
			getMovesCmd(userInput);
		}
		else if (strcmp(cmd, "get_best_moves") == 0)
		{
			getBestMovesCmd(userInput);
		}
		//else if (strcmp(cmd, "cast") == 0)  //For debugging: print current castling
		//{
		//	printCurrentCastling();
		//}
		else if (strcmp(cmd, "castle") == 0)
		{
			castleCmd(userInput);
		}
		else if (strcmp(cmd, "get_score") == 0)
		{
			getScoreCmd(userInput);
		}
		else if (strcmp(cmd, "save") == 0)
		{
			saveGameCmd(userInput);
		}
		else if (strcmp(cmd, "quit") == 0)
		{
			quitGame();
		}
		else
		{
			printf(ILLEGAL_COMMAND);
		}

	}

	//getchar(); //For debugging
}

void printEnterMove()
{
	if (next_player == WHITE)
	{
		printf("White ");
	}
	else
	{
		printf("Black ");
	}

	printf("player - enter your move:\n");
}

/*int runGUIMode()
{

}*/

void startGame_init()
{
	initCasteling();
}


