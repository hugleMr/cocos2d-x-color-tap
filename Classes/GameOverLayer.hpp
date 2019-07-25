//
//  GameOverLayer.hpp
//  FourTap
//
//  Created by Tran Tho on 4/13/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include <stdio.h>
//#include "PluginAdMob/PluginAdMob.h
#include "cocos2d.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;
using namespace ui;


class GameOverLayer : public Layer {
public:
    
    bool init();
    
    CREATE_FUNC(GameOverLayer);
    
    void updateScore(int score, int hightScore);
    
    bool canTap;
    
    void hideLayer();
    
    Size winSize;
    
    Button* buttonPlay;
    Button* buttonHome;
    Button* buttonShop;
    Button* buttonVideo;

    void setNewHightScore();
    void updateVideoGems();
    void moveGemsEffect(int number);
    
private:
    
    void update(float dt);
    
    
    bool m_updateScore;
    bool m_updateHightScore;
    bool m_newHightScore;
    int m_score;
    int m_tempScore;
    int m_hightScore;
    int m_tempHightScore;
    float m_countTime;
        
    
    float m_gameValue;
    Sprite* m_gem;
    Label* m_labelGem;
    Label* m_lableScore;
    Label* m_textScore;
    Label* m_textHightScore;
    Label* m_lableHightScore;
    Label* m_textGameOver;
    Label* m_textGiftGem;
    Label* m_textNew;
};

#endif /* GameOverLayer_hpp */
