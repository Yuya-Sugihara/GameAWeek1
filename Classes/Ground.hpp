
#ifndef Ground_hpp
#define Ground_hpp

#include "cocos2d.h"

class Ground
{
private:
    static constexpr float groundSpeed=5.0f;
public:
    //constexprは読み取りのみ可能な定数、static const
    static constexpr float mGroundWidth=100;
    static cocos2d::Color3B groundColor;
    cocos2d::Sprite* groundSprite;
    
    Ground(float x,float y,float width,float height);
    Ground(float x,float y);
    ~Ground();
    void move();
    void update(float dt);
    void draw();
    

    CC_SYNTHESIZE(float,mWidth,Width);
    CC_SYNTHESIZE(float,mHeight,Height);
    CC_SYNTHESIZE(float,gX,X);
    CC_SYNTHESIZE(float,gY,Y);
    CC_SYNTHESIZE(cocos2d::Color3B,mGroundColor,GroundColor);
    
};

#endif /* Ground_hpp */
