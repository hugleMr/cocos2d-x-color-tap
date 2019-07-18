#include "HelloWorldScene.h"
#include "GamePlay.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

//using namespace sdkbox;

//
//
//static void checkFaceBookStatus()
//{
//    CCLOG("##FB> permission list: ");
//    for (auto& permission : sdkbox::PluginFacebook::getPermissionList())
//    {
//        CCLOG("##FB>> permission %s", permission.data());
//    }
//    CCLOG("##FB> access token: %s", sdkbox::PluginFacebook::getAccessToken().c_str());
//    CCLOG("##FB> user id: %s", sdkbox::PluginFacebook::getUserID().c_str());
//    CCLOG("##FB> FBSDK version: %s", sdkbox::PluginFacebook::getSDKVersion().c_str());
//    
//}
//

static HelloWorld* _instance = nullptr;


Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


HelloWorld* HelloWorld::getInstance() {
    if(_instance == nullptr) {
        _instance = new HelloWorld();
    }
    
    return _instance;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _instance = this;
    
    //PluginFacebook::setListener(this);
    
    //UserManager::getInstance()->player->saveGemToDB(5000);
    
    
    Size winSize = Director::getInstance()->getWinSize();
    
    canTap = false;
    
    auto bg = Sprite::create("bacdk.png");
    bg->setPosition(winSize / 2);
    this->addChild(bg);
    
    
//    auto earth = Sprite::create("res/traidat.png");
//    earth->setPosition(winSize.width / 2, winSize.height  / 4);
//    this->addChild(earth);
//    
//    
//    auto moon = Sprite::create("res/mattrang.png");
//    moon->setPosition(winSize.width / 2 + 230, winSize.height  / 4 - 130);
//    this->addChild(moon);
    
    
    auto buttonPlay = Button::create("play.png");
    buttonPlay->setPosition(Point(winSize.width / 2, -100));
    buttonPlay->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
                break;
            case ui::Widget::TouchEventType::ENDED:
                if(canTap == true) {
                    auto scene = GamePlay::createScene();
                    Director::getInstance()->replaceScene(scene);
                }
                
                break;
                
        }
    });
    this->addChild(buttonPlay);
    

    
    
//    buttonLogin = Button::create("res/button.png");
//    buttonLogin->setTitleFontSize(55);
//    buttonLogin->setTitleFontName("fonts/AACHENB.TTF");
//    buttonLogin->setTitleText("Login");
//    buttonLogin->setPosition(Point(winSize.width  + buttonLogin->getContentSize().width + 30, winSize.height / 2 - 290));
//    buttonLogin->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
//        switch (type)
//        {
//            case ui::Widget::TouchEventType::BEGAN:
//                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
//                break;
//            case ui::Widget::TouchEventType::ENDED:
//
//
//                break;
//
//        }
//    });
//    this->addChild(buttonLogin);
//
//
//    auto buttonShop = Button::create("res/button.png");
//    buttonShop->setTitleFontSize(55);
//    buttonShop->setTitleFontName("fonts/AACHENB.TTF");
//    buttonShop->setTitleText("Shop");
//    buttonShop->setPosition(Point( - buttonLogin->getContentSize().width - 30, winSize.height / 2 - 290));
//    buttonShop->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
//        switch (type)
//        {
//            case ui::Widget::TouchEventType::BEGAN:
//                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
//                break;
//            case ui::Widget::TouchEventType::ENDED:
//
//
//                break;
//
//        }
//    });
//    this->addChild(buttonShop);
//
//
//
//    auto hideTitle = Sprite::create("res/hinh.png");
//    hideTitle->setPosition(winSize.width / 2, winSize.height * 2 / 3 + 20);
//    this->addChild(hideTitle);
//
//
//
    
    
    auto title = Sprite::create("color.png");
    title->setPosition(winSize.width / 2, winSize.height * 2 / 3 + 20);
    this->addChild(title);
    title->setOpacity(0);
    title->runAction(Sequence::create(DelayTime::create(0.1), CallFunc::create([=](){
        title->runAction(MoveBy::create(0.3, Vec2(0, 50)));
        title->runAction(FadeIn::create(0.3));
    }), DelayTime::create(0.2), CallFunc::create([=](){
        buttonPlay->runAction(EaseBackOut::create(MoveTo::create(1.0, Vec2(buttonPlay->getPositionX(), winSize.height / 2 - 230))));
        

//        buttonLogin->runAction(EaseBackOut::create(MoveTo::create(1.2, Vec2(winSize.width / 2 + buttonLogin->getContentSize().width + 50, buttonLogin->getPositionY()))));
//
        
        
//        buttonShop->runAction(EaseBackOut::create(MoveTo::create(1.2, Vec2(winSize.width / 2 - buttonShop->getContentSize().width - 50, buttonShop->getPositionY()))));
       

        
        canTap = true;
        
//        title->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.5, Vec2(0, 10)), MoveBy::create(1.5, Vec2(0, -10)),NULL)));
        
    }),NULL));

    
   
    
    //sdkbox::PluginAdMob::show("home");
    
   
    
    
    
    return true;
}






