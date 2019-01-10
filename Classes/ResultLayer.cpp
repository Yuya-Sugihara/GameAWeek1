
#include "ResultLayer.hpp"
#include "StartLayer.hpp"
#include <string>

ResultLayer::ResultLayer()
{
    
}

ResultLayer::~ResultLayer()
{
    
}

ResultLayer* create(float score)
{
    ResultLayer* layer=new ResultLayer();
    layer->autorelease();
    layer->init(score);
    
    return layer;
}

bool ResultLayer::init(float score)
{
    if(!Layer::init()) return false;
    mScore=score;
    
    return true;
}
void ResultLayer::onEnter()
{
    Layer::onEnter();
    
    auto touchListener=EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan=CC_CALLBACK_2(ResultLayer::onTouchBegan,this);
    touchListener->onTouchMoved=CC_CALLBACK_2(ResultLayer::onTouchMoved,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(ResultLayer::onTouchEnded,this);
    touchListener->onTouchCancelled=CC_CALLBACK_2(ResultLayer::onTouchCancelled,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);
    
    showScore();
}

Scene* ResultLayer::createScene(float score)
{
    cocos2d::Scene* scene=cocos2d::Scene::create();
    scene->autorelease();
    scene->retain();
    ResultLayer* layer=ResultLayer::create(score);
    
    scene->addChild(layer);
    
    return scene;
    
}
void showScore()
{
    std::string str=string("SCORE:  "+std::to_string(mScore));
    auto label=cocos2d::CCLabelTTF::create(str,"arial",56);
    label->setColor(cocos2d::Color3B::BLACK);
    label->setPosition(Point(200,600));
    addChild(label);
    
}

bool ResultLayer::onTouchBegan(Touch* touch,Event* event)
{
    auto scene=StartLayer::createScene();
    Director::getInstance()->replaceScene(scene);
    
    return true;
}

void ResultLayer::onTouchMoved(Touch* touch,Event* event)
{
    
}

void ResultLayer::onTouchEnded(Touch* touch,Event* event)
{
    
}

void ResultLayer::onTouchCancelled(Touch* touch,Event* event)
{
    
}
