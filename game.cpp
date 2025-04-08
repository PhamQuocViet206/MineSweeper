#include <iostream>
#include "game.h"
using namespace std;

char* Game::charHighScore(){
    ifstream fin;
    fin.open("assets\\best_score.txt");
    char* score = new char[10];
    fin >> score;
    fin.close();
    return score;
}

int Game::lastHighScore(){
    ifstream fin;
    fin.open("assets\\best_score.txt");
    int bestScore;
    fin >> bestScore;
    fin.close();
    return bestScore;
}

void Game::newHighScore(){
    ofstream fout;
    fout.open("assets\\best_score.txt");
    fout << score;
    fout.close();
}

Game::Game(){

    score = 0;
    bestScore = lastHighScore();
    isShovel = true;
    gameOver = true;
    bombField = vector<vector<int>> (14, vector<int> (22));
    playersField = vector<vector<char>> (14, vector<char> (22));

    easyButton.initButton(graphics.loadTexture("assets\\easy_button.png"), graphics.loadSound("assets\\button_sound.wav"), 176, 204);
    normalButton.initButton(graphics.loadTexture("assets\\normal_button.png"), graphics.loadSound("assets\\button_sound.wav"), 380, 204);
    hardButton.initButton(graphics.loadTexture("assets\\hard_button.png"), graphics.loadSound("assets\\button_sound.wav"), 660, 204);
    quitButton.initButton(graphics.loadTexture("assets\\quit_button.png"), graphics.loadSound("assets\\button_sound.wav"), 420, 360);
    pauseButton.initButton(graphics.loadTexture("assets\\pause_button.png"), graphics.loadSound("assets\\button_sound.wav"), 0, 0);
    continueButton.initButton(graphics.loadTexture("assets\\continue_button.png"), graphics.loadSound("assets\\button_sound.wav"), 360, 248);
    shovelButton.initButton(graphics.loadTexture("assets\\shovel_action_button.png"), graphics.loadSound("assets\\button_sound.wav"), 0, 620);
    flagButton.initButton(graphics.loadTexture("assets\\flag_action_button.png"), graphics.loadSound("assets\\button_sound.wav"), 0, 620);

    background = graphics.loadTexture("assets\\background.jpg");
    blurBackground = graphics.loadTexture("assets\\blur_background.png");
    tileGrass = graphics.loadTexture("assets\\tile_grass.png");
    tileFlag = graphics.loadTexture("assets\\tile_flag.png");
    tileBomb = graphics.loadTexture("assets\\tile_bomb.png");
    tile0 = graphics.loadTexture("assets\\tile_0.png");
    tile1 = graphics.loadTexture("assets\\tile_1.png");
    tile2 = graphics.loadTexture("assets\\tile_2.png");
    tile3 = graphics.loadTexture("assets\\tile_3.png");
    tile4 = graphics.loadTexture("assets\\tile_4.png");
    tile5 = graphics.loadTexture("assets\\tile_5.png");
    tile6 = graphics.loadTexture("assets\\tile_6.png");
    tile7 = graphics.loadTexture("assets\\tile_7.png");
    tile8 = graphics.loadTexture("assets\\tile_8.png");

    explode.init(graphics.loadTexture("assets\\explode_sprite.png"), explodeFrame, explodeClips);

    font = graphics.loadFont("assets\\light-arial.ttf", 50);
    highScoreNumber = graphics.renderText(charHighScore(), font, {0, 0, 0, 0});
    highScoreText = graphics.renderText("High score: ", font, {0, 0, 0, 0});
    youWin = graphics.renderText("You WIN!", font, {0, 255, 0, 0});
    youLost = graphics.renderText("You lost...", font, {255, 0, 0, 0});
    toContinue = graphics.renderText("Click anywhere to continue.", font, {0, 0, 0, 0});
    newHighScoreText = graphics.renderText("NEW HIGH SCORE!!!", font, {0, 255, 0, 0});
    SDL_QueryTexture(highScoreText, NULL, NULL, &textDest.w, &textDest.h);

    diggingSound = graphics.loadSound("assets\\digging_sound.wav");
    placingSound = graphics.loadSound("assets\\placing_sound.wav");
    explodeSound = graphics.loadSound("assets\\explode_sound.wav");
    winningSound = graphics.loadSound("assets\\winning_sound.wav");
    losingSound = graphics.loadSound("assets\\losing_sound.wav");

}

