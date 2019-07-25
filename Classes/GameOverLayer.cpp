//
//  GameOverLayer.cpp
//  FourTap
//
//  Created by Tran Tho on 4/13/16.
//
//

#include "GameOverLayer.hpp"
#include "GamePlay.hpp"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

bool GameOverLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    winSize = Director::getInstance()->getWinSize();
    
    auto bg = Sprite::create("bg_new.png");
    bg->setPosition(winSize / 2);
    this->addChild(bg);
    
    m_textGameOver = Label::createWithTTF("Game Over", "fonts/AACHENB.TTF", 90);
    m_textGameOver->setPosition(winSize / 2 + Size(0, 240));
    m_textGameOver->enableShadow();
    this->addChild(m_textGameOver);
    
    
    m_textScore = Label::createWithTTF("Score : ", "fonts/AACHENB.TTF", 45);
    m_textScore->setAnchorPoint(Vec2(1.0, 0.5));
    m_textScore->setPosition(winSize / 2 + Size(-0, 40));
    m_textScore->enableShadow();
    this->addChild(m_textScore);

    m_lableScore = Label::createWithTTF("0", "fonts/AACHENB.TTF", 50);
    m_lableScore->setAnchorPoint(Vec2(0, 0.5));
    m_lableScore->setPosition(winSize / 2 + Size(30, 40));
    m_lableScore->enableShadow();
    this->addChild(m_lableScore);

    
    m_textHightScore = Label::createWithTTF("Hight Score : ", "fonts/AACHENB.TTF", 50);
    m_textHightScore->setAnchorPoint(Vec2(1, 0.5));
    m_textHightScore->setPosition(winSize / 2 + Size(10, -40));
    m_textHightScore->enableShadow();
    this->addChild(m_textHightScore);
    
    m_lableHightScore = Label::createWithTTF("0", "fonts/AACHENB.TTF", 55);
    m_lableHightScore->setAnchorPoint(Vec2(0, 0.5));
    m_lableHightScore->setPosition(winSize / 2 + Size(30, -40));
    m_lableHightScore->enableShadow();
    this->addChild(m_lableHightScore);
    
    m_textNew = Label::createWithTTF("New", "fonts/AACHENB.TTF", 20);
    m_textNew->setPosition(m_lableHightScore->getContentSize() + Size(15, 5));
    m_textNew->setColor(Color3B::RED);
    m_lableHightScore->addChild(m_textNew);
    m_textNew->setVisible(false);
    
    
//    m_gem = Sprite::create("res/tiensMini.png");
//    m_gem->setPosition(winSize.width - 40, winSize.height - 45);
//    this->addChild(m_gem);
    
//    m_labelGem = Label::createWithTTF("0", "fonts/AACHENB.TTF", 35);
//    m_labelGem->setAnchorPoint(Vec2(1, 0.5));
//    m_labelGem->enableShadow();
//    m_labelGem->setPosition(m_gem->getPosition() - Vec2(35, 0));
//    this->addChild(m_labelGem);
    
//    buttonVideo = Button::create("res/btnVideo.png");
//    buttonVideo->setScale(0.4);
//    buttonVideo->setPosition(Point(winSize.width / 2, winSize.height / 2 - 120));
//    buttonVideo->setVisible(false);
//    buttonVideo->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
//        switch (type)
//        {
//            case ui::Widget::TouchEventType::BEGAN:
//                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
//                break;
//            case ui::Widget::TouchEventType::ENDED:
//                
//                buttonVideo->stopAllActions();
//                buttonVideo->setVisible(false);
//               UnityAdsManager::showAds();
//                
//                break;
//                
//        }
//    });
//
//    this->addChild(buttonVideo);
    
