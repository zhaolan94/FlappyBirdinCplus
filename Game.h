#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Drawer.h"
#include "EventHandler.h"
#include "Object.h"
#include "type.h"
class Game
{
private:
    //Data Field
    eGameStatus GameStatus = preStart;

    SDL_Window* window = NULL; //SDL窗口指针
    SDL_Surface* screenSurface = NULL;//SDL表面指针
    SDL_Renderer* screenRen = NULL;//SDL渲染器
    SDL_TimerID mainTimer;//SDL计时器
    SDL_Event Event;//SDL事件结构
    SDL_Texture *background = nullptr;

    BackGround *objBackground = nullptr;
    Object *objTextReady = nullptr;
    Object *objTextOver = nullptr;
    Object *objTextTips = nullptr;
    Ground *objGround = nullptr;
    PipeSetManager *mgnPipeSet = nullptr;
    Bird *objBird = nullptr;
    Score *objScore = nullptr;



    //End

    //Methon
    void ObjectInit();
    void SetGameStatus(eGameStatus _GameStatus);
    void Motion();
    void Reset();
    //EventHandle
    void EventHandler();
    void KeyEventHandler(SDL_KeyboardEvent* KeyEvent);
    void MouseEventHandler();
    //End EventHandle
    //Drawer
    void Drawer();
    void EnvironmentDrawer();
    void ObjectDrawer();
    //End Drawer
    void Collision();
    //SomeUnitily
    SDL_Texture* LoadImage(std::string file);
    //End Methon
public:
    //Data Field




    //End

    //Methon
    Game();//init Game
    void run();

    //End

};


#endif // GAME_H_INCLUDED
