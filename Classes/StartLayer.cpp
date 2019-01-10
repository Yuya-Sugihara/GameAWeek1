#include "StartLayer.hpp"
#include "GameLayer.hpp"

using namespace cocos2d;

StartLayer::StartLayer()
{
    
}

StartLayer* StartLayer::create()
{
    log("in StartLayer::create");
    StartLayer* layer=new StartLayer();
    layer->init();
    layer->autorelease();
    
    return layer;
}

bool StartLayer::init()
{
    if(!Layer::init()) return false;
    log("in StartLayer::init");
    
    return true;
}

void StartLayer::onEnter()
{
    Layer::onEnter();
    log("in StartLayer::onEnter");
    scheduleOnce(schedule_selector(StartLayer::changeToGameLayer),2.0f);
    //changeToGameLayer(2.0f);
}

void StartLayer::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("in StartLayer::onEnterTransitionDidFinish");
}


void StartLayer::onExit()
{
    Node::onExit();
    log("in StartLayer::onExit");
}

Scene* StartLayer::createScene()
{
    Scene* scene=Scene::create();
    scene->autorelease();
    scene->retain();
    StartLayer* layer=StartLayer::create();
    
    scene->addChild(layer);
    return scene;
}

StartLayer::~StartLayer()
{
    log("in StartLayer::~StartLayer");
    
}

void StartLayer::changeToGameLayer(float dt)
{
    log("in StartLayer::changeToGameLayer");
    Scene* scene=GameLayer::createScene();
    
    TransitionFade* fade=TransitionFade::create(3.0,scene,Color3B::WHITE);
    Director::getInstance()->replaceScene(fade);
    //Director::getInstance()->pushScene(fade);
    //Director::getInstance()->replaceScene(scene);
}
