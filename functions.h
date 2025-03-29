#ifndef _FUNCTIONS__H_
#define _FUNCTIONS__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"

void waitUntilKeyPressed();

void prepareMenu(Graphics graphics);
int checkMenuOption(Graphics graphics, int x, int y);
void prepareInGame(Graphics graphics, const bool isShovel, const char playersField[][12]);
int checkInGameOption(Graphics graphics, int x, int y);
void preparePauseMenu(Graphics graphics);
int checkPauseMenuOption(Graphics graphics, int x, int y);
void prepareGameOver(Graphics graphics, const bool won);
void prepareExplosion(Graphics graphics, Sprite explode, int x, int y, bool isShovel, const char playersField[][12]);

void printPlayersField(Graphics graphics, const char playersField[][12]);
void getClickPosition(int &x, int &y);
int lastBestScore();
void newBestScore(const int bestScore);

void generateBlankBombField(int bombField[][12]);
void generateBlankPlayersField(char playersField[][12]);
int generateBombField(int bombField[][12], const int x, const int y, const int numberOfBombs);
void clearBlankTile(int x, int y, char playersField[][12], const int bombField[][12], int &tileLeft);
void updatePlayersField(Graphics graphics, const int x, const int y, const bool isShovel, char playersField[][12], const int bombField[][12], int &tileLeft);

#endif _FUNCTIONS__H_
