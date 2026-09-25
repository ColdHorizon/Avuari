#include <grrlib.h>
#include <gccore.h>
#include <grrmod.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <wiiuse/wpad.h>
#include <ogc/lwp_watchdog.h>
#include "OlivettiThin_ttf.h"
#include "Rakelo_ttf.h"
#include "expo_it.h"

u32 MALLOC_MEM2 = 1;

/*
?Button skins
*/
#include "button_png.h"
#include "buttonF3_png.h"
#include "buttonF7_png.h"
#include "buttonF9_png.h"
/*
?Button Small skins
*/

#include "buttonS_png.h"
#include "buttonSF3_png.h"
#include "buttonSF7_png.h"
#include "buttonSF9_png.h"
/*
?Title Logo skins
*/

#include "titleLogo_png.h"
#include "titleLogoF3_png.h"
#include "titleLogoF7_png.h"
#include "titleLogoF9_png.h"
/*
?Falcon skins
*/

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
#include "TypeG_png.h"
#include "TypeH_png.h"
#include "TypeI_png.h"
#include "TypeX_png.h"
#include "TypeZ_png.h"
#include "Wall_png.h"
#include "Upgrade_png.h"
#include "UpgradeR_png.h"
#include "UpgradeL_png.h"
#include "UpgradeS_png.h"
#include "Points_png.h"
#include "Bullet_png.h"
#include "BulletR_png.h"
#include "BulletL_png.h"
#include "Bullet2_png.h"
#include "BulletUltimate_png.h"
#include "Star_png.h"
#include "UsaFlag_png.h"
#include "AvaliFlag_png.h"
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
    int gunMode;
    time_t ability;
};
struct bullet
{
    int xposition;
    int yposition;
    int bxsize;
    int bysize;
    int speed;
    int speedX;
    float dmg;
    int active;
    char type;
    GRRLIB_texImg *bulletName;
    int sizeMultiplier;
};
struct ennemy
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    float health;
    int speed;
    int speedY;
    int active;
    int dead;
    u32 color;
    char type;
    int boss;
    GRRLIB_texImg *imgName;
    int time;
    int phase;
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
    struct bullet box[150];
    struct bullet ennemyBox[150];
};
struct storage
{
    struct ennemy ennemybase[200];
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
struct mainMenuBGColors
{
    u8 R;
    u8 G;
    u8 B;
    u8 A;
};
struct buttoncollisions
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
};
struct UiComponents
{
    int xposition;
    int yposition;
    int xsize;
    int ysize;
    bool active;
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
void SelectLanguage();
void stars();
void bullet();
void enemy();
void enemyTurn();
void enemyBullet();
void powerUpTurn();
void UiInformation(int enemyBossNumber);
void falconSkins();
void exitTheGame();
void objectDrop(int enemyNumber);
void spawnTypeA(int enemySpawnNumber,int x,int y);
void spawnTypeB(int enemySpawnNumber,int x,int y);
void spawnTypeC(int enemySpawnNumber,int x,int y,int side);
void spawnTypeD(int enemySpawnNumber,int x,int y);
void spawnTypeE(int enemySpawnNumber,int x,int y);
void spawnTypeE2(int enemySpawnNumber,int x,int y);
void spawnTypeF(int enemySpawnNumber,int x,int y);
void spawnTypeG(int enemySpawnNumber,int x,int y);
void spawnTypeH(int enemySpawnNumber,int x,int y);
void spawnTypeI(int enemySpawnNumber,int x,int y);
void spawnTypeX(int enemySpawnNumber,int x,int y);
void spawnTypeZ(int enemySpawnNumber,int x,int y);

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
    
    void *tracker_memory = malloc(expo_it_size);

    memcpy(tracker_memory, expo_it, expo_it_size);

    DCFlushRange(tracker_memory, expo_it_size);

    GRRMOD_SetMOD(tracker_memory, expo_it_size);
    GRRMOD_SetVolume(64, 64);
    
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetVRes(WPAD_CHAN_0, 640, 480);

    


    
    /*
    ?Button skins
    */

    GRRLIB_texImg *button = GRRLIB_LoadTexture(button_png);
    GRRLIB_texImg *buttonF4 = GRRLIB_LoadTexture(button_png);
    GRRLIB_texImg *buttonF3 = GRRLIB_LoadTexture(buttonF3_png);
    GRRLIB_texImg *buttonF7 = GRRLIB_LoadTexture(buttonF7_png);
    GRRLIB_texImg *buttonF9 = GRRLIB_LoadTexture(buttonF9_png);
    /*
    ?Button Small skins
    */

    GRRLIB_texImg *buttonS = GRRLIB_LoadTexture(buttonS_png);
    GRRLIB_texImg *buttonSF4 = GRRLIB_LoadTexture(buttonS_png);
    GRRLIB_texImg *buttonSF3 = GRRLIB_LoadTexture(buttonSF3_png);
    GRRLIB_texImg *buttonSF7 = GRRLIB_LoadTexture(buttonSF7_png);
    GRRLIB_texImg *buttonSF9 = GRRLIB_LoadTexture(buttonSF9_png);
    /*
    ?Title Logo skins
    */

    GRRLIB_texImg *titleLogo = GRRLIB_LoadTexture(titleLogo_png);
    GRRLIB_texImg *titleLogoF4 = GRRLIB_LoadTexture(titleLogo_png);
    GRRLIB_texImg *titleLogoF3 = GRRLIB_LoadTexture(titleLogoF3_png);
    GRRLIB_texImg *titleLogoF7 = GRRLIB_LoadTexture(titleLogoF7_png);
    GRRLIB_texImg *titleLogoF9 = GRRLIB_LoadTexture(titleLogoF9_png);
    /*
    ?Falcon skins
    */

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
    GRRLIB_texImg *TypeGIMG = GRRLIB_LoadTexture(TypeG_png);
    GRRLIB_texImg *TypeHIMG = GRRLIB_LoadTexture(TypeH_png);
    GRRLIB_texImg *TypeIIMG = GRRLIB_LoadTexture(TypeI_png);
    GRRLIB_texImg *TypeXIMG = GRRLIB_LoadTexture(TypeX_png);
    GRRLIB_texImg *TypeZIMG = GRRLIB_LoadTexture(TypeZ_png);
    GRRLIB_texImg *WallIMG = GRRLIB_LoadTexture(Wall_png);
    GRRLIB_texImg *UpgradeIMG = GRRLIB_LoadTexture(Upgrade_png);
    GRRLIB_texImg *UpgradeRIMG = GRRLIB_LoadTexture(UpgradeR_png);
    GRRLIB_texImg *UpgradeLIMG = GRRLIB_LoadTexture(UpgradeL_png);
    GRRLIB_texImg *UpgradeSIMG = GRRLIB_LoadTexture(UpgradeS_png);
    GRRLIB_texImg *PointsIMG = GRRLIB_LoadTexture(Points_png);
    GRRLIB_texImg *BulletIMG = GRRLIB_LoadTexture(Bullet_png);
    GRRLIB_texImg *BulletRIMG = GRRLIB_LoadTexture(BulletR_png);
    GRRLIB_texImg *BulletLIMG = GRRLIB_LoadTexture(BulletL_png);
    GRRLIB_texImg *Bullet2IMG = GRRLIB_LoadTexture(Bullet2_png);
    GRRLIB_texImg *BulletUltimateIMG = GRRLIB_LoadTexture(BulletUltimate_png);
    GRRLIB_texImg *StarIMG = GRRLIB_LoadTexture(Star_png);

