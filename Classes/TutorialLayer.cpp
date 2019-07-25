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
    auto e = EventListenerTouchOneByOne::create();
    e->onTouchBegan = std::bind(&TutorialLayer::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);
    
    //scheduleUpdate();
    
    winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("res/backGround2.png");
    bg->setPosition(winSize / 2);
    this->addChild(bg);
    
    
    
    m_timeBarTop = Sprite::create("res/timeBar.png");
    m_timeBarTop->setPosition(Vec2(winSize.width / 2, winSize.height - 15));
    this->addChild(m_timeBarTop);
    m_timeBarTop->setOpacity(0);
    
    m_canTap = false;
    
    m_numberTut = 0;
    
    int z = 0;
    int offSet = 155;
    int m_offsetY = 75;
    
    m_listCircleTiles = new Vector<CircleTile*>();
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j ++) {
            auto tile = CircleTile::create();
            tile->setPosition(winSize.width / 2 + std::pow(-1, j) * offSet, winSize.height / 2 + std::pow(-1, i) * offSet - m_offsetY);
            tile->setIdTile(z);
            tile->hide();
            this->addChild(tile);
            m_listCircleTiles->pushBack(tile);
            z++;
            
        }
    }
    
    m_blackBackGround = Scale9Sprite::create("res/button.png", Rect(10, 10, 10, 10));
    m_blackBackGround->setContentSize(Size(winSize.width, winSize.height));
    m_blackBackGround->setPosition(winSize / 2);
    addChild(m_blackBackGround);
    m_blackBackGround->setVisible(false);
    
    //init winlayer
    m_winLayer = Layer::create();
    m_winLayer->setPosition(winSize / 2);
    addChild(m_winLayer,99);
    
    this->resetWinLayer();
    
    auto backGround = Sprite::create("res/backGround2.png");
    m_winLayer->addChild(backGround);
    
    m_labelScore = Label::createWithTTF("0", FONT_AACHENB, 120);
    m_labelScore->setPositionY(110);
    m_labelScore->enableShadow();
    m_winLayer->addChild(m_labelScore);
    
    m_status = Label::createWithTTF("", FONT_AACHENB, 45);
    m_status->setAlignment(TextHAlignment::CENTER);
    m_status->setPosition(winSize / 2);
    m_status->setOpacity(0);
    addChild(m_status);
    
    m_textWelcome = Label::createWithTTF("Welcome to Color Tap game", FONT_AACHENB, 50);
    m_textWelcome->setPosition(winSize / 2);
    m_textWelcome->setOpacity(0);
    addChild(m_textWelcome);
    m_textWelcome->runAction(Sequence::create(MoveBy::create(1.3, Vec2(0, 130)), DelayTime::create(1.0), CallFunc::create([=]() {
        m_textWelcome->runAction(Sequence::create(FadeOut::create(0.7), CallFunc::create([=]() {
            
            m_timeBarTop->runAction(Sequence::create(DelayTime::create(2.5),CallFunc::create([=]() {
                m_blackBackGround->setVisible(true);
                
                m_status->setString("Now ! look the circle run \n and remember");
                m_status->runAction(Sequence::create(FadeIn::create(0.2),DelayTime::create(2.2), CallFunc::create([=]() {
                    m_status->setOpacity(0);
                    m_blackBackGround->setVisible(false);
                    
                    this->doTutorial();
                    
                }) ,NULL) );
                
            }) , NULL) );
            for(auto tile : *m_listCircleTiles) {
                tile->show(0.7);
            }
            
        }),NULL));
        
    }), NULL));
    m_textWelcome->runAction(FadeIn::create(1.5));
    
    
    m_hand = Sprite::create("res/hand.png");
    m_hand->setVisible(false);
    addChild(m_hand, 1000);
   
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

