#include "Player.hpp"
#include "Ground.hpp"

#include "cocos2d.h"

Player::Player(float x,float y):
mX(x),
mY(y),
mWidth(50),
mHeight(50),
mVelo(0)
{
    cocos2d::log("in Player constractor ");
    
    cocos2d::Rect playerRect=cocos2d::Rect(0.0f,0.0f,mWidth,mHeight);
    
    playerSprite=cocos2d::Sprite::create();
    playerSprite->setTextureRect(playerRect);
    playerSprite->setAnchorPoint(cocos2d::Point(0,0));
    playerSprite->setColor(cocos2d::Color3B::BLUE);
    playerSprite->setPosition(mX,mY);
    
}

Player::~Player()
{
    delete playerSprite;
}

void Player::update(float dt,Ground* ground)
{
    cocos2d::log("isLand: %d",isLand(ground));
    if(isLand(ground))
    {
        ground->setGroundColor(cocos2d::Color3B::GREEN);
        mY=ground->getY()+ground->getHeight();
        mVelo=0;
    }else{
        mVelo+=gravity;
        mY+=mVelo;
        
      
    }
    //moveToで震えが生じる
    //cocos2d::Vec2はfloatなので誤差が生じやすく、指定された座標にいかない可能性がある
    //auto move=cocos2d::MoveTo::create(dt,cocos2d::Vec2(mX,mY));
    //playerSprite->runAction(move);
    
    playerSprite->setPosition(mX,mY);
    
    
    
}

void Player::draw()
{

}
void Player::jump()
{
    mVelo+=jumpForce;
}

bool Player::isLand(Ground* ground) const
{
   
    if(ground==NULL) return false;
   
    if(mY+mVelo<=ground->getY()+ground->getHeight())
        return true;
    
    return false;
}

bool Player::isIntersect(Ground* ground) const
{
    if(ground==NULL) return false;
    
    cocos2d::Rect playerRect=playerSprite->boundingBox();
    playerRect.origin.y+=15;
    cocos2d::Rect groundRect=ground->groundSprite->boundingBox();
    if(playerRect.intersectsRect(groundRect)) return true;
    return false;
}
