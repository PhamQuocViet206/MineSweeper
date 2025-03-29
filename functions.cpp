#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include "functions.h"
#include "texture.h"
using namespace std;

void waitUntilKeyPressed(){
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void prepareMenu(Graphics graphics){
    graphics.prepareScene(graphics.background);
    graphics.renderTexture(graphics.blurBackground, 0, 0);
    graphics.renderTexture(graphics.newGameButton,152,204);
    graphics.renderTexture(graphics.quitButton,220,324);
    graphics.renderTexture(graphics.bestScoreText, 10, 10);
    graphics.renderTexture(graphics.bestScoreNumber, 10 + graphics.textDest.w, 10);
    graphics.presentScene();
};

void printPlayersField(Graphics graphics, const char playersField[][12]){
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++){
            int x = (i-1)*40+100;
            int y = (j-1)*40+100;
            switch(playersField[i][j]){
                case '?':
                    graphics.renderTexture(graphics.tileGrass,x,y);
                    break;
                case '!':
                    graphics.renderTexture(graphics.tileFlag,x,y);
                    break;
                case 'b':
                    graphics.renderTexture(graphics.tileBomb,x,y);
                    break;
                case '0':
                    graphics.renderTexture(graphics.tile0,x,y);
                    break;
                case '1':
                    graphics.renderTexture(graphics.tile1,x,y);
                    break;
                case '2':
                    graphics.renderTexture(graphics.tile2,x,y);
                    break;
                case '3':
                    graphics.renderTexture(graphics.tile3,x,y);
                    break;
                case '4':
                    graphics.renderTexture(graphics.tile4,x,y);
                    break;
                case '5':
                    graphics.renderTexture(graphics.tile5,x,y);
                    break;
                case '6':
                    graphics.renderTexture(graphics.tile6,x,y);
                    break;
                case '7':
                    graphics.renderTexture(graphics.tile7,x,y);
                    break;
                case '8':
                    graphics.renderTexture(graphics.tile8,x,y);
                    break;
                default:
                    break;
            }
        }
    graphics.presentScene();
}

void prepareInGame(Graphics graphics, const bool isShovel, const char playersField[][12]){
    graphics.prepareScene(graphics.background);
    graphics.renderTexture(graphics.pauseButton,0,0);
    if(isShovel) graphics.renderTexture(graphics.shovelActionButton,0,540);
    else graphics.renderTexture(graphics.flagActionButton,0,540);
    printPlayersField(graphics,playersField);
    graphics.presentScene();
}

void preparePauseMenu(Graphics graphics){
    graphics.renderTexture(graphics.blurBackground,0,0);
    graphics.renderTexture(graphics.continueButton,160,204);
    graphics.renderTexture(graphics.quitButton,220,324);
    graphics.presentScene();
}

void prepareGameOver(Graphics graphics, const bool won){
    graphics.prepareScene(graphics.background);
    graphics.renderTexture(graphics.blurBackground,0,0);
    if(won){
        graphics.play(graphics.winningSound);
        graphics.renderTexture(graphics.youWin, 10, 10);
    }
    else{
        graphics.play(graphics.losingSound);
        graphics.renderTexture(graphics.youLost, 10, 10);
    }
    graphics.renderTexture(graphics.toContinue,10,600-10-graphics.textDest.h);
    graphics.presentScene();
}

void prepareExplosion(Graphics graphics, Sprite explode, int x, int y, bool isShovel, const char playersField[][12]){
    do{
        graphics.play(graphics.explodeSound);
        explode.tick();
        prepareInGame(graphics,isShovel,playersField);
        graphics.renderSprite(x,y,explode);
        graphics.presentScene();
        SDL_Delay(100);
    }while(explode.currentFrame<14);
}

void getClickPosition(int &x, int &y){
    SDL_Event event;
    int x1, y1;
    while (true) {
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x1, &y1);
        if(event.type==SDL_MOUSEBUTTONDOWN){
            x = x1;
            y = y1;
            break;
        }
    }
}

int lastBestScore(){
    ifstream fin;
    fin.open("assets\\best_score.txt");
    int bestScore;
    fin >> bestScore;
    fin.close();
    return bestScore;
}

void newBestScore(const int bestScore){
    ofstream fout;
    fout.open("assets\\best_score.txt");
    fout << bestScore;
    fout.close();
}