void Game::waitUntilKeyPressed(){
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void Game::getClickPosition(){
    SDL_Event event;
    int x1, y1;
    while (true) {
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x1, &y1);
        if(event.type==SDL_MOUSEBUTTONDOWN){
            x = x1;
            y = y1;
            return;
        }
    }
}

void Game::menuScene(){
    graphics.prepareScene(background);
    graphics.renderTexture(blurBackground, 0, 0);
    easyButton.render(graphics);
    normalButton.render(graphics);
    hardButton.render(graphics);
    quitButton.render(graphics);
    graphics.renderTexture(highScoreText, 10, 10);
    graphics.renderTexture(highScoreNumber, 10 + textDest.w, 10);
    graphics.presentScene();
}

int Game::menuOption(){
    gameMode = 0;
    if(easyButton.isPressed(graphics, x, y)){
        gameMode = 1;
        numberOfBombs = 15;
        fieldSizeX = 10;
        fieldSizeY = 10;
        gameOver = false;
    }
    if(normalButton.isPressed(graphics, x, y)){
        gameMode = 2;
        numberOfBombs = 25;
        fieldSizeX = 10;
        fieldSizeY = 15;
        gameOver = false;
    }
    if(hardButton.isPressed(graphics, x, y)){
        gameMode = 3;
        numberOfBombs = 40;
        fieldSizeX = 12;
        fieldSizeY = 20;
        gameOver = false;
    }
    if(quitButton.isPressed(graphics, x, y)) gameMode = 4;
    return 0;

}

void Game::generateNewGame(){
    isShovel = true;
    bombCount = 0;
    for(int i=0;i<14;i++)
        for(int j=0;j<22;j++){
            playersField[i][j] = '?';
            bombField[i][j] = 0;
        }
    while(bombCount<numberOfBombs){
        int randomX = rand() % fieldSizeX + 1;
        int randomY = rand() % fieldSizeY + 1;
        if(randomX!=choosenTileX&&randomY!=choosenTileY)
            if(bombField[randomX][randomY]==0){
                bombCount++;
                bombField[randomX][randomY] = -1;
            }
    }
    for(int i=1;i<=fieldSizeX;i++)
        for(int j=1;j<=fieldSizeY;j++)
            if(bombField[i][j]==-1)
                for(int k=i-1;k<=i+1;k++)
                    for(int l=j-1;l<=j+1;l++)
                        if((!(k==i&&l==j))&&bombField[k][l]!=-1) bombField[k][l]++;
    tileLeft = fieldSizeX*fieldSizeY - bombCount;
}

void Game::resetHighScoreNumber(){
    SDL_DestroyTexture(highScoreNumber);
    highScoreNumber = graphics.renderText(charHighScore(), font, {0, 0, 0, 0});
}

void Game::clearBlankTile(int Tx, int Ty){
    playersField[Tx][Ty]='0';
    tileLeft--;
    for(int i=Tx-1;i<=Tx+1;i++)
        for(int j=Ty-1;j<=Ty+1;j++)
            if(bombField[i][j]!=0){
                if(i!=0&&i!=fieldSizeX+1&&j!=0&&j!=fieldSizeY+1&&playersField[i][j]=='?') tileLeft--;
                playersField[i][j] = bombField[i][j] + 48;
            }
    if(bombField[Tx-1][Ty]==0&&playersField[Tx-1][Ty]!='0'&&Tx>=2) clearBlankTile(Tx-1,Ty);
    if(bombField[Tx+1][Ty]==0&&playersField[Tx+1][Ty]!='0'&&Tx<=fieldSizeX-1) clearBlankTile(Tx+1,Ty);
    if(bombField[Tx][Ty-1]==0&&playersField[Tx][Ty-1]!='0'&&Ty>=2) clearBlankTile(Tx,Ty-1);
    if(bombField[Tx][Ty+1]==0&&playersField[Tx][Ty+1]!='0'&&Ty<=fieldSizeY-1) clearBlankTile(Tx,Ty+1);

}

