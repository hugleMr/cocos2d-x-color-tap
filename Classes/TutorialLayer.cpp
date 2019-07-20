//
//  TutorialLayer.cpp
//  FourTap
//
//  Created by Tran Tho on 1/19/17.
//
//

#include "TutorialLayer.hpp"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"


Scene* TutorialLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TutorialLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool TutorialLayer::init() {
    if(!Layer::init()){
        return false;
    }
    // register touch
    auto e = EventListenerTouchOneByOne::create();
    e->onTouchBegan = std::bind(&TutorialLayer::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);
    
    //scheduleUpdate();
    
    winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("bg_Loading.png");
    bg->setPosition(winSize / 2);
    this->addChild(bg);
    
    
    this->runAction(Sequence::create(DelayTime::create(5.0), CallFunc::create([=]() {
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    }) ,NULL));
    
    
   
    return true;
}

void TutorialLayer::doTutorial() {
    
    m_listCircleTiles->at(0)->actionOnTap();
    m_hand->setPosition(m_listCircleTiles->at(0)->getPosition() - Vec2(250, 0));
    m_hand->setRotation(90);
    m_status->setPositionY(m_status->getPositionY() + 270);
    m_status->setString("Now ! tap in the light circle");
    m_status->setLocalZOrder(99);
    m_status->runAction(Sequence::create(DelayTime::create(1.3), CallFunc::create([=]() {
        for(auto tile : *m_listCircleTiles) {
            tile->setLocalZOrder(3);
            m_blackBackGround->setVisible(true);
            m_blackBackGround->setLocalZOrder(4);
            m_numberTut = 1;
            m_canTap = true;
            m_hand->setVisible(true);
            m_hand->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.6, Vec2(20, 0)), MoveBy::create(0.6, Vec2(-20, 0)), NULL)));
        }
        m_listCircleTiles->at(0)->setLocalZOrder(5);
        m_status->setOpacity(255);
    }), NULL));
    
    
}

void TutorialLayer::update(float dt) {
    
}

void TutorialLayer::resetWinLayer() {
    m_winLayer->setPositionX(-winSize.width / 2);
}

void TutorialLayer::showWinLayer() {
    int score = currentLevel;
    score--;
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundWin.mp3");
    m_labelScore->setString(StringUtils::format("%d", score));
    m_winLayer->runAction(
                          Sequence::create(
                                           MoveTo::create(0.2, winSize / 2),
                                           DelayTime::create(0.6) ,
                                           MoveTo::create(0.15, Vec2(winSize.width * 1.5, winSize.height / 2)),
                                           CallFunc::create([=] {
                              this->resetWinLayer();
                              
                              //resetLevel(currentLevel);
                          }),
                                           NULL));
}


