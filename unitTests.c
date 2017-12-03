#include "chess.h"
#include <assert.h>

void gameModeCmd_Test();
void gameDifficultyCmd_Test();
void gameUserColorCmd_Test();
void clearBoard_Test();
void nextPlayerCmd_Test();
void removePieceCmd_Test();
void setPieceCmd_Test();

void completeTest()
{
	gameModeCmd_Test();
	gameDifficultyCmd_Test();
	gameUserColorCmd_Test();
	clearBoard_Test();
	removePieceCmd_Test();
	setPieceCmd_Test();

	printf("\n\nTest was completed successfully!!\n");
	getchar();
}

void gameModeCmd_Test()
{
	assert(gameMode == 1); //Check Default value
	gameModeCmd("game_mode"); assert(gameMode == 1);
	gameModeCmd("game_mode  "); assert(gameMode == 1);
	gameModeCmd("game_mode  1"); assert(gameMode == 1);
	gameModeCmd("game_mode  2"); assert(gameMode == 2);
	gameModeCmd("game_mode  "); assert(gameMode == 2);
	gameModeCmd("game_mode  1  "); assert(gameMode == 1);
}

void gameDifficultyCmd_Test()
{
	gameModeCmd("game_mode 2");
	assert(gameDifficulty == 1); //Default value
	gameDifficultyCmd("difficulty best "); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty depth 1"); assert(gameDifficulty == 1);
	gameDifficultyCmd("difficulty depth 2"); assert(gameDifficulty == 2);
	gameDifficultyCmd("difficulty depth 3"); assert(gameDifficulty == 3);
	gameDifficultyCmd("difficulty depth 4"); assert(gameDifficulty == 4);
	gameDifficultyCmd("difficulty depth 5"); assert(gameDifficulty == 4);
	gameDifficultyCmd("difficulty  best  "); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty  depth 0  "); assert(gameDifficulty == 5);

	gameModeCmd("game_mode 1");
	gameDifficultyCmd("difficulty depth 3"); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty depth 2"); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty depth 1"); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty depth 0"); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty depth 5"); assert(gameDifficulty == 5);
	gameDifficultyCmd("difficulty best"); assert(gameDifficulty == 5);




}

void gameUserColorCmd_Test()
{
	gameModeCmd("game_mode 2");
	assert(user_color == WHITE); // Check default
	gameUserColorCmd("user_color white"); assert(user_color == WHITE);
	gameUserColorCmd("user_color black"); assert(user_color == BLACK);
	gameUserColorCmd("user_color  white   "); assert(user_color == WHITE);
	gameUserColorCmd("user_color  black111   "); assert(user_color == WHITE);
	gameUserColorCmd("user_color  black   "); assert(user_color == BLACK);
	gameUserColorCmd("user_color  whitea"); assert(user_color == BLACK);

	gameModeCmd("game_mode 1");
	gameUserColorCmd("user_color white"); assert(user_color == BLACK);

}

void clearBoard_Test()
{
	int i = 0, j = 0;

	//Fill board
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			chess_board[i][j] = 'a';
		}
	}

	//Verify Filled
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			assert(chess_board[i][j] != EMPTY);
		}
	}

	//Clear
	clearBoard(chess_board);

	//Verify cleared
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			assert(chess_board[i][j] == EMPTY);
		}
	}

	init_board(chess_board);


}

void nextPlayerCmd_Test()
{
	assert(next_player == WHITE); //Verify default
	nextPlayerCmd("next_player white"); assert(next_player == WHITE);
	nextPlayerCmd("next_player black"); assert(next_player == BLACK);
	nextPlayerCmd("next_player white1"); assert(next_player == BLACK);
	nextPlayerCmd("next_player white"); assert(next_player == WHITE);
	nextPlayerCmd("next_player white1"); assert(next_player == WHITE);
}

void removePieceCmd_Test()
{
	int i = 0, j = 0;
	char str[9] = "rm <a,1>";

	//Fill board
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			chess_board[i][j] = 'a';
		}
	}


	//Clear and verify
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			str[4] = i + 'a';
			str[6] = j + '1';
			assert(chess_board[i][j] != EMPTY);
			removePieceCmd(str);
			assert(chess_board[i][j] == EMPTY);
		}
	}

	init_board(chess_board);
}

