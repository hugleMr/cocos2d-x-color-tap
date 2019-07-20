//
//  GamePlay.cpp
//  FourTap
//
//  Created by Tran Tho on 3/26/16.
//
//

#include "GamePlay.hpp"
#include "SimpleAudioEngine.h"

static GamePlay* _instance = nullptr;

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlay::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

GamePlay* GamePlay::getInstance() {
    if(_instance == nullptr) {
        _instance = new GamePlay();
    }
    return _instance;
}

bool GamePlay::init() {
    if(!Layer::init())
        return false;
    
    //sdkbox::PluginAdMob::setListener(this);
    
    // register touch
    auto e = EventListenerTouchOneByOne::create();
    e->onTouchBegan = std::bind(&GamePlay::onTouchBegan, this, std::placeholders::_1, std::placeholders::_2);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(e, this);
    
    scheduleUpdate();
    //schedule(schedule_selector(GamePlay::countDownTime), 1.0);
    
    _instance = this;
    
    winSize = Director::getInstance()->getWinSize();
    
    m_countData = 0;
    
    m_delayTime = 0;
    
    currentLevel = 1;
    
    m_valueTimebar = 3.0;
    
    gameStatus = GameStatus::READY;
    
    auto bg = Sprite::create("bg_new.png");
    bg->setPosition(winSize / 2);
    this->addChild(bg);
    
    m_listCircleTiles = new Vector<CircleTile* >();
    
    int offSet = 140;
    int m_offsetY = 30;
    int z = 0;
    
    m_timeBarPos = Vec2(winSize.width / 2, winSize.height - 15);
    
    
    m_timeBarTop = Sprite::create("res/timeBar.png");
    m_timeBarTop->setPosition(m_timeBarPos);
    this->addChild(m_timeBarTop);
    
    
    

    srand((int)time(nullptr));
    //init data
    
    //init winlayer
    m_winLayer = Layer::create();
    m_winLayer->setPosition(winSize / 2);
    addChild(m_winLayer,99);
    
    auto backGround = Sprite::create("bg_new.png");
    m_winLayer->addChild(backGround);
    
    m_labelScore = Label::createWithTTF("0", FONT_AACHENB, 120);
    m_labelScore->setPositionY(90);
    m_labelScore->enableShadow();
    m_winLayer->addChild(m_labelScore);
    
    
    resetWinLayer();
    
    m_holdLayer = Button::create();
    m_holdLayer->setScale9Enabled(true);
    m_holdLayer->setContentSize(Size(winSize.width, winSize.height));
    m_holdLayer->setPosition(winSize / 2);
    m_holdLayer->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                CCLOG("please wait");
                break;
                
        }
    });
    addChild(m_holdLayer);
    

    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j ++) {
            auto tile = CircleTile::create();
            tile->setPosition(winSize.width / 2 + std::pow(-1, j) * offSet, winSize.height / 2 + std::pow(-1, i) * offSet - m_offsetY);
            tile->setIdTile(z);
            this->addChild(tile);
            m_listCircleTiles->pushBack(tile);
            z++;
            
        }
    }
    
    float offSetY = 210;
    
    m_gameTapText = Label::createWithTTF("1", FONT_AACHENB, 70);
    m_gameTapText->setPosition(winSize.width / 2, winSize.height / 2 + offSetY);
    this->addChild(m_gameTapText);
    
    m_gameTapValue = 1;
    m_gameTapText->setString(StringUtils::format("%d", m_gameTapValue));
    
    m_gameStatus = Label::createWithTTF("You Miss", FONT_AACHENB, 70);
    m_gameStatus->setColor(Color3B::YELLOW);
    m_gameStatus->setPosition(winSize.width / 2, winSize.height / 2 + 50);
    addChild(m_gameStatus);
    
    
    m_gameOverLayer = GameOverLayer::create();
    //m_gameOverLayer->setScale(0.0);
    addChild(m_gameOverLayer,999);
    m_gameOverLayer->setVisible(false);
    
    resetLevel(0);
    
    return true;
}

GameOverLayer* GamePlay::getGameOverLayer() {
    return m_gameOverLayer;
}

void GamePlay::dynamicCreateData(int level) {
    m_data.clear();
    for(int i = 0; i < level; i++) {
        m_data.push_back(random(0, 3));
    }
    
    m_countData = level;
    m_countData--;
}

