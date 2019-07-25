#include "AppDelegate.h"
#include "HelloWorldScene.h"
//#include "PluginFacebook/PluginFacebook.h"
//#include "PluginAdMob/PluginAdMob.h"
#include "SimpleAudioEngine.h"
#include "TutorialLayer.hpp"'
#include "GameConfig.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {

 //   sdkbox::PluginFacebook::init();
    
//    sdkbox::PluginAdMob::init();
//    sdkbox::PluginAdMob::cache("home");
//    sdkbox::PluginAdMob::cache("gameover");

    
    

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        //glview = GLViewImpl::createWithRect("FourTap", Rect(0, 0, 640, 960));
#else
        glview = GLViewImpl::create("FourTap");
        //glview = GLViewImpl::createWithRect("FourTap", Rect(0, 0, 640, 960));
#endif
        director->setOpenGLView(glview);
    }
   
    Size frameSize = glview->getFrameSize();
    // turn on display FPS
    director->setDisplayStats(false);
    Size screenSize = glview->getFrameSize();
    
    glview->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
    
//    float origin_ratio = 1136/640.0;
//    float ratio = frameSize.width / frameSize.height;
//    float scaleFactor = 1.0;
//    if (ratio > origin_ratio){
//        scaleFactor = 1.22f;
//    }else if (frameSize.width / frameSize.height >= 1.7f && frameSize.width / frameSize.height < 1.9f){
//        scaleFactor = 1.0f;
//    }else if (frameSize.width / frameSize.height > 1.5f && frameSize.width / frameSize.height < 1.7f) {
//        scaleFactor = 0.65f * frameSize.width / frameSize.height;
//    } else if(frameSize.width / frameSize.height == 1.5f) {
//        scaleFactor = 1.16f;
//    }else {
//        scaleFactor = 1.3f;
//    }
//
//    CCLOG("SCALE : %f",scaleFactor);
//    CCLOG("width: %f, height: %f", frameSize.width, frameSize.height);
    
    register_all_packages();
//    director->setContentScaleFactor(scaleFactor);
    //load resource
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("soundS.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("error.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("soundR.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("soundQ.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("soundT.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("soundWin.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("collectGem.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("getDiamond.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("hightScore.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("score.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("click.mp3");
     CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("coin.mp3");

    //ResourceManager::getInstance();

    // create a scene. it's an autorelease object
   
    auto scene = TutorialLayer::createScene();
    director->runWithScene(scene);
    
    // run

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
