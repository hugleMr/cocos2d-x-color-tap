#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;


class HelloWorld : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();
    
    static HelloWorld* getInstance();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    bool canTap;
    
    cocos2d::ui::Button* buttonLogin;
    
    
private:
    
    


};

#endif // __HELLOWORLD_SCENE_H__
