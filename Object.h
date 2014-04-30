#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <list>
#include "type.h"
using namespace std;

class Object
{
protected:
    static eGameStatus GameStatus;
    SDL_Renderer *objRen = nullptr;
    SDL_Texture *objTexture = nullptr;
    SDL_Texture* LoadImage(std::string file);
    SDL_Rect *objRect=nullptr;

public:
    Object(){objRect = new SDL_Rect;};
    Object(SDL_Renderer *_Render,std::string file);
    ~Object(){delete objRect;};
    void SetRect(int x,int y,int w,int h){objRect->x = x,objRect->y = y,objRect->w = w,objRect->h = h;};
    SDL_Rect* GetRect(){return objRect;};
    SDL_Texture* GetTexture(){return objTexture;};
    void SetGameStatus(eGameStatus _GameStatus){GameStatus = _GameStatus;};
    void Draw(){SDL_RenderCopy(objRen,objTexture,NULL,objRect);};
    void Motion(){;};
    void EventHandler(SDL_Event *Event);


};

class BackGround:public Object
{
public:
    BackGround(SDL_Renderer *_Render,std::string file):Object(_Render,file){};
    void Draw(){SDL_RenderCopy(objRen,objTexture,NULL,NULL);};

};
class Ground:public Object
{
public:
    Ground(SDL_Renderer *_Render,std::string file):Object(_Render,file){};
    void Motion();
};

class Pipe:public Object
{
public:
    Pipe(SDL_Renderer *_Render,std::string file):Object(_Render,file){};
    Pipe(SDL_Renderer *_Render,SDL_Texture *_Texture){objRen=_Render;objTexture=_Texture;};
    void Motion();
};
class Bird:public Object
{
private:
    double vy = 0;
    const double gravity = 0.4;
    public:
    Bird(SDL_Renderer *_Render,std::string file):Object(_Render,file){};
    void Motion();
    void Draw();
    void ReSet(){vy=0;};
    void EventHandler(SDL_Event *Event);

};
class PipeSet
{
private:
    Pipe *upPipe,*downPipe;
    static SDL_Texture *upPipeTexture,*downPipeTexture;

public:
    PipeSet();
    ~PipeSet(){delete upPipe;delete downPipe;};
    PipeSet(SDL_Renderer *_Render,int width,int height,int gap);
    int CollisionCheck(SDL_Rect *_Bird);//-1 no Coll;0 Coll
    int GetX(){return (upPipe->GetRect())->x;};
    void Motion(){upPipe->Motion();downPipe->Motion();}
    void Draw(){upPipe->Draw();downPipe->Draw();};

};
class PipeSetManager
{
private:
    int width,height,gap;
    eGameStatus GameStatus;
     PipeSet *tmpPipe;
    SDL_Renderer *screenRen;
    list <PipeSet> listPipe;
    list<PipeSet>::iterator iterPipe;
public:
    PipeSetManager(SDL_Renderer *_Render,int _width,int _height,int _gap);
    void Motion();
    void Draw();
    void Reset();
    int CollisionCheck(SDL_Rect *_Bird);//-1 no Coll;0 Coll

};
class ImageScore
{
private:
    Object *objNum;
    SDL_Rect numRect;
public:
    ImageScore(SDL_Renderer *_Renderer);
};
#endif // OBJECT_H_INCLUDED
