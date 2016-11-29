//
//  Lobby.hpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 30.10.2016.
//
//

#ifndef Lobby_hpp
#define Lobby_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Lobby : public cocos2d::Node
{
public:
    CREATE_FUNC(Lobby);
    
protected:
    bool init() override;
    void onEnter() override;
    void setupUI();
    void remove();
    
    void onePressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void twoPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
};

#endif /* Lobby_hpp */
