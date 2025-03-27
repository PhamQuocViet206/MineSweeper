#include "defs.h"
#include "graphics.h"
#include "functions.h"
#include "texture.h"
using namespace std;

int main(int argc, char *argv[]){
    int score = 0;
    Texture texture;
    int x, y;
    int bombField[12][12];
    char playersField[12][12];
    do{
        prepareMenu();
        getClickPosition(x,y);
        if(checkMenuOption(x,y)==1){
            x=0;
            y=0;
            generateBlankBombField(bombField);
            generateBlankPlayersField(playersField);
            bool gameOver = false;
            bool isShovel = true;
            prepareScene(texture.background);
            printPlayersField(playersField);
            do getClickPosition(x,y);
            while(checkInGameOption(x,y)!=1);
            int choosenTileX = (x-100)/40+1;
            int choosenTileY = (y-100)/40+1;
            int bombCount = generateBombField(bombField,choosenTileX,choosenTileY,numberOfBombs);
            int tileLeft = 100 - bombCount;
            updatePlayersField(choosenTileX,choosenTileY,true,playersField,bombField,tileLeft);
            score = (100-tileLeft)*10;
            while(!gameOver){
                prepareInGame(isShovel, playersField);
                do getClickPosition(x,y);
                while(checkInGameOption(x,y) == 0);
                if(checkInGameOption(x,y) == 2){
                    preparePauseMenu();
                    do getClickPosition(x,y);
                    while(checkPauseMenuOption(x,y) == 0);
                    if(checkPauseMenuOption(x,y) == 2) gameOver = true;
                }else if(checkInGameOption(x,y) == 3) isShovel = !isShovel;
                else{
                    choosenTileX = (x-100)/40+1;
                    choosenTileY = (y-100)/40+1;
                    if(isShovel&&bombField[choosenTileX][choosenTileY]==-1) gameOver = true;
                    else{
                        updatePlayersField(choosenTileX,choosenTileY,isShovel,playersField,bombField,tileLeft);
                    }
                }
                score = (100-tileLeft)*10;
                if(tileLeft==0) gameOver = true;
            }
            prepareGameOver(tileLeft==0);
            if(score>lastBestScore()){
                renderTexture(texture.newHighScore,10,20+texture.textDest.h);
                presentScene();
                newBestScore(score);
            }
            getClickPosition(x,y);
            x = 0;
            y = 0;
        }
    }while(checkMenuOption(x,y) != 2);
    texture.destroyTexture();
    quit();
    return 0;
}
