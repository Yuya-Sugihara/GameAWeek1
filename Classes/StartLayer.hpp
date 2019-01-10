#ifndef MainLayer_hpp
#define MainLayer_hpp

#include "cocos2d.h"
using namespace cocos2d;

class StartLayer:public Layer
{
private:
    
public:
    StartLayer();
    static StartLayer* create();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    static Scene* createScene();
    ~StartLayer();
    
    void changeToGameLayer(float dt);
};

#endif /* MainLayer_hpp */
