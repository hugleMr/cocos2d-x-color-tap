//
//  IconTile.cpp
//  FourTap
//
//  Created by Tran Tho on 4/9/16.
//
//

#include "IconTile.hpp"

bool IconTile::init() {
    if(!Node::init()) {
        return false;
    }
    
    
    //m_defaultIcon = MyUI::getInstance()->createScale9Sprite("iconCyan.png", Rect(10,10,10,10));
    m_defaultIcon->setContentSize(Size(30, 30));
    addChild(m_defaultIcon);
    
   // m_winIcon = MyUI::getInstance()->createScale9Sprite("iconYellow.png", Rect(10, 10, 10, 10));
    m_winIcon->setContentSize(Size(30, 30));
    addChild(m_winIcon);
    m_winIcon->setVisible(false);
    
    
//m_lostIcon = MyUI::getInstance()->createScale9Sprite("iconRed.png", Rect(10, 10, 10, 10));
    m_lostIcon->setContentSize(Size(30, 30));
    addChild(m_lostIcon);
    m_lostIcon->setVisible(false);
    
    
    return true;
}

void IconTile::reset() {
    m_winIcon->setVisible(false);
    m_winIcon->setScale(0.0);
    m_lostIcon->setVisible(false);
    m_lostIcon->setScale(0.0);
}

void IconTile::setWin() {
    m_winIcon->setVisible(true);
    m_winIcon->runAction(Sequence::create(
                         EaseBounceInOut::create(ScaleTo::create(0.3, 1.1)),
                         EaseBounceInOut::create(ScaleTo::create(0.1, 1.0)),
                                          NULL));
}

void IconTile::setLost() {
    m_lostIcon->setVisible(true);
    m_lostIcon->runAction(ScaleTo::create(0.1, 1.0));
}
