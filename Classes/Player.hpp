#ifndef Player_hpp
#define Player_hpp
#include "cocos2d.h"

class Ground;

class Player
{
public:
    cocos2d::Sprite* playerSprite;
    
    Player(float x,float y);
    ~Player();
    void update(float dt,Ground* ground);
    void draw();
    void jump();
    bool isLand(Ground* ground) const;
    bool isIntersect(Ground* ground) const;
    
    CC_SYNTHESIZE(float ,mX,X);
    CC_SYNTHESIZE(float ,mY,Y);
    CC_SYNTHESIZE(float ,mWidth,Width);
    CC_SYNTHESIZE(float ,mHeight,Height);
    
private:
    const float jumpForce=15.0f;
    const float gravity=-0.5f;
    float mVelo;
    
    
};

#endif /* Player_hpp */
