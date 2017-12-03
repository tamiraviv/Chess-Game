#ifndef CHESS_
#define CHESS_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

///////////////////////////////////////
#define MAIN_SCREEN 0
#define BOARD_SIZE 8
#define BLACK 'b'
#define WHITE 'w'
#define WRONG_DEPTH_ARGUMENTS "Wrong value for depth\n"
#define PLAYER_VS_PLAYER_MODE 1
#define PLAYER_VS_COMPUTER_MODE 2
#define MAX_INPUT_LENGTH 52
#define DIFFICULTY_DEFAULT 1
#define DIFFICULTY_BEST 5
#define SETTINGS_STATE 1
#define GAME_STATE 2

//Castling
extern int blackPieceWasMoved[3];
extern int whitePieceWasMoved[3];

#define KING 0
#define LEFT_ROOK 1
#define RIGHT_ROOK 2
#define YES 1
#define NO 0


extern char chess_board[BOARD_SIZE][BOARD_SIZE];
extern int programState;
extern char user_color;
extern int gameMode;
extern int gameDifficulty;
extern char next_player;

extern char cmd_arg_1[MAX_INPUT_LENGTH];
extern char cmd_arg_2[MAX_INPUT_LENGTH];
extern char cmd_arg_3[MAX_INPUT_LENGTH];
extern char cmd_arg_4[MAX_INPUT_LENGTH];

//Method decelerations//
void runConsoleMode();
int runGUIMode();
void printLine();
void printBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void init_board(char board[BOARD_SIZE][BOARD_SIZE]);
char *strcpy(char *dest, const char *src);
void getWord(char* dest, char* src, int wordNum);
char* getNextWord(char* word);
void setGameSettings();
int setGameMode(int gameModeInput);
void gameDifficultyCmd(char* userInput);
int setGameDifficulty(int difficultyInput);
int setGameDifficultyBest();
void gameModeCmd(char* userInput);
int setUserColor(char color);
void gameUserColorCmd(char* userInput);
void clearBoard(char board[BOARD_SIZE][BOARD_SIZE]);
void quitGame();
void removePieceCmd(char* userInput);
int removePiece(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);
void nextPlayerCmd(char* userInput);
int setNextPlayer(char color);
char pieceTypeToCharacter(char* pieceType);
void setPieceCmd(char* userInput);
int setPiece(char board[BOARD_SIZE][BOARD_SIZE], int x, int y, int pieceColor, char pieceType);
int isPieceTypeInRange(char pieceType);

void startGameCmd();
void startGameConsole();

//int isLegalBoard(char board[BOARD_SIZE][BOARD_SIZE]); //Delete
void processCurrentBoard();
void movePieceCmd(char* userInput);




//Main.c
void printEnterMove();
void printGameStatus();

//ParseUserInpuc.c
void getMovesCmd(char* userInput);
#define INVALID_POSITION_MESSAGE "The specified position does not contain your piece\n"
void getBestMovesCmd(char* userInput);
void startGame_init();
void loadGameCmd(char* userInput);
void saveGameCmd(char* userInput);
void getScoreCmd(char* userInput);
void castleCmd(char* userInput);
void setDefaultPromotion(int dst_y, char *pieceType);

//Services.c:
int isWithinBoardBorders(int x, int y);
void removeSpaces(char* src);
void copyBoard(char board[BOARD_SIZE][BOARD_SIZE], char new_board[BOARD_SIZE][BOARD_SIZE]);
int isLegalPiecePlacement(char board[BOARD_SIZE][BOARD_SIZE]);
int isLegalPiecePlacementPerPlayer(char board[BOARD_SIZE][BOARD_SIZE], int color);
int isBothKingsExist(char board[BOARD_SIZE][BOARD_SIZE]);
int isKingExist(char board[BOARD_SIZE][BOARD_SIZE], int color);
int isLegalMove(char board[BOARD_SIZE][BOARD_SIZE], int src_x, int src_y, int dst_x, int dst_y, char pieceType);
int isLegalCastle(char board[BOARD_SIZE][BOARD_SIZE], int src_x, int src_y);
void switchNextPlayerColor();

//Settings.c
#define INVALID_POSITION -2
#define NOT_YOUR_PIECE -3
#define IILEGAL_CASLTING_ERROR -4
#define INVALID_INITIALIZATION -5
#define IILEGAL_MOVE -6
#define WRONG_ROOK_POSITION_ERROR - 7

int movePiece(char board[BOARD_SIZE][BOARD_SIZE], int src_x, int src_y, int dst_x, int dst_y, char pieceType);
void initCasteling();
void initCastlePiece(int x, int y, char pieceType, int* isPieceWasMoved, int isPieceWasMovedType);
void printCurrentCastling();
void xml_loadCastling(char* fileContent, char* markupContent, char* markupName, int x, int y, char pieceType, int* isPieceWasMoved, int isPieceWasMovedType);
int getBestScore(char board[BOARD_SIZE][BOARD_SIZE], int difficultyInput, int src_x, int src_y, int dst_x, int dst_y, char pieceType);
int castle(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);

//console_services.c
void printBestMoves(int depth);
int printMoves(char board[BOARD_SIZE][BOARD_SIZE], int x, int y);


//xml.c
int xml_SaveGame(char* filePath);
int xml_LoadGame(char* filePath);
int xml_HandleRes(FILE* file, int res);

