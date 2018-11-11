/*******************************************************************************************
*
*   raylib game: FINAL PONG - game template
*
*   developed by [STUDENT NAME HERE]
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (Ray San)
*
********************************************************************************************/

#include "raylib.h"
#include "stdio.h"
#include <stdlib.h> 
#include <time.h> 

typedef enum GameScreen { LOGO, TITLE, PLAYER1, PLAYER2, OPCIONES, ENDING } GameScreen;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    srand(time(NULL));
    int screenWidth = 800;
    int screenHeight = 450;
    char windowTitle[30] = "raylib game - FINAL PONG";
    
    GameScreen screen = LOGO;
    
    // TODO: Define required variables here..........................(0.5p)
    // NOTE: Here there are some useful variables (should be initialized)
    
    //Logo
    Rectangle rec = {0, 0, screenWidth, screenHeight};
    Color recColor = BLACK;
    
    bool fadeOut = true;
    bool fadeIn = false;
    bool showLogo = false;
    float alpha = 0;
    float fadeSpeed = 0.012f;
    
    int contadorinout = 90;
    int contadorshow = 120;
    int EscenaAnterior = 0;
    
    //Title
    const char title[40] = "SUPESU";
    const char start[40] = "PRESS ENTER";
    
    int titley = -100;
    bool caida = true;
    bool temblor = false;
    bool direccion = false;
    int DistanciaMovimiento = 5;
    int contadorDistanciaMovimietos = 0;
    int option = 0;
    
    //Opciones
    bool sonido = false;
    bool controles = false;
    float volumen = 1;
    
    Rectangle barra_sonido;
    barra_sonido.width = 300;
    barra_sonido.height = 40;
    barra_sonido.x = screenWidth/2 - barra_sonido.width/2;
    barra_sonido.y = screenHeight/2;
    
    Rectangle barra_sonido_f = barra_sonido;
    
    //Gameplay
    int framescounter = 60000;
    int framescounter2 = 100;
    int playerLife = screenWidth/2 - 50;
    int enemyLife = screenWidth/2 - 50;
    int margen = 2;
    bool endtime = 0;
    bool control = 0;
    bool hitplayer = 0;
    bool hitenemy = 0;
    bool pause = 0;
    int r = 15;
    Vector2 speed;
    speed.x = GetRandomValue(-1,1) + 4;
    speed.y = GetRandomValue(-1,1) + 4;
    
    int winplayer1 = 0;
    int winplayer2 = 0;
    
    //Colores//
    Color MyRed = {244, 74, 44, 255};
    Color MyYellow = {212, 204, 14, 255};
    Color MyPurple = {169, 37, 223, 255};
    Color Selected = WHITE;
    //Parte superior//
    //Borde//
    Rectangle topborde;
    topborde.width = screenWidth;
    topborde.height = 60;
    topborde.x = 0;
    topborde.y = 0;
    
    //Rectangulo superior//
    Rectangle top = topborde;
    top.width -= margen * 2;
    top.height -= margen * 2;
    top.x = margen;
    top.y = margen;
 

    //Rectangulo rojo del player//
    Rectangle vidapr;
    vidapr.width = playerLife;
    vidapr.height = 17;
    vidapr.x = 0 + 10;
    vidapr.y = 0 + 20;
    
    //Rectangulo verde del player//
    Rectangle vidap = vidapr;
    
    //Borde rectangulo player//
    Rectangle vidapborde = vidapr;
    vidapborde.width += margen * 2;
    vidapborde.height = top.height - 10;
    vidapborde.x -= margen;
    vidapborde.y -= 13;
    
    //Rectangulo rojo enemigo//
    Rectangle vidaer;
    vidaer.width = enemyLife;
    vidaer.height = vidapr.height;
    vidaer.x = screenWidth - vidaer.width - 10;
    vidaer.y = vidapr.y;
    
    //Rectangulo azul del enemigo//
    Rectangle vidae = vidaer;

    
    //Borde rectangulo enemigo//
    Rectangle vidaeborde = vidaer;
    vidaeborde.width += margen * 2;
    vidaeborde.height = top.height - 10;
    vidaeborde.x -= margen;
    vidaeborde.y -= 13;
    
    //Porteria player//
    Rectangle porteriaL;
    porteriaL.width = margen;
    porteriaL.height = screenHeight;
    porteriaL.x = 0;
    porteriaL.y = 0;
    
    //Porteria enemigo//
    Rectangle porteriaR;
    porteriaR.width = margen;
    porteriaR.height = screenHeight;
    porteriaR.x = screenWidth - margen;
    porteriaR.y = 0;
    
    //Pala player//
    Rectangle pala1;
    pala1.width = 30;
    pala1.height = 100;
    pala1.x = porteriaL.width * 2;
    pala1.y = screenHeight/2 - pala1.height/2 + top.height/2;
    
    //Borde pala player//
    Rectangle pala1borde = pala1;
    pala1borde.width += margen * 2;
    pala1borde.height += margen * 2;
    pala1borde.x -= margen;
    pala1borde.y -= margen;
    
    
    //Pala enemigo//
    Rectangle pala2;
    pala2.width = 30;
    pala2.height = 100;
    int palaeY = screenHeight/2 - pala2.height/2 + top.height/2;
    pala2.x = screenWidth - pala2.width - porteriaR.width * 2;
    pala2.y = palaeY;
    int speedIA = speed.y;
    
    //Borde pala enemigo//
    Rectangle pala2borde = pala2;
    pala2borde.width += margen * 2;
    pala2borde.height += margen * 2;
    pala2borde.x -= margen;
    pala2borde.y -= margen;
    
    
    //Bola//
    int bolax = screenWidth/2;
    int bolay = screenHeight/2 + top.height/2;
    Vector2 bola;
    bola.x = bolax;
    bola.y = bolay;
    //Borde Bola//
    Vector2 bolaborde = bola;
    bool colision = 0;
    
    //Logica vidas
    int damage = vidap.height * 3;
    int cvida = 0;
    
    int gameResult = -1;        // 0 - Loose, 1 - Win, -1 - Not defined
    
    InitWindow(screenWidth, screenHeight, windowTitle);
    InitAudioDevice();      
    
    // NOTE: If using textures, declare Texture2D variables here (after InitWindow)
    //Texturas ventana logo
    Texture2D textureLogo = LoadTexture("resources/logo_texture.png");  
    Rectangle sourceLogoPro = {0,0,textureLogo.width, textureLogo.height};
    Rectangle destLogoPro = {screenWidth/2,screenHeight/2,400,400};
    Vector2 originLogo = {destLogoPro.width/2,destLogoPro.height/2};
    float rotationLogoPro = 0;

    Texture2D textureFondo1 = LoadTexture("resources/espacio_1.png");
    Rectangle sourceFondo1Pro = {0,0,textureFondo1.width, textureFondo1.height};
    Rectangle destFondo1Pro = {0,0,screenWidth,screenHeight};
    Vector2 originFondo1 = {0,0};
    float rotationFondo1Pro = 0;
    
    //Texturas titulo
    Texture2D textureTitulo = LoadTexture("resources/titulo.png");
    Rectangle sourceTituloPro = {0,0,textureTitulo.width, textureTitulo.height};
    Rectangle destTituloPro = {screenWidth/2,-100,300,100};
    Vector2 originTitulo = {destTituloPro.width/2, destTituloPro.height/2};
    float rotationTituloPro = 0;
    
    Texture2D textureFondo2 = LoadTexture("resources/espacio_2.png");
    Rectangle sourceFondo2Pro = {0,0,textureFondo2.width, textureFondo2.height};
    Rectangle destFondo2Pro = {0,0,screenWidth,screenHeight};
    Vector2 originFondo2 = {0,0};
    float rotationFondo2Pro = 0;
    
    Texture2D texture1player = LoadTexture("resources/1player.png");
    Texture2D texture1player_s = LoadTexture("resources/1player_s.png");
    Rectangle source1playerPro = {0,0,texture1player.width, texture1player.height};
    Rectangle dest1playerPro = {screenWidth/2 - 100, screenHeight/2 - 25,200,50};
    Vector2 origin1player = {0,0};
    float rotation1playerPro = 0;
    
    Texture2D texture2player = LoadTexture("resources/2player.png");
    Texture2D texture2player_s = LoadTexture("resources/2player_s.png");
    Rectangle source2playerPro = {0,0,texture2player.width, texture2player.height};
    Rectangle dest2playerPro = dest1playerPro;
    dest2playerPro.y += dest1playerPro.height + 20;
    Vector2 origin2player = {0,0};
    float rotation2playerPro = 0;
    
    Texture2D textureoptions = LoadTexture("resources/options.png");
    Texture2D textureoptions_s = LoadTexture("resources/options_s.png");
    Rectangle sourceoptionsPro = {0,0,textureoptions.width, textureoptions.height};
    Rectangle destoptionsPro = dest2playerPro;
    destoptionsPro.y += dest2playerPro.height + 20;
    Vector2 originoptions = {0,0};
    float rotationoptionsPro = 0;
    
    //Texturas gameplay
    Texture2D textureFondo = LoadTexture("resources/espacio.png");
    Rectangle sourceFondoPro = {0,0,textureFondo.width, textureFondo.height};
    Rectangle destFondoPro = {0,0,screenWidth,screenHeight};
    Vector2 originFondo = {0,0};
    float rotationFondoPro = 0;
    
    Texture2D textureVida = LoadTexture("resources/vida.png");
    Rectangle sourceVidaPro = {0,0,textureVida.width, textureVida.height};
    Rectangle destVidaPro = vidapborde;
    Vector2 originVida = {0,0};
    float rotationVidaPro = 0;
    
    Texture2D textureVidae = LoadTexture("resources/vidae.png");
    Rectangle sourceVidaePro = {0,0,textureVidae.width, textureVidae.height};
    Rectangle destVidaePro = vidaeborde;
    Vector2 originVidae = {0,0};
    float rotationVidaePro = 0;
    
    Texture2D texturePalap = LoadTexture("resources/paletap.png");
    Rectangle sourcePalapPro = {0,0,texturePalap.width, texturePalap.height};
    Rectangle destPalapPro = pala1borde;
    Vector2 originPalap = {0,0};
    float rotationPalapPro = 0;
    
    Texture2D texturePalae = LoadTexture("resources/paletae.png");
    Rectangle sourcePalaePro = {0,0,texturePalae.width, texturePalae.height};
    Rectangle destPalaePro = pala2borde;
    Vector2 originPalae = {0,0};
    float rotationPalaePro = 0;
    
    Texture2D textureBola = LoadTexture("resources/bola.png");
    Rectangle sourceBolaPro = {0,0,textureBola.width, textureBola.height};
    Rectangle destBolaPro = {bola.x, bola.y, 30, 30};
    Vector2 originBola = {destBolaPro.width/2,destBolaPro.height/2};
    float rotationBolaPro = 0;
    Rectangle BolaColaider = destBolaPro;
    BolaColaider.x -= destBolaPro.width/2;
    BolaColaider.y -= destBolaPro.height/2;
    
    Texture2D texturePlay = LoadTexture("resources/play.png");
    Texture2D texturePlay_s = LoadTexture("resources/play_s.png");
    Rectangle sourcePlayPro = {0,0,texturePlay.width, texturePlay.height};
    Rectangle destPlayPro = dest1playerPro;
    destPlayPro.y += dest1playerPro.height + 20;
    Vector2 originPlay = {0,0};
    float rotationPlayPro = 0;
    
    //Texturas Option
    Texture2D textureSonido = LoadTexture("resources/sound.png");
    Texture2D textureSonido_s = LoadTexture("resources/sound_s.png");
    Rectangle sourceSonidoPro = {0,0,textureSonido.width, textureSonido.height};
    Rectangle destSonidoPro = {screenWidth/2 - 100, screenHeight/2 -60,200,50};
    Vector2 originSonido = {0,0};
    float rotationSonidoPro = 0;
    
    Texture2D textureControles = LoadTexture("resources/controls.png");
    Texture2D textureControles_s = LoadTexture("resources/controls_s.png");
    Rectangle sourceControlesPro = {0,0,textureControles.width, textureControles.height};
    Rectangle destControlesPro = destSonidoPro;
    destControlesPro.y += destSonidoPro.height + 20;
    Vector2 originControles = {0,0};
    float rotationControlesPro = 0;
    
    Texture2D textureMenu = LoadTexture("resources/menu.png");
    Texture2D textureMenu_s = LoadTexture("resources/menu_s.png");
    Rectangle sourceMenuPro = {0,0,textureMenu.width, textureMenu.height};
    Rectangle destMenuPro = destControlesPro;
    destMenuPro.y += destControlesPro.height + 20;
    Vector2 originMenu = {0,0};
    float rotationMenuPro = 0;
        
    Texture2D textureReturn = LoadTexture("resources/return.png");
    Texture2D textureReturn_s = LoadTexture("resources/Return_s.png");
    Rectangle sourceReturnPro = {0,0,textureReturn.width, textureReturn.height};
    Rectangle destReturnPro = destMenuPro;
    destReturnPro.y += destMenuPro.height + 20;
    Vector2 originReturn = {0,0};
    float rotationReturnPro = 0;
    
    Texture2D textureImg_controles = LoadTexture("resources/img_controles.png");
    Rectangle sourceImg_controlesPro = {0,0,textureImg_controles.width, textureImg_controles.height};
    Rectangle destImg_controlesPro = {screenWidth/2, screenHeight/2 -120,650,250};
    Vector2 originImg_controles= {destImg_controlesPro.width/2,0};
    float rotationImg_controlesPro = 0;
    
    //Texturas exit
    Texture2D textureRestart = LoadTexture("resources/restart.png");
    Texture2D textureRestart_s = LoadTexture("resources/restart_s.png");
    Rectangle sourceRestartPro = {0,0,textureRestart.width, textureRestart.height};
    Rectangle destRestartPro = {screenWidth/2 - 100, screenHeight/2 + 30,200,50};
    Vector2 originRestart = {0,0};
    float rotationRestartPro = 0;
    
    Texture2D textureExit = LoadTexture("resources/exit.png");
    Texture2D textureExit_s = LoadTexture("resources/exit_s.png");
    Rectangle sourceExitPro = {0,0,textureExit.width, textureExit.height};
    Rectangle destExitPro = destRestartPro;
    destExitPro.y += destRestartPro.height + 20;
    Vector2 originExit = {0,0};
    float rotationExitPro = 0;
    
    // NOTE: If using SpriteFonts, declare SpriteFont variables here (after InitWindow)
    
    // NOTE: If using sound or music, InitAudioDevice() and load Sound variables here (after InitAudioDevice)
    Sound fxHit = LoadSound("resources/hit.ogg");
    Sound fxDanyo = LoadSound("resources/danyo.ogg");
    
    Music musicGameplay = LoadMusicStream("resources/gameplay.ogg");
    PlayMusicStream(musicGameplay);
    SetMusicVolume(musicGameplay, 0.3f);
    
    Music musictoepic = LoadMusicStream("resources/musica_to_epica.ogg");
    PlayMusicStream(musictoepic);
    SetMusicVolume(musictoepic, 0.3f);
    
    Music musicOpciones = LoadMusicStream("resources/opciones.ogg");
    PlayMusicStream(musicOpciones);
    SetMusicVolume(musicOpciones, 0.3f);
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch(screen) 
        {
            case LOGO: 
            {
                // Update LOGO screen data here!
                // TODO: Logo fadeIn and fadeOut logic...............(0.5p)
                sourceFondo1Pro.x ++;    
                if(contadorinout > 0)
                {
                    if(fadeOut)
                    {
                        alpha += fadeSpeed;
                        
                        if(alpha >= 1.0f)
                        {
                            alpha = 1.0f;
                        }
                        contadorinout --;
                    }
                    
                    
                    if(fadeIn)
                    {
                        alpha -= fadeSpeed;
                        
                        if(alpha <= 0.0f)
                        {
                            alpha = 0.0f;
                            screen = TITLE;
                        }
                        contadorinout --;
                    }
                    
   
                }
                else
                {
                    fadeOut = false;
                    showLogo = true;
                }
                
                if(contadorshow > 0)
                {
                    if(showLogo)
                    {
                        contadorshow --;
                    }
                }
                else
                {
                  fadeIn = true;  
                  contadorinout = 90;
                }
                
              
                
            } break;
            case TITLE: 
            {
                // Update TITLE screen data here!
                UpdateMusicStream(musictoepic);
                sourceFondo2Pro.x ++;    
                // TODO: Title animation logic.......................(0.5p)
                if(caida && titley < 100)
                {
                    titley += 10;
                    
                }
                else
                {
                    caida = false;
                    temblor = true;
                }
                
                if(temblor)
                {
                    if(direccion)
                    {
                        if(contadorDistanciaMovimietos < DistanciaMovimiento)
                        {
                            titley -= DistanciaMovimiento;
                            contadorDistanciaMovimietos ++;
                        }
                        else
                        {
                            direccion = false;
                            contadorDistanciaMovimietos = 0;
                            DistanciaMovimiento --;
                        }
                    }
                    else   
                    {
                        if(contadorDistanciaMovimietos < DistanciaMovimiento)
                        {
                            titley += DistanciaMovimiento;
                            contadorDistanciaMovimietos ++;
                        }
                        else
                        {
                            direccion = true;
                            contadorDistanciaMovimietos = 0;
                            DistanciaMovimiento --;
                        }
                    }
                }
                destTituloPro.y = titley;
                // TODO: "PRESS ENTER" logic.........................(0.5p)
                
                if(IsKeyPressed(KEY_UP))
                {
                    if(option > 0)
                    {
                        PlaySound(fxHit);
                        option --;
                    } 
                }
                if(IsKeyPressed(KEY_DOWN))
                {
                    if(option < 2)
                    {    
                        PlaySound(fxHit);
                        option ++;   
                    }
                }
                
                 if(IsKeyPressed(KEY_ENTER))
                {
                   switch(option)
                   {
                        case 0:
                            screen = PLAYER1;
                            option = 0;
                            break;
                            
                        case 1:
                            screen = PLAYER2;
                            option = 0;
                            break;
                        
                        case 2:
                            screen = OPCIONES;
                            option = 0;
                            EscenaAnterior = TITLE;
                            break;
                   }
                }
                
                
            } break;
            case PLAYER1:
            { 
                UpdateMusicStream(musicGameplay);
                
                // Update GAMEPLAY screen data here!
                if(!pause)
                {
                    sourceFondoPro.x ++;
                    // TODO: Ball movement logic.........................(0.2p)
                    
                    rotationBolaPro -= 10;
                    destBolaPro.x += speed.x;
                    destBolaPro.y += speed.y;
                    BolaColaider.x += speed.x;
                    BolaColaider.y += speed.y;
                    
                    
                    // TODO: Player movement logic.......................(0.2p)
                    if(IsKeyDown(KEY_W))
                    {
                        if(destPalapPro.y >= topborde.height + margen)
                        {
                           destPalapPro.y -= 7;
                        }
                    }
                    
                    
                    if(IsKeyDown(KEY_S))
                    {
                        if(destPalapPro.y <= screenHeight - margen - destPalapPro.height)
                        {
                           destPalapPro.y += 7; 
                        }
                    }
                    
                    // TODO: Enemy movement logic (IA)...................(1p)
                    if(BolaColaider.x > screenWidth/2)
                    {
                        if(!colision)
                        {
                            if(BolaColaider.y < destPalaePro.y + BolaColaider.height /2  && destPalaePro.y > topborde.height)
                            {
                                pala2.y -= speedIA;
                                destPalaePro.y -= speedIA; 
                            }
                            else if(BolaColaider.y >= destPalaePro.y  + BolaColaider.height /2 && destPalaePro.y < screenHeight - margen - destPalaePro.height)
                            {
                                pala2.y += speedIA;
                                destPalaePro.y += speedIA; 
                            }
                        }
                    }
                    else
                    {
                        colision = 0;
                    }
                    
                    // TODO: Collision detection (ball-player) logic.....(0.5p)
                    if(CheckCollisionRecs(BolaColaider, destPalapPro) && speed.x < 0)
                    {
                        speed.x *= -1;

                        speed.x ++;
                        PlaySound(fxHit);
                    }
                    
                    // TODO: Collision detection (ball-enemy) logic......(0.5p)
                    if(CheckCollisionRecs(BolaColaider, destPalaePro) && speed.x > 0)
                    {
                        speed.x *= -1;
                        colision = 1;
                        PlaySound(fxHit);
                    }
                    
                    // TODO: Collision detection (ball-limits) logic.....(1p)
                    if(BolaColaider.y + BolaColaider.height >= screenHeight - margen && speed.y > 0)
                    {
                        speed.y *= -1;
                        
                    }
                    else if(BolaColaider.y <= topborde.height && speed.y < 0)
                    {
                        speed.y *= -1;
                        
                    }
                    
                    if(BolaColaider.x + r >= screenWidth - margen && speed.x > 0)
                    {
                        destBolaPro.x = bolax;
                        destBolaPro.y = bolay;
                        BolaColaider = destBolaPro;
                        BolaColaider.x -= destBolaPro.width/2;
                        BolaColaider.y -= destBolaPro.height/2;
                        bolaborde.x = bolax;
                        bolaborde.y = bolay;
                        speed.x = speedIA;
                        speed.x *= -1;
                        pala1.y = palaeY;
                        destPalapPro.y = palaeY - margen;
                        pala2.y = palaeY;
                        destPalaePro.y = palaeY - margen;
                        hitenemy = 1;
                        PlaySound(fxDanyo);
                        
                    }
                    else if(BolaColaider.x - r <= 0 && speed.x < 0)
                    {
                        destBolaPro.x = bolax;
                        destBolaPro.y = bolay;
                        BolaColaider = destBolaPro;
                        BolaColaider.x -= destBolaPro.width/2;
                        BolaColaider.y -= destBolaPro.height/2;
                        bolaborde.x = bolax;
                        bolaborde.y = bolay;
                        speed.x = speedIA;
                        speed.x *= -1;
                        pala1.y = palaeY;
                        destPalapPro.y = palaeY - margen;
                        pala2.y = palaeY;
                        destPalaePro.y = palaeY - margen;
                        hitplayer = 1;
                        PlaySound(fxDanyo);
                        
                    }
                    
                    // TODO: Life bars decrease logic....................(1p)

                    if(hitplayer)
                    {
                        if(cvida <= damage && playerLife > 0)
                        {
                            playerLife --;
                            vidap.width = playerLife;
                            cvida ++;
                        }
                        else
                        {
                            hitplayer = 0;
                            cvida = 0;
                        }
                    }   
                   
                    
                    if(playerLife > 0)
                    {
                        if(hitenemy)
                        {
                            if(cvida <= damage && enemyLife > 0)
                            {
                                enemyLife --;
                                vidae.width = enemyLife;
                                vidae.x ++;
                                cvida ++;
                            }
                            else
                            {
                                hitenemy = 0;
                                cvida = 0;
                            }
                        }
                    }
                    else
                    {
                        gameResult = 1;
                    }
                    // TODO: Time counter logic..........................(0.2p)
                    if(framescounter % 60 == 0)
                    {
                        framescounter2 --;
                    }
                    
                    if(framescounter2 <= 0)
                    {
                        endtime = 1;
                        framescounter2 ++;
                    }
                    else
                    {
                        framescounter--;
                    }

                    // TODO: Game ending logic...........................(0.2p)
                                    
                    if(playerLife <= 0)
                    {
                        gameResult = 0;
                        screen = ENDING;
                    }
                    if(enemyLife <= 0)
                    {
                        gameResult = 1;
                        screen = ENDING;
                    }
                    if(endtime)
                    {
                        if(playerLife > enemyLife)
                        {
                            gameResult = 1;
                            screen = ENDING;
                        }
                        else if(playerLife < enemyLife)
                        {
                            gameResult = 0;
                            screen = ENDING;
                        }
                        else
                        {
                            gameResult = 2;
                            screen = ENDING;
                        }
                    }
                }
                else
                {
                    if(IsKeyPressed(KEY_UP))
                    {
                        if(option > 0)
                        {
                            PlaySound(fxHit);
                            option --;
                        } 
                    }
                    if(IsKeyPressed(KEY_DOWN))
                    {
                        if(option < 2)
                        {    
                            PlaySound(fxHit);
                            option ++;   
                        }
                    }
                    
                     if(IsKeyPressed(KEY_ENTER))
                    {
                       switch(option)
                       {
                            case 0:
                                screen = OPCIONES;
                                option = 0;
                                EscenaAnterior = PLAYER1;
                                break;
                                
                            case 1:
                                pause = !pause;
                                option = 0;
                                break;
                       }
                    }
                }    
                
                // TODO: Pause button logic..........................(0.2p)
                if(IsKeyPressed(KEY_P))
                {
                    pause = !pause;
                }
                
            } break;
            case PLAYER2:
            { 
                UpdateMusicStream(musicGameplay);
                // Update GAMEPLAY screen data here!
                if(!pause)
                {
                    sourceFondoPro.x ++;
                    // TODO: Ball movement logic.........................(0.2p)
                    
                    rotationBolaPro -= 10;
                    destBolaPro.x += speed.x;
                    destBolaPro.y += speed.y;
                    BolaColaider.x += speed.x;
                    BolaColaider.y += speed.y;
                   
                    
                    
                    // TODO: Player movement logic.......................(0.2p)
                    if(IsKeyDown(KEY_W))
                    {
                        if(destPalapPro.y >= topborde.height + margen)
                        {
                           destPalapPro.y -= 7;
                        }
                    }
                    
                    if(IsKeyDown(KEY_S))
                    {
                        if(destPalapPro.y <= screenHeight - margen - destPalapPro.height)
                        {
                           destPalapPro.y += 7; 
                        }
                    }
                    
                    // TODO: Enemy movement logic (IA)...................(1p)
                    
                    if(IsKeyDown(KEY_UP))
                    {
                        if(destPalaePro.y >= topborde.height + margen)
                        {
                           destPalaePro.y -= 7;
                        }
                    }
                    
                    if(IsKeyDown(KEY_DOWN))
                    {
                        if(destPalaePro.y <= screenHeight - margen - destPalaePro.height)
                        {
                           destPalaePro.y += 7; 
                        }
                    }
                    
                    // TODO: Collision detection (ball-player) logic.....(0.5p)
                    if(CheckCollisionRecs(BolaColaider, destPalapPro))
                    {
                        speed.x *= -1;

                        speed.x ++;
                        PlaySound(fxHit);
                    }
                    
                    // TODO: Collision detection (ball-enemy) logic......(0.5p)
                    if(CheckCollisionRecs(BolaColaider, destPalaePro))
                    {
                        speed.x *= -1;
                        colision = 1;
                        PlaySound(fxHit);
                    }
                    
                    // TODO: Collision detection (ball-limits) logic.....(1p)
                    if(BolaColaider.y + BolaColaider.height >= screenHeight - margen && speed.y > 0)
                    {
                        speed.y *= -1;
                        
                    }
                    else if(BolaColaider.y <= topborde.height && speed.y < 0)
                    {
                        speed.y *= -1;
                        
                    }
                    
                    if(BolaColaider.x + r >= screenWidth - margen && speed.x > 0)
                    {
                        destBolaPro.x = bolax;
                        destBolaPro.y = bolay;
                        BolaColaider = destBolaPro;
                        BolaColaider.x -= destBolaPro.width/2;
                        BolaColaider.y -= destBolaPro.height/2;
                        bolaborde.x = bolax;
                        bolaborde.y = bolay;
                        speed.x = speedIA;
                        speed.x *= -1;
                        pala1.y = palaeY;
                        destPalapPro.y = palaeY - margen;
                        pala2.y = palaeY;
                        destPalaePro.y = palaeY - margen;
                        hitenemy = 1;
                        PlaySound(fxDanyo);
                        
                    }
                    else if(BolaColaider.x - r <= 0 && speed.x < 0)
                    {
                        destBolaPro.x = bolax;
                        destBolaPro.y = bolay;
                        BolaColaider = destBolaPro;
                        BolaColaider.x -= destBolaPro.width/2;
                        BolaColaider.y -= destBolaPro.height/2;
                        bolaborde.x = bolax;
                        bolaborde.y = bolay;
                        speed.x = speedIA;
                        speed.x *= -1;
                        pala1.y = palaeY;
                        destPalapPro.y = palaeY - margen;
                        pala2.y = palaeY;
                        destPalaePro.y = palaeY - margen;
                        hitplayer = 1;
                        PlaySound(fxDanyo);
                        
                    }
                    
                    // TODO: Life bars decrease logic....................(1p)

                    if(hitplayer)
                    {
                        if(cvida <= damage && playerLife > 0)
                        {
                            playerLife --;
                            vidap.width = playerLife;
                            cvida ++;
                        }
                        else
                        {
                            hitplayer = 0;
                            cvida = 0;
                        }
                    }   
                   
                    
                    if(playerLife > 0)
                    {
                        if(hitenemy)
                        {
                            if(cvida <= damage && enemyLife > 0)
                            {
                                enemyLife --;
                                vidae.width = enemyLife;
                                vidae.x ++;
                                cvida ++;
                            }
                            else
                            {
                                hitenemy = 0;
                                cvida = 0;
                            }
                        }
                    }
                    else
                    {
                        gameResult = 1;
                    }
                    // TODO: Time counter logic..........................(0.2p)
                    if(framescounter % 60 == 0)
                    {
                        framescounter2 --;
                    }
                    
                    if(framescounter2 <= 0)
                    {
                        endtime = 1;
                        framescounter2 ++;
                    }
                    else
                    {
                        framescounter--;
                    }

                    // TODO: Game ending logic...........................(0.2p)
                                    
                    if(playerLife <= 0)
                    {
                        winplayer2 += 1;
                        gameResult = 5;
                        screen = ENDING;
                    }
                    if(enemyLife <= 0)
                    {
                        winplayer1 += 1;
                        gameResult = 5;
                        screen = ENDING;
                    }
                    if(endtime)
                    { 
                        if(playerLife > enemyLife)
                        {
                            winplayer1 += 1;
                            gameResult = 5;
                            screen = ENDING;
                        }
                        else if(playerLife < enemyLife)
                        {
                            winplayer2 += 1;
                            gameResult = 5;
                            screen = ENDING;
                        }
                        else
                        {
                            gameResult = 5;
                            screen = ENDING;
                        }
                    }
                }
                else
                {
                    if(IsKeyPressed(KEY_UP))
                    {
                        if(option > 0)
                        {
                            PlaySound(fxHit);
                            option --;
                        } 
                    }
                    if(IsKeyPressed(KEY_DOWN))
                    {
                        if(option < 2)
                        {    
                            PlaySound(fxHit);
                            option ++;   
                        }
                    }
                    
                     if(IsKeyPressed(KEY_ENTER))
                    {
                       switch(option)
                       {
                            case 0:
                                screen = OPCIONES;
                                option = 0;
                                EscenaAnterior = PLAYER2;
                                break;
                                
                            case 1:
                                pause = !pause;
                                option = 0;
                                break;
                       }
                    }
                }
                // TODO: Pause button logic..........................(0.2p)
                if(IsKeyPressed(KEY_P))
                {
                    pause = !pause;
                }
                
            } break;
            case OPCIONES: 
            {
                // Update END screen data here!
                UpdateMusicStream(musicOpciones);
                sourceFondo2Pro.x ++;    
                // TODO: Diferentes opciones.
                
                if(sonido)
                {
                    if(IsKeyDown(KEY_LEFT))
                    {
                        if(volumen >= 0)
                        {
                            volumen -= 0.01;
                            barra_sonido.width -= 3;
                        } 
                    }
                    if(IsKeyDown(KEY_RIGHT))
                    {
                        if(volumen <= 1 &&  barra_sonido.width < 300)
                        {
                            volumen += 0.01;
                            barra_sonido.width += 3;
                        } 
                    }
                    
                    if(IsKeyPressed(KEY_ENTER))
                    {
                        sonido = false;
                    }
                    
                    SetMasterVolume(volumen);
                    
                    
                }
                else if(controles)
                {
                    if(IsKeyPressed(KEY_ENTER))
                    {
                        controles = false;
                    }
                }
                else
                {
                     if(IsKeyPressed(KEY_UP))
                    {
                        if(option > 0)
                        {
                            PlaySound(fxHit);
                            option --;
                        } 
                    }
                    if(IsKeyPressed(KEY_DOWN))
                    {
                        if(option < 3)
                        {    
                            PlaySound(fxHit);
                            option ++;   
                        }
                    }
                    
                    if(IsKeyPressed(KEY_ENTER))
                    {
                        switch(option)
                        {
                            case 0:
                                sonido = true;
                                break;
                            
                            case 1:
                                controles = true;
                                break;

                            case 2:
                                destBolaPro.x = bolax;
                                destBolaPro.y = bolay;
                                BolaColaider = destBolaPro;
                                BolaColaider.x -= destBolaPro.width/2;
                                BolaColaider.y -= destBolaPro.height/2;
                                speed.x = speedIA;
                                speed.x *= -1;
                                pala1.y = palaeY;
                                destPalapPro.y = palaeY - margen;
                                pala2.y = palaeY;
                                destPalaePro.y = palaeY - margen;
                                playerLife = screenWidth/2 - 50;
                                enemyLife = screenWidth/2 - 50;
                                hitplayer = 0;
                                hitenemy = 0;
                                cvida = 0;
                                framescounter = 60000;
                                framescounter2 = 100;
                                vidap = vidapr;
                                vidae = vidaer;
                                screen = TITLE;
                                option = 0;
                                pause = false;
                                break;
                                
                            case 3:
                                screen = EscenaAnterior;
                                option = 0;
                                break;  
                        }
                    }
                }
                
               
                
                
                
            } break;
            case ENDING: 
            {
                // Update END screen data here!
                UpdateMusicStream(musictoepic);
                sourceFondo2Pro.x ++;    
                // TODO: Replay / Exit game logic....................(0.5p)
                if(IsKeyPressed(KEY_UP))
                {
                    if(option > 0)
                    {
                        PlaySound(fxHit);
                        option --;
                    } 
                }
                if(IsKeyPressed(KEY_DOWN))
                {
                    if(option < 2)
                    {    
                        PlaySound(fxHit);
                        option ++;   
                    }
                }
                
                 if(IsKeyPressed(KEY_ENTER))
                {
                   switch(option)
                   {
                        case 0:
                            destBolaPro.x = bolax;
                            destBolaPro.y = bolay;
                            BolaColaider = destBolaPro;
                            BolaColaider.x -= destBolaPro.width/2;
                            BolaColaider.y -= destBolaPro.height/2;
                            speed.x = speedIA;
                            speed.x *= -1;
                            pala1.y = palaeY;
                            destPalapPro.y = palaeY - margen;
                            pala2.y = palaeY;
                            destPalaePro.y = palaeY - margen;
                            playerLife = screenWidth/2 - 50;
                            enemyLife = screenWidth/2 - 50;
                            hitplayer = 0;
                            hitenemy = 0;
                            cvida = 0;
                            framescounter = 60000;
                            framescounter2 = 100;
                            vidap = vidapr;
                            vidae = vidaer;
                            screen = TITLE;
                            break;
                            
                        case 1:
                            UnloadTexture(textureLogo);
                            UnloadTexture(textureFondo1);
                            UnloadTexture(textureTitulo);
                            UnloadTexture(textureFondo2);
                            UnloadTexture(texture1player);
                            UnloadTexture(texture1player_s);
                            UnloadTexture(texture2player);
                            UnloadTexture(texture2player_s);
                            UnloadTexture(textureoptions);
                            UnloadTexture(textureoptions_s);
                            UnloadTexture(textureFondo);
                            UnloadTexture(textureVida);
                            UnloadTexture(textureVidae);
                            UnloadTexture(texturePalap);
                            UnloadTexture(texturePalae);
                            UnloadTexture(textureBola);
                            UnloadTexture(texturePlay);
                            UnloadTexture(texturePlay_s);
                            UnloadTexture(textureSonido);
                            UnloadTexture(textureSonido_s);
                            UnloadTexture(textureControles);
                            UnloadTexture(textureControles_s);
                            UnloadTexture(textureMenu);
                            UnloadTexture(textureMenu_s);
                            UnloadTexture(textureReturn);
                            UnloadTexture(textureReturn_s);
                            UnloadTexture(textureImg_controles);
                            UnloadTexture(textureRestart);
                            UnloadTexture(textureRestart_s);
                            UnloadTexture(textureExit);
                            UnloadTexture(textureExit_s);
                            
                            UnloadMusicStream(musicGameplay);
                            UnloadMusicStream(musictoepic);
                            UnloadMusicStream(musicOpciones);
                            UnloadSound(fxHit);
                            UnloadSound(fxDanyo);
                            CloseWindow();
                            break;
                   }
                }
                
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            switch(screen) 
            {
                case LOGO: 
                {
                    // Draw LOGO screen here!
                    
                    // TODO: Draw Logo...............................(0.2p)
                    DrawTexturePro(textureFondo1, sourceFondo1Pro, destFondo1Pro, originFondo1, rotationFondo1Pro, WHITE);
                    DrawTexturePro(textureLogo, sourceLogoPro, destLogoPro, originLogo, rotationLogoPro, Fade(WHITE, alpha));
                  
                } break;
                case TITLE: 
                {
                    // Draw TITLE screen here!
                    DrawTexturePro(textureFondo2, sourceFondo2Pro, destFondo2Pro, originFondo2, rotationFondo2Pro, WHITE);
                    
                    // TODO: Draw Title..............................(0.2p)
                    DrawTexturePro(textureTitulo, sourceTituloPro, destTituloPro, originTitulo, rotationTituloPro, WHITE);
                    
                    // TODO: Draw "PRESS ENTER" message..............(0.2p)
                    
                    DrawTexturePro(texture1player, source1playerPro, dest1playerPro, origin1player, rotation1playerPro, WHITE);
                    DrawTexturePro(texture2player, source2playerPro, dest2playerPro, origin2player, rotation2playerPro, WHITE);
                    DrawTexturePro(textureoptions, sourceoptionsPro, destoptionsPro, originoptions, rotationoptionsPro, WHITE);
                    
                    switch(option)
                    {
                        case 0:
                            DrawTexturePro(texture1player_s, source1playerPro, dest1playerPro, origin1player, rotation1playerPro, WHITE);
                            break;
                            
                        case 1:
                            DrawTexturePro(texture2player_s, source2playerPro, dest2playerPro, origin2player, rotation2playerPro, WHITE);
                            break;
                        
                        case 2:
                            DrawTexturePro(textureoptions_s, sourceoptionsPro, destoptionsPro, originoptions, rotationoptionsPro, WHITE);
                            break;
                    }
                   
                } break;
                case PLAYER1:
                { 
                    // Draw GAMEPLAY screen here!
                    DrawTexturePro(textureFondo, sourceFondoPro, destFondoPro, originFondo, rotationFondoPro, WHITE);
                    
                    //Porterias//
                    DrawRectangleRec(porteriaL, MyYellow);
                    DrawRectangleRec(porteriaR, MyPurple);
                    
                    //Bola//
                    DrawRectangleRec(BolaColaider, Fade(WHITE, 0));
                    DrawTexturePro(textureBola, sourceBolaPro, destBolaPro, originBola, rotationBolaPro, WHITE);
                    
                    // TODO: Draw player and enemy...................(0.2p)

                    DrawTexturePro(texturePalap, sourcePalapPro, destPalapPro, originPalap, rotationPalapPro, YELLOW);
                    DrawTexturePro(texturePalae, sourcePalaePro, destPalaePro, originPalae, rotationPalaePro, MAGENTA);
                    
                    // TODO: Draw player and enemy life bars.........(0.5p)
                    //Vidas//
                    DrawRectangleRec(vidapr, MyRed); 
                    DrawRectangleRec(vidap, MyYellow); 
                    
                    DrawRectangleRec(vidaer, MyRed);
                    DrawRectangleRec(vidae, MyPurple);
                    
                    DrawTexturePro(textureVida, sourceVidaPro, destVidaPro, originVida, rotationVidaPro, WHITE);
                    DrawTexturePro(textureVidae, sourceVidaePro, destVidaePro, originVidae, rotationVidaePro, WHITE);
                    
                    // TODO: Draw time counter.......................(0.5p)
                    //Contador//
                    DrawText(FormatText("%i",framescounter2-1), screenWidth / 2 - MeasureText(FormatText("%i",framescounter2-1), 40)/2, 10, 40, WHITE);
                    
                    // TODO: Draw pause message when required........(0.5p)
                    if(pause)
                    {
                        DrawRectangle(0,0,screenWidth,screenHeight, Fade(BLACK, 0.7));
                        DrawText("PAUSE", screenWidth/2 - MeasureText("PAUSE", 100) / 2, screenHeight/2 - 100, 100, WHITE);
                        DrawTexturePro(textureoptions, sourceoptionsPro, destRestartPro, originoptions, rotationoptionsPro, WHITE);
                        DrawTexturePro(texturePlay, sourcePlayPro, destExitPro, originPlay, rotationPlayPro, WHITE);
                        
                        switch(option)
                        {
                            case 0:
                                DrawTexturePro(textureoptions_s, sourceoptionsPro, destRestartPro, originoptions, rotationoptionsPro, WHITE);
                                break;
                                
                            case 1:
                                DrawTexturePro(texturePlay_s, sourcePlayPro, destExitPro, originPlay, rotationPlayPro, WHITE);
                                break;
                        }
                    }                    
                } break;
                
                case PLAYER2:
                { 
                    // Draw GAMEPLAY screen here!
                    DrawTexturePro(textureFondo, sourceFondoPro, destFondoPro, originFondo, rotationFondoPro, WHITE);
                    
                    //Porterias//
                    DrawRectangleRec(porteriaL, MyYellow);
                    DrawRectangleRec(porteriaR, MyPurple);

                    //Bola//
                    DrawRectangleRec(BolaColaider, Fade(WHITE, 0));
                    DrawTexturePro(textureBola, sourceBolaPro, destBolaPro, originBola, rotationBolaPro, WHITE);
                    
                    // TODO: Draw player and enemy...................(0.2p)
                    //Palas//
                    DrawTexturePro(texturePalap, sourcePalapPro, destPalapPro, originPalap, rotationPalapPro, YELLOW);
                    DrawTexturePro(texturePalae, sourcePalaePro, destPalaePro, originPalae, rotationPalaePro, MAGENTA);
                    
                    // TODO: Draw player and enemy life bars.........(0.5p)
                    //Vidas//
                    DrawRectangleRec(vidapr, MyRed); 
                    DrawRectangleRec(vidap, MyYellow); 

                    DrawRectangleRec(vidaer, MyRed);
                    DrawRectangleRec(vidae, MyPurple);
                    
                    DrawTexturePro(textureVida, sourceVidaPro, destVidaPro, originVida, rotationVidaPro, WHITE);
                    DrawTexturePro(textureVidae, sourceVidaePro, destVidaePro, originVidae, rotationVidaePro, WHITE);
                    
                    // TODO: Draw time counter.......................(0.5p)
                    //Contador//
                    DrawText(FormatText("%i",framescounter2-1), screenWidth / 2 - MeasureText(FormatText("%i",framescounter2-1), 40)/2, 10, 40, WHITE);
                    
                    // TODO: Draw pause message when required........(0.5p)
                    if(pause)
                    {
                        DrawRectangle(0,0,screenWidth,screenHeight, Fade(BLACK, 0.7));
                        DrawText("PAUSE", screenWidth/2 - MeasureText("PAUSE", 100) / 2, screenHeight/2 - 100, 100, WHITE);
                        DrawTexturePro(textureoptions, sourceoptionsPro, destRestartPro, originoptions, rotationoptionsPro, WHITE);
                        DrawTexturePro(texturePlay, sourcePlayPro, destExitPro, originPlay, rotationPlayPro, WHITE);
                        
                        switch(option)
                        {
                            case 0:
                                DrawTexturePro(textureoptions_s, sourceoptionsPro, destRestartPro, originoptions, rotationoptionsPro, WHITE);
                                break;
                                
                            case 1:
                                DrawTexturePro(texturePlay_s, sourcePlayPro, destExitPro, originPlay, rotationPlayPro, WHITE);
                                break;
                        }
                    }            
                    
                } break;
                case OPCIONES: 
                {
                    // Draw END screen here!
                    DrawTexturePro(textureFondo2, sourceFondo2Pro, destFondo2Pro, originFondo2, rotationFondo2Pro, WHITE);
                    // TODO: Draw ending message (win or loose)......(0.2p)
                    
                    if(sonido)
                    {
                        DrawText("SOUND", screenWidth/2 - MeasureText("SOUND", 100) / 2, 10, 100, WHITE);
                        DrawRectangleRec(barra_sonido_f, Fade(GRAY, 0.5));
                        DrawRectangleRec(barra_sonido, RED);
                        DrawTexturePro(textureReturn_s, sourceMenuPro, destMenuPro, originMenu, rotationMenuPro, WHITE);    
                    }
                    else if(controles)
                    {
                        DrawText("CONTROLS", screenWidth/2 - MeasureText("CONTROLS", 100) / 2,10, 100, WHITE);
                        DrawTexturePro(textureImg_controles, sourceImg_controlesPro, destImg_controlesPro, originImg_controles, rotationImg_controlesPro, WHITE); 
                        DrawTexturePro(textureReturn_s, sourceMenuPro, destReturnPro, originMenu, rotationMenuPro, WHITE);    
                    }
                    else
                    {
                        DrawText("OPTIONS", screenWidth/2 - MeasureText("OPTIONS", 100) / 2, 10, 100, WHITE);

                        DrawTexturePro(textureSonido, sourceSonidoPro, destSonidoPro, originSonido, rotationSonidoPro, WHITE);
                        DrawTexturePro(textureControles, sourceControlesPro, destControlesPro, originControles, rotationControlesPro, WHITE);
                        DrawTexturePro(textureMenu, sourceMenuPro, destMenuPro, originMenu, rotationMenuPro, WHITE);
                        DrawTexturePro(textureReturn, sourceReturnPro, destReturnPro, originReturn, rotationReturnPro, WHITE);

                        switch(option)
                        {
                            case 0:
                                DrawTexturePro(textureSonido_s, sourceSonidoPro, destSonidoPro, originSonido, rotationSonidoPro, WHITE);
                                break;
                                
                            case 1:
                                DrawTexturePro(textureControles_s, sourceControlesPro, destControlesPro, originControles, rotationControlesPro, WHITE);
                                break;
                                
                            case 2:
                                DrawTexturePro(textureMenu_s, sourceMenuPro, destMenuPro, originMenu, rotationMenuPro, WHITE);
                                break;
                                
                            case 3:
                                DrawTexturePro(textureReturn_s, sourceReturnPro, destReturnPro, originReturn, rotationReturnPro, WHITE);
                                break;
                        }                    
                    }
                    
                } break;
                case ENDING: 
                {
                    // Draw END screen here!
                    DrawTexturePro(textureFondo2, sourceFondo2Pro, destFondo2Pro, originFondo2, rotationFondo2Pro, WHITE);
                    
                    // TODO: Draw ending message (win or loose)......(0.2p)
                    if(gameResult == 0)
                    {
                        DrawText("LOSE", screenWidth/2 - MeasureText("LOSE", 100) / 2, screenHeight/2 - 100, 100, WHITE);
                    }
                    else if(gameResult == 1)
                    {
                        DrawText("WIN", screenWidth/2 - MeasureText("WIN", 100) / 2, screenHeight/2 - 100, 100, WHITE);    
                    }
                    else if(gameResult == 5)
                    {
                        DrawText(FormatText("%i - %i",winplayer1, winplayer2), screenWidth/2 - MeasureText(FormatText("%i - %i",winplayer1, winplayer2), 100) / 2, screenHeight/2 - 100, 100, WHITE);    
                    }
                    else
                    {  
                        DrawText("DRAW", screenWidth/2 - MeasureText("DRAW", 100) / 2, screenHeight/2 - 100, 100, WHITE);
                    }
                    
                    DrawTexturePro(textureRestart, sourceRestartPro, destRestartPro, originRestart, rotationRestartPro, WHITE);
                    DrawTexturePro(textureExit, sourceExitPro, destExitPro, originExit, rotationExitPro, WHITE);

                    switch(option)
                    {
                        case 0:
                            DrawTexturePro(textureRestart_s, sourceRestartPro, destRestartPro, originRestart, rotationRestartPro, WHITE);
                            break;
                            
                        case 1:
                            DrawTexturePro(textureExit_s, sourceExitPro, destExitPro, originExit, rotationExitPro, WHITE);
                            break;
                    }                    
                    
                } break;
                default: break;
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    
    // NOTE: Unload any Texture2D or SpriteFont loaded here
    UnloadTexture(textureLogo);
    UnloadTexture(textureFondo1);
    UnloadTexture(textureTitulo);
    UnloadTexture(textureFondo2);
    UnloadTexture(texture1player);
    UnloadTexture(texture1player_s);
    UnloadTexture(texture2player);
    UnloadTexture(texture2player_s);
    UnloadTexture(textureoptions);
    UnloadTexture(textureoptions_s);
    UnloadTexture(textureFondo);
    UnloadTexture(textureVida);
    UnloadTexture(textureVidae);
    UnloadTexture(texturePalap);
    UnloadTexture(texturePalae);
    UnloadTexture(textureBola);
    UnloadTexture(texturePlay);
    UnloadTexture(texturePlay_s);
    UnloadTexture(textureSonido);
    UnloadTexture(textureSonido_s);
    UnloadTexture(textureControles);
    UnloadTexture(textureControles_s);
    UnloadTexture(textureMenu);
    UnloadTexture(textureMenu_s);
    UnloadTexture(textureReturn);
    UnloadTexture(textureReturn_s);
    UnloadTexture(textureImg_controles);
    UnloadTexture(textureRestart);
    UnloadTexture(textureRestart_s);
    UnloadTexture(textureExit);
    UnloadTexture(textureExit_s);
    
    UnloadMusicStream(musicGameplay);
    UnloadMusicStream(musictoepic);
    UnloadMusicStream(musicOpciones);
    UnloadSound(fxHit);
    UnloadSound(fxDanyo);
    
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}