void GamePlay::showGameOverLayer() {
    gameStatus = GameStatus::GAMEOVER;
    m_gameOverLayer->setVisible(true);
    m_gameOverLayer->setScale(1.0);
    //m_gameOverLayer->runAction(ScaleTo::create(0.1, 1.0));
    int score = currentLevel;
    score--;
    
    int hightScore = UserDefault::getInstance()->getIntegerForKey("HIGHTSCORE");
    if(score > hightScore) {
        m_gameOverLayer->setNewHightScore();
        hightScore = score;
        UserDefault::getInstance()->setIntegerForKey("HIGHTSCORE", score);
    }
    m_gameOverLayer->updateScore(score, hightScore);
    this->currentLevel = 1;
}

void GamePlay::resetWinLayer() {
    m_winLayer->setPositionX(-winSize.width / 2);
}

void GamePlay::showWinLayer() {
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
                             
                              resetLevel(currentLevel);
                          }),
                                           NULL));
}

void GamePlay::drawListIcon(int number) {
    
    if(number > m_listIcons.size()) {
        int z = number - (int)m_listIcons.size();
        for(int i = 0; i < z; i++) {
            auto icon = IconTile::create();
            addChild(icon, 1);
            m_listIcons.pushBack(icon);
        }
    }
    
    this->drawIconOnLine(0, number);
    
}

void GamePlay::drawIconOnLine(float line, int number) {
    float offSetX = 35;
    float offSetY = 310;
    float tileSet = offSetX / 2;
    
    bool isMidle = false;
    
    if(number % 2 != 0) {
        tileSet = 0;
        isMidle = true;
    }
    
    int x = number / 2;
    
    for(int i = 0; i < x; i++) {
        auto tile = m_listIcons.at(i);
        tile->setVisible(true);
        tile->setPosition(winSize.width / 2 - (x - i) * offSetX + tileSet , winSize.height / 2 + offSetY);
    }
    
    if(isMidle) {
        auto tile = m_listIcons.at(x);
        tile->setVisible(true);
        tile->setPosition(winSize.width / 2, winSize.height / 2 + offSetY);
        
    }
    if(isMidle)
        x++;
    int y = 0;
    for(int i = x; i < number; i++) {
        y++;
        auto tile = m_listIcons.at(i);
        tile->setVisible(true);
        tile->setPosition(winSize.width / 2 + (y) * offSetX - tileSet, winSize.height / 2 + offSetY);
        
    }

}

void GamePlay::update(float dt) {
    
    if(gameStatus == GameStatus::ANDROIDRUN && !m_lockUpdate) {
        m_delayTime += dt;
        if(m_delayTime > TIME_PER_TILE) {
            m_delayTime = 0;
            androidRun(m_data);
        }
    }
    
}

void GamePlay::resetLevel(int level) {
    if(level == 0) {
        m_gameOverLayer->canTap = false;
//        if(sdkbox::PluginAdMob::isAvailable("home")) {
//            CCLOG("show ads home");
//            sdkbox::PluginAdMob::show("home");
//        } else {
//            CCLOG("no ads home");
//        }
    }
    if(level > 5) {
        m_valueTimebar += 1.5;
    } else {
        m_valueTimebar = 3.0;
    }
    dynamicCreateData(currentLevel);
    m_holdLayer->setVisible(true);
    //drawListIcon((int)m_data.size());
    m_timeBarTop->setPosition(this->m_timeBarPos);
    gameStatus = GameStatus::ANDROIDRUN;
    m_valueCountToPlay = 2;
    countTap = 0;
    m_delayTime = 0;
    m_lockUpdate = false;
    
    m_gameStatus->setVisible(false);
    m_gameStatus->setScale(0.0);
    
    m_gameTapValue = level;
    if(m_gameTapValue == 0) {
        m_gameTapValue = 1;
    }
    m_gameTapText->setVisible(false);
    m_gameTapText->setOpacity(0);
    m_gameTapText->setPositionY(m_gameTapText->getPositionY() - 60);
    m_gameTapText->setString(StringUtils::format("%d", m_gameTapValue));
    //hideTiles();
    
    
}

void GamePlay::showTiles() {
    for(int i = 0; i < currentLevel; i++) {
        m_listIcons.at(i)->reset();
        m_listIcons.at(i)->setVisible(true);
    }
}