int getFileContent(char* filePath, char* buf);
int getMarkupContent(char* src, char* dst, char* markupName);

//Delete
//unitTests.c
void completeTest();

//Logic.c
/* Struct: Coordinates of a single position on the board */
typedef struct
{
	char x;
	int y;
} Pos;


/* Struct: A node in a linked list of Positions. The entire list represnts a turn of a player
indicator: promotion: 'q' = Queen, 'r' = Rook, 'b' = Bishop, 'n' = Knight.
special move: 'c' = casteling.

*/
typedef struct Move
{
	Pos* startPos;
	Pos* endPos;
	char indicator;
	struct Move *next;
}Move;

/* Struct: A node in a linked list of turns. The entire list represts all the possible moves a player can perform in a specific turn */
typedef struct Move_List
{
	Move* head;
}Move_List;



Move_List * createEmptyMoveList();
Pos* createNewPos(char x, int y);
Move * createNewMove(Pos* start, Pos* end);
Move * createNewMove2(Pos* start, Pos* end, char indicator);
int free_Move(Move *move);
int free_Move_List(Move_List *move_list);
void appendMoveToMoveList(Move_List * moves, Move * nodeToAppend);
void appendMoveToMoveList2(Move_List * moves, Move * nodeToAppend);
void executeMove(char board[BOARD_SIZE][BOARD_SIZE], Move *move, int *isTheKingMoves, int *isTheRightRookMoves, int *isTheLeftRookMoves);
int getScore(char board[BOARD_SIZE][BOARD_SIZE], char color);
int getScore2(char board[BOARD_SIZE][BOARD_SIZE], char color);
int equalMove(Move *move1, Move *move2);
int isInMoveList(Move_List* moves, Move *move);
int thereIsCheck(char board[BOARD_SIZE][BOARD_SIZE], char player_color);
int thereIsCheck2(char board[BOARD_SIZE][BOARD_SIZE], char player_color, int kingColum, int kingRow);
void casteling(Move_List* moves, char board[BOARD_SIZE][BOARD_SIZE], char playerColor, int isTheKingMoves, int isTheRightRookMoves, int isTheLeftRookMoves);
Move_List* getMoves(char board[BOARD_SIZE][BOARD_SIZE], char playerColor, int isTheKingMoves, int isTheRightRookMoves, int isTheLeftRookMoves);
Move* copyMove(Move* toCopy);
int getBestMove(char board[BOARD_SIZE][BOARD_SIZE], char color, Move_List **bestMoves, int originalMaxDepth, int maxDepth, int MinMax, int alpa, int beta, int* isTheWhiteKingMoves, int* isTheWhiteRightRookMoves, int* isTheWhiteLeftRookMoves, int* isTheBlackKingMoves, int* isTheBlackRightRookMoves, int* isTheBlackLeftRookMoves);
int getBestMove2(char board[BOARD_SIZE][BOARD_SIZE], char color, int* numOfCalls, Move_List **bestMoves, int originalMaxDepth, int maxDepth, int MinMax, int alpa, int beta, int* isTheWhiteKingMoves, int* isTheWhiteRightRookMoves, int* isTheWhiteLeftRookMoves, int* isTheBlackKingMoves, int* isTheBlackRightRookMoves, int* isTheBlackLeftRookMoves);
int isMate(char board[BOARD_SIZE][BOARD_SIZE], char player_color);
int isTie(char board[BOARD_SIZE][BOARD_SIZE], char player_color);
Move* tip(char board[BOARD_SIZE][BOARD_SIZE], int difficultyInput, char color);

void printMoveList(Move_List* moves);
void printPieceMoves(Move_List* moves, int x, int y);
void printMove(Move* move);
int correctPositionFormant(char* word);

///////////////////////////////////////


#define WHITE_P 'm'
#define WHITE_B 'b'
#define WHITE_N 'n'
#define WHITE_R 'r'
#define WHITE_Q 'q'
#define WHITE_K 'k'

#define BLACK_P 'M'
#define BLACK_B 'B'
#define BLACK_N 'N'
#define BLACK_R 'R'
#define BLACK_Q 'Q'
#define BLACK_K 'K'


#define EMPTY ' '

#define BOARD_SIZE 8

// board initialization
#define ENTER_SETTINGS "Enter game settings:\n" 
#define WRONG_GAME_MODE "Wrong game mode\n"
#define TWO_PLAYERS_GAME_MODE "Running game in 2 players mode\n"
#define PLAYER_VS_AI_GAME_MODE "Running game in player vs. AI mode\n"
#define WRONG_MINIMAX_DEPTH "Wrong value for minimax depth. The value should be between 1 to 4\n"
#define WRONG_FILE_NAME "Wrong file name\n"
#define WRONG_POSITION "Invalid position on the board\n"
#define NO_PIECE "Setting this piece creates an invalid board\n"  
#define WROND_BOARD_INITIALIZATION "Wrong board initialization\n"

#define ILLEGAL_COMMAND "Illegal command, please try again\n"
#define ILLEGAL_MOVE_MESSAGE "Illegal move\n"

#define WRONG_ROOK_POSITION "Wrong position for a rook\n" 
#define ILLEGAL_CALTLING_MOVE "Illegal castling move\n"  

#define TIE "The game ends in a tie\n"

#define perror_message(func_name) (perror("Error: standard function %s has failed", func_name));
#define print_message(message) (printf("%s", message));




#endif //CHESS_
