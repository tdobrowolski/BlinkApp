//
//  DrawingCanvas.hpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 24.10.2016.
//
//

#ifndef DrawingCanvas_hpp
#define DrawingCanvas_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class DrawingCanvas : public cocos2d::Node
{
public:
    CREATE_FUNC(DrawingCanvas);
    
protected:
    cocos2d::DrawNode* drawNode;
    cocos2d::LayerColor* background;
    cocos2d::Sprite* selected;
    cocos2d::Color4F selectedColor;
    
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();
    void drawingMenu();
    
    void clrPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void bckPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void bulbPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    
    void colorChangePressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);

};

#endif /* DrawingCanvas_hpp */
