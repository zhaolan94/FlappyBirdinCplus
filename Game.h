#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include "Object.h"
#include "type.h"
class Game
{
private:
    //Data Field
    eGameStatus GameStatus = preStart;

    SDL_Window* window = NULL; //SDL����ָ��
    SDL_Renderer* screenRen = NULL;//SDL��Ⱦ��
    SDL_Event Event;//SDL�¼��ṹ
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
    //End Methon
public:
    //Data Field
    //End

    //Methon
    Game();//init Game
    ~Game();
    void run();

    //End

};


#endif // GAME_H_INCLUDED