bool TutorialLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
    if(m_canTap) {
         Vec2 pos = touch->getLocation();
        for(auto tile : *m_listCircleTiles) {
            if(tile->isTap(pos)) {
                if(m_numberTut == 1 && tile->getIdTile() == 0) {
                    m_numberTut = 0;
                    tile->actionOnTap();
                    m_canTap = false;
                    m_status->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=](){
                        m_status->setOpacity(0);
                        m_hand->stopAllActions();
                        m_hand->setVisible(false);
                        m_blackBackGround->setVisible(false);
                        currentLevel = 2;
                        showWinLayer();
                    }), DelayTime::create(1.0), CallFunc::create([=]() {
                        m_listCircleTiles->at(0)->setLocalZOrder(3);
                        m_status->setPositionY(m_status->getPositionY() - 270);
                        m_status->setOpacity(255);
                        m_status->setString("Well done! \n Now look two circles run \n and do agian");
                        m_blackBackGround->setVisible(true);
                    }) ,DelayTime::create(1.5), CallFunc::create([=]() {
                        m_status->setOpacity(0);
                        m_blackBackGround->setVisible(false);
                        this->doTutorialNext();
                    }) ,NULL));

                } else if(m_numberTut == 2 && tile->getIdTile() == 1) {
                    m_numberTut = 3;
                    tile->actionOnTap();
                } else if(m_numberTut == 3 && tile->getIdTile() == 2) {
                    m_numberTut = 0;
                    tile->actionOnTap();
                    m_hand->stopAllActions();
                    m_hand->setVisible(false);
                    m_blackBackGround->setVisible(false);
                    m_listCircleTiles->at(1)->setLocalZOrder(3);
                    m_listCircleTiles->at(2)->setLocalZOrder(3);
                    m_status->setVisible(false);
                    currentLevel = 3;
                    m_hand->runAction(Sequence::create(DelayTime::create(0.5),CallFunc::create([=](){
                        m_canTap = false;
                        this->showWinLayer();
                    }) ,DelayTime::create(1.5), CallFunc::create([=]() {
                        m_status->setPositionY(m_status->getPositionY());
                        m_status->setOpacity(0);
                        m_status->runAction(Sequence::create(FadeIn::create(0.6), DelayTime::create(0.5), CallFunc::create([=]() {
                            m_status->setOpacity(0);
                            m_status->setString("Now ! we have \n a time bar at the top \n to control the level");
                            m_timeBarTop->setLocalZOrder(6);
                            m_timeBarTop->runAction(Sequence::create(FadeIn::create(0.6), MoveBy::create(3.0, Vec2(-m_timeBarTop->getContentSize().width, 0)),CallFunc::create([=]() {
                                m_status->runAction(FadeOut::create(0.2));
                                
                            }), CallFunc::create([=]() {
                                this->doTutorialEnd();
                            }) ,NULL));
                        }), FadeIn::create(0.6) ,NULL) );
                        m_status->setString("Good game");
                        m_status->setVisible(true);
                        m_blackBackGround->setVisible(true);
                    }) ,NULL));
                }
            }
        }
    }
    
    return true;
}

void TutorialLayer::doTutorialEnd() {
    m_status->runAction(Sequence::create(DelayTime::create(0.3) ,CallFunc::create([=]() {
        m_status->setString("Here we go \n let's go to the game");
    }), FadeIn::create(0.4), DelayTime::create(1.5), CallFunc::create([=]() {
        UserDefault::getInstance()->setBoolForKey(KEY_TUTORIAL, true);
        auto scene = HelloWorld::createScene();
        Director::getInstance()->replaceScene(scene);
    }) ,NULL));
}

void TutorialLayer::doTutorialNext() {
    this->runAction(Sequence::create(CallFunc::create([=]() {
        m_listCircleTiles->at(1)->actionOnTap();
    }), DelayTime::create(0.5), CallFunc::create([=]() {
        m_listCircleTiles->at(2)->actionOnTap();
    }), DelayTime::create(0.5), CallFunc::create([=]() {
        m_blackBackGround->setVisible(true);
        m_status->setOpacity(255);
        m_status->setPositionY(m_status->getPositionY() + 270);
        m_status->setString("Now ! tap in the light circle");
        m_hand->setVisible(true);
        m_numberTut = 2;
        m_hand->setPosition(m_listCircleTiles->at(1)->getPosition() + Vec2(230, -60));
        m_hand->runAction(RepeatForever::create(Sequence::create(CallFunc::create([=]() {
            m_hand->setRotation(-70);
        }), MoveBy::create(0.5, Vec2(-30, 0)), MoveBy::create(0.5, Vec2(30, 0)),
                                                                 
                                                                 RotateTo::create(1.5, -190),MoveBy::create(0.5, Vec2(0, -30)), MoveBy::create(0.5, Vec2(0, 30)),NULL)));
        m_hand->setRotation(-70);
        m_listCircleTiles->at(1)->setLocalZOrder(5);
        m_listCircleTiles->at(2)->setLocalZOrder(5);
        m_canTap = true;
    }) ,NULL));
}

