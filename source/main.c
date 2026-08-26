#include <grrlib.h>
#include <gccore.h>
#include <grrmod.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include "OlivettiThin_ttf.h"
#include "expo_it.h"
#include "button_png.h"
#include "buttonS_png.h"
#include "Falcon_png.h"
#include "FalconS_png.h"
#include "Falcon3_png.h"
#include "Falcon7_png.h"
#include "Falcon9_png.h"
#include "TypeA_png.h"
#include "TypeB_png.h"
#include "TypeC_png.h"
#include "TypeD_png.h"
#include "TypeE_png.h"
#include "TypeE2_png.h"
#include "TypeF_png.h"
#include "TypeX_png.h"
#include "TypeZ_png.h"
#include "Wall_png.h"
#include "Upgrade_png.h"
#include "Points_png.h"
#include "Bullet_png.h"
#include "Bullet2_png.h"
#include "BulletUltimate_png.h"
#include "Star_png.h"
/*
?Creation of the object items
*/

struct player
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    int power;
    int speed;
    int life;
    time_t ability;
};
struct bullet
{
    int xposition;
    int yposition;
    int bxsize;
    int bysize;
    int speed;
    int dmg;
    int active;
    char type;
    GRRLIB_texImg *bulletName;
};
struct ennemy
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    int health;
    int speed;
    int speedY;
    int active;
    int dead;
    u32 color;
    char type;
    GRRLIB_texImg *imgName;
    time_t time;
};
struct upgrade
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    float speed;
    float deacceleration;
    int magnetised;
    int active;
    u32 color;
    char upgradeType;
    GRRLIB_texImg *upgradeName;
};
struct bulletCount
{
    struct bullet box[100];
    struct bullet ennemyBox[100];
};
struct storage
{
    struct ennemy ennemybase[51];
    struct upgrade itemsBox[100];
    // level 51 breaks game change or keep
};
struct levelSystem
{
    int start;
    int game;
    int gameover;
    int win;
};
struct buttoncollisions
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
};
struct star
{
    int xposition;
    int yposition;
    int size;
    int active;
};
struct sky
{
    struct star starrySky[20];
};
void stars();
void bullet();
void enemy();
void enemyTurn();
void enemyBullet();
void powerUpTurn();
void falconSkins();

/*
?This is the main loop
*/

