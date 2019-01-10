#include "Ground.hpp"

//static変数はクラス外で初期化
cocos2d::Color3B Ground::groundColor=cocos2d::Color3B(100,100,100);

Ground::Ground(float x,float y,float width,float height):
gX(x),
gY(y),
mWidth(width),
mHeight(height),
mGroundColor(Ground::groundColor)
{
    cocos2d::Rect ground=cocos2d::Rect(0.0f,0.0f,mWidth,mHeight);
    
    groundSprite=cocos2d::Sprite::create();
    groundSprite->setTextureRect(ground);
    groundSprite->setAnchorPoint(cocos2d::Point(0,0));
    groundSprite->setColor((cocos2d::Color3B)mGroundColor);
    groundSprite->setPosition(gX,gY);
    
}

Ground::Ground(float x,float y):
Ground(x,y,mGroundWidth,150)
{
}

Ground::~Ground()
{
    delete groundSprite;
}

void Ground::move()
{
    gX-=groundSpeed;
}

void Ground::update(float dt)
{
    //cocos2d::log("in ground update");
    move();
    groundSprite->setColor((cocos2d::Color3B) mGroundColor);
    groundSprite->setPosition(gX,gY);
    //auto move=cocos2d::MoveTo::create(dt,cocos2d::Vec2(gX,gY));
    //groundSprite->runAction(move);
}
