//
//  IconTile.hpp
//  FourTap
//
//  Created by Tran Tho on 4/9/16.
//
//

#ifndef IconTile_hpp
#define IconTile_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;
using namespace ui;


class IconTile : public Node {
public:
    
    CREATE_FUNC(IconTile);
    
    bool init();
    
    void reset();
    
    void setWin();
    
    void setLost();
    
private:
    
    Scale9Sprite* m_defaultIcon;
    Scale9Sprite* m_winIcon;
    Scale9Sprite* m_lostIcon;
};

#endif /* IconTile_hpp */
