//
//  DrawingCanvas.cpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 24.10.2016.
//
//

#include "DrawingCanvas.hpp"

using namespace cocos2d;

bool DrawingCanvas::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    drawNode = DrawNode::create();
    background = LayerColor::create(Color4B(255, 255, 255, 255));
    
    this->addChild(background);
    
    this->addChild(drawNode);
    
    return true;
}

void DrawingCanvas::onEnter()
{
    Node::onEnter();
    
    Size visibleSize = Director::getInstance() -> getVisibleSize();
    
    this->setContentSize(visibleSize);
    drawNode->setContentSize(visibleSize);
    
    this->setupTouchHandling();
    
    drawingMenu();
}

void DrawingCanvas::setupTouchHandling()
{
    static Vec2 lastTouchPos;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        lastTouchPos = drawNode->convertTouchToNodeSpace(touch);
        
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = drawNode->convertTouchToNodeSpace(touch);
        
        drawNode->drawSegment(lastTouchPos, touchPos, 4.0f, Color4F(0.0f, 0.0f, 0.0f, 1.0f));
        
        lastTouchPos = touchPos;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void DrawingCanvas::drawingMenu()
{
    Size visibleSize = Director::getInstance() -> getVisibleSize();
    
    ui::Button* clrButton = ui::Button::create();
    clrButton -> setAnchorPoint(Vec2(1.0f, 1.0f));
    clrButton -> setPosition(Vec2(visibleSize.width * 1.74f, visibleSize.height * 0.94f));
    clrButton -> loadTextures("clrButton.png", "clrButtonPressed.png");
    clrButton -> addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::clrPressed, this)); //dodaje metode powiazana z nacisnieciem przycisku
    this -> addChild(clrButton); //dodaje przycisk czyszczenia do sceny
    
    ui::Button* bckButton = ui::Button::create();
    bckButton -> setAnchorPoint(Vec2(1.0f, 1.0f));
    bckButton -> setPosition(Vec2(visibleSize.width, visibleSize.height * 0.94f));
    bckButton -> loadTextures("bckButton.png", "bckButtonPressed.png");
    bckButton -> addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::bckPressed, this)); //dodaje metode powiazana z nacisnieciem przycisku
    this -> addChild(bckButton); //dodaje przycisk powrotu do sceny
    
    ui::Button* bulbButton = ui::Button::create();
    bulbButton -> setAnchorPoint(Vec2(1.0f, 1.0f));
    bulbButton -> setPosition(Vec2(visibleSize.width * 1.36f, visibleSize.height * 0.94f));
    bulbButton -> loadTextures("bulbButton.png", "bulbButtonPressed.png");
    bulbButton -> addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::bulbPressed, this)); //dodaje metode powiazana z nacisnieciem przycisku
    this -> addChild(bulbButton); //dodaje przycisk zmiany tła do sceny

    
}

void DrawingCanvas::clrPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) //przejscie do danego trybu jesli uzytkownik przestanie dotykac przycisk
    {
        drawNode -> clear(); //wyczyszczenie
    }
}

void DrawingCanvas::bckPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) //przejscie do danego trybu jesli uzytkownik przestanie dotykac przycisk
    {
        Director::getInstance() -> popScene(); //cofniecie do lobby
    }
}

void DrawingCanvas::bulbPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) //przejscie do danego trybu jesli uzytkownik przestanie dotykac przycisk
    {
       
    }
}