//    auto textGift = Label::createWithTTF("Free 1000", "fonts/AACHENB.TTF", 30);
//    textGift->setPosition(90, buttonVideo->getContentSize().height / 2 - 22);
//    buttonVideo->addChild(textGift);
    

    
    buttonPlay = Button::create("play.png");
    buttonPlay->setScale(0.8);
    buttonPlay->setPosition(Point(winSize.width / 2, winSize.height / 2 - 200));
    buttonPlay->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
                break;
            case ui::Widget::TouchEventType::ENDED:
               
                this->hideLayer();
                this->setScale(0.0);
                GamePlay::getInstance()->resetLevel(0);
                
                break;
                
        }
    });
    this->addChild(buttonPlay);
    buttonPlay->setOpacity(0);

    
    buttonHome = Button::create("res/home.png");
    buttonHome->setScale(0.6);
    buttonHome->setPosition(Point(winSize.width / 2 - buttonHome->getContentSize().width , winSize.height / 2 - 290));
    buttonHome->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
                break;
            case ui::Widget::TouchEventType::ENDED:
                
                auto scene = HelloWorld::createScene();
                Director::getInstance()->replaceScene(scene);
                
                break;
                
        }
    });
    this->addChild(buttonHome);
    buttonHome->setVisible(false);
    buttonHome->setOpacity(0);

    buttonShop = Button::create("res/share.png");
    buttonShop->setScale(0.6);
    buttonShop->setPosition(Point(winSize.width / 2 + buttonShop->getContentSize().width , winSize.height / 2 - 290));
    buttonShop->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BUTTON_CLICK);
                break;
            case ui::Widget::TouchEventType::ENDED:
                
              
                
                
                break;
                
        }
    });
    buttonShop->setVisible(false);
    this->addChild(buttonShop);
    buttonShop->setOpacity(0);
    
    
    m_updateScore = false;
    m_updateHightScore = false;

    m_score = 0;
    m_hightScore = 0;

//    m_textGiftGem = Label::createWithTTF("0", "fonts/AACHENB.TTF", 60);
//    m_textGiftGem->setColor(Color3B::YELLOW);
//    m_textGiftGem->setPosition(winSize / 2);
//    this->addChild(m_textGiftGem);
    
    m_gameValue = 0;
    
//    m_gameValue = UserManager::getInstance()->player->getGem();
//    m_labelGem->setString(StringUtils::format("%d",(int)m_gameValue));
  
   
    
    this->scheduleUpdate();
    
    
    canTap = false;
    m_newHightScore = false;
    
    return true;
}

void GameOverLayer::updateVideoGems() {
    //this->moveGemsEffect(10);
    //m_labelGem->setString(StringUtils::format("%d",(int)m_gameValue));
}


void GameOverLayer::hideLayer() {
    this->setVisible(false);
    this->canTap = false;
    m_lableHightScore->setVisible(false);
    m_lableScore->setVisible(false);
    m_updateScore = false;
    m_updateHightScore = false;
   // buttonVideo->stopAllActions();
   // buttonVideo->setVisible(false);

}


void GameOverLayer::moveGemsEffect(int number) {
//    auto winSize = Director::getInstance()->getWinSize();
//    
//    for(int i = 0; i < 10; i++) {
//        
//        auto game = Sprite::create("res/tiensMini.png");
//        game->setPosition(winSize / 2 + Size(130, 30));
//        this->addChild(game, 1000);
//        game->runAction(Sequence::create(DelayTime::create((float)i / 8),
//                                         EaseIn::create(MoveTo::create(1.0, m_gem->getPosition()), 5), CallFunc::create([=]{
//            this->m_gameValue += 20;
//            this->m_labelGem->setString(StringUtils::format("%d",(int)m_gameValue));
//            this->m_gem->stopAllActions();
//            this->m_gem->setScale(1.0);
//            this->m_gem->runAction(Sequence::create(ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1.0),NULL));
//            this->m_labelGem->stopAllActions();
//            this->m_labelGem->setScale(1.0);
//            this->m_labelGem->runAction(Sequence::create(ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1.0),NULL));
//            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("collectGem.mp3");
//
//        }),NULL));
//    }
    //UserManager::getInstance()->player->saveGemToDB(m_gameValue);
}