void Game::printPlayersField(){
    for(int i=1;i<=fieldSizeX;i++)
        for(int j=1;j<=fieldSizeY;j++){
            int x = (j-1)*40+(SCREEN_WIDTH-fieldSizeY*40)/2;
            int y = (i-1)*40+(SCREEN_HEIGHT-fieldSizeX*40)/2;
            switch(playersField[i][j]){
                case '?':
                    graphics.renderTexture(tileGrass, x, y);
                    break;
                case '!':
                    graphics.renderTexture(tileFlag, x, y);
                    break;
                case 'b':
                    graphics.renderTexture(tileBomb, x, y);
                    break;
                case '0':
                    graphics.renderTexture(tile0, x, y);
                    break;
                case '1':
                    graphics.renderTexture(tile1, x, y);
                    break;
                case '2':
                    graphics.renderTexture(tile2, x, y);
                    break;
                case '3':
                    graphics.renderTexture(tile3, x, y);
                    break;
                case '4':
                    graphics.renderTexture(tile4, x, y);
                    break;
                case '5':
                    graphics.renderTexture(tile5, x, y);
                    break;
                case '6':
                    graphics.renderTexture(tile6, x, y);
                    break;
                case '7':
                    graphics.renderTexture(tile7, x, y);
                    break;
                case '8':
                    graphics.renderTexture(tile8, x, y);
                    break;
            }
        }
    graphics.presentScene();

}

void Game::inGameScene(){
    graphics.prepareScene(background);
    pauseButton.render(graphics);
    if(isShovel) shovelButton.render(graphics);
    else flagButton.render(graphics);
    printPlayersField();
    graphics.presentScene();
}

bool Game::ifChooseATile(){
    if(x>=(SCREEN_WIDTH-fieldSizeY*40)/2&&x<=(SCREEN_WIDTH-fieldSizeY*40)/2+fieldSizeY*40&&
       y>=(SCREEN_HEIGHT-fieldSizeX*40)/2&&y<=(SCREEN_HEIGHT-fieldSizeX*40)/2+fieldSizeX*40){
           choosenTileX = (y-(SCREEN_HEIGHT-fieldSizeX*40)/2)/40+1;
           choosenTileY = (x-(SCREEN_WIDTH-fieldSizeY*40)/2)/40+1;
           return true;
    }
    return false;
}

int Game::inGameOption(){
    if(ifChooseATile()) return 1;
    if(pauseButton.isPressed(graphics, x, y)) return 2;
    if(shovelButton.isPressed(graphics, x, y)||flagButton.isPressed(graphics, x, y)){
        isShovel = !isShovel;
        return 3;
    }
    return 0;
}

void Game::prepareExplosion(){
    graphics.play(explodeSound);
    do{
        explode.tick();
        inGameScene();
        graphics.renderSprite((x-(SCREEN_WIDTH-fieldSizeY*40)/2)/40*40-30+(SCREEN_WIDTH-fieldSizeY*40)/2,
                              (y-(SCREEN_HEIGHT-fieldSizeX*40)/2)/40*40-30+(SCREEN_HEIGHT-fieldSizeX*40)/2,explode);
        graphics.presentScene();
        SDL_Delay(100);
    }while(explode.currentFrame<14);
}

void Game::updatePlayersField(){
    if(!isShovel){
        if(playersField[choosenTileX][choosenTileY]=='?'){
            graphics.play(placingSound);
            playersField[choosenTileX][choosenTileY]='!';
        }
        else if(playersField[choosenTileX][choosenTileY]=='!'){
            graphics.play(placingSound);
            playersField[choosenTileX][choosenTileY]='?';
        }
    }
    else{
        if(playersField[choosenTileX][choosenTileY]=='?'||playersField[choosenTileX][choosenTileY]=='!'){
            graphics.play(diggingSound);
            if(bombField[choosenTileX][choosenTileY]==0&&playersField[choosenTileX][choosenTileY]=='?')
                clearBlankTile(choosenTileX,choosenTileY);
            else{
                playersField[choosenTileX][choosenTileY]=bombField[choosenTileX][choosenTileY]+48;
                tileLeft--;
            }
            if(tileLeft==0){
                gameOver = true;
                return;
            }
        }
        if(bombField[choosenTileX][choosenTileY]==-1){
            gameOver = true;
            playersField[choosenTileX][choosenTileY] = 'b';
        }
    }

}

void Game::pauseScene(){
    graphics.renderTexture(blurBackground,0,0);
    continueButton.render(graphics);
    quitButton.render(graphics);
    graphics.presentScene();
}

