#ifndef ResultLayer_hpp
#define ResultLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class ResultLayer:public Layer
{
private:
    float mScore;
public:
    ResultLayer();
    ~ResultLayer();
    static ResultLayer* create(float score);
    bool init(float score);
    void onEnter() override;
    Scene* createScene(float score);
    
    void showScore();
    
    virtual bool onTouchBegan(Touch* touch,Event* event) override;
    virtual void onTouchMoved(Touch* touch,Event* event) override;
    virtual void onTouchEnded(Touch* touch,Event* event) override;
    virtual void onTouchCancelled(Touch* touch,Event* event) override;
    
};
#endif /* ResultLayer_hpp */
