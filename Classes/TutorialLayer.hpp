//
//  TutorialLayer.hpp
//  FourTap
//
//  Created by Tran Tho on 1/19/17.
//
//

#ifndef TutorialLayer_hpp
#define TutorialLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameConfig.h"
#include "CircleTile.hpp"

using namespace cocos2d;

class TutorialLayer : public Layer {
public:
    
    CREATE_FUNC(TutorialLayer);
    
    static cocos2d::Scene* createScene();
    
    bool init();
    
    void update(float dt);
    
    Size winSize;
    
    int currentLevel;
    
private:
    
    bool m_canTap;
    
    void doTutorial();
    
    void doTutorialNext();
    
    void doTutorialEnd();
    
    void resetWinLayer();
    
    void showWinLayer();
    
    int m_numberTut;
    
    Layer* m_winLayer;
    
    Sprite* m_hand;
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    Label* m_textWelcome;
    Label* m_status;
    Label* m_labelScore;
    
    Sprite* m_timeBarTop;
    
    Vector<CircleTile*>* m_listCircleTiles;
    
    ui::Scale9Sprite* m_blackBackGround;
};

#endif /* TutorialLayer_hpp */