//Currently in comment!!!!!!!!!!!!!!!!!!!!!!!! faster build time
void setPieceCmd_Test()
{
	int i = 0, j = 0;
	clearBoard(chess_board);

	//Verify cleared
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			assert(chess_board[i][j] == EMPTY);
		}
	}

	//setPieceCmd("set <a,1> white rook"); assert(chess_board[0][0] == 'r');
	//setPieceCmd("set <h,1> white rook"); assert(chess_board[7][0] == 'r');
	//setPieceCmd("set <b,1> white rook"); assert(chess_board[1][0] == EMPTY);

	//setPieceCmd("set <a,8> black rook"); assert(chess_board[0][7] == 'R');
	//setPieceCmd("set <h,8> black rook"); assert(chess_board[7][7] == 'R');
	//setPieceCmd("set <b,8> black rook"); assert(chess_board[1][7] == EMPTY);

	//setPieceCmd("set <b,1> white knight"); assert(chess_board[1][0] == 'n');
	//setPieceCmd("set <g,1> white knight"); assert(chess_board[6][0] == 'n');
	//setPieceCmd("set <c,1> white knight"); assert(chess_board[2][0] == EMPTY);

	//setPieceCmd("set <b,8> black knight"); assert(chess_board[1][7] == 'N');
	//setPieceCmd("set <g,8> black knight"); assert(chess_board[6][7] == 'N');
	//setPieceCmd("set <c,8> black knight"); assert(chess_board[2][7] == EMPTY);

	//setPieceCmd("set <d,1> white king"); assert(chess_board[3][0] == 'k');
	//setPieceCmd("set <a,3> white king"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <d,8> black king"); assert(chess_board[3][7] == 'K');
	//setPieceCmd("set <a,3> black king"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <e,1> white queen"); assert(chess_board[4][0] == 'q');
	//setPieceCmd("set <a,3> white queen"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <e,8> black queen"); assert(chess_board[4][7] == 'Q');
	//setPieceCmd("set <a,3> black queen"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <c,1> white bishop"); assert(chess_board[2][0] == 'b');
	//setPieceCmd("set <f,1> white bishop"); assert(chess_board[5][0] == 'b');
	//setPieceCmd("set <a,3> white bishop"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <c,8> black bishop"); assert(chess_board[2][7] == 'B');
	//setPieceCmd("set <f,8> black bishop"); assert(chess_board[5][7] == 'B');
	//setPieceCmd("set <a,3> black bishop"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <a,2> white pawn"); assert(chess_board[0][1] == 'm');
	//setPieceCmd("set <b,2> white pawn"); assert(chess_board[1][1] == 'm');
	//setPieceCmd("set <c,2> white pawn"); assert(chess_board[2][1] == 'm');
	//setPieceCmd("set <d,2> white pawn"); assert(chess_board[3][1] == 'm');
	//setPieceCmd("set <e,2> white pawn"); assert(chess_board[4][1] == 'm');
	//setPieceCmd("set <f,2> white pawn"); assert(chess_board[5][1] == 'm');
	//setPieceCmd("set <g,2> white pawn"); assert(chess_board[6][1] == 'm');
	//setPieceCmd("set <h,2> white pawn"); assert(chess_board[7][1] == 'm');
	//setPieceCmd("set <a,3> white pawn"); assert(chess_board[0][2] == EMPTY);

	//setPieceCmd("set <a,7> black pawn"); assert(chess_board[0][6] == 'M');
	//setPieceCmd("set <b,7> black pawn"); assert(chess_board[1][6] == 'M');
	//setPieceCmd("set <c,7> black pawn"); assert(chess_board[2][6] == 'M');
	//setPieceCmd("set <d,7> black pawn"); assert(chess_board[3][6] == 'M');
	//setPieceCmd("set <e,7> black pawn"); assert(chess_board[4][6] == 'M');
	//setPieceCmd("set <f,7> black pawn"); assert(chess_board[5][6] == 'M');
	//setPieceCmd("set <g,7> black pawn"); assert(chess_board[6][6] == 'M');
	//setPieceCmd("set <h,7> black pawn"); assert(chess_board[7][6] == 'M');
	//setPieceCmd("set <a,3> black pawn"); assert(chess_board[0][2] == EMPTY);

	clearBoard(chess_board);
	init_board(chess_board);
	printBoard(chess_board);
}