    GRRLIB_ttfFont *font = GRRLIB_LoadTTF(OlivettiThin_ttf, OlivettiThin_ttf_size);
    GRRLIB_ttfFont *englishFont = GRRLIB_LoadTTF(OlivettiThin_ttf, OlivettiThin_ttf_size);
    GRRLIB_ttfFont *rakeloFont = GRRLIB_LoadTTF(Rakelo_ttf, Rakelo_ttf_size);


    // changes the rotation spot
    GRRLIB_SetHandle(FalconIMG, 10, 12);
    GRRLIB_SetHandle(Falcon4IMG, 10, 12);
    GRRLIB_SetHandle(Falcon3IMG, 10, 12);
    GRRLIB_SetHandle(Falcon7IMG, 10, 12);
    GRRLIB_SetHandle(Falcon9IMG, 10, 12);
    GRRLIB_SetHandle(FalconSIMG, 10, 12);
    int falconSkin = 1;
    int musicActivation = 1;
    int mainMenu = 1;
    int creditsMenu = 0;
    int reset = 0;
    struct player Falcon;
    struct bulletCount bulletCount;
    struct storage enemyCount;
    struct sky space;
    struct mainMenuBGColors menuColors;
    struct levelSystem MenuSystem = {1, 0, 0, 0};
    struct UiComponents bossBar = {590, 440, 0, 0, 0};
    struct UiComponents bossBarContour = {580, 30, 0, 0, 0};
    int bossStarted =0;
    int bossBarAnimation = 0;
    int level = 0;
    int score = 0;
    int win = 0;
    int enemySpawn =0;
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
    Falcon.gunMode = 1;
    Falcon.ability = time(NULL);
    menuColors.R = 0x03;
    menuColors.G = 0x09;
    menuColors.B = 0xa8;
    menuColors.A = 0xFF;
    int count = sizeof(bulletCount.box) / sizeof(bulletCount.box[0]);
    int starCounter = sizeof(space.starrySky) / sizeof(space.starrySky[0]);
    int sizeOfEnemies = sizeof(enemyCount.ennemybase) / sizeof(enemyCount.ennemybase[0]);
    int sizeOfItems = sizeof(enemyCount.itemsBox) / sizeof(enemyCount.itemsBox[0]);

