#include "Game.h"
using namespace std;
int iScore = 0;
Game::Game()
{

    /* SDL初始化*/
    if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0 )
    {
        cout<<"SDL could not initialize! SDL_Error: "<< SDL_GetError()<<endl;

    }

    //创建窗口对象
    window = SDL_CreateWindow("Flappy Bird", //标题
                              SDL_WINDOWPOS_CENTERED,//横向剧中
                              SDL_WINDOWPOS_CENTERED,//纵向居中
                              SCREEN_WIDTH,//窗口宽度
                              SCREEN_HEIGHT, //窗口高度
                              SDL_WINDOW_SHOWN );//窗口样式：创建后立即显示并全屏
    if( window == NULL )
    {
        cout<<"Window could not be created! SDL_Error:"<< SDL_GetError()<<endl;

    }

    //创建渲染器
    screenRen = SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if( screenRen == NULL )
    {
        cout<<"Render could not be get! SDL_Error: "<< SDL_GetError()<<endl;

    }

}
void Game::run()
{
    ObjectInit();
    SetGameStatus(preStart);
    while(GameStatus != Quit)
    {
        EventHandler();
        Motion();
        Drawer();
        Collision();
    }

}

void Game::SetGameStatus(eGameStatus _GameStatus)
{
    GameStatus = _GameStatus;
    objBackground->SetGameStatus(_GameStatus);

}
void Game::EventHandler()
{
    if (SDL_PollEvent(&Event))
    {
        if (Event.type == SDL_QUIT)
        {
            SetGameStatus(Quit);
        }
        else if ( Event.type == SDL_KEYDOWN)
        {

            KeyEventHandler(&(Event.key));

        }
        else if (Event.type == SDL_MOUSEBUTTONDOWN)
        {
            MouseEventHandler();
        }

        objBird->EventHandler(&Event);

    }
}
void Game::MouseEventHandler()
{
    if (GameStatus == preStart ||GameStatus ==Pause)
    {
        SetGameStatus(Running);
    }

}
void Game::KeyEventHandler(SDL_KeyboardEvent* KeyEvent)
{
    switch (KeyEvent->keysym.scancode)
    {
    case SDL_SCANCODE_ESCAPE:
        if(GameStatus == Running)
        {
            SetGameStatus(Pause);
        }
        else if(GameStatus == Pause)
        {
            SetGameStatus(preStart);
        }
        else if(GameStatus == preStart || GameStatus == Over)
        {
            SetGameStatus(Quit);
        }

        break;
    case SDL_SCANCODE_SPACE:
        if(GameStatus == Over)
        {
            Reset();
            SetGameStatus(preStart);
        }

        break;

    default:
        break;



    }
}
void Game::Motion()
{
    objGround->Motion();
    mgnPipeSet->Motion();
    objBird->Motion();
}
void Game::Drawer()
{
    EnvironmentDrawer();
    ObjectDrawer();
    SDL_RenderPresent(screenRen);
}
void Game::EnvironmentDrawer()
{
    objBackground->Draw();
    objGround->Draw();



}
void Game::ObjectDrawer()
{

    mgnPipeSet->Draw();
    objBird->Draw();
    objScore->Draw(iScore);
    switch(GameStatus)
    {

    case preStart:
        objTextReady->Draw();
        objTextTips->Draw();
        break;
    case Running:

        break;
    case Pause:
        objTextTips->Draw();
        break;
    case Over:
        objTextOver->Draw();
        objTextTips->Draw();
        break;
        case Quit:break;
        default:break;
    }

}

void Game::ObjectInit()
{
    objBackground = new BackGround(screenRen,".//Res//bg.png");
    objTextReady = new Object(screenRen,".//Res//ready.png");
    objTextReady->SetRect(SCREEN_WIDTH*0.35,SCREEN_HEIGHT/5,SCREEN_WIDTH/3,SCREEN_WIDTH/10);
    objTextOver = new Object(screenRen,".//Res//over.png");
    objTextOver->SetRect(SCREEN_WIDTH*0.35,SCREEN_HEIGHT/5,SCREEN_WIDTH/3,SCREEN_WIDTH/10);
    objTextTips = new Object(screenRen,".//Res//tips.png");
    objTextTips->SetRect(10,SCREEN_HEIGHT *0.4,SCREEN_WIDTH-10,SCREEN_HEIGHT /4);
    objGround = new Ground(screenRen,".//Res//ground.png");
    objGround->SetRect(0,SCREEN_HEIGHT- SCREEN_HEIGHT /4,2* SCREEN_WIDTH,SCREEN_HEIGHT /4);
    mgnPipeSet = new PipeSetManager(screenRen,SCREEN_WIDTH/9,SCREEN_HEIGHT- SCREEN_HEIGHT /4,110);
    objBird = new Bird(screenRen,".//Res//bird.png");
    objBird->SetRect(SCREEN_WIDTH/3,SCREEN_HEIGHT/3,SCREEN_WIDTH/12,25);
    objScore = new Score(screenRen,".//Res//number.png");

}
void Game::Reset()
{
    mgnPipeSet->Reset();
    objBird->ReSet();
    iScore = 0;
}
void Game::Collision()
{
    if(GameStatus == Running)
    {
        if( mgnPipeSet->CollisionCheck(objBird->GetRect()) == 0)
        {
        SetGameStatus(Over);

        }

    }

}
Game::~Game()
{
    delete objBackground;
    delete objTextReady;
    delete objTextOver;
    delete objTextTips;
    delete objGround;
    delete mgnPipeSet;
    delete objBird;
    delete objScore;
    SDL_DestroyRenderer(screenRen);
    SDL_DestroyWindow(window);
}
