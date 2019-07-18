//
//  CircleTile.hpp
//  FourTap
//
//  Created by Tran Tho on 3/26/16.
//
//

#ifndef CircleTile_hpp
#define CircleTile_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class CircleTile : public Node {
public:
    
    bool init();
    
    CREATE_FUNC(CircleTile);
    
    bool isTap(Vec2 pos);
    
    void actionOnTap();
    
    void hide();
    void show(float time);

    
    CC_SYNTHESIZE(int, idTile, IdTile);
    
private:
    
    Sprite* spriteTile;
    Sprite* effect;
    
    std::string name;
};

#endif /* CircleTile_hpp */
