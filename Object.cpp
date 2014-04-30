#include "Object.h"
using namespace std;

Object::Object(SDL_Renderer *_Render,std::string file)
{
    //Bug:Para not check
    objRen = _Render;
    objTexture = LoadImage(file);
    objRect = new SDL_Rect;

}
SDL_Texture* Object::LoadImage(std::string file)
{
    SDL_Texture* tex = nullptr;
    tex = IMG_LoadTexture(objRen, file.c_str());
    if (tex == nullptr)
    {
        cout<<"Failed to load image: " << IMG_GetError();

        return NULL;
    }

    return tex;
}
void Object::EventHandler(SDL_Event *Event)
{
    ;
}

void Ground::Motion()
{
    cout<<"Motion"<<GameStatus<<endl;
    if(GameStatus == Running ||GameStatus == preStart )
    {
        if (objRect->x >(-objRect->w/2) )
        {
            objRect->x =objRect->x-VeloX ;
        }
        else
        {
            objRect->x = 0;
        }
    }
}



void Pipe::Motion()
{
    if(GameStatus == Running)
    {

        objRect->x =objRect->x-VeloX ;

    }
}
void Bird::Motion()
{
    if(GameStatus == Running)
    {
        if(objRect->y<-(1.0*objRect->h))
        {
            objRect->y =- 1.0*objRect->h;
            vy = -vy;
        }
        if(objRect->y> (SCREEN_HEIGHT-SCREEN_HEIGHT/4)-objRect->h)
        {
            objRect->y =SCREEN_HEIGHT-SCREEN_HEIGHT/4-objRect->h;
            vy = -0.25*vy;
        }
        else
        {
            objRect->y = objRect->y + vy;
            vy += gravity;
        }

    }
}
void Bird::Draw()
{
    if(GameStatus == Running ||GameStatus == Pause ||GameStatus == Over)
    {
        SDL_RenderCopy(objRen,objTexture,NULL,objRect);
    }



}
void Bird::EventHandler(SDL_Event *Event)
{
    if(GameStatus ==Running)
    {
        if (Event ->type == SDL_MOUSEBUTTONDOWN)
        {
            vy = -6.0;
        }
        else if(Event->type ==SDL_KEYDOWN && (Event->key).keysym.scancode == SDL_SCANCODE_SPACE)
        {
            vy = -6.0;
        }
    }

}
PipeSet::PipeSet(SDL_Renderer *_Render,int width,int height,int gap)
{
    SDL_Rect *upRect=nullptr;
    upPipe = new Pipe(_Render,".//Res//up.png");
    downPipe = new Pipe(_Render,".//Res//down.png");
    upPipe->SetRect(SCREEN_WIDTH,0,width,height*(0.1*(SDL_GetTicks()%10)+1)/4);
    upRect = upPipe->GetRect();
    downPipe->SetRect(SCREEN_WIDTH,upRect->h+gap,width,height-(upRect->h+gap));
}
int PipeSet::CollisionCheck(SDL_Rect *_Bird)
{
    SDL_Rect *upRect,*downRect;
    upRect =upPipe->GetRect();
    downRect =downPipe->GetRect();
    if(_Bird->y >= upRect->y && (_Bird->y <= upRect->y+upRect->h) || _Bird->y+_Bird->h >= upRect->y && (_Bird->y+_Bird->h <= upRect->y+upRect->h))
    {
        if(_Bird->x >= upRect->x && _Bird->x <= (upRect->x+upRect->w))
        {
            return 0;
        }
        if((_Bird->x+_Bird->w) >= upRect->x && (_Bird->x+_Bird->w) <= (upRect->x+upRect->w))
        {
            return 0;
        }
    }
    if((_Bird->y+_Bird->h) >= downRect->y &&(_Bird->y+_Bird->h) <= (downRect->y+downRect->h))
    {
        if(_Bird->x >= downRect->x && _Bird->x <= (downRect->x+downRect->w))
        {
            return 0;
        }
        if((_Bird->x+_Bird->w) >= downRect->x && (_Bird->x+_Bird->w) <= (downRect->x+downRect->w))
        {
            return 0;
        }
    }
    return -1;

}
PipeSetManager::PipeSetManager(SDL_Renderer *_Render,int _width,int _height,int _gap)
{
    width = _width,height= _height,gap=_gap;
    screenRen= _Render;
    tmpPipe = new PipeSet(screenRen,width,height,gap);
    listPipe.push_back(*tmpPipe);

}
void PipeSetManager::Draw()
{
    if(!listPipe.empty())
    {
        for(iterPipe=listPipe.begin(); iterPipe!=listPipe.end(); iterPipe++)
        {
            iterPipe->Draw();

        }
    }
}
void PipeSetManager::Motion()
{
    SetPipeStatus();
    if(!listPipe.empty())
    {
        for(iterPipe=listPipe.begin(); iterPipe!=listPipe.end(); iterPipe++)
        {
            if(iterPipe->GetX() < (-width))
            {
                listPipe.pop_front();
                continue;
            }
            if( SCREEN_WIDTH-(iterPipe->GetX()) ==3*width)
            {

                tmpPipe = new PipeSet(screenRen,width,height,gap);
                listPipe.push_back(*tmpPipe);

            }
            iterPipe->Motion();

        }
    }
}
void PipeSetManager::SetGameStatus(eGameStatus _GameStatus)
{
    GameStatus = _GameStatus;
    if(GameStatus == preStart)
    {
        iterPipe=listPipe.begin();
        if(iterPipe->GetX()!=SCREEN_WIDTH)
        {
            listPipe.clear();
            tmpPipe = new PipeSet(screenRen,width,height,gap);
            listPipe.push_back(*tmpPipe);
        }
    }
}
void PipeSetManager::SetPipeStatus()
{
    if(!listPipe.empty())
    {

        for(iterPipe=listPipe.begin(); iterPipe!=listPipe.end(); iterPipe++)
        {
            iterPipe->SetGameStatus(GameStatus);
        }
    }
}
int PipeSetManager::CollisionCheck(SDL_Rect *_Bird)
{
    if(!listPipe.empty())
    {

        for(iterPipe=listPipe.begin(); iterPipe!=listPipe.end(); iterPipe++)
        {
            if(iterPipe->CollisionCheck(_Bird) ==0 )
            {
                return 0;
            }
        }
    }
    return -1;
}
/*Bug :What the hell that error comes from surface loading by SDL_IMAGE
ImageScore::ImageScore(SDL_Renderer *_Renderer)
{
    int i = 0;
    int alpha;
    SDL_Surface *surAllNum;
    surAllNum = IMG_Load(".//Res//number.png");
 //   SDL_CreateTextureFromSurface(NULL,surAllNum);
    SDL_GetSurfaceAlphaMod(surAllNum,alpha);//What the hell?!!
    SDL_Surface *surEachNum;
    SDL_Rect rectNum = {0,0,67.5,100};

    while(rectNum.x != 675)
    {
    SDL_BlitScaled(surAllNum,NULL,surEachNum,NULL);


        objNum = new Object(_Renderer,surEachNum);//What the hell?!!
        i++;
        rectNum.x += 67.5;
        cout<<"shit"<<endl;


    }
}
*/
