#ifndef GameLayer_hpp
#define GameLayer_hpp

#include <cocos2d.h>
#include <list>

#include "Ground.hpp"
#include "Player.hpp"

#include <list>

using namespace cocos2d;

class GameLayer:public Layer
{
private:
    std::list<Ground*> mGroundList;
    Player* player;
    bool isGameOver=false;
    float score;
public:
    GameLayer();
    static GameLayer* create();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void update(float dt) override;
    virtual void onExit() override;
    static Scene* createScene();
    ~GameLayer();
    
    void createGround();
    void addGround();
    void drawGround();
    void removeGround();
    void gameOver();
    void calcScore(float dt);
    void showScore();
    
    virtual bool onTouchBegan(Touch* touch,Event* event) override;
    virtual void onTouchMoved(Touch* touch,Event* event)override;
    virtual void onTouchEnded(Touch* touch,Event* event)override;
    virtual void onTouchCancelled(Touch* touch,Event* event)override;
};


#endif /* GameLayer_hpp */