int checkMenuOption(Graphics graphics, int x, int y){
    if(x>=152&&x<=448&&y>=204&&y<=276){
        graphics.play(graphics.buttonSound);
        return 1;
    }
    if(x>=220&&x<=380&&y>=324&&y<=396){
        graphics.play(graphics.buttonSound);
        return 2;
    }
    return 0;
}

int checkInGameOption(Graphics graphics, int x, int y){
    if(x>=100&&x<=500&&y>=100&&y<=500){
        return 1;
    }
    if(x>=0&&x<=60&&y>=0&&y<=60){
        graphics.play(graphics.buttonSound);
        return 2;
    }
    if(x>=0&&x<=100&&y>=540&&y<=600){
        graphics.play(graphics.buttonSound);
        return 3;
    }
    return 0;
}

int checkPauseMenuOption(Graphics graphics, int x, int y){
    if(x>=160&&x<=440&&y>=204&&y<=276){
        graphics.play(graphics.buttonSound);
        return 1;
    }
    if(x>=220&&x<=380&&y>=324&&y<=396){
        graphics.play(graphics.buttonSound);
        return 2;
    }
    return 0;
}

void generateBlankBombField(int field[][12]){
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            field[i][j] = 0;
}

void generateBlankPlayersField(char playersField[][12]){
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            playersField[i][j] = '?';
}

int generateBombField(int bombField[][12], const int x, const int y, const int numberOfBombs){
    int bombCount = 0;
    for(int i=1;i<=numberOfBombs;i++){
        int randomX = rand() % 10 + 1;
        int randomY = rand() % 10 + 1;
        if(randomX!=x&&randomY!=y){
            if(bombField[randomX][randomY]==0) bombCount++;
            bombField[randomX][randomY] = -1;
        }
    }
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
            if(bombField[i][j]==-1)
                for(int k=i-1;k<=i+1;k++)
                    for(int l=j-1;l<=j+1;l++)
                        if((!(k==i&&l==j))&&bombField[k][l]!=-1) bombField[k][l]++;
    return bombCount;
}

void clearBlankTile(int x, int y, char playersField[][12], const int bombField[][12], int &tileLeft){
    if(playersField[x][y]=='?'){
        playersField[x][y]='0';
        tileLeft--;
    }
    for(int i=x-1;i<=x+1;i++)
        for(int j=y-1;j<=y+1;j++)
            if(bombField[i][j]!=0){
                if(i!=0&&i!=11&&j!=0&&j!=11&&playersField[i][j]=='?') tileLeft--;
                playersField[i][j] = bombField[i][j] + 48;
            }
    if(bombField[x-1][y]==0&&playersField[x-1][y]!='0'&&x>=2) clearBlankTile(x-1,y,playersField,bombField,tileLeft);
    if(bombField[x+1][y]==0&&playersField[x+1][y]!='0'&&x<=9) clearBlankTile(x+1,y,playersField,bombField,tileLeft);
    if(bombField[x][y-1]==0&&playersField[x][y-1]!='0'&&y>=2) clearBlankTile(x,y-1,playersField,bombField,tileLeft);
    if(bombField[x][y+1]==0&&playersField[x][y+1]!='0'&&y<=9) clearBlankTile(x,y+1,playersField,bombField,tileLeft);
}
void updatePlayersField(Graphics graphics, const int x, const int y, const bool isShovel, char playersField[][12], const int bombField[][12], int &tileLeft){
    if(!isShovel){
        if(playersField[x][y]=='?'){
            graphics.play(graphics.placingSound);
            playersField[x][y]='!';
        }
        else if(playersField[x][y]=='!'){
            graphics.play(graphics.placingSound);
            playersField[x][y]='?';
        }
    }
    else{
        if(playersField[x][y]=='?'||playersField[x][y]=='!'){
            graphics.play(graphics.diggingSound);
            if(bombField[x][y]==0&&playersField[x][y]=='?'){
                clearBlankTile(x,y,playersField,bombField,tileLeft);
                return;
            }
            playersField[x][y]=bombField[x][y]+48;
            tileLeft--;
            if(tileLeft==0) return;
        }
        if(bombField[x][y]==-1) playersField[x][y] = 'b';
    }
}