int main(int argc, char **argv)
{
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

    GRRLIB_ttfFont *font = GRRLIB_LoadTTF(OlivettiThin_ttf, OlivettiThin_ttf_size);
    GRRLIB_texImg *button = GRRLIB_LoadTexture(button_png);
    GRRLIB_texImg *buttonS = GRRLIB_LoadTexture(buttonS_png);
    GRRLIB_texImg *FalconIMG = GRRLIB_LoadTexture(Falcon_png);
    GRRLIB_texImg *Falcon4IMG = GRRLIB_LoadTexture(Falcon_png);
    GRRLIB_texImg *Falcon3IMG = GRRLIB_LoadTexture(Falcon3_png);
    GRRLIB_texImg *Falcon7IMG = GRRLIB_LoadTexture(Falcon7_png);
    GRRLIB_texImg *Falcon9IMG = GRRLIB_LoadTexture(Falcon9_png);
    GRRLIB_texImg *FalconSIMG = GRRLIB_LoadTexture(FalconS_png);
    GRRLIB_texImg *TypeAIMG = GRRLIB_LoadTexture(TypeA_png);
    GRRLIB_texImg *TypeBIMG = GRRLIB_LoadTexture(TypeB_png);
    GRRLIB_texImg *TypeCIMG = GRRLIB_LoadTexture(TypeC_png);
    GRRLIB_texImg *TypeDIMG = GRRLIB_LoadTexture(TypeD_png);
    GRRLIB_texImg *TypeEIMG = GRRLIB_LoadTexture(TypeE_png);
    GRRLIB_texImg *TypeE2IMG = GRRLIB_LoadTexture(TypeE2_png);
    GRRLIB_texImg *TypeFIMG = GRRLIB_LoadTexture(TypeF_png);
    GRRLIB_texImg *TypeXIMG = GRRLIB_LoadTexture(TypeX_png);
    GRRLIB_texImg *TypeZIMG = GRRLIB_LoadTexture(TypeZ_png);
    GRRLIB_texImg *WallIMG = GRRLIB_LoadTexture(Wall_png);
    GRRLIB_texImg *UpgradeIMG = GRRLIB_LoadTexture(Upgrade_png);
    GRRLIB_texImg *PointsIMG = GRRLIB_LoadTexture(Points_png);
    GRRLIB_texImg *BulletIMG = GRRLIB_LoadTexture(Bullet_png);
    GRRLIB_texImg *Bullet2IMG = GRRLIB_LoadTexture(Bullet2_png);
    GRRLIB_texImg *BulletUltimateIMG = GRRLIB_LoadTexture(BulletUltimate_png);
    GRRLIB_texImg *StarIMG = GRRLIB_LoadTexture(Star_png);
    //changes the rotation spot
    GRRLIB_SetHandle(FalconIMG,10,12);
    GRRLIB_SetHandle(Falcon4IMG,10,12);
    GRRLIB_SetHandle(Falcon3IMG,10,12);
    GRRLIB_SetHandle(Falcon7IMG,10,12);
    GRRLIB_SetHandle(Falcon9IMG,10,12);
    GRRLIB_SetHandle(FalconSIMG,10,12);
    int falconSkin = 1;
    int musicActivation = 1;
    int mainMenu = 1;
    int creditsMenu = 0;
    int reset = 0;
    struct player Falcon;
    struct bulletCount bulletCount;
    struct storage enemyCount;
    struct sky space;
    struct levelSystem MenuSystem = {1, 0, 0, 0};
    int enemyCounter = 0;
    int level = 0;
    int score = 0;
    int win = 0;
    int gameend = 0;
    int timeValues = 1;
    char levelCounter[20];
    char scoreCounter[20];
    char lives[10];
    char skinName[20];
    sprintf(skinName, "Falcon 4");
    Falcon.xposition = 300;
    Falcon.yposition = 240;
    Falcon.xsize = 20;
    Falcon.ysize = 24;
    Falcon.power = 0;
    Falcon.speed = 5;
    Falcon.life = 10;
    Falcon.ability = time(NULL);
    int count = sizeof(bulletCount.box) / sizeof(bulletCount.box[0]);
    int starCounter = sizeof(space.starrySky) / sizeof(space.starrySky[0]);
    int sizeOfEnemies = sizeof(enemyCount.ennemybase) / sizeof(enemyCount.ennemybase[0]);
    int sizeOfItems = sizeof(enemyCount.itemsBox) / sizeof(enemyCount.itemsBox[0]);

    int skinRotation =0;
    //// DO NOT CHANGE THE BULLET AMOUNT BEFORE CHANGING THIS
    for (int i = 0; i < count; i++)
    {
        bulletCount.box[i].active = 0;
        bulletCount.ennemyBox[i].active = 0;
    }
    for (int i = 0; i < sizeOfEnemies; i++)
    {
        enemyCount.ennemybase[i].active = 0;
    }
    for (int i = 0; i < sizeOfItems; i++)
    {
        enemyCount.itemsBox[i].active = 0;
    }
    for (int i = 0; i < starCounter; i++)
    {
        struct star s = {(rand() % (540 - 80 + 1) + 80), rand() % (480 + 1), rand() % (2 + 1), 1};
        space.starrySky[i] = s;
    }

    /*
    ?Boss specific values
    */

    int placed = 0;
    int battleMode = 0;
    int attackMode = rand() % (3 + 1);
    int unit = rand() % (5 + 1);
    int cannon = rand() % (2 + 1);
    /*
    ?The SYS loop starts here
    */

    while (SYS_MainLoop())
    {
        /*
        ?Reset system for restart of the game
        */

        while (reset == 1)
        {
            skinRotation =0;
            enemyCounter = 0;
            level = 0;
            score = 0;
            gameend = 0;
            win = 0;
            Falcon.xposition = 300;
            Falcon.yposition = 240;
            Falcon.xsize = 20;
            Falcon.ysize = 24;
            Falcon.power = 0;
            Falcon.speed = 5;
            Falcon.life = 10;
            timeValues = 1;
            for (int i = 0; i < count; i++)
            {
                bulletCount.box[i].active = 0;
                bulletCount.ennemyBox[i].active = 0;
            }
            for (int i = 0; i < sizeOfEnemies; i++)
            {
                enemyCount.ennemybase[i].active = 0;
            }
            for (int i = 0; i < sizeOfItems; i++)
            {
                enemyCount.itemsBox[i].active = 0;
            }
            for (int i = 0; i < starCounter; i++)
            {
                struct star s = {(rand() % (540 - 80 + 1) + 80), rand() % (480 + 1), rand() % (2 + 1), 1};
                space.starrySky[i] = s;
            }
            reset = 0;
            placed = 0;
            battleMode = 0;
            attackMode = rand() % (3 + 1);
            unit = rand() % (5 + 1);
            cannon = rand() % (2 + 1);
        }
        /*
        ?main menu loop starts here
        */

        while (MenuSystem.start == 1)
        {
            struct buttoncollisions credits = {400, 300, 120, 64};
            struct buttoncollisions music = {100, 300, 120, 64};
            struct buttoncollisions back = {240, 300, 120, 64};
            struct buttoncollisions plus = {350, 400, 64, 64};
            struct buttoncollisions minus = {200, 400, 64, 64};
            WPAD_ScanPads();
            ir_t ir;
            WPAD_IR(0, &ir);
            u32 pressed = WPAD_ButtonsDown(0);
            GRRLIB_SetBackgroundColour(0x3C, 0x00, 0x61, 0xFF);

            /*
            ?menu sections
            */

            if (mainMenu == 1)
            {
                GRRLIB_PrintfTTF(270, 140, font, "Avuari", 30, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(180, 210, font, "Use the pointer to go into the menus", 22, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(180, 240, font, "To Start : press + on remote", 22, 0xFFFFFFFF);
                GRRLIB_DrawImg(400, 300, button, 0, 2, 2, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(420, 320, font, "Information", 18, 0xFFFFFFFF);
                GRRLIB_DrawImg(100, 300, button, 0, 2, 2, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(110, 320, font, "Music(On/Off)", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(520, 440, font, "Version 1.30", 16, 0xFFFFFFFF);
                GRRLIB_DrawImg(200, 400, buttonS, 0, 2, 2, 0xFFFFFFFF);
                GRRLIB_DrawImg(350, 400, buttonS, 0, 2, 2, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(370, 395, font, "+", 50, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(220, 395, font, "-", 50, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(270, 350, font, "Change Skin", 16, 0xFFFFFFFF);
                GRRLIB_DrawImg(295, 420, FalconIMG, skinRotation, 1.5, 1.5, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(280, 390, font, skinName, 16, 0xFFFFFFFF);


                void falconSkins(){
                    switch (falconSkin)
                    {
                    case 1:
                        FalconIMG = Falcon4IMG;
                        sprintf(skinName, "Falcon 4");
                        break;
                    case 2:
                        FalconIMG = Falcon3IMG;
                        sprintf(skinName, "Falcon 3");
                        break;
                    case 3:
                        FalconIMG = Falcon7IMG;
                        sprintf(skinName, "Falcon 7");
                        break;
                    case 4:
                        FalconIMG = Falcon9IMG;
                        sprintf(skinName, "Falcon 9");
                        break;
                    case 5:
                        FalconIMG = FalconSIMG;
                        sprintf(skinName, "Falcon S");
                        break;
                    }
                }


                if (pressed & WPAD_BUTTON_A)
                {
                    if (GRRLIB_RectOnRect(credits.xposition, credits.yposition, credits.xsize, credits.ysize, ir.x, ir.y, 20, 20))
                    {
                        mainMenu = 0;
                        creditsMenu = 1;
                    }
                    if (GRRLIB_RectOnRect(music.xposition, music.yposition, music.xsize, music.ysize, ir.x, ir.y, 20, 20))
                    {
                        if (musicActivation == 1)
                        {

                            GRRMOD_Pause();
                        }
                        else
                        {

                            GRRMOD_Start();
                        }
                    }
                    if (GRRLIB_RectOnRect(plus.xposition, plus.yposition, plus.xsize, plus.ysize, ir.x, ir.y, 20, 20) && falconSkin <= 4)
                    {
                        falconSkin += 1;
                        falconSkins();
                    }
                    if (GRRLIB_RectOnRect(minus.xposition, minus.yposition, minus.xsize, minus.ysize, ir.x, ir.y, 20, 20) && falconSkin >= 2)
                    {
                        falconSkin -= 1;
                        falconSkins();
                    }
                }

                if(skinRotation != 360){
                    skinRotation++;
                }
                else
                {
                    skinRotation = 0;
                }

                if (pressed & WPAD_BUTTON_PLUS)
                {
                    MenuSystem.start = 0;
                    MenuSystem.game = 1;
                    break;
                }
            }
            if (creditsMenu == 1)
            {
                GRRLIB_PrintfTTF(135, 60, font, "Controls:", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(135, 80, font, "2: Shoot", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(135, 100, font, "1:Speed Boost", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(135, 120, font, "B:Ultimate when ready", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(135, 140, font, "Dpad :Move", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(135, 170, font, "Everything except the GRRLIB engine was made by me", 18, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(135, 190, font, "ColdHorizon", 18, 0xFFFFFFFF);

                GRRLIB_DrawImg(240, 300, button, 0, 2, 2, 0xFFFFFFFF);
                GRRLIB_PrintfTTF(285, 320, font, "Back", 20, 0xFFFFFFFF);
                if (pressed & WPAD_BUTTON_A)
                {
                    if (GRRLIB_RectOnRect(back.xposition, back.yposition, back.xsize, back.ysize, ir.x, ir.y, 20, 20))
                    {
                        mainMenu = 1;
                        creditsMenu = 0;
                    }
                }
            }
            if (ir.valid)
            {
                GRRLIB_Rectangle(ir.x, ir.y, 20, 20, 0xFF10F0FF, 1);
            }

            /*
            ?Falcon Skins
            */

            

            /*
            ?Homebrew Exit
            */

            if (pressed & WPAD_BUTTON_HOME)
            {
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

        while (MenuSystem.game == 1)
        {
            void stars()
            {
                for (int i = 0; i < starCounter; i++)
                {
                    if (space.starrySky[i].active == 1)
                    {
                        GRRLIB_DrawImg(space.starrySky[i].xposition, space.starrySky[i].yposition, StarIMG, 0, space.starrySky[i].size, space.starrySky[i].size, 0xFFFFFFCC);
                        space.starrySky[i].yposition += 1;
                        if (space.starrySky[i].yposition >= 500)
                        {
                            space.starrySky[i].active = 0;
                        }
                    }
                    else
                    {
                        struct star s = {(rand() % (540 - 80 + 1) + 80), rand() % (-50 + 1) - 70, rand() % (2 + 1), 1};
                        space.starrySky[i] = s;
                    }
                }
            }
            void bullet()
            {
                for (int i = 0; i < count; i++)
                {
                    if (bulletCount.box[i].active == 1)
                    {

                        if (bulletCount.box[i].type == 'U')
                        {
                            GRRLIB_DrawImg(bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bulletName, 0, 4, 4, 0xFFFFFFFF);
                            for (int j = 0; j < level; j++)
                            {
                                if (enemyCount.ennemybase[j].active == 1)
                                {
                                    if (enemyCount.ennemybase[j].ysize <= bulletCount.box[i].bysize)
                                    {
                                        if (GRRLIB_RectOnRect(bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bxsize, bulletCount.box[i].bysize,
                                                              enemyCount.ennemybase[j].xposition, enemyCount.ennemybase[j].yposition, enemyCount.ennemybase[j].xsize, enemyCount.ennemybase[j].ysize))
                                        {
                                            if (enemyCount.ennemybase[j].type == 'X')
                                            {
                                                enemyCount.ennemybase[j].health -= 100;
                                                bulletCount.box[i].active = 0;
                                            }
                                            else
                                            {
                                                enemyCount.ennemybase[j].active = 0;
                                                enemyCount.ennemybase[j].health = 0;
                                            }
                                            if (enemyCount.ennemybase[j].health <= 0)
                                            {
                                                int object = 0;
                                                enemyCount.ennemybase[j].active = 0;
                                                object = rand() % (6 + 1);
                                                
                                                for(int u =0; u <sizeOfItems;u++){
                                                    if(enemyCount.itemsBox[u].active ==0){
                                                        switch(object){
                                                        case 6:
                                                            enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize / 2;
                                                            enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize / 2;
                                                            enemyCount.itemsBox[u].xsize = 12;
                                                            enemyCount.itemsBox[u].ysize = 12;
                                                            enemyCount.itemsBox[u].speed = -5;
                                                            enemyCount.itemsBox[u].deacceleration = 0.25f;
                                                            enemyCount.itemsBox[u].magnetised =0;
                                                            enemyCount.itemsBox[u].active = 1;
                                                            enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                                            enemyCount.itemsBox[u].upgradeType = 'D';
                                                            enemyCount.itemsBox[u].upgradeName = UpgradeIMG;
                                                        break;

                                                        case 5:
                                                            enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize / 2;
                                                            enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize / 2;
                                                            enemyCount.itemsBox[u].xsize = 12;
                                                            enemyCount.itemsBox[u].ysize = 12;
                                                            enemyCount.itemsBox[u].speed = -5;
                                                            enemyCount.itemsBox[u].deacceleration = 0.25f;
                                                            enemyCount.itemsBox[u].magnetised =0;
                                                            enemyCount.itemsBox[u].active = 1;
                                                            enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                                            enemyCount.itemsBox[u].upgradeType = 'P';
                                                            enemyCount.itemsBox[u].upgradeName = PointsIMG;
                                                        break;

                                                        default:
                                                        break;

                                                        }
                                                        break;
                                                        
                                                        
                                                    }
                                                    
                                                }
                                                    
                                                
                                            }
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        if (GRRLIB_RectOnRect(enemyCount.ennemybase[j].xposition, enemyCount.ennemybase[j].yposition, enemyCount.ennemybase[j].xsize, enemyCount.ennemybase[j].ysize,
                                                              bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bxsize, bulletCount.box[i].bysize))
                                        {
                                            if (enemyCount.ennemybase[j].type == 'X')
                                            {
                                                enemyCount.ennemybase[j].health -= 100;
                                                bulletCount.box[i].active = 0;
                                            }
                                            else
                                            {
                                                enemyCount.ennemybase[j].active = 0;
                                                enemyCount.ennemybase[j].health = 0;
                                            }
                                            if (enemyCount.ennemybase[j].health <= 0)
                                            {
                                                int object = 0;
                                                enemyCount.ennemybase[j].active = 0;
                                                object = rand() % (6 + 1);
                                                for(int u =0; u <sizeOfItems;u++){
                                                    if(enemyCount.itemsBox[u].active ==0){
                                                        switch(object){
                                                        case 6:
                                                            enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize / 2;
                                                            enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize / 2;
                                                            enemyCount.itemsBox[u].xsize = 12;
                                                            enemyCount.itemsBox[u].ysize = 12;
                                                            enemyCount.itemsBox[u].speed = -5;
                                                            enemyCount.itemsBox[u].deacceleration = 0.25f;
                                                            enemyCount.itemsBox[u].magnetised =0;
                                                            enemyCount.itemsBox[u].active = 1;
                                                            enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                                            enemyCount.itemsBox[u].upgradeType = 'D';
                                                            enemyCount.itemsBox[u].upgradeName = UpgradeIMG;
                                                        break;

                                                        case 5:
                                                            enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize / 2;
                                                            enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize / 2;
                                                            enemyCount.itemsBox[u].xsize = 12;
                                                            enemyCount.itemsBox[u].ysize = 12;
                                                            enemyCount.itemsBox[u].speed = -5;
                                                            enemyCount.itemsBox[u].deacceleration = 0.25f;
                                                            enemyCount.itemsBox[u].magnetised =0;
                                                            enemyCount.itemsBox[u].active = 1;
                                                            enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                                            enemyCount.itemsBox[u].upgradeType = 'P';
                                                            enemyCount.itemsBox[u].upgradeName = PointsIMG;
                                                        break;

                                                        default:
                                                        break;

                                                        }
                                                        break;
                                                        
                                                        
                                                    }
                                                    
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {

                            GRRLIB_DrawImg(bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bulletName, 0, 1, 1, 0xFFFFFFFF);
                            for (int j = 0; j < level; j++)
                            {
                                if (enemyCount.ennemybase[j].active == 1)
                                {

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[j].xposition, enemyCount.ennemybase[j].yposition, enemyCount.ennemybase[j].xsize, enemyCount.ennemybase[j].ysize,
                                                          bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bxsize, bulletCount.box[i].bysize))
                                    {

                                        enemyCount.ennemybase[j].health -= bulletCount.box[i].dmg;
                                        bulletCount.box[i].active = 0;
                                        if (enemyCount.ennemybase[j].health <= 0)
                                        {
                                            int object = 0;
                                            enemyCount.ennemybase[j].active = 0;
                                            object = rand() % (6 + 1);
                                            for(int u =0; u <sizeOfItems;u++){
                                                    if(enemyCount.itemsBox[u].active ==0){
                                                        switch(object){
                                                        case 6:
                                                            enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize / 2;
                                                            enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize / 2;
                                                            enemyCount.itemsBox[u].xsize = 12;
                                                            enemyCount.itemsBox[u].ysize = 12;
                                                            enemyCount.itemsBox[u].speed = -5;
                                                            enemyCount.itemsBox[u].deacceleration = 0.25f;
                                                            enemyCount.itemsBox[u].magnetised =0;
                                                            enemyCount.itemsBox[u].active = 1;
                                                            enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                                            enemyCount.itemsBox[u].upgradeType = 'D';
                                                            enemyCount.itemsBox[u].upgradeName = UpgradeIMG;
                                                        break;

                                                        case 5:
                                                            enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[j].xposition + enemyCount.ennemybase[j].xsize / 2;
                                                            enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[j].yposition + enemyCount.ennemybase[j].ysize / 2;
                                                            enemyCount.itemsBox[u].xsize = 12;
                                                            enemyCount.itemsBox[u].ysize = 12;
                                                            enemyCount.itemsBox[u].speed = -5;
                                                            enemyCount.itemsBox[u].deacceleration = 0.25f;
                                                            enemyCount.itemsBox[u].magnetised =0;
                                                            enemyCount.itemsBox[u].active = 1;
                                                            enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                                            enemyCount.itemsBox[u].upgradeType = 'P';
                                                            enemyCount.itemsBox[u].upgradeName = PointsIMG;
                                                        break;

                                                        default:
                                                        break;

                                                        }
                                                        break;
                                                        
                                                    }
                                                    
                                                }
                                        }

                                        break;
                                    }
                                }
                            }
                        }
                        bulletCount.box[i].yposition -= bulletCount.box[i].speed;
                        if (bulletCount.box[i].yposition <= 0 || bulletCount.box[i].xposition <= 80 || bulletCount.box[i].xposition >= 560)
                        {
                            bulletCount.box[i].active = 0;
                        }
                    }
                }
            }
            void enemy()
            {
                if (enemyCounter == 0)
                {
                    level++;
                    if (level >= 52)
                    {
                        win = 1;
                    }
                    else if (level == 51)
                    {
                        struct ennemy typeX = {120, -150, 400, 100, 4000, 1, 1, 1, 0, 0xFF0000FF, 'X', TypeXIMG, time(NULL)};
                        enemyCount.ennemybase[0] = typeX;
                        enemyCounter = 10;
                    }
                    else
                    {
                        int boss = 0;
                        for (int i = 0; i < level; i++)
                        {
                            int enemytype;
                            enemytype = rand() % (10 + 1);

                            /*
                            ?Level 40
                            */

                            if (level >= 40)
                            {
                                if ((level == 10 || level == 20 || level == 30 || level == 40 || level == 50) && boss == 0)
                                {
                                    struct ennemy typeZ = {(rand() % (488 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 52, 52, 50, 1, 1, 1, 0, 0x101010FF, 'Z', TypeZIMG, time(NULL)};
                                    enemyCount.ennemybase[i] = typeZ;
                                    boss = 1;
                                }
                                else
                                {
                                    switch(enemytype){
                                        case 10:

                                        struct ennemy typeF = {(rand() % (508 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 32, 32, 20, 1, 1, 1, 0, 0x0000FFFF, 'F', TypeFIMG, time(NULL)};
                                        enemyCount.ennemybase[i] = typeF;

                                        break;

                                        case 9:

                                        int side = rand() % (2 + 1);
                                        if (side == 1)
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, 2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }
                                        else
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, -2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }

                                        break;

                                        case 8:

                                            struct ennemy typeD = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 20, 4, 4, 1, 0, 0xFF0000FF, 'D', TypeDIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeD;

                                        break;

                                        case 7:

                                            struct ennemy typeE = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 32, 1000, 6, 2, 1, 0, 0xFF0000FF, 'E', TypeEIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeE;

                                        break;

                                        default:

                                            struct ennemy typeA = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 2, 2, 1, 0, 0xFF0000FF, 'A', TypeAIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeA;

                                        break;


                                    }
                                    
                                }
                            }

                            /*
                            ?Level 30
                            */

                            else if (level >= 30)
                            {
                                if ((level == 10 || level == 20 || level == 30 || level == 40 || level == 50) && boss == 0)
                                {
                                    struct ennemy typeZ = {(rand() % (488 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 52, 52, 50, 1, 1, 1, 0, 0x101010FF, 'Z', TypeZIMG, time(NULL)};
                                    enemyCount.ennemybase[i] = typeZ;
                                    boss = 1;
                                }
                                else
                                {
                                    switch(enemytype){
                                        case 10:

                                            struct ennemy typeB = {(rand() % (508 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 32, 32, 5, 1, 1, 1, 0, 0x0000FFFF, 'B', TypeBIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeB;

                                        break;

                                        case 9:

                                        int side = rand() % (2 + 1);
                                        if (side == 1)
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, 2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }
                                        else
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, -2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }

                                        break;

                                        case 8:

                                            struct ennemy typeD = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 20, 4, 4, 1, 0, 0xFF0000FF, 'D', TypeDIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeD;

                                        break;

                                        case 7:

                                            struct ennemy typeE = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 32, 1000, 6, 2, 1, 0, 0xFF0000FF, 'E', TypeEIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeE;

                                        break;

                                        default:

                                            struct ennemy typeA = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 2, 2, 1, 0, 0xFF0000FF, 'A', TypeAIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeA;

                                        break;
                                    }
                                }
                                
                            }

                            /*
                            ?Level 20
                            */

                            else if (level >= 20)
                            {
                                if ((level == 10 || level == 20 || level == 30 || level == 40 || level == 50) && boss == 0)
                                {
                                    struct ennemy typeZ = {(rand() % (488 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 52, 52, 50, 1, 1, 1, 0, 0x101010FF, 'Z', TypeZIMG, time(NULL)};
                                    enemyCount.ennemybase[i] = typeZ;
                                    boss = 1;
                                }
                                else 
                                {
                                    switch(enemytype){
                                        case 10:

                                            struct ennemy typeB = {(rand() % (508 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 32, 32, 5, 1, 1, 1, 0, 0x0000FFFF, 'B', TypeBIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeB;

                                        break;

                                        case 9:

                                        int side = rand() % (2 + 1);
                                        if (side == 1)
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, 2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }
                                        else
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, -2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }

                                        break;

                                        case 8:

                                            struct ennemy typeD = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 20, 4, 4, 1, 0, 0xFF0000FF, 'D', TypeDIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeD;

                                        break;

                                        default:

                                            struct ennemy typeA = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 2, 2, 1, 0, 0xFF0000FF, 'A', TypeAIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeA;

                                        break;
                                    }
                                }
                                    
                            }

                            /*
                            ?Level 10
                            */

                            else if (level >= 10)
                            {
                                if ((level == 10 || level == 20 || level == 30 || level == 40 || level == 50) && boss == 0)
                                {
                                    struct ennemy typeZ = {(rand() % (488 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 52, 52, 50, 1, 1, 1, 0, 0x101010FF, 'Z', TypeZIMG, time(NULL)};
                                    enemyCount.ennemybase[i] = typeZ;
                                    boss = 1;
                                }
                                else 
                                {
                                    switch(enemytype){
                                        case 10:

                                            struct ennemy typeB = {(rand() % (508 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 32, 32, 5, 1, 1, 1, 0, 0x0000FFFF, 'B', TypeBIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeB;

                                        break;

                                        case 9:

                                        int side = rand() % (2 + 1);
                                        if (side == 1)
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, 2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }
                                        else
                                        {
                                            struct ennemy typeC = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 4, -2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeC;
                                        }

                                        break;

                                        default:

                                            struct ennemy typeA = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 2, 2, 1, 0, 0xFF0000FF, 'A', TypeAIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeA;

                                        break;
                                    }
                                }
                            }

                            /*
                            ?Level 5
                            */

                            else if (level >= 5)
                            {
                                switch(enemytype){
                                        case 10:

                                            struct ennemy typeB = {(rand() % (508 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 32, 32, 5, 1, 1, 1, 0, 0x0000FFFF, 'B', TypeBIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeB;

                                        break;

                                        default:

                                            struct ennemy typeA = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 2, 2, 1, 0, 0xFF0000FF, 'A', TypeAIMG, time(NULL)};
                                            enemyCount.ennemybase[i] = typeA;

                                        break;
                                }
                                

                            }
                            else
                            {
                                struct ennemy typeA = {(rand() % (540 - 80 + 1) + 80), (rand() % (-10 - 200 + 1) - 200), 20, 20, 1, 2, 2, 1, 0, 0xFF0000FF, 'A', TypeAIMG, time(NULL)};
                                enemyCount.ennemybase[i] = typeA;
                            }

                            enemytype = 0;
                            enemyCounter++;
                        }
                    }
                }
            }
            void enemyTurn()
            {
                for (int i = 0; i < level; i++)
                {
                    {
                        if (enemyCount.ennemybase[i].active == 1)
                        {
                            switch (enemyCount.ennemybase[i].type)
                            {

                            case 'Z':
                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                if (enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                   Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }
                                break;
                            case 'B':
                            GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                if (enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                   Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }   


                            break;

                            case 'C':
                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;
                                if (enemyCount.ennemybase[i].xposition <= 80 || enemyCount.ennemybase[i].xposition >= 540)
                                {
                                    if (enemyCount.ennemybase[i].speedY == 2)
                                    {
                                        enemyCount.ennemybase[i].speedY = -2;
                                    }
                                    else
                                    {
                                        enemyCount.ennemybase[i].speedY = 2;
                                    }
                                }
                                enemyCount.ennemybase[i].xposition += enemyCount.ennemybase[i].speedY;
                                if (enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                   Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }
                                break;

                            case 'D':
                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                if (enemyCount.ennemybase[i].yposition < Falcon.yposition)
                                {
                                    enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;
                                }
                                else if (enemyCount.ennemybase[i].yposition > Falcon.yposition)
                                {
                                    enemyCount.ennemybase[i].yposition -= enemyCount.ennemybase[i].speed;
                                }

                                if (enemyCount.ennemybase[i].xposition < Falcon.xposition)
                                {
                                    enemyCount.ennemybase[i].xposition += enemyCount.ennemybase[i].speed;
                                }
                                else if (enemyCount.ennemybase[i].xposition > Falcon.xposition)
                                {
                                    enemyCount.ennemybase[i].xposition -= enemyCount.ennemybase[i].speed;
                                }

                                if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                                      enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }
                                break;

                            case 'E':

                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;
                                if (enemyCount.ennemybase[i].xposition < Falcon.xposition)
                                {
                                    enemyCount.ennemybase[i].xposition += enemyCount.ennemybase[i].speedY;
                                }
                                else if (enemyCount.ennemybase[i].xposition > Falcon.xposition)
                                {
                                    enemyCount.ennemybase[i].xposition -= enemyCount.ennemybase[i].speedY;
                                }

                                if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                                      enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }
                                if (enemyCount.ennemybase[i].yposition >= 550)
                                {
                                    enemyCount.ennemybase[i].active = 0;
                                }
                                break;

                            case 'F':
                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                if (difftime(time(NULL), enemyCount.ennemybase[i].time) >= 2)
                                {
                                    for (int j = 0; j < count; j++)
                                    {
                                        if (bulletCount.ennemyBox[j].active == 0)
                                        {
                                            struct bullet ennemyBullet = {(enemyCount.ennemybase[i].xposition + enemyCount.ennemybase[i].xsize / 2), (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4, 1, 1,'E',Bullet2IMG};
                                            bulletCount.ennemyBox[j] = ennemyBullet;
                                            break;
                                        }
                                    }
                                    enemyCount.ennemybase[i].time = time(NULL);
                                }

                                if (enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                   Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }
                                break;

                            case 'X':
                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 4, 4, 0xFFFFFFFF);
                                if (enemyCount.ennemybase[i].yposition <= -10 && placed == 0)
                                {
                                    enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;
                                }
                                else
                                {
                                    placed = 1;
                                }
                                if (placed == 1 && battleMode == 0)
                                {
                                    placed = 0;
                                    enemyCount.ennemybase[i].time = time(NULL);
                                    battleMode = 1;
                                }
                                if (battleMode == 1)
                                {
                                    if (difftime(time(NULL), enemyCount.ennemybase[i].time) >= 2)
                                    {
                                        switch (attackMode)
                                        {
                                        case 1:
                                            for (int b = 0; b < level; b++)
                                            {
                                                int spawn;
                                                if (cannon == 1)
                                                {
                                                    spawn = 120;
                                                }
                                                else
                                                {
                                                    spawn = 480;
                                                }
                                                if (enemyCount.ennemybase[b].active == 0)
                                                {
                                                    if (unit == 1)
                                                    {
                                                        struct ennemy typeZ = {spawn, 170, 52, 52, 50, 1, 1, 1, 0, 0x101010FF, 'Z', TypeZIMG, time(NULL)};
                                                        enemyCount.ennemybase[b] = typeZ;
                                                    }
                                                    else if (unit == 2)
                                                    {
                                                        struct ennemy typeF = {spawn, 132, 32, 32, 20, 1, 1, 1, 0, 0x0000FFFF, 'F', TypeFIMG, time(NULL)};
                                                        enemyCount.ennemybase[b] = typeF;
                                                    }
                                                    else if (unit == 3)
                                                    {

                                                        struct ennemy typeC = {spawn, 120, 20, 20, 1, 4, 2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                                        enemyCount.ennemybase[b] = typeC;
                                                    }
                                                    else if (unit == 4)
                                                    {
                                                        struct ennemy typeD = {spawn, 120, 20, 20, 20, 4, 4, 1, 0, 0xFF0000FF, 'D', TypeDIMG, time(NULL)};
                                                        enemyCount.ennemybase[b] = typeD;
                                                    }
                                                    else
                                                    {
                                                        struct ennemy typeC = {spawn, 120, 20, 20, 1, 4, -2, 1, 0, 0xFF0000FF, 'C', TypeCIMG, time(NULL)};
                                                        enemyCount.ennemybase[b] = typeC;
                                                    }
                                                    enemyCounter++;
                                                    break;
                                                }
                                            }
                                            unit = rand() % (5 + 1);
                                            cannon = rand() % (2 + 1);

                                            break;

                                        case 2:
                                            for (int b = 0; b < 10; b++)
                                            {
                                                for (int j = 0; j < count; j++)
                                                {
                                                    if (bulletCount.ennemyBox[j].active == 0)
                                                    {
                                                        struct bullet ennemyBullet = {(rand() % (300 + 1) + 150), (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4, 1, 1, 'E',Bullet2IMG};
                                                        bulletCount.ennemyBox[j] = ennemyBullet;
                                                        break;
                                                    }
                                                }
                                            }
                                            break;

                                        default:
                                            for (int b = 0; b < level; b++)
                                            {
                                                if (enemyCount.ennemybase[b].active == 0)
                                                {
                                                    struct ennemy typeE2 = {320, 110, 20, 32, 1000, 6, 5, 1, 0, 0xFF0000FF, 'E', TypeE2IMG, time(NULL)};
                                                    enemyCount.ennemybase[b] = typeE2;
                                                    enemyCounter++;
                                                    break;
                                                }
                                            }

                                            break;
                                        }
                                        enemyCount.ennemybase[i].time = time(NULL);
                                        attackMode = rand() % (3 + 1);
                                    }
                                }

                                if (enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                   Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                {
                                    Falcon.life -= 1;
                                }

                                break;

                            default:
                                GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                if (enemyCount.ennemybase[i].yposition >= 480 || GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                                                                                   enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize))
                                {
                                    Falcon.life -= 1;
                                    enemyCount.ennemybase[i].active = 0;
                                }

                                break;
                            }
                        }

                        else if (enemyCount.ennemybase[i].dead == 0)
                        {
                            if (enemyCount.ennemybase[i].type == 'X')
                            {
                                enemyCount.ennemybase[i].dead = 1;
                                enemyCounter = 0;
                            }
                            else
                            {
                                enemyCount.ennemybase[i].dead = 1;
                                enemyCounter -= 1;
                            }
                            switch (enemyCount.ennemybase[i].type)
                            {
                            case 'Z':
                                score += 50;
                                break;
                            case 'B':
                                score += 5;
                                break;
                            case 'C':
                                score += 5;
                                break;
                            case 'D':
                                score += 5;
                                break;
                            case 'E':
                                score += 10;
                                break;
                            case 'F':
                                score += 20;
                                break;
                            case 'X':
                                score += 2000;
                                break;
                            default:
                                score += 1;
                                break;
                            }
                        }
                    }
                }
            }
            void enemyBullet()
            {
                for (int i = 0; i < count; i++)
                {
                    if (bulletCount.ennemyBox[i].active == 1)
                    {

                        GRRLIB_DrawImg(bulletCount.ennemyBox[i].xposition, bulletCount.ennemyBox[i].yposition,bulletCount.ennemyBox[i].bulletName , 0, 1, 1, 0xFFFFFFFF);

                        bulletCount.ennemyBox[i].yposition -= bulletCount.ennemyBox[i].speed;
                        if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                              bulletCount.ennemyBox[i].xposition, bulletCount.ennemyBox[i].yposition, bulletCount.ennemyBox[i].bxsize, bulletCount.ennemyBox[i].bysize))
                        {
                            bulletCount.ennemyBox[i].active = 0;
                            Falcon.life -= 1;
                        }
                        if (bulletCount.ennemyBox[i].yposition >= 550)
                        {
                            bulletCount.ennemyBox[i].active = 0;
                        }
                    }
                }
            }
            void powerUpTurn()
            {
                for (int i = 0; i < sizeOfItems; i++)
                {

                if (enemyCount.itemsBox[i].active == 1)
                {
                    //*GRRLIB_Rectangle(powerUp.xposition,powerUp.yposition,powerUp.xsize,powerUp.ysize,powerUp.color,1);
                    GRRLIB_DrawImg(enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].upgradeName, 0, 1, 1, 0xFFFFFFFF);
                    if(enemyCount.itemsBox[i].magnetised == 1){
                        enemyCount.itemsBox[i].yposition += enemyCount.itemsBox[i].speed/2;
                    }
                    else{
                        enemyCount.itemsBox[i].yposition += enemyCount.itemsBox[i].speed;   
                    }
                    enemyCount.itemsBox[i].speed += enemyCount.itemsBox[i].deacceleration;
                    if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                          enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize))
                    {
                        enemyCount.itemsBox[i].active = 0;
                        switch(enemyCount.itemsBox[i].upgradeType){
                            case 'D':
                                if (Falcon.power >= 5)
                                {
                                    score += 5;
                                }
                                else
                                {
                                    Falcon.power += 1;
                                }
                            break;
                            case 'P':
                                score += 10;
                            break;
                            

                        }
                        
                    }
                    //only works when on a side ( not like top right)
                    if(GRRLIB_RectOnRect(Falcon.xposition -20, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                        enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize)){
                            enemyCount.itemsBox[i].xposition +=5;
                            enemyCount.itemsBox[i].magnetised =1;
                    }
                    else if(GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize+20, Falcon.ysize,
                        enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize)){
                            enemyCount.itemsBox[i].xposition -=5;
                            enemyCount.itemsBox[i].magnetised =1;
                    }

                    if(GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition -20, Falcon.xsize, Falcon.ysize,
                        enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize)){
                            enemyCount.itemsBox[i].yposition +=5;
                            enemyCount.itemsBox[i].magnetised =1;
                    }
                    else if(GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize +20,
                        enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize)){
                            enemyCount.itemsBox[i].yposition -=5;
                            enemyCount.itemsBox[i].magnetised =1;
                    }
                    
                    if (enemyCount.itemsBox[i].yposition >= 480)
                    {
                        enemyCount.itemsBox[i].active = 0;
                    }
                }
            }
            }

            if (timeValues == 1)
            {
                Falcon.ability = time(NULL);
                timeValues = 0;
            }

            WPAD_ScanPads();
            u32 pressed = WPAD_ButtonsDown(0);
            u32 hold = WPAD_ButtonsHeld(0);
            GRRLIB_SetBackgroundColour(0x10, 0x10, 0x10, 0xFF);
            GRRLIB_DrawImg(0, 0, WallIMG, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_DrawImg(560, 0, WallIMG, 0, 1, 1, 0xFFFFFFFF);
            sprintf(levelCounter, "level:%d", level);
            sprintf(scoreCounter, "lives:%d", Falcon.life);
            sprintf(lives, "score:%d", score);
            GRRLIB_PrintfTTF(5, 40, font, levelCounter, 20, 0x000000FF);
            GRRLIB_PrintfTTF(5, 80, font, scoreCounter, 16, 0x000000FF);
            GRRLIB_PrintfTTF(5, 120, font, lives, 16, 0x000000FF);

            if ((difftime(time(NULL), Falcon.ability) >= 20))
            {
                GRRLIB_PrintfTTF(5, 440, font, "ability:ON", 14, 0x000000FF);
            }
            else
            {
                GRRLIB_PrintfTTF(5, 440, font, "ability:OFF", 14, 0x000000FF);
            }

            /*
            ?Stars
            */
            stars();

            GRRLIB_DrawImg(Falcon.xposition, Falcon.yposition, FalconIMG, 0, 1, 1, 0xFFFFFFFF);

            /*
            ?Movement system
            */

            if (hold & WPAD_BUTTON_DOWN)
            {
                if (Falcon.xposition >= 560 - Falcon.xsize)
                {
                }
                else
                {
                    Falcon.xposition += Falcon.speed;
                }
            }
            else if (hold & WPAD_BUTTON_UP)
            {
                if (Falcon.xposition <= 80)
                {
                }
                else
                {
                    Falcon.xposition -= Falcon.speed;
                }
            }

            if (hold & WPAD_BUTTON_RIGHT)
            {
                if (Falcon.yposition <= 0)
                {
                }
                else
                {
                    Falcon.yposition -= Falcon.speed;
                }
            }
            else if (hold & WPAD_BUTTON_LEFT)
            {
                if (Falcon.yposition >= 480 - Falcon.ysize)
                {
                }
                else
                {
                    Falcon.yposition += Falcon.speed;
                }
            }
            /*
            ?Gun system
            */

            if (pressed & WPAD_BUTTON_2)
            {
                int maxBullets = Falcon.power;
                int region = -8 * maxBullets;
                for (int i = 0; i < maxBullets + 1; i++)
                {
                    for (int j = 0; j < count; j++)
                    {
                        if (bulletCount.box[j].active == 0)
                        {
                            if(Falcon.power ==5){
                                struct bullet b = {Falcon.xposition + Falcon.xsize / 3 + region, (Falcon.yposition - Falcon.ysize / 4) - 5, 8, 12, 10, 1 + Falcon.power, 1, 'S',BulletUltimateIMG};
                                bulletCount.box[j] = b;
                                break;
                            }
                            else{
                                struct bullet b = {Falcon.xposition + Falcon.xsize / 3 + region, (Falcon.yposition - Falcon.ysize / 4) - 5, 8, 12, 10, 1 + Falcon.power, 1, 'S',BulletIMG};
                                bulletCount.box[j] = b;
                                break;
                            }
                            
                        }
                    }
                    region += 15;
                }
            }

            if (pressed & WPAD_BUTTON_B && (difftime(time(NULL), Falcon.ability) >= 20))
            {
                for (int i = 0; i < count; i++)
                {
                    if (bulletCount.box[i].active == 0)
                    {
                        if(Falcon.power ==5)
                        {
                            struct bullet ultimate = {(Falcon.xposition + Falcon.xsize / 3) - 12, (Falcon.yposition - Falcon.ysize / 4) - 40, 32, 48, 10, 0, 1, 'U',BulletUltimateIMG};
                            bulletCount.box[i] = ultimate;
                            Falcon.ability = time(NULL);
                            break;
                        }
                        else
                        {
                            struct bullet ultimate = {(Falcon.xposition + Falcon.xsize / 3) - 12, (Falcon.yposition - Falcon.ysize / 4) - 40, 32, 48, 10, 0, 1, 'U',BulletIMG};
                            bulletCount.box[i] = ultimate;
                            Falcon.ability = time(NULL);
                            break;
                        }
                    }
                }
            }
            /*
            ?Boost system
            */

            if (hold & WPAD_BUTTON_1)
            {
                Falcon.speed = 10;
            }
            else
            {
                Falcon.speed = 5;
            }
            /*
            ?Bullet turn
            */

            bullet();

            /*
            ?Enemy spawn
            */

            enemy();

            /*
            ?Enemy Turn
            */
            enemyTurn();

            /*
            ?Ennemy Bullet turn
            */
            enemyBullet();

            /*
            ?when you lose all lives
            */

            if (Falcon.life == 0)
            {
                gameend = 1;
            }

            /*
            ?Power Up Turn
            */
            powerUpTurn();

            /*
            ?Win and lose conditions
            */

            if (win == 1)
            {
                MenuSystem.game = 0;
                MenuSystem.win = 1;
                break;
            }
            if (gameend == 1)
            {
                MenuSystem.game = 0;
                MenuSystem.gameover = 1;
                break;
            }

            /*
            ?Homebrew Exit
            */

            if (pressed & WPAD_BUTTON_HOME)
            {
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

        while (MenuSystem.gameover == 1)
        {
            WPAD_ScanPads();
            u32 pressed = WPAD_ButtonsDown(0);
            GRRLIB_SetBackgroundColour(0x64, 0x00, 0x00, 0xFF);
            GRRLIB_PrintfTTF(280, 220, font, "GAME OVER", 30, 0xFFFFFFFF);
            sprintf(scoreCounter, "score:%d", score);
            GRRLIB_PrintfTTF(280, 260, font, scoreCounter, 30, 0xFFFFFFFF);
            GRRLIB_PrintfTTF(200, 300, font, "To Restart : press + on remote", 22, 0xFFFFFFFF);

            GRRLIB_Render();
            if (pressed & WPAD_BUTTON_PLUS)
            {
                MenuSystem.gameover = 0;
                MenuSystem.start = 1;
                reset = 1;
                break;
            }
            /*
            ?Homebrew Exit
            */

            if (pressed & WPAD_BUTTON_HOME)
            {
                GRRLIB_FreeTTF(font);
                GRRMOD_End();
                GRRLIB_Exit();
                return 0;
            }
        }
        /*
        ?win loop starts here
        */

        while (MenuSystem.win == 1)
        {
            WPAD_ScanPads();
            u32 pressed = WPAD_ButtonsDown(0);
            GRRLIB_SetBackgroundColour(0xFF, 0xFF, 0x00, 0xFF);
            GRRLIB_PrintfTTF(280, 220, font, "WIN", 22, 0xFFFFFFFF);
            sprintf(scoreCounter, "score:%d", score);
            GRRLIB_PrintfTTF(280, 260, font, scoreCounter, 30, 0xFFFFFFFF);
            GRRLIB_PrintfTTF(200, 300, font, "To Restart : press + on remote", 22, 0xFFFFFFFF);
            GRRLIB_Render();
            if (pressed & WPAD_BUTTON_PLUS)
            {
                MenuSystem.win = 0;
                MenuSystem.start = 1;
                reset = 1;
                break;
            }
            /*
            ?Homebrew Exit
            */

            if (pressed & WPAD_BUTTON_HOME)
            {
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
