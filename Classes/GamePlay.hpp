//
//  GamePlay.hpp
//  FourTap
//
//  Created by Tran Tho on 3/26/16.
//
//

#ifndef GamePlay_hpp
#define GamePlay_hpp

#include <stdio.h>
#include "CircleTile.hpp"
#include "IconTile.hpp"
#include "GameOverLayer.hpp"
//#include "PluginAdMob/PluginAdMob.h"
#include "GameConfig.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include <TargetConditionals.h>
#endif

USING_NS_CC;



enum class GameStatus {
    READY,
    ANDROIDRUN,
    STOP,
    PLAYERRUN,
    GAMEOVER,
    GAMEWIN,
    END,
};

class GamePlay : public Layer{
public:
    
    static cocos2d::Scene* createScene();
    
    static GamePlay* getInstance();
    
    bool init();
    
    GameStatus gameStatus;
    
    void update(float dt);
    
    CREATE_FUNC(GamePlay);
    
    Size winSize;
    
    int countTap;
    
    int currentLevel;
    
    void resetLevel(int level);
    
    GameOverLayer* getGameOverLayer();
    
private:
    
    float m_valueTimebar;
    
    Vec2 m_timeBarPos;
    
    Sprite* m_timeBarTop;
        
    GameOverLayer* m_gameOverLayer;
    
    Button* m_holdLayer;
    
    float m_offsetY;
    
    bool m_lockUpdate;
    
    Layer* m_winLayer;
    
    void dynamicCreateData(int level);
    
    void resetWinLayer();
    
    void showWinLayer();
    
    void showGameOverLayer();
    
    bool checkPlayerTap(CircleTile* currentTile);
    
    void showTiles();
    
    void hideTiles();
    
    float m_delayTime;
    
    int m_valueCountToPlay;
    
    int m_countData;
    
    Label* m_labelScore;
    
    Label* m_gameStatus;
    
    Label* m_gameTapText;
    
    int m_gameTapValue;
    
    Vector<CircleTile*>* m_listCircleTiles;
    
    Vector<IconTile*> m_listIcons;
    
    void drawListIcon(int number);
    
    void drawIconOnLine(float line, int number);
    
    std::vector<int> m_data;
    
    void androidRun(std::vector<int> data);
    
    CircleTile* getCircleById(int id);
    
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //Admod
    void adViewDidReceiveAd(const std::string &name) {
        CCLOG("adViewDidReceiveAd  %s", name.c_str());
    }
    void adViewDidFailToReceiveAdWithError(const std::string &name, const std::string &msg) {
        CCLOG("adViewDidFailToReceiveAdWithError %s", name.c_str());
        CCLOG("adViewDidFailToReceiveAdWithError %s", msg.c_str());
    }
    void adViewWillPresentScreen(const std::string &name) {
        CCLOG("adViewDidReceiveAd  %s", name.c_str());

    }
    void adViewDidDismissScreen(const std::string &name) {
        CCLOG("adViewDidDismissScreen  %s", name.c_str());
    }
    void adViewWillDismissScreen(const std::string &name) {
        CCLOG("adViewWillDismissScreen  %s", name.c_str());
    }
    void adViewWillLeaveApplication(const std::string &name) {
        CCLOG("adViewWillLeaveApplication  %s", name.c_str());
    }
};

#endif /* GamePlay_hpp */
