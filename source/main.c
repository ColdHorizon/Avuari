#include <grrlib.h>
#include <gccore.h>
#include <grrmod.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include "OlivettiThin_ttf.h"
#include "expo_it.h"
#include "button_png.h"
#include "Falcon_png.h"
#include "TypeA_png.h"
#include "TypeB_png.h"
#include "TypeZ_png.h"
#include "Wall_png.h"
#include "Upgrade_png.h"
#include "Bullet_png.h"
/*
?Creation of the object items
*/


struct player{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    int power;
    int speed;
};
struct bullet{
    int xposition;
    int yposition;
    int bxsize;
    int bysize;
    int speed;
    int dmg;
    int active;
};
struct ennemy{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    int health;
    int speed;
    int active;
    int dead;
    u32 color;
    char type;
    GRRLIB_texImg *imgName;
};
struct upgrade{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    int speed;
    int active;
    u32 color;
};
struct bulletCount{
    struct bullet box[100];
};
struct storage{
    struct ennemy ennemybase[50];
    //level 51 breaks game change or keep
};
struct levelSystem{
    int start;
    int game;
    int gameover;
    int win;
};
struct buttoncollisions{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
};
/*
?This is the main loop
*/


int main(int argc, char **argv){
    /*
    ?Initilisation of the values
    */


    srand(time(NULL));

    GRRLIB_Init();
    WPAD_Init();

    GRRMOD_Init(0);
    GRRMOD_SetMOD(expo_it, expo_it_size);
    GRRMOD_SetVolume(64, 64);
    GRRMOD_Start();

    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetVRes(WPAD_CHAN_0, 640, 480);

    GRRLIB_ttfFont *font = GRRLIB_LoadTTF(OlivettiThin_ttf,OlivettiThin_ttf_size);
    GRRLIB_texImg *button = GRRLIB_LoadTexture(button_png);
    GRRLIB_texImg *FalconIMG = GRRLIB_LoadTexture(Falcon_png);
    GRRLIB_texImg *TypeAIMG = GRRLIB_LoadTexture(TypeA_png);
    GRRLIB_texImg *TypeBIMG = GRRLIB_LoadTexture(TypeB_png);
    GRRLIB_texImg *TypeZIMG = GRRLIB_LoadTexture(TypeZ_png);
    GRRLIB_texImg *WallIMG = GRRLIB_LoadTexture(Wall_png);
    GRRLIB_texImg *UpgradeIMG = GRRLIB_LoadTexture(Upgrade_png);
    GRRLIB_texImg *BulletIMG = GRRLIB_LoadTexture(Bullet_png);
    //ActionTimer dodgeTimer = {0};
    int musicActivation =1;
    int mainMenu =1;
    int creditsMenu = 0;
    int reset =0;
    struct upgrade powerUp = {0,0,0,0,0,0,0x00000000};
    struct player Falcon;
    struct bulletCount bulletCount;
    struct storage enemyCount;
    struct levelSystem MenuSystem ={1,0,0,0};
    int enemyCounter = 0;
    int level = 0;
    int score =0;
    int win =0;
    int gameend =0;
    char levelCounter[20];
    char scoreCounter[20];
    Falcon.xposition = 300;
    Falcon.yposition = 240;
    Falcon.xsize = 20;
    Falcon.ysize = 24;
    Falcon.power = 0;
    Falcon.speed=5;
    int count = sizeof(bulletCount.box) / sizeof(bulletCount.box[0]);
    int sizeOfEnemies = sizeof(enemyCount.ennemybase) / sizeof(enemyCount.ennemybase[0]);
    for (int i = 0; i < count; i++) {
        bulletCount.box[i].active = 0;
    }
    /*
    ?The SYS loop starts here
    */


    while(SYS_MainLoop()) {
        /*
        ?Reset system for restart of the game
        */


        while(reset ==1){
            enemyCounter = 0;
            level = 0;
            score =0;
            gameend =0;
            win =0;
            Falcon.xposition = 300;
            Falcon.yposition = 240;
            Falcon.xsize = 20;
            Falcon.ysize = 24;
            Falcon.power = 0;
            Falcon.speed=5;
            powerUp.active =0;
            for (int i = 0; i < count; i++) {
                bulletCount.box[i].active = 0;
            }
            for (int i = 0; i < sizeOfEnemies; i++) {
                enemyCount.ennemybase[i].active = 0;
            }
            reset =0;
        }
    /*
    ?main menu loop starts here
    */



    while(MenuSystem.start ==1){
        struct buttoncollisions credits ={400,300,120,64};
        struct buttoncollisions music ={100,300,120,64};
        struct buttoncollisions back ={240,300,120,64};
        WPAD_ScanPads();
        ir_t ir;
        WPAD_IR(0, &ir);
        u32 pressed = WPAD_ButtonsDown(0);
        GRRLIB_SetBackgroundColour(0x3C, 0x00, 0x61, 0xFF);
        


        /*
        ?menu sections
        */

        if(mainMenu ==1){
        GRRLIB_PrintfTTF(270,140,font,"Avuari",30,0xFFFFFFFF);
        GRRLIB_PrintfTTF(180,210,font,"Use the pointer to go into the menus",22,0xFFFFFFFF);
        GRRLIB_PrintfTTF(180,240,font,"To Start : press + on remote",22,0xFFFFFFFF);
        GRRLIB_DrawImg(400, 300, button, 0, 2, 2, 0xFFFFFFFF);
        GRRLIB_PrintfTTF(420,320,font,"Information",18,0xFFFFFFFF);
        GRRLIB_DrawImg(100, 300, button, 0, 2, 2, 0xFFFFFFFF);
        GRRLIB_PrintfTTF(110,320,font,"Music(On/Off)",18,0xFFFFFFFF);
        if(pressed & WPAD_BUTTON_A){
            if(GRRLIB_RectOnRect(credits.xposition,credits.yposition,credits.xsize,credits.ysize,ir.x, ir.y, 20, 20)){
                mainMenu =0;
                creditsMenu =1;
            }
            if(GRRLIB_RectOnRect(music.xposition,music.yposition,music.xsize,music.ysize,ir.x, ir.y, 20, 20)){
                if(musicActivation ==1){
                    
                    GRRMOD_Pause();
                }
                else{
                    
                    GRRMOD_Start();
                }
            }
        }
        if(pressed & WPAD_BUTTON_PLUS){
            MenuSystem.start = 0;
            MenuSystem.game =1;
            break;
        }
        }
        if(creditsMenu ==1){
        GRRLIB_PrintfTTF(135,60,font,"Controls:",18,0xFFFFFFFF);
        GRRLIB_PrintfTTF(135,80,font,"2: Shoot",18,0xFFFFFFFF);
        GRRLIB_PrintfTTF(135,100,font,"1:Speed Boost",18,0xFFFFFFFF);
        GRRLIB_PrintfTTF(135,120,font,"Dpad :Move",18,0xFFFFFFFF);
        GRRLIB_PrintfTTF(135,150,font,"Everything except the GRRLIB engine was made by me",18,0xFFFFFFFF);
        GRRLIB_PrintfTTF(135,170,font,"ColdHorizon",18,0xFFFFFFFF);



        GRRLIB_DrawImg(240, 300, button, 0, 2, 2, 0xFFFFFFFF);
        GRRLIB_PrintfTTF(285,320,font,"Back",20,0xFFFFFFFF);
        if(pressed & WPAD_BUTTON_A){
            if(GRRLIB_RectOnRect(back.xposition,back.yposition,back.xsize,back.ysize,ir.x, ir.y, 20, 20)){
                mainMenu =1;
                creditsMenu =0;
            }
        }
        }
        if (ir.valid) {
            GRRLIB_Rectangle(ir.x, ir.y, 20, 20, 0xFF10F0FF, 1);
        }


        /*
        ?Homebrew Exit
        */


        if(pressed & WPAD_BUTTON_HOME){
            GRRLIB_FreeTTF(font);
            GRRMOD_End();
            GRRLIB_Exit();
            return 0;
        }
        GRRLIB_Render();
    }
     /*
     ?game loop starts here
     */



    while(MenuSystem.game ==1){
        
        WPAD_ScanPads();
        u32 pressed = WPAD_ButtonsDown(0);
        u32 hold = WPAD_ButtonsHeld(0);
        GRRLIB_SetBackgroundColour(0x10, 0x10, 0x10, 0xFF);
        //*GRRLIB_Rectangle(0,0,80,480,0xFFFF00FF, 1);
        //*GRRLIB_Rectangle(560,0,80,480,0xFFFF00FF, 1);
        GRRLIB_DrawImg(0,0,WallIMG,0,1,1,0xFFFFFFFF);
        GRRLIB_DrawImg(560,0,WallIMG,0,1,1,0xFFFFFFFF);
        //*GRRLIB_Rectangle(Falcon.xposition,Falcon.yposition,Falcon.xsize,Falcon.ysize,0x3333FFFF, 1);
        GRRLIB_DrawImg(Falcon.xposition, Falcon.yposition, FalconIMG, 0, 1, 1, 0xFFFFFFFF);
        sprintf(levelCounter,"level:%d",level);
        sprintf(scoreCounter,"score:%d",score);
        GRRLIB_PrintfTTF(5,40,font,levelCounter,20,0x000000FF);
        GRRLIB_PrintfTTF(5,80,font,scoreCounter,16,0x000000FF);
        /*
        ?Movement system
        */


        if(hold & WPAD_BUTTON_DOWN){
            if (Falcon.xposition >= 560 - Falcon.xsize){

            }
            else{
                Falcon.xposition+=Falcon.speed;
            }
            
        }
        else if(hold & WPAD_BUTTON_UP){
            if (Falcon.xposition <= 80){

            }
            else{
            Falcon.xposition-=Falcon.speed;
            }
        }

        if(hold & WPAD_BUTTON_RIGHT){
            if (Falcon.yposition <= 0){

            }
            else{
            Falcon.yposition-=Falcon.speed;
            }
        }
        else if(hold & WPAD_BUTTON_LEFT){
            if (Falcon.yposition >= 480 - Falcon.ysize){

            }
            else{
            Falcon.yposition+=Falcon.speed;
            }
        }
        /*
        ?Gun system
        */


        if(pressed & WPAD_BUTTON_2){
            int maxBullets = Falcon.power;
            int region = -8 * maxBullets;
            for(int i=0;i<maxBullets+1;i++){
                for(int j=0;j<count;j++){
                    if(bulletCount.box[j].active == 0){
                        struct bullet b = {Falcon.xposition+Falcon.xsize/3+region,(Falcon.yposition-Falcon.ysize/4)-5,8,12,10,1+Falcon.power,1};
                        bulletCount.box[j] = b;
                        break;
                    }
                }
                region +=15;
                
            }
            
        }
        /*
        ?Boost system
        */


        if(hold & WPAD_BUTTON_1){
            Falcon.speed = 10;
            
        }
        else{
            Falcon.speed = 5;
        }
        /*
        ?Bullet turn
        */


        for(int i=0;i<count;i++){
            if(bulletCount.box[i].active == 1){

                //*GRRLIB_Rectangle(bulletCount.box[i].xposition,bulletCount.box[i].yposition,bulletCount.box[i].bxsize + Falcon.power,bulletCount.box[i].bysize + (Falcon.power*2),0x0099FFFF, 1);
                GRRLIB_DrawImg(bulletCount.box[i].xposition,bulletCount.box[i].yposition,BulletIMG,0, 1, 1, 0xFFFFFFFF);
                for(int j =0;j<level;j++){
                    if(enemyCount.ennemybase[j].active==1){


                        if(GRRLIB_RectOnRect(enemyCount.ennemybase[j].xposition,enemyCount.ennemybase[j].yposition,enemyCount.ennemybase[j].xsize,enemyCount.ennemybase[j].ysize,
                            bulletCount.box[i].xposition,bulletCount.box[i].yposition,bulletCount.box[i].bxsize,bulletCount.box[i].bysize)){

                            enemyCount.ennemybase[j].health -= bulletCount.box[i].dmg;
                            bulletCount.box[i].active = 0;
                            if(enemyCount.ennemybase[j].health <= 0){
                                int object = 0;
                                enemyCount.ennemybase[j].active = 0;
                                object = rand() %(6 +1);
                                if(object == 6 && powerUp.active == 0){
                                    powerUp.xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize/2;
                                    powerUp.yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize/2;
                                    powerUp.xsize =12;
                                    powerUp.ysize=12;
                                    powerUp.speed=3;
                                    powerUp.active=1;
                                    powerUp.color=0xFFFF00FF;
                                }
                            }
                            break;
                        }
                    }
                    
                }
                bulletCount.box[i].yposition -= bulletCount.box[i].speed;
            if(bulletCount.box[i].yposition <= 0 || bulletCount.box[i].xposition <= 80 || bulletCount.box[i].xposition >= 560)
            {
                bulletCount.box[i].active = 0;
            }
            }
        }
        /*
        ?Enemy spawn
        */


        if(enemyCounter == 0){
            level++;
            if(level >= 51){
                win =1;
            }
            else
            {
                int boss =0;
                for(int i =0;i<level;i++)
                {
                    int enemytype;
                    enemytype = rand()%(10+1);
                    
                    if(level >= 5){
                        if((level == 10 || level == 20 || level == 30 || level == 40 || level == 50) && boss == 0){
                        struct ennemy typeZ = {(rand()%(540-100 + 1)+100)-50,(rand()%(-10-200 +1)-200),52,52,50,1,1,0,0x101010FF,'Z',TypeZIMG};
                        enemyCount.ennemybase[i] = typeZ;
                        boss = 1;
                        }
                        else if(enemytype == 10){
                            struct ennemy typeB = {(rand()%(540-100 + 1)+100)-30,(rand()%(-10-200 +1)-200),32,32,5,1,1,0,0x0000FFFF,'B',TypeBIMG};
                            enemyCount.ennemybase[i] = typeB;
                        }
                        else{
                            struct ennemy typeA = {(rand()%(540-100 + 1)+100)-20,(rand()%(-10-200 +1)-200),20,20,1,2,1,0,0xFF0000FF,'A',TypeAIMG};
                            enemyCount.ennemybase[i] = typeA;
                        }
                    }
                    else{
                        struct ennemy typeA = {(rand()%(540-100 + 1)+100)-20,(rand()%(-10-200 +1)-200),20,20,1,2,1,0,0xFF0000FF,'A',TypeAIMG};
                        enemyCount.ennemybase[i] = typeA;
                    }
                enemytype = 0;       
                enemyCounter++;
                }
            }
        }
        /*
        ?Enemy Turn
        */


        for(int i=0;i<level;i++){
            {
                
                if(enemyCount.ennemybase[i].active == 1)
                {
                    if(enemyCount.ennemybase[i].type == 'Z'){
                        //*GRRLIB_Rectangle(enemyCount.ennemybase[i].xposition,enemyCount.ennemybase[i].yposition,enemyCount.ennemybase[i].xsize,enemyCount.ennemybase[i].ysize,enemyCount.ennemybase[i].color, 1);
                        GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                        enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;  
                        if(enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition,enemyCount.ennemybase[i].yposition,enemyCount.ennemybase[i].xsize,enemyCount.ennemybase[i].ysize,
                        Falcon.xposition,Falcon.yposition,Falcon.xsize,Falcon.ysize) ){
                        gameend =1;
                        break;
                        }
                    }
                    else
                    {
                        //*GRRLIB_Rectangle(enemyCount.ennemybase[i].xposition,enemyCount.ennemybase[i].yposition,enemyCount.ennemybase[i].xsize,enemyCount.ennemybase[i].ysize,enemyCount.ennemybase[i].color, 1);
                        GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition,enemyCount.ennemybase[i].imgName , 0, 1, 1, 0xFFFFFFFF);
                        enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;  
                        if(enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(Falcon.xposition,Falcon.yposition,Falcon.xsize,Falcon.ysize,
                        enemyCount.ennemybase[i].xposition,enemyCount.ennemybase[i].yposition,enemyCount.ennemybase[i].xsize,enemyCount.ennemybase[i].ysize) ){
                        gameend =1;
                        break;
                        }
                    }
                }
                else if(enemyCount.ennemybase[i].dead == 0){
                    enemyCount.ennemybase[i].dead = 1;
                    enemyCounter-=1;
                    if(enemyCount.ennemybase[i].type == 'Z'){
                        score += 10;
                    }
                    else if(enemyCount.ennemybase[i].type == 'B'){
                        score += 5;
                    }
                    else{
                        score+=1;
                    }
                }
                

            }
        }
        /*
        ?Power Up Turn
        */


        if (powerUp.active ==1){
            //*GRRLIB_Rectangle(powerUp.xposition,powerUp.yposition,powerUp.xsize,powerUp.ysize,powerUp.color,1);
            GRRLIB_DrawImg(powerUp.xposition,powerUp.yposition,UpgradeIMG,0,1,1,0xFFFFFFFF);
            powerUp.yposition += powerUp.speed;
            if(GRRLIB_RectOnRect(Falcon.xposition,Falcon.yposition,Falcon.xsize,Falcon.ysize,
            powerUp.xposition,powerUp.yposition,powerUp.xsize,powerUp.ysize) ){
                powerUp.active =0;
                if(Falcon.power ==3){
                score +=5;
                }
                else{
                Falcon.power +=1;
                }
                
            }
            if(powerUp.yposition >=480){
                powerUp.active=0;
            }
        }
        /*
        ?Win and lose conditions
        */


        if(win ==1){
            MenuSystem.game =0;
            MenuSystem.win =1;
            break;
        }
        if(gameend ==1){
            MenuSystem.game =0;
            MenuSystem.gameover =1;
            break;
        }
        /*
        ?Homebrew Exit
        */


        if(pressed & WPAD_BUTTON_HOME){
            GRRLIB_FreeTTF(font);
            GRRMOD_End();
            GRRLIB_Exit();
            return 0;
        }
        GRRLIB_Render();
        }
         /*
         ?game over loop starts here
         */




        while(MenuSystem.gameover ==1){
            WPAD_ScanPads();
            u32 pressed = WPAD_ButtonsDown(0);
            GRRLIB_SetBackgroundColour(0x64, 0x00, 0x00, 0xFF);
            GRRLIB_PrintfTTF(280,220,font,"GAME OVER",30,0xFFFFFFFF);
            sprintf(scoreCounter,"score:%d",score);
            GRRLIB_PrintfTTF(280,260,font,scoreCounter,30,0xFFFFFFFF);
            GRRLIB_PrintfTTF(200,300,font,"To Restart : press + on remote",22,0xFFFFFFFF);
            
            
            GRRLIB_Render();
            if(pressed & WPAD_BUTTON_PLUS){
            MenuSystem.gameover = 0;
            MenuSystem.start=1;
            reset =1;
            break;
            }
            /*
            ?Homebrew Exit
            */


            if(pressed & WPAD_BUTTON_HOME){
            GRRLIB_FreeTTF(font);
            GRRMOD_End();
            GRRLIB_Exit();
            return 0;
            }
        }
         /*
         ?win loop starts here
         */





        while(MenuSystem.win ==1){
            WPAD_ScanPads();
            u32 pressed = WPAD_ButtonsDown(0);
            GRRLIB_SetBackgroundColour(0xFF, 0xFF, 0x00, 0xFF);
            GRRLIB_PrintfTTF(280,220,font,"WIN",22,0xFFFFFFFF);
            sprintf(scoreCounter,"score:%d",score);
            GRRLIB_PrintfTTF(280,260,font,scoreCounter,30,0xFFFFFFFF);
            GRRLIB_PrintfTTF(200,300,font,"To Restart : press + on remote",22,0xFFFFFFFF);
            GRRLIB_Render();
            if(pressed & WPAD_BUTTON_PLUS){
            MenuSystem.win = 0;
            MenuSystem.start=1;
            reset =1;
            break;
            }
            /*
            ?Homebrew Exit
            */


            if(pressed & WPAD_BUTTON_HOME){
            GRRLIB_FreeTTF(font);
            GRRMOD_End();
            GRRLIB_Exit();
            return 0;
            }
        }
    }
    GRRLIB_FreeTTF(font);
    GRRMOD_End();
    GRRLIB_Exit();
    return 0;
}