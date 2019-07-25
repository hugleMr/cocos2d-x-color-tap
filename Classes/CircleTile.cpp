//
//  CircleTile.cpp
//  FourTap
//
//  Created by Tran Tho on 3/26/16.
//
//

#include "CircleTile.hpp"
#include "SimpleAudioEngine.h"

bool CircleTile::init() {
    if(!Node::init())
        return false;
    
    effect = Sprite::create("tile0.png");
    effect->setOpacity(170);
    addChild(effect);
    
    
    spriteTile = Sprite::create("tile0.png");
    addChild(spriteTile);
    
    
    return true;
}

bool CircleTile::isTap(cocos2d::Vec2 pos) {
    
    float disX = pos.x - getPositionX();
    float disY = pos.y - getPositionY();
    float disZ = spriteTile->getContentSize().width / 2;
    float disC = std::pow(disX, 2) + std::pow(disY, 2);
    disZ = std::pow(disZ, 2);
    
    if(disC <= disZ)
        return true;
    
    return false;
}

void CircleTile::actionOnTap() {
    switch (idTile) {
        case 0:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundQ.mp3");
            break;
        case 1:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundR.mp3");
            break;
        case 2:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundS.mp3");
            break;
        case 3:
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("soundT.mp3");
            break;
            
        default:
            break;
    }
    spriteTile->setTexture("tile0.png");
    effect->setVisible(true);
    effect->setScale(1.0);
    effect->stopAllActions();
    effect->runAction(Sequence::create(ScaleTo::create(0.5, 1.3), Hide::create(), CallFunc::create([=]() {
       spriteTile->setTexture("tile0.png");
    }) ,NULL));
}

void CircleTile::hide() {
    spriteTile->setOpacity(0);
    effect->setOpacity(0);
}

void CircleTile::show(float time) {
    spriteTile->runAction(Sequence::create(DelayTime::create(0.7) ,FadeIn::create(time), NULL) );
    effect->runAction(Sequence::create(DelayTime::create(0.7) ,FadeIn::create(time), NULL) );
}
