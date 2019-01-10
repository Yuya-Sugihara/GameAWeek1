#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "GameLayer.hpp"
#include "StartLayer.hpp"

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

   virtual bool applicationDidFinishLaunching();

   virtual void applicationDidEnterBackground();

   virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

