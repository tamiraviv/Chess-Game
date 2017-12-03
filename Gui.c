#include <SDL.h>
#include <SDL_video.h>
#include "chess.h"

#define WIN_W 406
#define WIN_H 500
#define SLOTS 7

int x; int y; int i = 31; int k = 31; int j = 31; int squareWidth = 43; int squareHeight = 43; int counterX = -1; int counterY = -1; int pvp = 0; int loaded = 0; char typeOfPiece = 0;
int squareX = -1; int squareY = -1;	int counterZ = -1; int counterW = -1; int squareZ = -1; int squareW = -1; int pieceX = 0; int slotsDistance = 56; char pieceToSet; char colorToSet = 'w';
int pieceY = 0;	int l = 432; int pieceWidth = 34; int pieceHeight = 32;	int cancel = 0;	int startingPoint = 35;	double difference = 43.3; int setMode = 0; int difficultyInput = 0; int delay = 0;
char temp_chess_board[BOARD_SIZE][BOARD_SIZE];

char path[10] = "Slot0.xml";

SDL_Rect imgrect = { 0, 0, WIN_W, WIN_H };
SDL_Rect rectWhite = { 85, 238, 15, 15 };
SDL_Rect rectBlack = { 218, 238, 15, 15 };
SDL_Rect rect1 = { 85, 70, 15, 15 };
SDL_Rect rect2 = { 153, 70, 15, 15 };
SDL_Rect rect3 = { 218, 70, 15, 15 };
SDL_Rect rect4 = { 280, 70, 15, 15 };
SDL_Rect rectBest = { 85, 148, 15, 15 };

SDL_Rect rectG1 = { 291, 440, 5, 5 };
SDL_Rect rectG2 = { 318, 440, 5, 5 };
SDL_Rect rectG3 = { 345, 440, 5, 5 };
SDL_Rect rectG4 = { 372, 440, 5, 5 };
SDL_Rect rectGBest = { 291, 474, 5, 5 };

SDL_Rect rectPr = { 138, 453, 15, 15 };

SDL_Rect rectTemp;
SDL_Rect rectTie = { 6, 435, 10, 10 };
SDL_Rect rectCheck = { 6, 458, 10, 10 };
SDL_Rect rectMate = { 6, 480, 10, 10 };
SDL_Event e;
SDL_Event ev;

int fillRectSDL(SDL_Surface *mainMenu, SDL_Surface *win);
int setColorKeySDL(SDL_Surface *piece);
int BlitSDL2(SDL_Surface *piece, SDL_Surface *win);
int BlitSDL(SDL_Surface *mainMenu, SDL_Surface *win);
int FlipSdl(SDL_Surface *mainMenu, SDL_Surface *win);
int scanBoard(char board[BOARD_SIZE][BOARD_SIZE], SDL_Surface *mainMenu, SDL_Surface *win, SDL_Surface *pieceBishopBlack, SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite,
	SDL_Surface *pieceKnightBlack, SDL_Surface *pieceKnightWhite, SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack,
	SDL_Surface *pieceQueenWhite, SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite, SDL_Surface *darkSquare, SDL_Surface *lightSquare);
void SDL_FreeSurfaces(SDL_Surface *mainMenu, SDL_Surface *playersSelection, SDL_Surface *AISettings, SDL_Surface *gameWindow, SDL_Surface *setBoard, SDL_Surface *pieceBishopBlack,
	SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite, SDL_Surface *pieceKnightBlack, SDL_Surface *pieceKnightWhite,
	SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack, SDL_Surface *pieceQueenWhite, SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite);
int basicGameMode(SDL_Surface *mainMenu, SDL_Surface *win, SDL_Surface *gameWindow, SDL_Surface *loadSave, SDL_Surface *playersSelection, SDL_Surface *AISettings, SDL_Surface *setBoard,
	SDL_Surface *gameWindowPvC, SDL_Surface *pieceBishopBlack, SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite, SDL_Surface *pieceKnightBlack,
	SDL_Surface *pieceKnightWhite, SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack, SDL_Surface *pieceQueenWhite,
	SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite, SDL_Surface *darkSquare, SDL_Surface *lightSquare, SDL_Surface *fileNotFound, SDL_Surface *redSquare);
int newGame(SDL_Surface *mainMenu, SDL_Surface *win, SDL_Surface *gameWindow, SDL_Surface *loadSave, SDL_Surface *playersSelection, SDL_Surface *AISettings, SDL_Surface *setBoard,
	SDL_Surface *gameWindowPvC, SDL_Surface *pieceBishopBlack, SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite, SDL_Surface *pieceKnightBlack,
	SDL_Surface *pieceKnightWhite, SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack, SDL_Surface *pieceQueenWhite,
	SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite, SDL_Surface *darkSquare, SDL_Surface *lightSquare, SDL_Surface *fileNotFound, SDL_Surface *redSquare);

