#include "GameLayer.hpp"
#include "StartLayer.hpp"
#include "stdio.h"
#include "time.h"
#include <iostream>
#include <string>

using namespace cocos2d;
//todo::クラス内をreleaseする
GameLayer::GameLayer():
score(0)
{
    
}
GameLayer* GameLayer::create()
{
    cocos2d::log("in GameLayer::create");
    auto gameLayer=new GameLayer();
    gameLayer->init();
    gameLayer->autorelease();
    
    return gameLayer;
}

bool GameLayer::init()
{
    cocos2d::log("in GameLayer::init");
    if(!Layer::init()) return false;
    
    return true;
}

void GameLayer::onEnter()
{
    cocos2d::log("in GameLayer::onEnter");
    Layer::onEnter();
    
    
   
}

void GameLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    cocos2d::log("in GameLayer::onEnterTransitionDidFinish");
    
    //init
    auto touchListener=cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan=CC_CALLBACK_2(GameLayer::onTouchBegan,this);
    touchListener->onTouchMoved=CC_CALLBACK_2(GameLayer::onTouchMoved,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(GameLayer::onTouchEnded,this);
    touchListener->onTouchCancelled=CC_CALLBACK_2(GameLayer::onTouchCancelled,this);
    cocos2d::Director::getInstance()->getEventDispatcher()->
    addEventListenerWithSceneGraphPriority(touchListener,this);
    
    srand((unsigned int) time(NULL));
    cocos2d::Size size=Director::getInstance()->getWinSize();
    
    //auto bg=LayerColor::create(cocos2d::Color4B::WHITE,size.width,size.height);
    auto bg=cocos2d::Sprite::create("背景.jpg");
    bg->setPosition(Point(size.width/2,size.height/2));
    bg->setScale(2,2);
    this->addChild(bg);
    
    createGround();
    drawGround();
    
    player=new Player(0.0f,800.0f);
    addChild(player->playerSprite);
    
    showScore();
    scheduleUpdate();
}

Scene* GameLayer::createScene()
{
    cocos2d::Scene* scene=Scene::create();
    //scene->retain();
    auto layer=GameLayer::create();
    
    scene->addChild(layer);
    return scene;
}

GameLayer::~GameLayer()
{
    delete player;
    mGroundList.clear();
    cocos2d::log("GameLayer::~GameLayer()");
    
}

void GameLayer::createGround()
{
    auto director=cocos2d::Director::getInstance();
    cocos2d::Size size=director->getWinSize();
    Ground* newGround=new Ground(0.0f,0.0f,size.width*2,100.0f);
    mGroundList.push_back(newGround);
    
}

void GameLayer::addGround()
{
    cocos2d::log("size %lu",mGroundList.size());
    auto size=cocos2d::Director::getInstance()->getWinSize();
    std::list<Ground*>::iterator lastGround=mGroundList.end();
    lastGround--;
    
    if((*lastGround)->getX()+(*lastGround)->getWidth()<=size.width)
    {
        float newGroundHeight=(*lastGround)->getHeight()+rand()%8*10-40;
        if(newGroundHeight<=100) newGroundHeight+=100;
        Ground* newGround=new Ground(size.width,0,
                                     Ground::mGroundWidth,newGroundHeight);
        mGroundList.push_back(newGround);
        addChild(newGround->groundSprite);
    }
    
}

void GameLayer::drawGround()
{
    std::list<Ground*>::iterator it;
    for(it=mGroundList.begin();it!=mGroundList.end();it++)
    {
        addChild((*it)->groundSprite);
    }
}

void GameLayer::removeGround()
{
    std::list<Ground*>::iterator it;
    for(it=mGroundList.begin();it!=mGroundList.end();it++)
    {
        if((*it)->getX()+(*it)->getWidth()<0)
        {
            mGroundList.erase(it);
            return ;
        }
    }
    return ;
    
}


void GameLayer::update(float dt)
{
    Ground* onPlayer=NULL;
    std::list<Ground*>::iterator it;
    std::list<Ground*>::iterator nextIt;
    addGround();
    removeGround();
    for(it=mGroundList.begin();it!=mGroundList.end();it++)
    {
 
        (*it)->update(dt);
        
        //接地している地面を選択する
        if( (*it)->getX()<=player->getX()&&
           ( player->getX() <= ( (*it)->getX()+(*it)->getWidth())  ))
        {
            onPlayer=(*it);
            if(player->isIntersect(*(it))) gameOver();
        }
    }
    
    player->update(dt,onPlayer);
    calcScore(dt);

}
void GameLayer::onExit()
{
    Node::onExit();
    cocos2d::log("GameLayer::onExit");
}

void GameLayer::gameOver()
{
    cocos2d::log("in gameOver");
    unscheduleUpdate();
    isGameOver=true;
    
    auto label=cocos2d::CCLabelTTF::create("Game Over!!","arial",56);
    label->setColor(cocos2d::Color3B::BLACK);
    label->setPosition(Point(200,600));
    addChild(label);
    
    auto move1=MoveTo::create(5,Vec2(100,2000));
    
    auto playerMove=Sequence::create(move1,nullptr);
    player->playerSprite->runAction(playerMove);
    
    //Scene* nextScene=StartLayer::createScene();
    //TransitionFade* fade=TransitionFade::create(3.0f,nextScene,cocos2d::Color3B::RED);
    //cocos2d::Director::getInstance()->pushScene(fade);
    
}

void GameLayer::calcScore(float dt)
{
    cocos2d::log("in GameLayer::calcScore");
    score+=dt;
    //cocos2d::Label* label=(cocos2d::Label*)this->getChildByTag(1);
    auto label=(Label*)getChildByTag(1);
    //auto points=cocos2d::CCLabelTTF::create("SCORE: "+std::to_string(score),"arial",48);
    std::string points=std::string("SCORE: "+std::to_string(score));
    //cocos2d::String* points=cocos2d::String::createWithFormat("%f",score);
    label->setString(points);
    cocos2d::log("score: %f",score);
}

void GameLayer::showScore()
{
    cocos2d::log("in GameLayer::showScore");
    cocos2d::Label* label=cocos2d::Label::create("SCORE: "+std::to_string(score),"arial",48);
    
    label->setColor(cocos2d::Color3B(255,150,150));
    label->setPosition(Point(230,1000));
    label->setTag(1);
    
    addChild(label);
    
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch,cocos2d::Event* event)
{
    if(isGameOver)
    {
        cocos2d::Scene* scene=StartLayer::createScene();
        cocos2d::Director::getInstance()->replaceScene(scene);
    }
    player->jump();
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch* touch,cocos2d::Event* event)
{

}

void GameLayer::onTouchEnded(cocos2d::Touch* touch,cocos2d::Event* event)
{

}

void GameLayer::onTouchCancelled(cocos2d::Touch* touch,cocos2d::Event* event)
{
    
}

