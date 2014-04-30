#include "Game.h"
using namespace std;
int Score;
Game::Game()
{

    /* SDL��ʼ��*/
    if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_TIMER ) < 0 )
    {
        cout<<"SDL could not initialize! SDL_Error: "<< SDL_GetError()<<endl;

    }

    //�������ڶ���
    window = SDL_CreateWindow("Flappy Bird", //����
                              SDL_WINDOWPOS_CENTERED,//�������
                              SDL_WINDOWPOS_CENTERED,//�������
                              SCREEN_WIDTH,//���ڿ��
                              SCREEN_HEIGHT, //���ڸ߶�
                              SDL_WINDOW_SHOWN );//������ʽ��������������ʾ��ȫ��
    if( window == NULL )
    {
        cout<<"Window could not be created! SDL_Error:"<< SDL_GetError()<<endl;

    }

    //������Ⱦ��
    screenRen = SDL_CreateRenderer(window,
                                   -1,
                                   SDL_RENDERER_ACCELERATED| SDL_RENDERER_PRESENTVSYNC);
    if( screenRen == NULL )
    {
        cout<<"Render could not be get! SDL_Error: "<< SDL_GetError()<<endl;

    }
   // SDL_RenderSetScale(screenRen,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

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
        else if(GameStatus == preStart)
        {
            SetGameStatus(Quit);
        }

        break;
    case SDL_SCANCODE_SPACE:
        if (GameStatus == preStart ||GameStatus ==Pause)
        {
            SetGameStatus(Running);
        }

        break;
    case SDL_SCANCODE_RETURN:
        if(GameStatus == Over)
        {
            Reset();
            SetGameStatus(preStart);
        }
        break;
    default:break;



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
    switch(GameStatus)
    {

    case preStart:
        objTextReady->Draw();
        break;
    case Running:

        break;
    case Pause:
        break;
    case Over:
        objTextOver->Draw();
        break;
    }

}
SDL_Texture* Game::LoadImage(std::string file)
{
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(screenRen, file.c_str());
    if (tex == nullptr)
    {
        cout<<"Failed to load image: " << IMG_GetError();
        GameStatus = Quit;
        return NULL;
    }

    return tex;
}
void Game::ObjectInit()
{
    objBackground = new BackGround(screenRen,".//Res//bg.png");
    objTextReady = new Object(screenRen,".//Res//ready.png");
    objTextReady->SetRect(SCREEN_WIDTH*0.35,SCREEN_HEIGHT/4,SCREEN_WIDTH/3,SCREEN_WIDTH/10);
    objTextOver = new Object(screenRen,".//Res//over.png");
    objTextOver->SetRect(SCREEN_WIDTH*0.35,SCREEN_HEIGHT/4,SCREEN_WIDTH/3,SCREEN_WIDTH/10);
    objGround = new Ground(screenRen,".//Res//ground.png");
    objGround->SetRect(0,SCREEN_HEIGHT- SCREEN_HEIGHT /4,2* SCREEN_WIDTH,SCREEN_HEIGHT /4);
    mgnPipeSet = new PipeSetManager(screenRen,SCREEN_WIDTH/9,SCREEN_HEIGHT- SCREEN_HEIGHT /4,100);
    objBird = new Bird(screenRen,".//Res//bird.png");
    objBird->SetRect(SCREEN_WIDTH/3,SCREEN_HEIGHT/3,SCREEN_WIDTH/12,25);

}
void Game::Reset()
{
    mgnPipeSet->Reset();
    objBird->ReSet();
}
void Game::Collision()
{
    if(GameStatus == Running)
    {
        if( mgnPipeSet->CollisionCheck(objBird->GetRect()) == 0)
        {
            SetGameStatus(Over);

        }
        Score++;
    }

}