void GamePlay::hideTiles() {
    for(auto tile : m_listIcons) {
        tile->reset();
        tile->setVisible(false);
    }
}

void GamePlay::androidRun(std::vector<int> data) {
    if(m_countData >= 0) {
        int value = data.at(m_countData);
        m_countData--;
        auto circle = getCircleById(value);
        if(circle) {
            circle->actionOnTap();
        }
    } else if(gameStatus == GameStatus::ANDROIDRUN) {
        m_lockUpdate = true;
        //showTiles();
        m_gameTapText->stopAllActions();
        m_gameTapText->setVisible(true);
        m_gameTapText->runAction(FadeIn::create(0.2));
        m_gameTapText->runAction(MoveBy::create(0.2, Vec2(0, 60)));
        m_holdLayer->setVisible(false);
        m_timeBarTop->runAction(Sequence::create(CallFunc::create([=]{
            gameStatus = GameStatus::PLAYERRUN;
            m_timeBarTop->runAction(Sequence::create(
                                                     MoveBy::create(m_valueTimebar, Vec2(-m_timeBarTop->getContentSize().width, 0)),
                                                  CallFunc::create([=](){
                gameStatus = GameStatus::STOP;
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("error.mp3");
                m_gameStatus->setString("Time Out");
                m_gameStatus->setVisible(true);
                m_gameStatus->runAction(Sequence::create(ScaleTo::create(0.4, 1.0) ,
                                                         DelayTime::create(1.0),
                                                         CallFunc::create([=] {
                    this->hideTiles();
                    //this->m_continuePopup->show();
                    this->showGameOverLayer();
                    CCLOG("show Game Over");
                }), NULL));
                CCLOG("game Over");
            })
                                                  ,NULL));
            CCLOG("Layer run");
            
        }) ,NULL));
        
        
        
    }
}

CircleTile* GamePlay::getCircleById(int id) {

    for(auto circle: *m_listCircleTiles) {
        if(circle->getIdTile() == id){
            return circle;
        }
    }
    
    return nullptr;
}


bool GamePlay::checkPlayerTap(CircleTile* currentTile) {
    if(m_data.size() > 0) {
        if(m_data.at(m_data.size() - 1) == currentTile->getIdTile()) {
            m_data.pop_back();
            
            CCLOG("Tap right");
            //m_listIcons.at(countTap)->setWin();
            m_gameTapValue--;
            m_gameTapText->setString(StringUtils::format("%d", m_gameTapValue));
            m_gameTapText->stopAllActions();
            m_gameTapText->runAction(Sequence::create(ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 1.0), NULL));
            countTap++;
            return true;
        }
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("error.mp3");
    CCLOG("Tap fail");
    //m_listIcons.at(countTap)->setLost();
    gameStatus = GameStatus::STOP;
    m_timeBarTop->stopAllActions();
    m_gameTapText->stopAllActions();
    m_gameTapText->runAction(Sequence::create(TintTo::create(0.1, Color3B::RED),
                                              TintTo::create(0.1, Color3B::WHITE),NULL) );
    m_gameStatus->setString("You Miss");
    m_gameStatus->setVisible(true);
    m_gameStatus->runAction(Sequence::create(ScaleTo::create(0.4, 1.0),
                                             DelayTime::create(0.5),
                                             CallFunc::create([=] {
        //this->hideTiles();
        //this->m_continuePopup->show();
        this->showGameOverLayer();
        CCLOG("show Game Over");
    }), NULL));

    return false;
}

bool GamePlay::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Vec2 pos = touch->getLocation();
    if(gameStatus == GameStatus::PLAYERRUN) {
        for(auto tile : *m_listCircleTiles) {
            if(tile->isTap(pos) && this->checkPlayerTap(tile)) {
                tile->actionOnTap();
                CCLOG("%d ", tile->getIdTile());
            }
        }
        if(m_data.size() <= 0) {
            gameStatus = GameStatus::GAMEWIN;
            currentLevel++;
            m_timeBarTop->stopAllActions();
            runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=] {
                this->showWinLayer();
                this->hideTiles();
                
                
            }) ,NULL));
            
            CCLOG("game win");
        }
    } else if (gameStatus == GameStatus::GAMEOVER && m_gameOverLayer->canTap) {
//        m_gameOverLayer->hideLayer();
//        m_gameOverLayer->setScale(0.0);
//        resetLevel(0);
    }
    
    return true;
}
