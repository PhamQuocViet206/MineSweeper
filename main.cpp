#include "defs.h"
#include "graphics.h"
#include "functions.h"
using namespace std;

int main(int argc, char *argv[]){
    Graphics graphics;

    int score = 0;
    int x, y;
    int bombField[12][12];
    char playersField[12][12];

    Sprite explode;
    explode.init(graphics.explodeSprite, graphics.explodeFrame, graphics.explodeClips);

    do{
        prepareMenu(graphics);
        getClickPosition(x,y);
        if(checkMenuOption(graphics,x,y)==1){
            x=0;
            y=0;
            generateBlankBombField(bombField);
            generateBlankPlayersField(playersField);
            bool gameOver = false;
            bool isShovel = true;
            graphics.prepareScene(graphics.background);
            printPlayersField(graphics, playersField);
            do getClickPosition(x,y);
            while(checkInGameOption(graphics,x,y)!=1);
            int choosenTileX = (x-100)/40+1;
            int choosenTileY = (y-100)/40+1;
            int bombCount = generateBombField(bombField,choosenTileX,choosenTileY,numberOfMaximumBombs);
            int tileLeft = 100 - bombCount;
            updatePlayersField(graphics,choosenTileX,choosenTileY,true,playersField,bombField,tileLeft);
            score = (100-tileLeft)*10;
            while(!gameOver){
                prepareInGame(graphics, isShovel, playersField);
                do getClickPosition(x,y);
                while(checkInGameOption(graphics,x,y) == 0);
                if(checkInGameOption(graphics,x,y) == 2){
                    preparePauseMenu(graphics);
                    do getClickPosition(x,y);
                    while(checkPauseMenuOption(graphics,x,y) == 0);
                    if(checkPauseMenuOption(graphics,x,y) == 2) gameOver = true;
                }else if(checkInGameOption(graphics,x,y) == 3) isShovel = !isShovel;
                else{
                    choosenTileX = (x-100)/40+1;
                    choosenTileY = (y-100)/40+1;
                    updatePlayersField(graphics,choosenTileX,choosenTileY,isShovel,playersField,bombField,tileLeft);
                    if(isShovel&&bombField[choosenTileX][choosenTileY]==-1){
                        gameOver = true;
                        prepareExplosion(graphics,explode,70+(choosenTileX-1)*40,70+(choosenTileY-1)*40,isShovel,playersField);
                    }
                }
                score = (100-tileLeft)*10;
                if(tileLeft==0) gameOver = true;
            }
            prepareGameOver(graphics, tileLeft==0);
            if(score>lastBestScore()){
                graphics.renderTexture(graphics.newHighScore,10,20+graphics.textDest.h);
                graphics.presentScene();
                newBestScore(score);
                SDL_DestroyTexture( graphics.bestScoreNumber );
                graphics.bestScoreNumber = graphics.renderText(graphics.charBestScore(), graphics.font, graphics.color);
            }
            getClickPosition(x,y);
            x = 0;
            y = 0;
        }
    }while(checkMenuOption(graphics,x,y) != 2);
    graphics.destroyTexture();
    graphics.quit();
    return 0;
}