void GameOverLayer::updateScore(int score, int hightScore) {
    m_lableScore->setString(StringUtils::format("%d", 0));
    m_lableHightScore->setString(StringUtils::format("%d", 0));
    
    m_score = 0;
    m_hightScore = 0;
    m_tempScore = score;
    m_tempHightScore = hightScore;
    m_countTime = 0.0;
    
    //rewardLayer->show();
    //this->moveGemsEffect(10);
    
//    sdkbox::PluginAdMob::hide("home");
//    sdkbox::PluginAdMob::show("home");
//    
    m_textNew->setVisible(false);
    
    m_textGameOver->setVisible(false);
    m_textGameOver->setPositionY(m_textGameOver->getPositionY() - 20);
    m_textGameOver->setOpacity(100);
    
    m_textHightScore->setVisible(false);
    m_textHightScore->setPositionY(m_textHightScore->getPositionY() - 20);
    m_textHightScore->setOpacity(100);
    
    m_lableHightScore->setVisible(false);
    m_lableHightScore->setPositionY(m_lableHightScore->getPositionY() - 20);
    m_lableHightScore->setOpacity(100);
    
    m_lableScore->setVisible(false);
    m_lableScore->setPositionY(m_lableScore->getPositionY() - 20);
    m_lableScore->setOpacity(100);
    
    m_textScore->setVisible(false);
    m_textScore->setPositionY(m_textScore->getPositionY() - 20);
    m_textScore->setOpacity(100);

    buttonPlay->setVisible(false);
    buttonPlay->setPositionY(buttonPlay->getPositionY() - 20);
    buttonPlay->setOpacity(100);
    
    buttonHome->setVisible(false);
    buttonHome->setPositionY(buttonHome->getPositionY() - 20);
    buttonHome->setOpacity(100);

    buttonShop->setVisible(false);
    buttonShop->setPositionY(buttonShop->getPositionY() - 20);
    buttonShop->setOpacity(100);

    
    //m_textGiftGem->setVisible(false);
    //m_textGiftGem->setPositionY(m_lableScore->getPositionY());
    //m_textGiftGem->setOpacity(255);

    
    int ran = random(0, 5);
    if(ran == 2 || ran == 3)  {
        //sdkbox::PluginAdMob::show("gameover");
    }
    canTap = false;
    
    
    //m_labelGem->setString(StringUtils::format("%d",(int)m_gameValue));
    
    
    this->runAction(Sequence::create(DelayTime::create(1.0),
                                     CallFunc::create([=](){
        m_textGameOver->setVisible(true);
        m_textGameOver->runAction(MoveBy::create(0.15, Vec2(0, 20)));
        m_textGameOver->runAction(FadeIn::create(0.15));
    
    })
                                     ,
                                     DelayTime::create(0.5),
                                     CallFunc::create([=](){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin.mp3");
        
        m_lableScore->setVisible(true);
        m_lableScore->runAction(MoveBy::create(0.15, Vec2(0, 20)));
        m_lableScore->runAction(Sequence::create(FadeIn::create(0.15), DelayTime::create(0.1), CallFunc::create([=]() {
            m_updateScore = true;
        }) , NULL) );
        
        m_textScore->setVisible(true);
        m_textScore->runAction(MoveBy::create(0.15, Vec2(0, 20)));
        m_textScore->runAction(FadeIn::create(0.15));
        
    }),NULL));
}


void GameOverLayer::setNewHightScore() {
    m_newHightScore = true;
}


void GameOverLayer::update(float dt) {
    if(m_updateScore) {
        if(m_score < m_tempScore) {
            m_countTime += dt;
            if(m_countTime > 0.1) {
                m_countTime = 0;
                m_score++;
                m_lableScore->setString(StringUtils::format("%d",m_score));
            }
        } else {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin.mp3");
            m_updateScore = false;
            
            m_countTime = 0;
            m_lableHightScore->setVisible(true);
            m_lableHightScore->runAction(MoveBy::create(0.15, Vec2(0, 20)));
            m_lableHightScore->runAction(Sequence::create( FadeIn::create(0.5),
                                                        CallFunc::create([=]() {
                                                        m_updateHightScore = true;
            })
                                                          ,NULL));
            
            m_textHightScore->setVisible(true);
            m_textHightScore->runAction(MoveBy::create(0.15, Vec2(0, 20)));
            m_textHightScore->runAction(FadeIn::create(0.15));
        }
    }
    
    if(m_updateHightScore) {
        if(m_hightScore < m_tempHightScore) {
            m_countTime += dt;
            if(m_countTime > 0.05) {
                m_countTime = 0;
                m_hightScore++;
                m_lableHightScore->setString(StringUtils::format("%d",m_hightScore));
            }
        } else {
            m_updateHightScore = false;
            
            this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=]() {
                
//                if(UnityAdsManager::canShow()) {
//                   // buttonVideo->setVisible(true);
//                   // buttonVideo->stopAllActions();
//                    buttonVideo->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.2, 0.5), ScaleTo::create(0.2, 0.6) , NULL)));
//                } else {
//                   //buttonVideo->setVisible(false);
//                }
                
                buttonPlay->setVisible(true);
                buttonPlay->runAction(MoveBy::create(0.15, Vec2(0, 20)));
                buttonPlay->runAction(FadeIn::create(0.15));
                
                //buttonHome->setVisible(true);
                buttonHome->runAction(MoveBy::create(0.15, Vec2(0, 20)));
                buttonHome->runAction(FadeIn::create(0.15));
                
                //buttonShop->setVisible(true);
                buttonShop->runAction(MoveBy::create(0.15, Vec2(0, 20)));
                buttonShop->runAction(FadeIn::create(0.15));
                
                if(m_newHightScore == true) {
                    m_newHightScore = false;
                    m_textNew->setVisible(true);
                    m_lableHightScore->runAction(Sequence::create(ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 1.0) , ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 1.0) ,NULL));
                }
                
                canTap = true;

                
            }) , NULL));
            
            
        }
    }
}