int Game::pauseOption(){
    if(continueButton.isPressed(graphics, x, y)) return 1;
    if(quitButton.isPressed(graphics, x, y)){
        gameOver = true;
        return 2;
    }
    return 0;
}

void Game::endGameScene(){
    graphics.prepareScene(background);
    graphics.renderTexture(blurBackground,0,0);
    if(won){
        graphics.play(winningSound);
        graphics.renderTexture(youWin, 10, 10);
    }
    else{
        graphics.play(losingSound);
        graphics.renderTexture(youLost, 10, 10);
    }
    if(score>bestScore) graphics.renderTexture(newHighScoreText,10,20+textDest.h);
    graphics.renderTexture(toContinue,10,680-10-textDest.h);
    graphics.presentScene();
}

void Game::run(){
    while(gameMode!=4){
        menuScene();
        getClickPosition();
        menuOption();
        if(gameMode!=0&&gameMode!=4){
            generateNewGame();
            graphics.prepareScene(background);
            printPlayersField();
            do getClickPosition();
            while(!ifChooseATile());
            generateNewGame();
            updatePlayersField();
            while(!gameOver){
                inGameScene();
                do getClickPosition();
                while(inGameOption()==0);
                if(inGameOption()==1){
                    updatePlayersField();
                    if(playersField[choosenTileX][choosenTileY]=='b') prepareExplosion();
                }
                else if(inGameOption()==2){
                    pauseScene();
                    do getClickPosition();
                    while(pauseOption()==0);
                }
                score = (fieldSizeX*fieldSizeY - bombCount - tileLeft)*10;
            }
            if(tileLeft==0) won = true;
            else won = false;
            endGameScene();
            SDL_Delay(300);
            getClickPosition();
            if(score>bestScore) newHighScore();
            resetHighScoreNumber();
        }
    }
}

Game::~Game(){

    easyButton.~Button();
    normalButton.~Button();
    hardButton.~Button();
    quitButton.~Button();
    pauseButton.~Button();
    continueButton.~Button();
    shovelButton.~Button();
    flagButton.~Button();

    SDL_DestroyTexture( background );
    background = NULL;
    SDL_DestroyTexture( blurBackground );
    blurBackground = NULL;
    SDL_DestroyTexture( tileGrass );
    tileGrass = NULL;
    SDL_DestroyTexture( tileFlag );
    tileFlag = NULL;
    SDL_DestroyTexture( tileBomb );
    tileBomb = NULL;
    SDL_DestroyTexture( tile0 );
    tile0 = NULL;
    SDL_DestroyTexture( tile1 );
    tile1 = NULL;
    SDL_DestroyTexture( tile2 );
    tile2 = NULL;
    SDL_DestroyTexture( tile3 );
    tile3 = NULL;
    SDL_DestroyTexture( tile4 );
    tile4 = NULL;
    SDL_DestroyTexture( tile5 );
    tile5 = NULL;
    SDL_DestroyTexture( tile6 );
    tile6 = NULL;
    SDL_DestroyTexture( tile7 );
    tile7 = NULL;
    SDL_DestroyTexture( tile8 );
    tile8 = NULL;

    SDL_DestroyTexture( explode.texture );
    explode.texture = NULL;

    TTF_CloseFont( font );
    font = NULL;
    SDL_DestroyTexture( highScoreNumber );
    highScoreNumber = NULL;
    SDL_DestroyTexture( highScoreText );
    highScoreText = NULL;
    SDL_DestroyTexture( youWin );
    youWin = NULL;
    SDL_DestroyTexture( youLost );
    youLost = NULL;
    SDL_DestroyTexture( toContinue );
    toContinue = NULL;
    SDL_DestroyTexture( newHighScoreText );
    newHighScoreText = NULL;

    Mix_FreeChunk( buttonSound );
    buttonSound = NULL;
    Mix_FreeChunk( diggingSound );
    diggingSound = NULL;
    Mix_FreeChunk( placingSound );
    placingSound = NULL;
    Mix_FreeChunk( explodeSound );
    explodeSound = NULL;
    Mix_FreeChunk( winningSound );
    winningSound = NULL;
    Mix_FreeChunk( losingSound );
    losingSound = NULL;

    graphics.quit();
}