    int skinRotation = 0;
    int languages =1;
    //// DO NOT CHANGE THE BULLET AMOUNT BEFORE CHANGING THIS
    for (int i = 0; i < count; i++)
    {
        bulletCount.box[i].active = 0;
        bulletCount.ennemyBox[i].active = 0;
    }
    for (int i = 0; i < sizeOfEnemies; i++)
    {
        enemyCount.ennemybase[i].active = 2;
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

    void exitTheGame()
    {

        GRRMOD_Unload();
        GRRMOD_End();
        GRRLIB_Exit();
    }





    while (SYS_MainLoop())
    {
    void SelectLanguage(){
        struct buttoncollisions english = {100,200,160,80};
        struct buttoncollisions rakelo = {400,200,160,80};
        GRRLIB_texImg *usaFlagIMG = GRRLIB_LoadTexture(UsaFlag_png);
        GRRLIB_texImg *avaliFlagIMG = GRRLIB_LoadTexture(AvaliFlag_png);

        while(true){
            GRRLIB_DrawImg(english.xposition, english.yposition,usaFlagIMG, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_DrawImg(rakelo.xposition, rakelo.yposition, avaliFlagIMG, 0, 1, 1, 0xFFFFFFFF);
            WPAD_ScanPads();
            ir_t ir;
            WPAD_IR(0, &ir);
            u32 pressed = WPAD_ButtonsDown(0);
            if (pressed & WPAD_BUTTON_A)
            {
                if(GRRLIB_RectOnRect(english.xposition,english.yposition,english.xsize,english.ysize, ir.x, ir.y, 20, 20)){
                    font = englishFont;
                    break;
                }
                if(GRRLIB_RectOnRect(rakelo.xposition, rakelo.yposition, rakelo.xsize, rakelo.ysize, ir.x, ir.y, 20, 20)){
                    font = rakeloFont;
                    break;
                }
            }
            if (ir.valid)
            {
                GRRLIB_Rectangle(ir.x, ir.y, 20, 20, 0xFF10F0FF, 1);
            }
            GRRLIB_Render();
        }
        GRRLIB_FreeTexture(usaFlagIMG);
        GRRLIB_FreeTexture(avaliFlagIMG);
        GRRMOD_Start();
        
        languages =0;

    }

    
        /*
        ?Reset system for restart of the game
        */
        if(languages ==1)
        {
            SelectLanguage();
        }

        while (reset == 1)
        {
            skinRotation = 0;
            level = 0;
            score = 0;
            enemySpawn =0;
            gameend = 0;
            win = 0;
            Falcon.xposition = 300;
            Falcon.yposition = 240;
            Falcon.xsize = 20;
            Falcon.ysize = 24;
            Falcon.power = 0;
            Falcon.speed = 5;
            Falcon.life = 10;
            Falcon.gunMode = 1;
            timeValues = 1;
            bossStarted =0;
            bossBar.active = 0;
            bossBarAnimation = 0;
            for (int i = 0; i < count; i++)
            {
                bulletCount.box[i].active = 0;
                bulletCount.ennemyBox[i].active = 0;
            }
            for (int i = 0; i < sizeOfEnemies; i++)
            {
                enemyCount.ennemybase[i].active = 2;
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
            GRRLIB_SetBackgroundColour(menuColors.R, menuColors.G, menuColors.B, menuColors.A);

            /*
            ?menu sections
            */

            if (mainMenu == 1)
            {

                GRRLIB_DrawImg(240, 120, titleLogo, 0, 1, 1, 0xFFFFFFFF);
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

                void falconSkins()
                {
                    switch (falconSkin)
                    {
                    case 1:
                        FalconIMG = Falcon4IMG;
                        button = buttonF4;
                        buttonS = buttonSF4;
                        titleLogo = titleLogoF4;
                        menuColors.R = 0x03;
                        menuColors.G = 0x09;
                        menuColors.B = 0xa8;
                        menuColors.A = 0xFF;
                        sprintf(skinName, "Falcon 4");
                        break;
                    case 2:
                        FalconIMG = Falcon3IMG;
                        button = buttonF3;
                        buttonS = buttonSF3;
                        titleLogo = titleLogoF3;
                        menuColors.R = 0xd4;
                        menuColors.G = 0x9f;
                        menuColors.B = 0x0d;
                        menuColors.A = 0xFF;
                        sprintf(skinName, "Falcon 3");
                        break;
                    case 3:
                        FalconIMG = Falcon7IMG;
                        button = buttonF7;
                        buttonS = buttonSF7;
                        titleLogo = titleLogoF7;
                        menuColors.R = 0xa6;
                        menuColors.G = 0x03;
                        menuColors.B = 0x21;
                        menuColors.A = 0xFF;
                        sprintf(skinName, "Falcon 7");
                        break;
                    case 4:
                        FalconIMG = Falcon9IMG;
                        button = buttonF9;
                        buttonS = buttonSF9;
                        titleLogo = titleLogoF9;
                        menuColors.R = 0x90;
                        menuColors.G = 0x03;
                        menuColors.B = 0xa6;
                        menuColors.A = 0xFF;
                        sprintf(skinName, "Falcon 9");
                        break;
                    case 5:
                        FalconIMG = FalconSIMG;
                        button = buttonF4;
                        buttonS = buttonSF4;
                        titleLogo = titleLogoF4;
                        menuColors.R = 0x03;
                        menuColors.G = 0x09;
                        menuColors.B = 0xa8;
                        menuColors.A = 0xFF;
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

                if (skinRotation != 360)
                {
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
                exitTheGame();
                return 0;
            }
            GRRLIB_Render();
        }
        /*
        ?game loop starts here
        */

        while (MenuSystem.game == 1)
        {


            //IMPORTANT 
            int bossSpawnNumber;

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
                void objectDrop(int enemyNumber)
                {
                    int object = 0;
                    enemyCount.ennemybase[enemyNumber].health = 0;
                    enemyCount.ennemybase[enemyNumber].active = 0;
                    object = rand() % (20 + 1);
                    for (int u = 0; u < sizeOfItems; u++)
                    {
                        if (enemyCount.itemsBox[u].active == 0)
                        {
                            if(object <= 6){
                                enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[enemyNumber].xposition + enemyCount.ennemybase[enemyNumber].xsize / 2;
                                enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[enemyNumber].yposition + enemyCount.ennemybase[enemyNumber].ysize / 2;
                                enemyCount.itemsBox[u].xsize = 12;
                                enemyCount.itemsBox[u].ysize = 12;
                                enemyCount.itemsBox[u].speed = -5;
                                enemyCount.itemsBox[u].deacceleration = 0.25f;
                                enemyCount.itemsBox[u].magnetised = 0;
                                enemyCount.itemsBox[u].active = 1;
                                enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                enemyCount.itemsBox[u].upgradeType = 'P';
                                enemyCount.itemsBox[u].upgradeName = PointsIMG;
                                break;
                            }

                            else if(object > 6 && object <= 9){
                                enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[enemyNumber].xposition + enemyCount.ennemybase[enemyNumber].xsize / 2;
                                enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[enemyNumber].yposition + enemyCount.ennemybase[enemyNumber].ysize / 2;
                                enemyCount.itemsBox[u].xsize = 12;
                                enemyCount.itemsBox[u].ysize = 12;
                                enemyCount.itemsBox[u].speed = -5;
                                enemyCount.itemsBox[u].deacceleration = 0.25f;
                                enemyCount.itemsBox[u].magnetised = 0;
                                enemyCount.itemsBox[u].active = 1;
                                enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                enemyCount.itemsBox[u].upgradeType = 'D';
                                enemyCount.itemsBox[u].upgradeName = UpgradeIMG;
                                break;
                            }
                            else if(object ==10 || object == 11){
                                int weapon = 0;
                                weapon = rand() % (3 + 1);
                                if(weapon ==1){
                                enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[enemyNumber].xposition + enemyCount.ennemybase[enemyNumber].xsize / 2;
                                enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[enemyNumber].yposition + enemyCount.ennemybase[enemyNumber].ysize / 2;
                                enemyCount.itemsBox[u].xsize = 12;
                                enemyCount.itemsBox[u].ysize = 12;
                                enemyCount.itemsBox[u].speed = -5;
                                enemyCount.itemsBox[u].deacceleration = 0.25f;
                                enemyCount.itemsBox[u].magnetised = 0;
                                enemyCount.itemsBox[u].active = 1;
                                enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                enemyCount.itemsBox[u].upgradeType = 'S';
                                enemyCount.itemsBox[u].upgradeName = UpgradeSIMG;
                                break;
                                }
                                else if(weapon ==2){
                                enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[enemyNumber].xposition + enemyCount.ennemybase[enemyNumber].xsize / 2;
                                enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[enemyNumber].yposition + enemyCount.ennemybase[enemyNumber].ysize / 2;
                                enemyCount.itemsBox[u].xsize = 12;
                                enemyCount.itemsBox[u].ysize = 12;
                                enemyCount.itemsBox[u].speed = -5;
                                enemyCount.itemsBox[u].deacceleration = 0.25f;
                                enemyCount.itemsBox[u].magnetised = 0;
                                enemyCount.itemsBox[u].active = 1;
                                enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                enemyCount.itemsBox[u].upgradeType = 'R';
                                enemyCount.itemsBox[u].upgradeName = UpgradeRIMG;
                                break;
                                }
                                else{
                                enemyCount.itemsBox[u].xposition = enemyCount.ennemybase[enemyNumber].xposition + enemyCount.ennemybase[enemyNumber].xsize / 2;
                                enemyCount.itemsBox[u].yposition = enemyCount.ennemybase[enemyNumber].yposition + enemyCount.ennemybase[enemyNumber].ysize / 2;
                                enemyCount.itemsBox[u].xsize = 12;
                                enemyCount.itemsBox[u].ysize = 12;
                                enemyCount.itemsBox[u].speed = -5;
                                enemyCount.itemsBox[u].deacceleration = 0.25f;
                                enemyCount.itemsBox[u].magnetised = 0;
                                enemyCount.itemsBox[u].active = 1;
                                enemyCount.itemsBox[u].color = 0xFFFF00FF;
                                enemyCount.itemsBox[u].upgradeType = 'L';
                                enemyCount.itemsBox[u].upgradeName = UpgradeLIMG;
                                break;
                                }

                            }

                            
                            
                            
                        }
                        
                    }
                }
                for (int i = 0; i < count; i++)
                {
                    if (bulletCount.box[i].active == 1)
                    {
                        GRRLIB_DrawImg(bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bulletName, 0, bulletCount.box[i].sizeMultiplier, bulletCount.box[i].sizeMultiplier, 0xFFFFFFFF);
                        
                        for (int j = 0; j < sizeOfEnemies; j++)
                            {
                                int colided =0;
                                if (enemyCount.ennemybase[j].active == 1)
                                {
                                    
                                    //?COULD MAKE PROBLEMS
                                    if(bulletCount.box[i].bxsize > enemyCount.ennemybase[j].xsize && bulletCount.box[i].bysize > enemyCount.ennemybase[j].ysize){
                                        if (GRRLIB_RectOnRect(bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bxsize, bulletCount.box[i].bysize,
                                            enemyCount.ennemybase[j].xposition, enemyCount.ennemybase[j].yposition, enemyCount.ennemybase[j].xsize, enemyCount.ennemybase[j].ysize
                                                            )){
                                                colided =1;
                                            }
                                    }
                                    else if(bulletCount.box[i].bxsize > enemyCount.ennemybase[j].xsize){
                                        if (GRRLIB_RectOnRect(bulletCount.box[i].xposition, enemyCount.ennemybase[j].yposition, bulletCount.box[i].bxsize, enemyCount.ennemybase[j].ysize,
                                                            enemyCount.ennemybase[j].xposition, bulletCount.box[i].yposition, enemyCount.ennemybase[j].xsize, bulletCount.box[i].bysize)){
                                                colided =1;
                                            }
                                    }
                                    else if (bulletCount.box[i].bysize > enemyCount.ennemybase[j].ysize){
                                        if (GRRLIB_RectOnRect(enemyCount.ennemybase[j].xposition, bulletCount.box[i].yposition, enemyCount.ennemybase[j].xsize, bulletCount.box[i].bysize,
                                                            bulletCount.box[i].xposition, enemyCount.ennemybase[j].yposition, bulletCount.box[i].bxsize, enemyCount.ennemybase[j].ysize)){
                                                colided =1;
                                            }
                                    }
                                    else{
                                        if (GRRLIB_RectOnRect(enemyCount.ennemybase[j].xposition, enemyCount.ennemybase[j].yposition, enemyCount.ennemybase[j].xsize, enemyCount.ennemybase[j].ysize,
                                                            bulletCount.box[i].xposition, bulletCount.box[i].yposition, bulletCount.box[i].bxsize, bulletCount.box[i].bysize)){
                                                colided =1;
                                            }
                                    }

                                    if(colided ==1){
                                        enemyCount.ennemybase[j].health -= bulletCount.box[i].dmg;
                                            if(bulletCount.box[i].type == 'S' || (bulletCount.box[i].type == 'U' && enemyCount.ennemybase[j].type == 'X')){
                                                bulletCount.box[i].active = 0;
                                            }
                                            if (enemyCount.ennemybase[j].health <= 0 || (bulletCount.box[i].type == 'U' && enemyCount.ennemybase[j].type != 'X'))
                                            {
                                                int enemyNumber = j;
                                                objectDrop(enemyNumber);
                                            }
                                            if(bulletCount.box[i].type != 'L'){
                                                break;
                                            }
                                    }
                                        
                                

                                }
                                
                            }
                            
                        bulletCount.box[i].yposition -= bulletCount.box[i].speed;
                        bulletCount.box[i].xposition += bulletCount.box[i].speedX;
                        if (bulletCount.box[i].yposition <= 0 || bulletCount.box[i].xposition <= 80 || bulletCount.box[i].xposition >= 560)
                        {
                            if(bulletCount.box[i].type != 'L'){
                                bulletCount.box[i].active = 0;
                            }
                        }
                        if(bulletCount.box[i].type == 'L'){
                            bulletCount.box[i].active = 0;
                        }
                    }
                }
            }


                    
                
                
            
                    
                
            
            void enemy()
            {
                void spawnTypeA(int enemySpawnNumber,int x,int y){
                    struct ennemy typeA = {x, y, 20, 20, 5, 2, 2, 1, 0, 0xFF0000FF, 'A',0, TypeAIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeA;
                }
                void spawnTypeB(int enemySpawnNumber,int x,int y){
                    struct ennemy typeB = {x, y, 32, 32, 25, 1, 1, 1, 0, 0x0000FFFF, 'B',0, TypeBIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeB;
                }
                void spawnTypeC(int enemySpawnNumber,int x,int y,int side){
                    if (side == 1)
                    {
                        struct ennemy typeC = {x, y, 20, 20, 5, 4, 2, 1, 0, 0xFF0000FF, 'C',0, TypeCIMG, 0,0};
                        enemyCount.ennemybase[enemySpawnNumber] = typeC;
                    }
                    else
                    {
                        struct ennemy typeC = {x, y, 20, 20, 5, 4, -2, 1, 0, 0xFF0000FF, 'C',0, TypeCIMG, 0,0};
                        enemyCount.ennemybase[enemySpawnNumber] = typeC;
                    }
                }
                void spawnTypeD(int enemySpawnNumber,int x,int y){
                    struct ennemy typeD = {x, y, 20, 20, 25, 4, 4, 1, 0, 0xFF0000FF, 'D',0, TypeDIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeD;
                }
                void spawnTypeE(int enemySpawnNumber,int x,int y){
                    struct ennemy typeE = {x, y, 20, 32, 1000, 6, 2, 1, 0, 0xFF0000FF, 'E',0, TypeEIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeE;
                }
                void spawnTypeE2(int enemySpawnNumber,int x,int y){
                    struct ennemy typeE2 = {x, y, 20, 32, 1000, 6, 5, 1, 0, 0xFF0000FF, 'E',0, TypeE2IMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeE2;
                }
                void spawnTypeF(int enemySpawnNumber,int x,int y){
                    struct ennemy typeF = {x, y, 32, 32, 35, 1, 1, 1, 0, 0x0000FFFF, 'F',0, TypeFIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeF;
                }
                void spawnTypeX(int enemySpawnNumber,int x,int y){
                    struct ennemy typeX = {120, y, 400, 100, 4000, 1, 1, 1, 0, 0xFF0000FF, 'X',1, TypeXIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeX;
                }
                void spawnTypeZ(int enemySpawnNumber,int x,int y){
                    struct ennemy typeZ = {x, y, 52, 52, 100, 1, 1, 1, 0, 0x101010FF, 'Z',0, TypeZIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeZ;
                }
                void spawnTypeG(int enemySpawnNumber,int x,int y){
                    struct ennemy typeG = {x, y, 20, 20, 25, 5, 5, 1, 0, 0xFF0000FF, 'G',0, TypeGIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeG;
                }
                void spawnTypeH(int enemySpawnNumber,int x,int y){
                    struct ennemy typeH = {x, y, 32, 32, 45, 1, 1, 1, 0, 0x0000FFFF, 'H',0, TypeHIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeH;
                }
                void spawnTypeI(int enemySpawnNumber,int x,int y){
                    struct ennemy typeI = {x, y, 32, 32, 75, 1, 1, 1, 0, 0x0000FFFF, 'I',0, TypeIIMG, 0,0};
                    enemyCount.ennemybase[enemySpawnNumber] = typeI;
                }


                if(level == 0){
                    //wave 1
                    spawnTypeA(0,100,-20);
                    spawnTypeA(1,140,-40);
                    spawnTypeA(2,180,-60);
                    spawnTypeA(3,220,-80);
                    spawnTypeA(4,260,-100);
                    //wave 2
                    spawnTypeA(5,510,-320);
                    spawnTypeA(6,470,-340);
                    spawnTypeA(7,430,-360);
                    spawnTypeA(8,390,-380);
                    spawnTypeA(9,350,-400);
                    //wave 3
                    spawnTypeA(10,300,-700);
                    spawnTypeA(11,340,-700);
                    spawnTypeA(12,300,-740);
                    spawnTypeA(13,340,-740);
                    spawnTypeA(14,300,-780);
                    spawnTypeA(15,340,-780);
                    spawnTypeA(16,300,-820);
                    spawnTypeA(17,340,-820);
                    spawnTypeA(18,300,-860);
                    spawnTypeA(19,340,-860);
                    spawnTypeB(20,310,-840);
                    //wave 4
                    spawnTypeB(21,300,-1000);
                    spawnTypeB(22,340,-1000);
                    spawnTypeD(23,200,-1040);
                    //wave 5
                    spawnTypeC(24,200,-1250,1);
                    spawnTypeC(25,300,-1250,2);
                    spawnTypeC(26,350,-1300,1);
                    spawnTypeC(27,220,-1400,2);
                    spawnTypeC(28,400,-1290,1);
                    spawnTypeC(29,440,-1320,2);
                    spawnTypeC(30,200,-1200,2);
                    //wave 6
                    spawnTypeZ(31,300,-1500);
                    spawnTypeF(32,310,-1620);
                    //wave 7
                    spawnTypeA(33,200,-1800);
                    spawnTypeA(34,230,-1800);
                    spawnTypeA(35,260,-1800);
                    spawnTypeA(36,290,-1800);
                    spawnTypeA(37,320,-1800);
                    spawnTypeA(38,350,-1800);
                    spawnTypeA(39,380,-1800);
                    spawnTypeA(40,410,-1800);
                    spawnTypeF(41,200,-1850);
                    spawnTypeF(42,400,-1850);
                    //wave 8
                    spawnTypeB(43,300,-2000);
                    spawnTypeB(44,350,-2000);
                    spawnTypeD(45,200,-2100);
                    spawnTypeB(46,250,-2100);
                    spawnTypeB(47,400,-2200);
                    spawnTypeD(48,450,-2200);
                    //wave 9
                    spawnTypeF(49,300,-2500);
                    spawnTypeF(50,350,-2550);
                    spawnTypeF(51,250,-2550);
                    spawnTypeF(52,400,-2600);
                    spawnTypeF(53,200,-2600);
                    spawnTypeF(54,450,-2650);
                    spawnTypeF(55,150,-2650); 
                    //wave 10
                    spawnTypeA(56,510,-3300);
                    spawnTypeA(57,470,-3320);
                    spawnTypeA(58,430,-3340);
                    spawnTypeA(59,390,-3360);
                    spawnTypeA(60,350,-3380);
                    spawnTypeF(61,400,-3420);
                    spawnTypeA(62,100,-3400);
                    spawnTypeA(63,140,-3420);
                    spawnTypeA(64,180,-3440);
                    spawnTypeA(65,220,-3460);
                    spawnTypeA(66,260,-3480);
                    spawnTypeF(67,240,-3520);
                    //wave 11(Driller Wave)
                    spawnTypeE(68,200,-3900);
                    spawnTypeE(69,400,-3900);
                    spawnTypeE2(70,150,-4000);
                    spawnTypeE2(71,250,-4020);
                    spawnTypeE2(72,350,-4040);
                    spawnTypeE2(73,450,-4060);
                    spawnTypeI(74,300,-4000);
                    //wave 12
                    spawnTypeG(75,450,-4400);
                    spawnTypeG(76,430,-4400);
                    spawnTypeG(77,130,-4400);
                    spawnTypeG(78,150,-4400);
                    spawnTypeF(79,200,-4600);
                    spawnTypeF(80,250,-4600);
                    spawnTypeF(81,350,-4600);
                    spawnTypeF(82,400,-4600);
                    spawnTypeH(83,300,-4600);
                    //wave 13
                    spawnTypeI(84,200,-5100);
                    spawnTypeI(85,300,-5100);
                    spawnTypeI(86,400,-5100);
                    //wave 14
                    spawnTypeZ(87,200,-5500);
                    spawnTypeZ(88,300,-5500);
                    spawnTypeZ(89,400,-5500);
                    spawnTypeI(90,200,-5600);
                    spawnTypeI(91,420,-5600);
                    //wave 15
                    spawnTypeH(92,150,-6400);
                    spawnTypeH(93,200,-6400);
                    spawnTypeH(94,250,-6400);
                    spawnTypeH(95,300,-6400);
                    spawnTypeE2(96,200,-6400);
                    //wave 16
                    spawnTypeH(97,500,-6900);
                    spawnTypeH(98,450,-6900);
                    spawnTypeH(99,400,-6900);
                    spawnTypeH(100,350,-6900);
                    spawnTypeE2(101,200,-6900);
                    //wave 17
                    spawnTypeF(102,150,-7600);
                    spawnTypeF(103,275,-7600);
                    spawnTypeF(104,300,-7700);
                    spawnTypeF(105,100,-7500);
                    spawnTypeF(106,400,-7600);
                    spawnTypeF(107,350,-7750);
                    spawnTypeF(108,150,-7400);
                    spawnTypeF(109,275,-7800);
                    spawnTypeF(110,300,-7500);
                    spawnTypeF(111,450,-7800);
                    spawnTypeF(112,450,-7600);
                    spawnTypeF(113,400,-7500);
                    spawnTypeF(114,450,-7500);
                    //wave 18
                    spawnTypeG(115,200,-8800);
                    spawnTypeG(116,400,-8800);
                    spawnTypeG(117,250,-8800);
                    spawnTypeG(118,350,-8800);
                    spawnTypeI(119,200,-9000);
                    spawnTypeI(120,400,-9000);
                    //wave 19
                    spawnTypeZ(121,100,-9500);
                    spawnTypeZ(122,150,-9500);
                    spawnTypeZ(123,200,-9500);
                    spawnTypeZ(124,250,-9500);
                    spawnTypeZ(125,300,-9500);
                    spawnTypeZ(126,350,-9500);
                    spawnTypeZ(127,400,-9500);
                    spawnTypeZ(128,450,-9500);
                    spawnTypeZ(129,500,-9500);
                    //boss wave
                    spawnTypeX(130,0,-11000);
                    bossSpawnNumber =130;
                }
                        
                    
                
            }
            void enemyTurn()
            {
                for (int i = 0; i < sizeOfEnemies; i++)
                {
                    {
                        if (enemyCount.ennemybase[i].active == 1)
                        {     
                            enemyCount.ennemybase[i].time += 1;
                            if(enemyCount.ennemybase[i].yposition +enemyCount.ennemybase[i].ysize + 20 >= 0){
                                switch (enemyCount.ennemybase[i].type)
                                {

                                case 'Z':
                                    GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                    enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
                                    }
                                    break;
                                case 'B':
                                    GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                    enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
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
                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
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

                                    if (enemyCount.ennemybase[i].time >= 120)
                                    {
                                        for (int j = 0; j < count; j++)
                                        {
                                            if (bulletCount.ennemyBox[j].active == 0)
                                            {
                                                struct bullet ennemyBullet = {(enemyCount.ennemybase[i].xposition + enemyCount.ennemybase[i].xsize / 2), (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4, 0, 1, 1, 'E', Bullet2IMG,1};
                                                bulletCount.ennemyBox[j] = ennemyBullet;
                                                break;
                                            }
                                        }
                                        enemyCount.ennemybase[i].time = 0;
                                    }

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
                                    }
                                    break;
                                    case 'G':
                                    GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                    if(enemyCount.ennemybase[i].yposition +enemyCount.ennemybase[i].ysize + 20 >= 0 && enemyCount.ennemybase[i].phase == 0){
                                        enemyCount.ennemybase[i].time =0;
                                        enemyCount.ennemybase[i].phase =1;
                                    }
                                    if(enemyCount.ennemybase[i].phase == 1 || enemyCount.ennemybase[i].phase >=4){
                                        enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;
                                    }
                                    if(enemyCount.ennemybase[i].time >= 20 && enemyCount.ennemybase[i].phase ==1){
                                        enemyCount.ennemybase[i].phase = 2;
                                    }

                                    if (enemyCount.ennemybase[i].time >= 120 && (enemyCount.ennemybase[i].phase ==2 || enemyCount.ennemybase[i].phase ==3))
                                    {
                                        int speed =0;
                                    for(int j = 0; j < 3; j++)
                                    {
                                        for (int b = 0; b < count; b++)
                                        {
                                            if (bulletCount.ennemyBox[b].active == 0)
                                            {
                                                struct bullet ennemyBullet = {(enemyCount.ennemybase[i].xposition + enemyCount.ennemybase[i].xsize / 2), (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4-speed, 0, 1, 1, 'E', Bullet2IMG,1};
                                                bulletCount.ennemyBox[b] = ennemyBullet;
                                                break;
                                            }
                                        }
                                        speed +=1;
                                        
                                    }
                                    enemyCount.ennemybase[i].phase +=1;
                                    enemyCount.ennemybase[i].time = 0;
                                    }
                                    

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
                                    }
                                    break;
                                case 'H':
                                    GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                    enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                    if (enemyCount.ennemybase[i].time >= 120)
                                    {
                                        int region = enemyCount.ennemybase[i].xposition;
                                        for(int j = 0; j < 2; j++)
                                        {
                                            for (int b = 0; b < count; b++)
                                            {
                                                if (bulletCount.ennemyBox[b].active == 0)
                                                {
                                                    struct bullet ennemyBullet = {region, (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4, 0, 1, 1, 'E', Bullet2IMG,1};
                                                    bulletCount.ennemyBox[b] = ennemyBullet;
                                                    break;
                                                }
                                            }
                                            region += 24;
                                            
                                        }
                                        enemyCount.ennemybase[i].time = 0;
                                    }

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
                                    }
                                    break;

                                case 'I':
                                    GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 1, 1, 0xFFFFFFFF);
                                    enemyCount.ennemybase[i].yposition += enemyCount.ennemybase[i].speed;

                                    if (enemyCount.ennemybase[i].time >= 120)
                                    {
                                        int region = enemyCount.ennemybase[i].xposition;
                                        int rotation = 1;
                                        for(int j = 0; j < 3; j++)
                                        {
                                            for (int b = 0; b < count; b++)
                                            {
                                                if (bulletCount.ennemyBox[b].active == 0)
                                                {
                                                    struct bullet ennemyBullet = {region, (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4, rotation, 1, 1, 'E', Bullet2IMG,1};
                                                    bulletCount.ennemyBox[b] = ennemyBullet;
                                                    break;
                                                }
                                            }
                                            rotation -=1;
                                            region += 12;
                                            
                                        }
                                        enemyCount.ennemybase[i].time = 0;
                                    }

                                    if (GRRLIB_RectOnRect(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize,
                                                                                                    Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
                                    }
                                    break;
                                case 'X':
                                    GRRLIB_DrawImg(enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].imgName, 0, 4, 4, 0xFFFFFFFF);
                                    if(bossStarted ==0){
                                        bossStarted =1;
                                    }
                                    if (enemyCount.ennemybase[i].yposition <= 0 && placed == 0)
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
                                        enemyCount.ennemybase[i].time = 0;
                                        battleMode = 1;
                                    }
                                    if (battleMode == 1)
                                    {
                                        if (enemyCount.ennemybase[i].time >= 120)
                                        {
                                            switch (attackMode)
                                            {
                                            case 1:
                                                for (int b = 0; b <  sizeOfEnemies; b++)
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
                                                            struct ennemy typeZ = {spawn, 170, 52, 52, 50, 1, 1, 1, 0, 0x101010FF, 'Z',0, TypeZIMG, 0,0};
                                                            enemyCount.ennemybase[b] = typeZ;
                                                        }
                                                        else if (unit == 2)
                                                        {
                                                            struct ennemy typeF = {spawn, 132, 32, 32, 20, 1, 1, 1, 0, 0x0000FFFF, 'F',0, TypeFIMG, 0,0};
                                                            enemyCount.ennemybase[b] = typeF;
                                                        }
                                                        else if (unit == 3)
                                                        {

                                                            struct ennemy typeC = {spawn, 120, 20, 20, 1, 4, 2, 1, 0, 0xFF0000FF, 'C',0, TypeCIMG, 0,0};
                                                            enemyCount.ennemybase[b] = typeC;
                                                        }
                                                        else if (unit == 4)
                                                        {
                                                            struct ennemy typeD = {spawn, 120, 20, 20, 20, 4, 4, 1, 0, 0xFF0000FF, 'D',0, TypeDIMG, 0,0};
                                                            enemyCount.ennemybase[b] = typeD;
                                                        }
                                                        else
                                                        {
                                                            struct ennemy typeC = {spawn, 120, 20, 20, 1, 4, -2, 1, 0, 0xFF0000FF, 'C',0, TypeCIMG, 0,0};
                                                            enemyCount.ennemybase[b] = typeC;
                                                        }
                                                        
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
                                                            struct bullet ennemyBullet = {(rand() % (300 + 1) + 150), (enemyCount.ennemybase[i].yposition + enemyCount.ennemybase[i].ysize), 8, 12, -4, 0, 1, 1, 'E', Bullet2IMG,1};
                                                            bulletCount.ennemyBox[j] = ennemyBullet;
                                                            break;
                                                        }
                                                    }
                                                }
                                                break;

                                            default:
                                                for (int b = 0; b < sizeOfEnemies; b++)
                                                {
                                                    if (enemyCount.ennemybase[b].active == 0)
                                                    {
                                                        struct ennemy typeE2 = {320, 110, 20, 32, 1000, 6, 5, 1, 0, 0xFF0000FF, 'E',0, TypeE2IMG, 0,0};
                                                        enemyCount.ennemybase[b] = typeE2;
                                                        
                                                        break;
                                                    }
                                                }

                                                break;
                                            }
                                            enemyCount.ennemybase[i].time = 0;
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

                                    if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                                                                                    enemyCount.ennemybase[i].xposition, enemyCount.ennemybase[i].yposition, enemyCount.ennemybase[i].xsize, enemyCount.ennemybase[i].ysize))
                                    {
                                        Falcon.life -= 1;
                                        enemyCount.ennemybase[i].active = 0;
                                    }
                                    if (enemyCount.ennemybase[i].yposition >= 480){
                                        enemyCount.ennemybase[i].active = -1;
                                    }

                                    break;
                                }
                            }
                            else{
                            enemyCount.ennemybase[i].yposition += 2;
                            }
                        }

                            else if (enemyCount.ennemybase[i].active == 0 && enemyCount.ennemybase[i].dead == 0)
                            {
                                if (enemyCount.ennemybase[i].type == 'X')
                                {
                                    enemyCount.ennemybase[i].dead = 1;
                                    win =1;
                                    
                                }
                                else
                                {
                                    enemyCount.ennemybase[i].dead = 1;
                                    
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
                                case 'G':
                                    score += 20;
                                    break;
                                case 'H':
                                    score += 30;
                                    break;
                                case 'I':
                                    score += 35;
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

                        GRRLIB_DrawImg(bulletCount.ennemyBox[i].xposition, bulletCount.ennemyBox[i].yposition, bulletCount.ennemyBox[i].bulletName, 0, bulletCount.ennemyBox[i].sizeMultiplier, bulletCount.ennemyBox[i].sizeMultiplier, 0xFFFFFFFF);

                        bulletCount.ennemyBox[i].yposition -= bulletCount.ennemyBox[i].speed;
                        bulletCount.ennemyBox[i].xposition -= bulletCount.ennemyBox[i].speedX;
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
                        if (enemyCount.itemsBox[i].magnetised == 1)
                        {
                            enemyCount.itemsBox[i].yposition += enemyCount.itemsBox[i].speed / 2;
                        }
                        else
                        {
                            enemyCount.itemsBox[i].yposition += enemyCount.itemsBox[i].speed;
                        }
                        enemyCount.itemsBox[i].speed += enemyCount.itemsBox[i].deacceleration;
                        if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                              enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize))
                        {
                            enemyCount.itemsBox[i].active = 0;
                            switch (enemyCount.itemsBox[i].upgradeType)
                            {
                            case 'D':
                                if (Falcon.power >= 4)
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
                            case 'S':
                                Falcon.gunMode =1;
                            break;
                            case 'R':
                                Falcon.gunMode =2;
                            break;
                            case 'L':
                                Falcon.gunMode =3;
                            break;
                            }
                        }
                        // only works when on a side ( not like top right)
                        if (GRRLIB_RectOnRect(Falcon.xposition - 20, Falcon.yposition, Falcon.xsize, Falcon.ysize,
                                              enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize))
                        {
                            enemyCount.itemsBox[i].xposition += 5;
                            enemyCount.itemsBox[i].magnetised = 1;
                        }
                        else if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize + 20, Falcon.ysize,
                                                   enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize))
                        {
                            enemyCount.itemsBox[i].xposition -= 5;
                            enemyCount.itemsBox[i].magnetised = 1;
                        }

                        if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition - 20, Falcon.xsize, Falcon.ysize,
                                              enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize))
                        {
                            enemyCount.itemsBox[i].yposition += 5;
                            enemyCount.itemsBox[i].magnetised = 1;
                        }
                        else if (GRRLIB_RectOnRect(Falcon.xposition, Falcon.yposition, Falcon.xsize, Falcon.ysize + 20,
                                                   enemyCount.itemsBox[i].xposition, enemyCount.itemsBox[i].yposition, enemyCount.itemsBox[i].xsize, enemyCount.itemsBox[i].ysize))
                        {
                            enemyCount.itemsBox[i].yposition -= 5;
                            enemyCount.itemsBox[i].magnetised = 1;
                        }

                        if (enemyCount.itemsBox[i].yposition >= 480)
                        {
                            enemyCount.itemsBox[i].active = 0;
                        }
                    }
                }
            }

            void UiInformation(int enemyBossNumber)
            {
                if(bossStarted == 1){
                bossBar.active = 1;
                bossBarContour.active = 1;
                bossBarAnimation = 1;
                bossStarted =2;
                }
                if (bossBar.active == 1 && bossBarContour.active == 1)
                {
                    bossBar.xsize = 20;
                    if (bossBarAnimation == 1 && bossBar.ysize > -400)
                    {
                        bossBar.ysize -= 5;
                    }
                    else if (bossBar.ysize < -400)
                    {
                        bossBarAnimation = 0;
                    }
                    bossBarContour.xsize = 40;
                    bossBarContour.ysize = 420;
                    GRRLIB_Rectangle(bossBarContour.xposition, bossBarContour.yposition, bossBarContour.xsize, bossBarContour.ysize, 0xA1A1A1FF, 1);
                    if (((float)enemyCount.ennemybase[enemyBossNumber].health / 4000) <= 0.5f)
                    {
                        GRRLIB_Rectangle(bossBar.xposition, bossBar.yposition, bossBar.xsize, bossBar.ysize * (((float)enemyCount.ennemybase[enemyBossNumber].health / 4000)), 0xFF0000FF, 1);
                    }
                    else
                    {
                        GRRLIB_Rectangle(bossBar.xposition, bossBar.yposition, bossBar.xsize, bossBar.ysize * (((float)enemyCount.ennemybase[enemyBossNumber].health / 4000)), 0x00FF00FF, 1);
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

            /*
            ?Enemy spawn
            */
            if(enemySpawn == 0){
                enemy();
                enemySpawn =1;
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

            if ((pressed & WPAD_BUTTON_2) && Falcon.gunMode != 3)
            {
                int angle[5];
                int region;
                switch(Falcon.gunMode){

                    case 1:
                    int maxBullets = Falcon.power;
                    if (maxBullets != 0)
                    {
                        region = maxBullets;
                        for (int i = 0; i < maxBullets + 1; i++)
                        {
                            angle[i] = region;
                            region -= 2;
                        }
                    }
                    else
                    {
                        for (int i = 0; i < maxBullets + 1; i++)
                        {
                            angle[i] = 0;
                        }
                    }

                    for (int i = 0; i < maxBullets + 1; i++)
                    {

                        for (int j = 0; j < count; j++)
                        {
                            if (bulletCount.box[j].active == 0)
                            {
                                if (Falcon.power == 4)
                                {
                                    struct bullet b = {Falcon.xposition + Falcon.xsize / 3, (Falcon.yposition - Falcon.ysize / 4) - 5, 8, 12, 10, angle[i], 5, 1, 'S', BulletUltimateIMG,1};
                                    bulletCount.box[j] = b;
                                    break;
                                }
                                else
                                {
                                    struct bullet b = {Falcon.xposition + Falcon.xsize / 3, (Falcon.yposition - Falcon.ysize / 4) - 5, 8, 12, 10, angle[i], 5, 1, 'S', BulletIMG,1};
                                    bulletCount.box[j] = b;
                                    break;
                                }
                            }
                        }
                    }
                    break;

                    case 2: 
                            region = 2;
                            for (int i = 0; i < 3 ; i++)
                            {
                                angle[i] = region;
                                region -= 2;
                            }
                            for (int i = 0; i < 3 ; i++)
                            {
                                for (int j = 0; j < count; j++)
                                {
                                    if (bulletCount.box[j].active == 0)
                                    {
                                        struct bullet r = {Falcon.xposition + Falcon.xsize / 3, (Falcon.yposition - Falcon.ysize / 4) - 5, 8, 16, 10,angle[i], 0.4 + (Falcon.power*0.4), 1, 'R', BulletRIMG,1};
                                        bulletCount.box[j] = r;
                                        break;

                                    }
                                }
                            }
                        


                    break;
                }
            }
            if ((hold & WPAD_BUTTON_2) && Falcon.gunMode == 3)
            {
                for (int i = 0; i < count; i++)
                        {
                            if (bulletCount.box[i].active == 0)
                            {
                                struct bullet l = {Falcon.xposition + Falcon.xsize / 3 -23, (Falcon.yposition - Falcon.ysize / 4) - 5 - 390, 56, 400, 0,0, 0.18 + (Falcon.power*0.18), 1, 'L', BulletLIMG,2};
                                bulletCount.box[i] = l;
                                break;
                            }


                        }

            }

            if (pressed & WPAD_BUTTON_B && (difftime(time(NULL), Falcon.ability) >= 20))
            {
                for (int i = 0; i < count; i++)
                {
                    if (bulletCount.box[i].active == 0)
                    {
                        if (Falcon.power == 4)
                        {
                            struct bullet ultimate = {(Falcon.xposition + Falcon.xsize / 3) - 12, (Falcon.yposition - Falcon.ysize / 4) - 40, 32, 48, 10, 0, 500, 1, 'U', BulletUltimateIMG,4};
                            bulletCount.box[i] = ultimate;
                            Falcon.ability = time(NULL);
                            break;
                        }
                        else
                        {
                            struct bullet ultimate = {(Falcon.xposition + Falcon.xsize / 3) - 12, (Falcon.yposition - Falcon.ysize / 4) - 40, 32, 48, 10, 0, 500, 1, 'U', BulletIMG,4};
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
            ?Modify Ui information
            */
            


            /*
            ?BG looks
            */
            
            GRRLIB_DrawImg(0, 0, WallIMG, 0, 1, 1, 0xFFFFFFFF);
            GRRLIB_DrawImg(560, 0, WallIMG, 0, 1, 1, 0xFFFFFFFF);
            sprintf(levelCounter, "level:%d", level);
            sprintf(scoreCounter, "lives:%d", Falcon.life);
            sprintf(lives, "score:%d", score);
            GRRLIB_PrintfTTF(5, 40, font, levelCounter, 20, 0x000000FF);
            GRRLIB_PrintfTTF(5, 80, font, scoreCounter, 16, 0x000000FF);
            GRRLIB_PrintfTTF(5, 120, font, lives, 16, 0x000000FF);
            UiInformation(bossSpawnNumber);

            if ((difftime(time(NULL), Falcon.ability) >= 20))
            {
                GRRLIB_PrintfTTF(5, 440, font, "ability:ON", 14, 0x000000FF);
            }
            else
            {
                GRRLIB_PrintfTTF(5, 440, font, "ability:OFF", 14, 0x000000FF);
            }

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
                exitTheGame();
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
                exitTheGame();
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
                exitTheGame();
                return 0;
            }
        }
    }
    GRRLIB_FreeTTF(font);
    GRRMOD_End();
    GRRLIB_Exit();
    return 0;
}
