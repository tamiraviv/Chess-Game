#define _CRT_SECURE_NO_WARNINGS
#include "chess.h"
#define MAXBUFLEN 10000

//This function is slowing the compiler!
//So for now it's content is marked as a comment

int xml_SaveGame(char* filePath)
{
	FILE *file;
	//int res = 0; //Delete
	//int tabCounter = 0; //Counter for tab writing //Delete
	int i, j; // For "for loop"

	file = fopen(filePath, "w");

	//Failed to open file
	if (file == NULL)
	{
		return -1;
	}

	//Write XML Version markup
	if (xml_HandleRes(file, fprintf(file, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")) < -1) return -1;

	//Write Game
	if (xml_HandleRes(file, fprintf(file, "<game>\n")) < -1) return -1;

	//Write Next_Turn
	if (next_player == WHITE)
	{
		if (xml_HandleRes(file, fprintf(file, "\t<next_turn>White</next_turn>\n")) < -1) return -1;
	}
	else if (next_player == BLACK)
	{
		if (xml_HandleRes(file, fprintf(file, "\t<next_turn>Black</next_turn>\n")) < -1) return -1;
	}

	//Write Game_Mode
	if (xml_HandleRes(file, fprintf(file, "\t<game_mode>%d</game_mode>\n", gameMode)) < -1) return -1;


	//Write Difficutly
	if (gameDifficulty == DIFFICULTY_BEST)
	{
		if (xml_HandleRes(file, fprintf(file, "\t<difficulty>best</difficulty>\n")) < 0) return -1;
	}
	else
	{
		if (xml_HandleRes(file, fprintf(file, "\t<difficulty>%d</difficulty>\n", gameDifficulty)) < 0) return -1;
	}

	//Write User_Color
	if (user_color == WHITE)
	{
		if (xml_HandleRes(file, fprintf(file, "\t<user_color>White</user_color>\n")) < -1) return -1;
	}
	else if (user_color == BLACK)
	{
		if (xml_HandleRes(file, fprintf(file, "\t<user_color>Black</user_color>\n")) < -1) return -1;
	}

	//Write Open_Board
	if (xml_HandleRes(file, fprintf(file, "\t<board>\n")) < -1) return -1;

	for (i = BOARD_SIZE - 1; i >= 0; i--)
	{
		//Print ROW_MARKUP
		if (xml_HandleRes(file, fprintf(file, "\t\t<row_%d>", i + 1)) < -1) return -1;
		//Print ROW_Content
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (chess_board[j][i] == EMPTY)
			{
				if (xml_HandleRes(file, fprintf(file, "_")) < -1) return -1;
			}
			else
			{
				if (xml_HandleRes(file, fprintf(file, "%c", chess_board[j][i])) < -1) return -1;
			}
		}
		//Print ROW_MARKUP
		if (xml_HandleRes(file, fprintf(file, "</row_%d>\n", i + 1)) < -1) return -1;

	}

	//Write Close_Board
	if (xml_HandleRes(file, fprintf(file, "\t</board>\n")) < -1) return -1;

	//Write Open General
	if (xml_HandleRes(file, fprintf(file, "\t<general>\n")) < -1) return -1;

	//Write Castling
	if (xml_HandleRes(file, fprintf(file, "\t\t<white_king_moved>%d</white_king_moved>\n", whitePieceWasMoved[KING])) < -1) return -1;
	if (xml_HandleRes(file, fprintf(file, "\t\t<white_left_rook_moved>%d</white_left_rook_moved>\n", whitePieceWasMoved[LEFT_ROOK])) < -1) return -1;
	if (xml_HandleRes(file, fprintf(file, "\t\t<white_right_rook_moved>%d</white_right_rook_moved>\n", whitePieceWasMoved[RIGHT_ROOK])) < -1) return -1;

	if (xml_HandleRes(file, fprintf(file, "\t\t<black_king_moved>%d</black_king_moved>\n", blackPieceWasMoved[KING])) < -1) return -1;
	if (xml_HandleRes(file, fprintf(file, "\t\t<black_left_rook_moved>%d</black_left_rook_moved>\n", blackPieceWasMoved[LEFT_ROOK])) < -1) return -1;
	if (xml_HandleRes(file, fprintf(file, "\t\t<black_right_rook_moved>%d</black_right_rook_moved>\n", blackPieceWasMoved[RIGHT_ROOK])) < -1) return -1;

	//Write Close General
	if (xml_HandleRes(file, fprintf(file, "\t</general>\n")) < -1) return -1;


	//Write Close_Game
	if (xml_HandleRes(file, fprintf(file, "</game>\n")) < -1) return -1;


	fclose(file);
	return 0;

}

//In case res = -1 --> close the file and return -1
int xml_HandleRes(FILE* file, int res)
{
	if (res < 0)
	{
		fclose(file);
		return -1;
	}

	return 0;
}

int xml_LoadGame(char* filePath)
{
	char fileContent[MAXBUFLEN + 1];
	char markupContent[MAXBUFLEN + 1];
	char rowMarkup[6] = "row_ ";
	int i, j;

	if (getFileContent(filePath, fileContent) < 0) return -1;

	//Load Next_Turn
	getMarkupContent(fileContent, markupContent, "next_turn");

	if (strcmp(markupContent, "White") == 0) //TODO: should we igonre the case??
	{
		next_player = WHITE;
	}
	else if (strcmp(markupContent, "Black") == 0) //TODO: should we igonre the case??
	{
		next_player = BLACK;
	}

	//Load Game_Mode
	getMarkupContent(fileContent, markupContent, "game_mode");
	gameMode = (int)(*markupContent) - 48;

	//Load Difficulty
	getMarkupContent(fileContent, markupContent, "difficulty");
	if (*markupContent != '\0')
	{
		if (strcmp(markupContent, "best") == 0)  //TODO: should we igonre the case??
		{
			gameDifficulty = DIFFICULTY_BEST;
		}
		else
		{
			gameDifficulty = (int)(*markupContent) - 48;
		}
	}
	else
	{
		gameDifficulty = DIFFICULTY_DEFAULT;
	}

	//Load User_Color
	getMarkupContent(fileContent, markupContent, "user_color");
	if (*markupContent != '\0')
	{
		if (strcmp(markupContent, "White") == 0) //TODO: should we igonre the case??
		{
			user_color = WHITE;
		}
		else if (strcmp(markupContent, "Black") == 0) //TODO: should we igonre the case??
		{
			user_color = BLACK;
		}
	}
	else
	{//set Default user color:
		user_color = WHITE;
	}

	//Load Board
	for (i = BOARD_SIZE - 1; i >= 0; i--)
	{
		//Get Row content
		rowMarkup[4] = i + 49; //Set Row_Markup string
		getMarkupContent(fileContent, markupContent, rowMarkup);
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (markupContent[j] == '_')
			{
				chess_board[j][i] = EMPTY;
			}
			else
			{
				chess_board[j][i] = markupContent[j];
			}
		}
	}

	//Load Castling - White player
	xml_loadCastling(fileContent, markupContent, "white_king_moved", 3, 0, WHITE_K, whitePieceWasMoved, KING);
	xml_loadCastling(fileContent, markupContent, "white_left_rook_moved", 0, 0, WHITE_R, whitePieceWasMoved, LEFT_ROOK);
	xml_loadCastling(fileContent, markupContent, "white_right_rook_moved", 7, 0, WHITE_R, whitePieceWasMoved, RIGHT_ROOK);

	//Load Castling - Black player
	xml_loadCastling(fileContent, markupContent, "black_king_moved", 3, 7, BLACK_K, blackPieceWasMoved, KING);
	xml_loadCastling(fileContent, markupContent, "black_left_rook_moved", 0, 7, BLACK_R, blackPieceWasMoved, LEFT_ROOK);
	xml_loadCastling(fileContent, markupContent, "black_right_rook_moved", 7, 7, BLACK_R, blackPieceWasMoved, RIGHT_ROOK);

	//printCurrentCastling();

	return 0;

}

void xml_loadCastling(char* fileContent, char* markupContent, char* markupName, int x, int y, char pieceType, int* isPieceWasMoved, int isPieceWasMovedType)
{
	getMarkupContent(fileContent, markupContent, markupName);
	//removeSpaces(markupContent);

	if (*markupContent != '\0')
	{
		isPieceWasMoved[isPieceWasMovedType] = (int)(*markupContent) - 48;
	}
	else
	{   //set Default
		if (chess_board[x][y] == pieceType)
		{
			isPieceWasMoved[isPieceWasMovedType] = NO;
		}
		else
		{
			isPieceWasMoved[isPieceWasMovedType] = YES;
		}
	}
}

//Copy file content to buf
int getFileContent(char* filePath, char* buf)
{
	//Open file for reading
	size_t length;
	FILE *file = NULL;

	file = fopen(filePath, "r");

	//File Open failed
	if (file == NULL)
	{
		//No need to fclose, in case open has failed!!
		return -1;
	}

	//Read whole file content to buf
	length = fread(buf, sizeof(char), MAXBUFLEN, file);

	//Read has failed, close file
	if (length == 0)
	{
		fclose(file);
		return -1;
	}
	else
	{
		buf[++length] = '\0';
	}

	//close file
	fclose(file);

	return 0;
}

//get XML specific Markup content from src to dst
int getMarkupContent(char* src, char* dst, char* markupName)
{
	char *orgininalDst = dst;
	char *curPos = NULL;
	char *closeMarkupPos = NULL;


	//Get Markup value start_position
	curPos = strstr(src, markupName);

	//Markup wasn't found
	if (curPos == NULL)
	{
		*dst = '\0';
		return -1;
	}

	curPos += strlen(markupName) + 1;

	//Get Markup value end_position 
	closeMarkupPos = strstr(curPos, markupName);
	closeMarkupPos -= 2;


	//Copy markup content to dst
	while (curPos != closeMarkupPos && *curPos != '\0')
	{
		*dst = *curPos;
		dst++;
		curPos++;
	}

	*dst = '\0';

	removeSpaces(orgininalDst);

	return 0;
}