int runGUIMode()
{

	SDL_Surface *pieceBishopBlack = SDL_LoadBMP("images/pieceBishopBlack1.bmp");
	SDL_Surface *pieceBishopWhite = SDL_LoadBMP("images/pieceBishopWhite1.bmp");
	SDL_Surface *pieceKingBlack = SDL_LoadBMP("images/pieceKingBlack1.bmp");
	SDL_Surface *pieceKingWhite = SDL_LoadBMP("images/pieceKingWhite1.bmp");
	SDL_Surface *pieceKnightBlack = SDL_LoadBMP("images/pieceKnightBlack1.bmp");
	SDL_Surface *pieceKnightWhite = SDL_LoadBMP("images/pieceKnightWhite1.bmp");
	SDL_Surface *piecePawnBlack = SDL_LoadBMP("images/piecePawnBlack1.bmp");
	SDL_Surface *piecePawnWhite = SDL_LoadBMP("images/piecePawnWhite1.bmp");
	SDL_Surface *pieceQueenBlack = SDL_LoadBMP("images/pieceQueenBlack1.bmp");
	SDL_Surface *pieceQueenWhite = SDL_LoadBMP("images/pieceQueenWhite1.bmp");
	SDL_Surface *pieceRookBlack = SDL_LoadBMP("images/pieceRookBlack1.bmp");
	SDL_Surface *pieceRookWhite = SDL_LoadBMP("images/pieceRookWhite1.bmp");

	SDL_Surface *darkSquare = SDL_LoadBMP("images/darkSquare1.bmp");
	SDL_Surface *lightSquare = SDL_LoadBMP("images/lightSquare1.bmp");
	SDL_Surface *redSquare = SDL_LoadBMP("images/redSquare.bmp");

	SDL_Surface* win = SDL_SetVideoMode(WIN_W, WIN_H, 0, SDL_SWSURFACE | SDL_NOFRAME);
	if (win == NULL) {
		fprintf(stderr, "ERROR: Couldn't set video mode: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface *mainMenu = SDL_LoadBMP("images/MainMenu.bmp");
	SDL_Surface *playersSelection = SDL_LoadBMP("images/PlayersSelection.bmp");
	SDL_Surface *AISettings = SDL_LoadBMP("images/AISettings.bmp");
	SDL_Surface *gameWindow = SDL_LoadBMP("images/gameWindow.bmp");
	SDL_Surface *gameWindowPvC = SDL_LoadBMP("images/gameWindowPvC.bmp");
	SDL_Surface *setBoard = SDL_LoadBMP("images/setBoard.bmp");
	SDL_Surface *loadSave = SDL_LoadBMP("images/loadSave.bmp");
	SDL_Surface *fileNotFound = SDL_LoadBMP("images/fileNotFound.bmp");

	rectTemp.w = WIN_W;
	rectTemp.h = WIN_H;

	if (mainMenu == NULL || playersSelection == NULL || AISettings == NULL || gameWindow == NULL || gameWindowPvC == NULL || setBoard == NULL
		|| pieceBishopBlack == NULL || pieceBishopWhite == NULL || pieceKingBlack == NULL || pieceKingWhite == NULL || pieceKnightBlack == NULL || pieceKnightWhite == NULL
		|| piecePawnBlack == NULL || piecePawnWhite == NULL || pieceQueenBlack == NULL || pieceQueenWhite == NULL || pieceRookBlack == NULL || pieceRookWhite == NULL){
		fprintf(stderr, "ERROR: Couldn't draw image: %s\n", SDL_GetError());
		return 1;
	}

	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "ERROR: Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	atexit(SDL_Quit);

	if (setColorKeySDL(pieceBishopBlack))
		return 1;
	if (setColorKeySDL(pieceBishopWhite))
		return 1;
	if (setColorKeySDL(pieceKingBlack))
		return 1;
	if (setColorKeySDL(pieceKingWhite))
		return 1;
	if (setColorKeySDL(pieceKnightBlack))
		return 1;
	if (setColorKeySDL(pieceKnightWhite))
		return 1;
	if (setColorKeySDL(piecePawnBlack))
		return 1;
	if (setColorKeySDL(piecePawnWhite))
		return 1;
	if (setColorKeySDL(pieceQueenBlack))
		return 1;
	if (setColorKeySDL(pieceQueenWhite))
		return 1;
	if (setColorKeySDL(pieceRookBlack))
		return 1;
	if (setColorKeySDL(pieceRookWhite))
		return 1;

	SDL_WM_SetCaption("SDL Test", "SDL Test");

	if (BlitSDL(mainMenu, win))
		return 1;
	if (FlipSdl(mainMenu, win))
		return 1;



	while (1){
		init_board(chess_board);
		SDL_PollEvent(&e);
		if (e.type == SDL_QUIT)
			break;
		if (e.type == SDL_MOUSEBUTTONDOWN){
			//If the left mouse button was pressed
			if (e.button.button == SDL_BUTTON_LEFT){
				//Get the mouse offsets
				x = e.button.x;
				y = e.button.y;
				init_board(chess_board);
				//If the mouse is over New game
				if ((x > 80) && (x < 342) && (y > 142) && (y < 195)){
					setUserColor(WHITE);
					setNextPlayer(WHITE);
					setGameDifficulty(DIFFICULTY_DEFAULT);

					if (newGame(mainMenu, win, gameWindow, loadSave, playersSelection, AISettings, setBoard, gameWindowPvC, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack,
						pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare, fileNotFound, redSquare))
						return 1;

				}
				//If the mouse is over Load game
				else if ((x > 80) && (x < 342) && (y > 232) && (y < 283)){
					if (fillRectSDL(mainMenu, win))
						return 1;
					SDL_Delay(120);
					if (BlitSDL(loadSave, win))
						return 1;
					if (FlipSdl(mainMenu, win))
						return 1;

					while (1){
						loaded = 0;
						SDL_PollEvent(&ev);
						if (ev.type == SDL_QUIT)
							break;
						if (ev.type == SDL_MOUSEBUTTONDOWN){
							if (ev.button.button == SDL_BUTTON_LEFT){
								x = ev.button.x;
								y = ev.button.y;

								//If the mouse is over cancel
								if ((x > 81) && (x < 341) && (y > 432) && (y < 481)){
									if (fillRectSDL(mainMenu, win))
										return 1;
									SDL_Delay(120);
									if (BlitSDL(mainMenu, win))
										return 1;
									if (FlipSdl(mainMenu, win))
										return 1;
									break;
								}

								counterX = 27;
								counterY = 72;
								path[4] = 0;
								//if moust is over slots
								for (i = 0; i < SLOTS; i++){
									if ((x > 81) && (x < 341) && (y > counterX) && (y < counterY)){
										path[4] = 'a' + i;
										if (xml_LoadGame(path) != -1){
											loaded = 1;

											if (newGame(mainMenu, win, gameWindow, loadSave, playersSelection, AISettings, setBoard, gameWindowPvC, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack,
												pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare, fileNotFound, redSquare))
												return 1;

											break;
										}
										else {
											rectTemp.x = 81 + 5;
											rectTemp.y = counterX + 5;
											if (BlitSDL2(fileNotFound, win))
												return 1;
											if (FlipSdl(mainMenu, win))
												return 1;
										}
									}
									counterX += slotsDistance;
									counterY += slotsDistance;
								}
								if (loaded)
									break;
							}
						}
					}

				}


				//If the mouse is over quit
				else if ((x > 80) && (x < 342) && (y > 323) && (y < 375)){
					break;
				}
				//SDL_Delay(120);
			}
		}

	}

	SDL_FreeSurfaces(mainMenu, playersSelection, AISettings, gameWindow, setBoard, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite,
		pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite);
	quitGame();

	return 0;
}



void SDL_FreeSurfaces(SDL_Surface *mainMenu, SDL_Surface *playersSelection, SDL_Surface *AISettings, SDL_Surface *gameWindow, SDL_Surface *setBoard, SDL_Surface *pieceBishopBlack,
	SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite, SDL_Surface *pieceKnightBlack, SDL_Surface *pieceKnightWhite,
	SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack, SDL_Surface *pieceQueenWhite, SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite) {
	SDL_FreeSurface(mainMenu);
	SDL_FreeSurface(playersSelection);
	SDL_FreeSurface(AISettings);
	SDL_FreeSurface(gameWindow);
	SDL_FreeSurface(setBoard);
	SDL_FreeSurface(pieceBishopBlack);
	SDL_FreeSurface(pieceBishopWhite);
	SDL_FreeSurface(pieceKingBlack);
	SDL_FreeSurface(pieceKingWhite);
	SDL_FreeSurface(pieceKnightBlack);
	SDL_FreeSurface(pieceKnightWhite);
	SDL_FreeSurface(piecePawnBlack);
	SDL_FreeSurface(piecePawnWhite);
	SDL_FreeSurface(pieceQueenBlack);
	SDL_FreeSurface(pieceQueenWhite);
	SDL_FreeSurface(pieceRookBlack);
	SDL_FreeSurface(pieceRookWhite);
}


int scanBoard(char board[BOARD_SIZE][BOARD_SIZE], SDL_Surface *mainMenu, SDL_Surface *win, SDL_Surface *pieceBishopBlack, SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite,
	SDL_Surface *pieceKnightBlack, SDL_Surface *pieceKnightWhite, SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack,
	SDL_Surface *pieceQueenWhite, SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite, SDL_Surface *darkSquare, SDL_Surface *lightSquare) {

	//draw empty squares
	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			rectTemp.x = startingPoint + difference * i;
			rectTemp.y = startingPoint + difference * (BOARD_SIZE - 1 - j);

			if ((i + j) % 2 == 0){
				if (BlitSDL2(darkSquare, win))
					return 1;
			}
			else
				if (BlitSDL2(lightSquare, win))
					return 1;
		}
	}

	for (i = 0; i < BOARD_SIZE; i++){
		for (j = 0; j < BOARD_SIZE; j++){
			rectTemp.x = startingPoint + difference * i;
			rectTemp.y = startingPoint + difference * (BOARD_SIZE - 1 - j);
			if (board[i][j] != EMPTY){
				if (board[i][j] == WHITE_K){
					if (BlitSDL2(pieceKingWhite, win))
						return 1;
				}
				else if (board[i][j] == WHITE_Q){
					if (BlitSDL2(pieceQueenWhite, win))
						return 1;
				}
				else if (board[i][j] == WHITE_B){
					if (BlitSDL2(pieceBishopWhite, win))
						return 1;
				}
				else if (board[i][j] == WHITE_N){
					if (BlitSDL2(pieceKnightWhite, win))
						return 1;
				}
				else if (board[i][j] == WHITE_R){
					if (BlitSDL2(pieceRookWhite, win))
						return 1;
				}
				else if (board[i][j] == WHITE_P){
					if (BlitSDL2(piecePawnWhite, win))
						return 1;
				}
				else if (board[i][j] == BLACK_K){
					if (BlitSDL2(pieceKingBlack, win))
						return 1;
				}
				else if (board[i][j] == BLACK_Q){
					if (BlitSDL2(pieceQueenBlack, win))
						return 1;
				}
				else if (board[i][j] == BLACK_B){
					if (BlitSDL2(pieceBishopBlack, win))
						return 1;
				}
				else if (board[i][j] == BLACK_N){
					if (BlitSDL2(pieceKnightBlack, win))
						return 1;
				}
				else if (board[i][j] == BLACK_R){
					if (BlitSDL2(pieceRookBlack, win))
						return 1;
				}
				else if (board[i][j] == BLACK_P){
					if (BlitSDL2(piecePawnBlack, win))
						return 1;
				}
			}
			else {//draw empty square
				if ((i + j) % 2 == 0){
					if (BlitSDL2(darkSquare, win))
						return 1;
				}
				else
					if (BlitSDL2(lightSquare, win))
						return 1;
			}
		}
	}
	//over tie, check, mate
	if (!setMode){
		SDL_Delay(120);
		if (SDL_FillRect(win, &rectTie, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
			printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
			SDL_FreeSurface(mainMenu);
			return 1;
		}
		if (SDL_FillRect(win, &rectCheck, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
			printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
			SDL_FreeSurface(mainMenu);
			return 1;
		}
		if (SDL_FillRect(win, &rectMate, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
			printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
			SDL_FreeSurface(mainMenu);
			return 1;
		}
		if (FlipSdl(mainMenu, win))
			return 1;

		if (isTie(board, next_player)){
			if (SDL_FillRect(win, &rectTie, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (SDL_FillRect(win, &rectCheck, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (SDL_FillRect(win, &rectMate, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (FlipSdl(mainMenu, win))
				return 1;
		}
		if (thereIsCheck(board, next_player)){
			if (SDL_FillRect(win, &rectTie, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (SDL_FillRect(win, &rectCheck, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (SDL_FillRect(win, &rectMate, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (FlipSdl(mainMenu, win))
				return 1;
		}
		if (isMate(board, next_player))
		{
			if (SDL_FillRect(win, &rectTie, SDL_MapRGB(win->format, 255, 255, 255)) != 0)
			{
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (SDL_FillRect(win, &rectCheck, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (SDL_FillRect(win, &rectMate, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
				printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
				SDL_FreeSurface(mainMenu);
				return 1;
			}
			if (FlipSdl(mainMenu, win))
				return 1;
		}
	}
	if (FlipSdl(mainMenu, win))
		return 1;
	return 0;
}

int FlipSdl(SDL_Surface *mainMenu, SDL_Surface *win){
	if (SDL_Flip(win) != 0){
		printf("ERROR: failed to flip buffer: %s\n", SDL_GetError());
		SDL_FreeSurface(mainMenu);
		return 1;
	}
	return 0;
}

int BlitSDL2(SDL_Surface *piece, SDL_Surface *win){
	if (SDL_BlitSurface(piece, NULL, win, &rectTemp) < 0) {
		fprintf(stderr, "ERROR: failed to blit image: %s\n", SDL_GetError());
		SDL_FreeSurface(piece);
		return 1;
	}
	return 0;
}

int BlitSDL(SDL_Surface *mainMenu, SDL_Surface *win){
	if (SDL_BlitSurface(mainMenu, &imgrect, win, 0) < 0) {
		fprintf(stderr, "ERROR: failed to blit image: %s\n", SDL_GetError());
		SDL_FreeSurface(mainMenu);
		return 1;
	}
	return 0;
}

int setColorKeySDL(SDL_Surface *piece){
	if (SDL_SetColorKey(piece, SDL_SRCCOLORKEY, SDL_MapRGB(piece->format, 255, 0, 255)) != 0) {
		printf("ERROR: failed to set color key: %s\n", SDL_GetError());
		SDL_FreeSurface(piece);
		return 1;
	}
	return 0;
}

int fillRectSDL(SDL_Surface *mainMenu, SDL_Surface *win){
	if (SDL_FillRect(win, 0, 0) != 0){
		printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
		SDL_FreeSurface(mainMenu);
		return 1;
	}
	return 0;
}

int basicGameMode(SDL_Surface *mainMenu, SDL_Surface *win, SDL_Surface *gameWindow, SDL_Surface *loadSave, SDL_Surface *playersSelection, SDL_Surface *AISettings, SDL_Surface *setBoard,
	SDL_Surface *gameWindowPvC, SDL_Surface *pieceBishopBlack, SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite, SDL_Surface *pieceKnightBlack,
	SDL_Surface *pieceKnightWhite, SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack, SDL_Surface *pieceQueenWhite,
	SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite, SDL_Surface *darkSquare, SDL_Surface *lightSquare, SDL_Surface *fileNotFound, SDL_Surface *redSquare){

	if (fillRectSDL(mainMenu, win))
		return 1;
	SDL_Delay(120);
	if (pvp){
		if (BlitSDL(gameWindow, win))
			return 1;
	}
	else
		if (BlitSDL(gameWindowPvC, win))
			return 1;
	if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
		pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
		return 1;


	if (!pvp && user_color != next_player)
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
				if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
					pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
				{
					free_Move(move);
					return 1;
				}
			}
			free_Move(move);

		}

	}

	while (1)
	{
		delay = 0;
		cancel = 0;
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
			break;
		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				x = ev.button.x;
				y = ev.button.y;

				//If the mouse is over save game
				if ((x > 1) && (x < 132) && (y > 405) && (y < 430))
				{
					if (fillRectSDL(mainMenu, win))
						return 1;
					if (BlitSDL(loadSave, win))
						return 1;
					if (FlipSdl(mainMenu, win))
						return 1;

					while (1){
						SDL_PollEvent(&ev);
						if (ev.type == SDL_QUIT)
							break;
						if (ev.type == SDL_MOUSEBUTTONDOWN){
							if (ev.button.button == SDL_BUTTON_LEFT){
								x = ev.button.x;
								y = ev.button.y;

								//If the mouse is over cancel
								if ((x > 81) && (x < 341) && (y > 432) && (y < 481)){
									if (fillRectSDL(mainMenu, win))
										return 1;
									SDL_Delay(120);
									if (pvp){
										if (BlitSDL(gameWindow, win))
											return 1;
									}
									else {
										if (BlitSDL(gameWindowPvC, win))
											return 1;
									}
									if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
										pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
										return 1;
									break;
								}
								counterX = 27;
								counterY = 72;
								path[4] = 0;
								for (i = 0; i < SLOTS; i++){
									if ((x > 81) && (x < 341) && (y > counterX) && (y < counterY)){
										//set save
										path[4] = 'a' + i;
										if (xml_SaveGame(path) != -1){
											if (fillRectSDL(mainMenu, win))
												return 1;
											SDL_Delay(120);
											if (pvp){
												if (BlitSDL(gameWindow, win))
													return 1;
											}
											else {
												if (BlitSDL(gameWindowPvC, win))
													return 1;
											}
											if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
												pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
												return 1;
											break;
										}
										else {
											rectTemp.x = 81 + 5;
											rectTemp.y = counterX + 5;
											if (BlitSDL2(fileNotFound, win))
												return 1;
											if (FlipSdl(mainMenu, win))
												return 1;
										}
										break;
									}
									counterX += slotsDistance;
									counterY += slotsDistance;
								}
								break;
							}
						}
					}
				}
				else
				{
					i = j = k = 31;
					counterX = counterY = squareX = squareY = -1;
					//if mouse is over board
					while (j < (k + BOARD_SIZE * squareHeight)){
						counterY++;
						while (i < (k + BOARD_SIZE * squareWidth)) {
							counterX++;
							if ((x > i) && (x < i + squareWidth) && (y > j) && (y < j + squareHeight)){
								squareX = counterX;
								squareY = counterY;
							}
							i += squareWidth;
						}
						counterX = -1;
						i = k;
						j += squareHeight;
					}
					if (squareX > -1 && 
						!(chess_board[squareX][(BOARD_SIZE - 1 - squareY)] == EMPTY || (next_player == WHITE && isupper(chess_board[squareX][(BOARD_SIZE - 1 - squareY)])) 
							|| (next_player == BLACK && islower(chess_board[squareX][(BOARD_SIZE - 1 - squareY)]))))
					{
						SDL_Delay(120);
						while (1){
							SDL_PollEvent(&ev);
							if (ev.type == SDL_QUIT)
								break;
							if (ev.type == SDL_MOUSEBUTTONDOWN){
								if (ev.button.button == SDL_BUTTON_LEFT){
									x = ev.button.x;
									y = ev.button.y;

									i = j = k = 31;
									counterZ = counterW = squareZ = squareW = -1;
									//if mouse is over board
									while (j < (k + BOARD_SIZE * squareHeight)){
										counterW++;
										while (i < (k + BOARD_SIZE * squareWidth)) {
											counterZ++;
											if ((x > i) && (x < i + squareWidth) && (y > j) && (y < j + squareHeight)){
												squareZ = counterZ;
												squareW = counterW;
											}
											i += squareWidth;
										}
										counterZ = -1;
										i = k;
										j += squareHeight;
									}
									if (squareZ > -1)
									{
										typeOfPiece = 0;

										//if legal promotion move
										if ((next_player == WHITE && chess_board[squareX][(BOARD_SIZE - 1 - squareY)] == WHITE_P && (BOARD_SIZE - 1 - squareW) == 7) || (next_player == BLACK &&chess_board[squareX][(BOARD_SIZE - 1 - squareY)] == BLACK_P && ((BOARD_SIZE - 1 - squareW) == 0)))
										{
											if (isLegalMove(chess_board, squareX, (BOARD_SIZE - 1 - squareY), squareZ, (BOARD_SIZE - 1 - squareW), 'q'))
											{

												SDL_Delay(120);
												if (SDL_FillRect(win, &rectPr, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
													printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
													SDL_FreeSurface(mainMenu);
													return 1;
												}
												if (FlipSdl(mainMenu, win))
													return 1;

												//SDL_Delay(120);
												while (1)
												{
													SDL_PollEvent(&ev);
													if (ev.type == SDL_QUIT)
														break;
													if (ev.type == SDL_MOUSEBUTTONDOWN){
														if (ev.button.button == SDL_BUTTON_LEFT){
															x = ev.button.x;
															y = ev.button.y;

															if ((BOARD_SIZE - 1 - squareW) == 0){
																//If the mouse is over queen
																if ((x > 163) && (x < 183) && (y > 455) && (y < 474)){
																	typeOfPiece = BLACK_Q;
																	break;
																}
																//If the mouse is over bishop
																if ((x > 186) && (x < 206) && (y > 455) && (y < 474)){
																	typeOfPiece = BLACK_B;
																	break;
																}
																//If the mouse is over knight
																if ((x > 163) && (x < 183) && (y > 475) && (y < 493)){
																	typeOfPiece = BLACK_N;
																	break;
																}
																//If the mouse is over rook
																if ((x > 186) && (x < 206) && (y > 475) && (y < 493)){
																	typeOfPiece = BLACK_R;
																	break;
																}
															}
															else if ((BOARD_SIZE - 1 - squareW) == 7){
																//If the mouse is over queen
																if ((x > 163) && (x < 183) && (y > 455) && (y < 474)){
																	typeOfPiece = WHITE_Q;
																	break;
																}
																//If the mouse is over bishop
																if ((x > 186) && (x < 206) && (y > 455) && (y < 474)){
																	typeOfPiece = WHITE_B;
																	break;
																}
																//If the mouse is over knight
																if ((x > 163) && (x < 183) && (y > 475) && (y < 493)){
																	typeOfPiece = WHITE_N;
																	break;
																}
																//If the mouse is over rook
																if ((x > 186) && (x < 206) && (y > 475) && (y < 493)){
																	typeOfPiece = WHITE_R;
																	break;
																}
															}
															//If the mouse is over quit
															else if ((x > 270) && (x < 405) && (y > 405) && (y < 430)){
																SDL_FreeSurfaces(mainMenu, playersSelection, AISettings, gameWindow, setBoard, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite,
																	pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite);
																quitGame();
																return 0;
															}
														}
													}
												}
											}
										}

										if (SDL_FillRect(win, &rectPr, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (FlipSdl(mainMenu, win))
											return 1;

										if (movePiece(chess_board, squareX, (BOARD_SIZE - 1 - squareY), squareZ, (BOARD_SIZE - 1 - squareW), typeOfPiece) == 0)
										{
											if (next_player == WHITE)
												setNextPlayer(BLACK);
											else
												setNextPlayer(WHITE);
											if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
												pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
												return 1;

											if (!pvp)
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
														if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
															pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
														{
															free_Move(move);
															return 1;
														}
													}
													free_Move(move);

												}

											}
										}
										else 
											delay = 1;
										break;
									}

									//If the mouse is over save game
									if ((x > 1) && (x < 132) && (y > 405) && (y < 430))
									{
										if (fillRectSDL(mainMenu, win))
											return 1;
										if (BlitSDL(loadSave, win))
											return 1;
										if (FlipSdl(mainMenu, win))
											return 1;

										while (1){
											SDL_PollEvent(&ev);
											if (ev.type == SDL_QUIT)
												break;
											if (ev.type == SDL_MOUSEBUTTONDOWN){
												if (ev.button.button == SDL_BUTTON_LEFT){
													x = ev.button.x;
													y = ev.button.y;

													//If the mouse is over cancel
													if ((x > 81) && (x < 341) && (y > 432) && (y < 481)){
														if (fillRectSDL(mainMenu, win))
															return 1;
														SDL_Delay(120);
														if (pvp){
															if (BlitSDL(gameWindow, win))
																return 1;
														}
														else {
															if (BlitSDL(gameWindowPvC, win))
																return 1;
														}
														if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
															pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
															return 1;
														break;
													}
													counterX = 27;
													counterY = 72;
													path[4] = 0;
													for (i = 0; i < SLOTS; i++){
														if ((x > 81) && (x < 341) && (y > counterX) && (y < counterY)){
															//set save
															path[4] = 'a' + i;
															if (xml_SaveGame(path) != -1){
																if (fillRectSDL(mainMenu, win))
																	return 1;
																SDL_Delay(120);
																if (pvp){
																	if (BlitSDL(gameWindow, win))
																		return 1;
																}
																else {
																	if (BlitSDL(gameWindowPvC, win))
																		return 1;
																}
																if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
																	pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
																	return 1;
																break;
															}
															else {
																rectTemp.x = 81 + 5;
																rectTemp.y = counterX + 5;
																if (BlitSDL2(fileNotFound, win))
																	return 1;
																if (FlipSdl(mainMenu, win))
																	return 1;
															}
															break;
														}
														counterX += slotsDistance;
														counterY += slotsDistance;
													}
													break;
												}
											}
										}
									}

									//If the mouse is over main menu
									if ((x > 133) && (x < 270) && (y > 405) && (y < 430)){
										cancel = 1;
										if (fillRectSDL(mainMenu, win))
											return 1;
										SDL_Delay(120);
										if (BlitSDL(mainMenu, win))
											return 1;
										if (FlipSdl(mainMenu, win))
											return 1;
										break;
									}
									//If the mouse is over quit
									else if ((x > 270) && (x < 405) && (y > 405) && (y < 430)){
										SDL_FreeSurfaces(mainMenu, playersSelection, AISettings, gameWindow, setBoard, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite,
											pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite);
										quitGame();
										return 0;
									}
								}
							}
						}
						if (cancel)
							break;
						if (delay)
							SDL_Delay(120);
					}


					//If the mouse is over main menu
					else if ((x > 133) && (x < 270) && (y > 405) && (y < 430)){
						if (fillRectSDL(mainMenu, win))
							return 1;
						SDL_Delay(120);
						if (BlitSDL(mainMenu, win))
							return 1;
						if (FlipSdl(mainMenu, win))
							return 1;
						break;
					}
					//If the mouse is over quit
					else if ((x > 270) && (x < 405) && (y > 405) && (y < 430)){
						SDL_FreeSurfaces(mainMenu, playersSelection, AISettings, gameWindow, setBoard, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite,
							pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite);
						quitGame();
						return 0;
					}
					if (pvp)
					{
						//If the mouse is over tip
						if ((x > 242) && (x < 281) && (y > 449) && (y < 476)){
							Move* move;
							move = tip(chess_board, difficultyInput, next_player);
							if (move != NULL)
							{
								//draw red line at src
								rectTemp.x = startingPoint + difference * (move->startPos->x - 'a');
								rectTemp.y = startingPoint + difference * (BOARD_SIZE - 1 - (move->startPos->y - 1));

								if (BlitSDL2(redSquare, win))
								{
									free_Move(move);
									return 1;
								}
								//draw red line at dst
								rectTemp.x = startingPoint + difference * (move->endPos->x - 'a');
								rectTemp.y = startingPoint + difference * (BOARD_SIZE - 1 - (move->endPos->y - 1));

								free_Move(move);

								if (BlitSDL2(redSquare, win))
									return 1;
								if (FlipSdl(mainMenu, win))
									return 1;
								if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
									pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
									return 1;
							}

						}
						//If the mouse is over 1
						else if ((x > 288) && (x < 315) && (y > 437) && (y < 457)){
							difficultyInput = 1;
							SDL_Delay(120);
							if (SDL_FillRect(win, &rectG1, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectGBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}

							if (FlipSdl(mainMenu, win))
								return 1;
						}
						//If the mouse is over 2
						else if ((x > 315) && (x < 342) && (y > 437) && (y < 457)){
							difficultyInput = 2;
							SDL_Delay(120);
							if (SDL_FillRect(win, &rectG1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG2, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectGBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}

							if (FlipSdl(mainMenu, win))
								return 1;
						}
						//If the mouse is over 3
						else if ((x > 342) && (x < 369) && (y > 437) && (y < 457)){
							difficultyInput = 3;
							SDL_Delay(120);
							if (SDL_FillRect(win, &rectG1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG3, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectGBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}

							if (FlipSdl(mainMenu, win))
								return 1;
						}
						//If the mouse is over 4
						else if ((x > 369) && (x < 396) && (y > 437) && (y < 457)){
							difficultyInput = 4;
							SDL_Delay(120);
							if (SDL_FillRect(win, &rectG1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG4, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectGBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}

							if (FlipSdl(mainMenu, win))
								return 1;
						}
						//If the mouse is over best
						else if ((x > 288) && (x < 396) && (y > 471) && (y < 491)){
							difficultyInput = DIFFICULTY_BEST;
							SDL_Delay(120);
							if (SDL_FillRect(win, &rectG1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectG4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
							if (SDL_FillRect(win, &rectGBest, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}

							if (FlipSdl(mainMenu, win))
								return 1;
						}
					}
					else { //pvc
						//If the mouse is over tip
						if ((x > 355) && (x < 394) && (y > 460) && (y < 488)){
							Move* move;
							move = tip(chess_board, gameDifficulty, next_player);
							if (move != NULL)
							{
								//draw red line at src
								rectTemp.x = startingPoint + difference * (move->startPos->x - 'a');
								rectTemp.y = startingPoint + difference * (BOARD_SIZE - 1 - (move->startPos->y - 1));

								if (BlitSDL2(redSquare, win))
								{
									free_Move(move);
									return 1;
								}
								//draw red line at dst
								rectTemp.x = startingPoint + difference * (move->endPos->x - 'a');
								rectTemp.y = startingPoint + difference * (BOARD_SIZE - 1 - (move->endPos->y - 1));

								free_Move(move);

								if (BlitSDL2(redSquare, win))
									return 1;
								if (FlipSdl(mainMenu, win))
									return 1;
								if (scanBoard(chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
									pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
									return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}



int newGame(SDL_Surface *mainMenu, SDL_Surface *win, SDL_Surface *gameWindow, SDL_Surface *loadSave, SDL_Surface *playersSelection, SDL_Surface *AISettings, SDL_Surface *setBoard,
	SDL_Surface *gameWindowPvC, SDL_Surface *pieceBishopBlack, SDL_Surface *pieceBishopWhite, SDL_Surface *pieceKingBlack, SDL_Surface *pieceKingWhite, SDL_Surface *pieceKnightBlack,
	SDL_Surface *pieceKnightWhite, SDL_Surface *piecePawnBlack, SDL_Surface *piecePawnWhite, SDL_Surface *pieceQueenBlack, SDL_Surface *pieceQueenWhite,
	SDL_Surface *pieceRookBlack, SDL_Surface *pieceRookWhite, SDL_Surface *darkSquare, SDL_Surface *lightSquare, SDL_Surface *fileNotFound, SDL_Surface *redSquare){

	SDL_Delay(120);
	if (fillRectSDL(mainMenu, win))
		return 1;
	if (BlitSDL(playersSelection, win))
		return 1;
	if (!(next_player == WHITE)){
		if (SDL_FillRect(win, &rectBlack, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
			printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
			SDL_FreeSurface(mainMenu);
			return 1;
		}
	}
	else { // next_player == WHITE
		if (SDL_FillRect(win, &rectWhite, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
			printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
			SDL_FreeSurface(mainMenu);
			return 1;
		}
	}
	/*if (!isBothKingsExist(chess_board)){
	//draw red rect at set the board
	}*/
	if (FlipSdl(mainMenu, win))
		return 1;

	while (1){
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT)
			break;
		if (ev.type == SDL_MOUSEBUTTONDOWN){
			if (ev.button.button == SDL_BUTTON_LEFT){
				x = ev.button.x;
				y = ev.button.y;

				//If the mouse is over set the board
				if ((x > 81) && (x < 341) && (y > 144) && (y < 194)){
					copyBoard(chess_board, temp_chess_board);
					setMode = 1;
					if (fillRectSDL(mainMenu, win))
						return 1;
					SDL_Delay(120);
					if (BlitSDL(setBoard, win))
						return 1;
					if (scanBoard(temp_chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
						pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
						return 1;

					while (1){
						cancel = 0;
						SDL_PollEvent(&ev);
						if (ev.type == SDL_QUIT)
							break;
						if (ev.type == SDL_MOUSEBUTTONDOWN){
							if (ev.button.button == SDL_BUTTON_LEFT){
								x = ev.button.x;
								y = ev.button.y;

								//if the mouse is over clear
								if ((x > 5) && (x < 132) && (y > 405) && (y < 430)){
									clearBoard(temp_chess_board);
									if (scanBoard(temp_chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
										pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
										return 1;
								}
								//if the mouse if over remove piece
								else if ((x > 227) && (x < 376) && (y > 449) && (y < 473)){
									while (1){
										SDL_PollEvent(&ev);
										if (ev.type == SDL_QUIT)
											break;
										if (ev.type == SDL_MOUSEBUTTONDOWN){
											if (ev.button.button == SDL_BUTTON_LEFT){
												x = ev.button.x;
												y = ev.button.y;

												i = j = k = 31;
												counterX = counterY = squareX = squareY = -1;

												//if mouse is over board
												while (j < (k + BOARD_SIZE * squareHeight)){
													counterY++;
													while (i < (k + BOARD_SIZE * squareWidth)) {
														counterX++;
														if ((x > i) && (x < i + squareWidth) && (y > j) && (y < j + squareHeight)){
															squareX = counterX;
															squareY = counterY;
														}
														i += squareWidth;
													}
													counterX = -1;
													i = k;
													j += squareHeight;
												}
												if (squareX > -1){
													removePiece(temp_chess_board, squareX, BOARD_SIZE - 1 - squareY);
													if (scanBoard(temp_chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
														pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
														return 1;

													break;
												}
												//If the mouse is over cancel
												if ((x > 270) && (x < 405) && (y > 405) && (y < 430)){
													cancel = 1;
													SDL_Delay(120);
													if (fillRectSDL(mainMenu, win))
														return 1;
													if (BlitSDL(playersSelection, win))
														return 1;
													if (FlipSdl(mainMenu, win))
														return 1;
													break;
												}
											}
										}
									}
									if (cancel)
										break;
									//SDL_Delay(120);
								}

								//If the mouse is over set
								else if ((x > 133) && (x < 270) && (y > 405) && (y < 430)){
									if (isBothKingsExist(temp_chess_board)){
										copyBoard(temp_chess_board, chess_board);
										if (fillRectSDL(mainMenu, win))
											return 1;
										SDL_Delay(120);
										if (BlitSDL(playersSelection, win))
											return 1;
										if (FlipSdl(mainMenu, win))
											return 1;
										break;
									}
								}
								//If the mouse is over cancel
								else if ((x > 270) && (x < 405) && (y > 405) && (y < 430)){
									SDL_Delay(120);
									if (fillRectSDL(mainMenu, win))
										return 1;
									if (BlitSDL(playersSelection, win))
										return 1;
									if (FlipSdl(mainMenu, win))
										return 1;
									break;
								}

								else{
									//if the mouse if over pieces
									i = k = 9;
									j = l = 432;
									pieceWidth = 34;
									pieceHeight = 32;
									counterX = counterY = pieceX = pieceY = 0;

									while (j < (l + 2 * pieceHeight)){ // 2 colors-rows
										counterY++;
										while (i < (k + 6 * pieceWidth)) { //6 pieces-columns
											counterX++;
											if ((x > i) && (x < i + pieceWidth) && (y > j) && (y < j + pieceHeight)){
												pieceX = counterX;
												pieceY = counterY;
											}
											i += pieceWidth;
										}
										counterX = 0;
										i = k;
										j += pieceHeight;
									}

									if (pieceX > 0){

										while (1){
											SDL_PollEvent(&ev);
											if (ev.type == SDL_QUIT)
												break;
											if (ev.type == SDL_MOUSEBUTTONDOWN){
												if (ev.button.button == SDL_BUTTON_LEFT){
													x = ev.button.x;
													y = ev.button.y;

													i = j = k = 31;
													counterX = counterY = squareX = squareY = -1;

													//if mouse is over board
													while (j < (k + BOARD_SIZE * squareHeight)){
														counterY++;
														while (i < (k + BOARD_SIZE * squareWidth)) {
															counterX++;
															if ((x > i) && (x < i + squareWidth) && (y > j) && (y < j + squareHeight)){
																squareX = counterX;
																squareY = counterY;
															}
															i += squareWidth;
														}
														counterX = -1;
														i = k;
														j += squareHeight;
													}
													if (squareX > -1){
														rectTemp.x = startingPoint + difference * squareX;
														rectTemp.y = startingPoint + difference * squareY;

														if (pieceX == 1 && pieceY == 1){
															pieceToSet = WHITE_K;
															colorToSet = WHITE;
														}
														else if (pieceX == 2 && pieceY == 1){
															pieceToSet = WHITE_Q;
															colorToSet = WHITE;
														}
														else if (pieceX == 3 && pieceY == 1){
															pieceToSet = WHITE_B;
															colorToSet = WHITE;
														}
														else if (pieceX == 4 && pieceY == 1){
															pieceToSet = WHITE_N;
															colorToSet = WHITE;
														}
														else if (pieceX == 5 && pieceY == 1){
															pieceToSet = WHITE_R;
															colorToSet = WHITE;
														}
														else if (pieceX == 6 && pieceY == 1){
															pieceToSet = WHITE_P;
															colorToSet = WHITE;
														}
														else if (pieceX == 1 && pieceY == 2){
															pieceToSet = BLACK_K;
															colorToSet = BLACK;
														}
														else if (pieceX == 2 && pieceY == 2){
															pieceToSet = BLACK_Q;
															colorToSet = BLACK;
														}
														else if (pieceX == 3 && pieceY == 2){
															pieceToSet = BLACK_B;
															colorToSet = BLACK;
														}
														else if (pieceX == 4 && pieceY == 2){
															pieceToSet = BLACK_N;
															colorToSet = BLACK;
														}
														else if (pieceX == 5 && pieceY == 2){
															pieceToSet = BLACK_R;
															colorToSet = BLACK;
														}
														else if (pieceX == 6 && pieceY == 2){
															pieceToSet = BLACK_P;
															colorToSet = BLACK;
														}
														setPiece(temp_chess_board, squareX, BOARD_SIZE - 1 - squareY, colorToSet, pieceToSet);
														if (scanBoard(temp_chess_board, mainMenu, win, pieceBishopBlack, pieceBishopWhite, pieceKingBlack, pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack,
															pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare))
															return 1;
														break;
													}


													//If the mouse is over cancel
													if ((x > 270) && (x < 405) && (y > 405) && (y < 430)){
														cancel = 1;
														SDL_Delay(120);
														if (fillRectSDL(mainMenu, win))
															return 1;
														if (BlitSDL(playersSelection, win))
															return 1;
														if (FlipSdl(mainMenu, win))
															return 1;
														break;
													}
												}
											}
										}
										if (cancel)
											break;
										//SDL_Delay(120);
									}
								}
							}
						}
						//SDL_Delay(120);
					}
				}

				//If the mouse is over PvC
				else if ((x > 80) && (x < 213) && (y > 64) && (y < 113)){
					if (isBothKingsExist(chess_board)){
						startGame_init();
						pvp = 0;
						setGameMode(PLAYER_VS_COMPUTER_MODE);
						setMode = 0;
						if (fillRectSDL(mainMenu, win))
							return 1;
						SDL_Delay(120);
						if (BlitSDL(AISettings, win))
							return 1;
						if (!loaded){
							//set defaults - depth: 1 and color: white
							setUserColor(WHITE);
							setGameDifficulty(DIFFICULTY_DEFAULT);
						}
						if (!(user_color == WHITE)){
							if (SDL_FillRect(win, &rectBlack, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						else{ //user_color == WHITE
							if (SDL_FillRect(win, &rectWhite, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						if (gameDifficulty == 1){
							if (SDL_FillRect(win, &rect1, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						else if (gameDifficulty == 2){
							if (SDL_FillRect(win, &rect2, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						else if (gameDifficulty == 3){
							if (SDL_FillRect(win, &rect3, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						else if (gameDifficulty == 4){
							if (SDL_FillRect(win, &rect4, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						else if (gameDifficulty == DIFFICULTY_BEST){
							if (SDL_FillRect(win, &rectBest, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
								printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
								SDL_FreeSurface(mainMenu);
								return 1;
							}
						}
						if (FlipSdl(mainMenu, win))
							return 1;



						while (1){
							SDL_PollEvent(&ev);
							if (ev.type == SDL_QUIT)
								break;
							if (ev.type == SDL_MOUSEBUTTONDOWN){
								if (ev.button.button == SDL_BUTTON_LEFT){
									x = ev.button.x;
									y = ev.button.y;

									//difficulty depth
									//If the mouse is over 1
									if ((x > 81) && (x < 148) && (y > 65) && (y < 113)){
										setGameDifficulty(1);
										SDL_Delay(120);
										if (SDL_FillRect(win, &rect1, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}
									//If the mouse is over 2
									if ((x > 148) && (x < 213) && (y > 65) && (y < 113)){
										setGameDifficulty(2);
										SDL_Delay(120);
										if (SDL_FillRect(win, &rect1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect2, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}
									//If the mouse is over 3
									if ((x > 213) && (x < 275) && (y > 65) && (y < 113)){
										setGameDifficulty(3);
										SDL_Delay(120);
										if (SDL_FillRect(win, &rect1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect3, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}
									//If the mouse is over 4
									if ((x > 275) && (x < 341) && (y > 65) && (y < 113)){
										setGameDifficulty(4);
										SDL_Delay(120);
										if (SDL_FillRect(win, &rect1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect4, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectBest, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}
									//If the mouse is over best
									if ((x > 81) && (x < 341) && (y > 144) && (y < 194)){
										setGameDifficultyBest();
										SDL_Delay(120);
										if (SDL_FillRect(win, &rect1, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect2, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect3, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rect4, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectBest, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}

									//If the mouse is over user color: white player
									else if ((x > 80) && (x < 213) && (y > 232) && (y < 283)){
										setUserColor(WHITE);
										SDL_Delay(120);
										if (SDL_FillRect(win, &rectWhite, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectBlack, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}

									//If the mouse is over user color: black player
									else if ((x > 213) && (x < 342) && (y > 233) && (y < 284)){
										setUserColor(BLACK);
										SDL_Delay(120);
										if (SDL_FillRect(win, &rectBlack, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}
										if (SDL_FillRect(win, &rectWhite, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
											printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
											SDL_FreeSurface(mainMenu);
											return 1;
										}

										if (FlipSdl(mainMenu, win))
											return 1;
									}
									//If the mouse is over continue
									else if ((x > 80) && (x < 342) && (y > 323) && (y < 375)){
										if (basicGameMode(mainMenu, win, gameWindow, loadSave, playersSelection, AISettings, setBoard, gameWindowPvC, pieceBishopBlack, pieceBishopWhite, pieceKingBlack,
											pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare, fileNotFound, redSquare))
											return 1;
										break;
									}
								}
							}
						}
						break;
					}
				}
				//If the mouse is over PvP
				else if ((x > 214) && (x < 341) && (y > 66) && (y < 112)){
					if (isBothKingsExist(chess_board)){
						difficultyInput = 0;
						startGame_init();
						pvp = 1;
						setGameMode(PLAYER_VS_PLAYER_MODE);
						setMode = 0;
						if (basicGameMode(mainMenu, win, gameWindow, loadSave, playersSelection, AISettings, setBoard, gameWindowPvC, pieceBishopBlack, pieceBishopWhite, pieceKingBlack,
							pieceKingWhite, pieceKnightBlack, pieceKnightWhite, piecePawnBlack, piecePawnWhite, pieceQueenBlack, pieceQueenWhite, pieceRookBlack, pieceRookWhite, darkSquare, lightSquare, fileNotFound, redSquare))
							return 1;

						break;
					}
				}

				//If the mouse is over next player: white player
				else if ((x > 80) && (x < 213) && (y > 232) && (y < 283)){
					setNextPlayer(WHITE);
					SDL_Delay(120);
					if (SDL_FillRect(win, &rectWhite, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
						printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
						SDL_FreeSurface(mainMenu);
						return 1;
					}
					if (SDL_FillRect(win, &rectBlack, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
						printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
						SDL_FreeSurface(mainMenu);
						return 1;
					}

					if (FlipSdl(mainMenu, win))
						return 1;
				}

				//If the mouse is over next player: black player
				else if ((x > 213) && (x < 342) && (y > 233) && (y < 284)){
					setNextPlayer(BLACK);
					SDL_Delay(120);
					if (SDL_FillRect(win, &rectBlack, SDL_MapRGB(win->format, 255, 0, 0)) != 0){
						printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
						SDL_FreeSurface(mainMenu);
						return 1;
					}
					if (SDL_FillRect(win, &rectWhite, SDL_MapRGB(win->format, 255, 255, 255)) != 0){
						printf("ERROR: failed to draw rectangle: %s\n", SDL_GetError());
						SDL_FreeSurface(mainMenu);
						return 1;
					}

					if (FlipSdl(mainMenu, win))
						return 1;
				}

				//If the mouse is over cancel
				else if ((x > 80) && (x < 342) && (y > 323) && (y < 375)){
					if (fillRectSDL(mainMenu, win))
						return 1;
					SDL_Delay(120);
					if (BlitSDL(mainMenu, win))
						return 1;
					if (FlipSdl(mainMenu, win))
						return 1;
					break;
				}
			}
		}

	}
	return 0;
}