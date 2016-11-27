//
//  DrawingCanvas.cpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 24.10.2016.
//
//

#include "DrawingCanvas.hpp"
#include "Constants.h"
#include "SceneManager.hpp"
#include "JSONPacker.hpp"

using namespace cocos2d;

bool DrawingCanvas::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    this -> setNetworkedSession(false);
    
    drawNode = DrawNode::create();
    background = LayerColor::create(Color4B(COLOR_WHITE));
    
    this -> addChild(background);
    
    this -> addChild(drawNode);
    
    selectedColor = COLOR_RED;
    
    return true;
}

void DrawingCanvas::onEnter()
{
    Node::onEnter();
    
    Size visibleSize = Director::getInstance() -> getVisibleSize();
    
    this -> setContentSize(visibleSize);
    drawNode -> setContentSize(visibleSize);
    
    this -> setupTouchHandling();
    
    this -> drawingMenu();
}

void DrawingCanvas::setupTouchHandling()
{
    static Vec2 lastTouchPos;
    
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener -> onTouchBegan = [&](Touch* touch, Event* event)
    {
        lastTouchPos = drawNode -> convertTouchToNodeSpace(touch);
        
        drawNode -> drawDot(lastTouchPos, INITIAL_RADIUS, selectedColor);
        
        if (this -> networkedSession)
        {
            this -> sendStrokeOverNetwork(lastTouchPos, lastTouchPos, INITIAL_RADIUS, selectedColor);
        }
        
        return true;
    };
    
    touchListener -> onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = drawNode -> convertTouchToNodeSpace(touch);
        
        drawNode -> drawSegment(lastTouchPos, touchPos, INITIAL_RADIUS, selectedColor);
        
        if (this -> networkedSession)
        {
            this -> sendStrokeOverNetwork(lastTouchPos, touchPos, INITIAL_RADIUS, selectedColor);
        }
        
        lastTouchPos = touchPos;
    };
    
    this -> getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
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
    
    selected = Sprite::create("colorRectanglePicked.png");
    selected -> setAnchorPoint(Vec2(0, 0));
    selected -> setNormalizedPosition(Vec2(0, 0));
    selected -> setColor(Color3B(COLOR_RED));

    Node* colorButtonLayout = Node::create();
    colorButtonLayout -> setContentSize(Size(visibleSize.width, visibleSize.height * 0.10f));
    colorButtonLayout -> setAnchorPoint(Vec2(0, 0));
    colorButtonLayout -> setPosition(Vec2(120, 0));
    this -> addChild(colorButtonLayout);
    
    for (int i = 1; i <= 6; ++i) //petla dodajaca przyciski i ustawiajaca ich dane
    {
        ui::Button* colorButton = ui::Button::create();
        colorButton -> setAnchorPoint(Vec2(0.0, 0.0));
        colorButton -> setPosition(Vec2(visibleSize.width * i * (1.0f/6.0f), 0.0f));
        colorButton -> loadTextures("colorRectangle.png", "colorRectangle.png");
        colorButton -> addTouchEventListener(CC_CALLBACK_2(DrawingCanvas::colorChangePressed, this)); //dodaje metode powiazana z wybraniem koloru
        colorButton -> setScale(1.03);
        
        Color4F rectangleColor;
        
        switch(i)
        {
            case 1:
                rectangleColor = COLOR_RED;
                break;
            case 2:
                rectangleColor = COLOR_ORANGE;
                break;
            case 3:
                rectangleColor = COLOR_YELLOW;
                break;
            case 4:
                rectangleColor = COLOR_BLUE;
                break;
            case 5:
                rectangleColor = COLOR_GREEN;
                break;
            case 6:
                rectangleColor = COLOR_PURPLE;
                break;
        }
        
        if (rectangleColor == COLOR_RED)
        {
            colorButton -> addChild(this -> selected);
        }
        
        colorButton -> setColor(Color3B(rectangleColor));
        colorButtonLayout -> addChild(colorButton);        
        
    }
    
}

void DrawingCanvas::setNetworkedSession(bool networkedSession)
{
    this -> networkedSession = networkedSession;
}

void DrawingCanvas::receivedData(const void* data, unsigned long length)
{
    const char* cstr = reinterpret_cast<const char*>(data);
    std::string json = std::string(cstr, length);
    
    JSONPacker::LineData lineData = JSONPacker::unpackLineDataJSON(json);
    
    drawNode -> drawDot(lineData.startPoint, lineData.radius, lineData.color);
    
    drawNode -> drawSegment(lineData.startPoint, lineData.endPoint, lineData.radius, lineData.color);
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
        SceneManager::getInstance() -> returnToLobby(); //cofniecie do lobby
    }
}

void DrawingCanvas::bulbPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) //przejscie do danego trybu jesli uzytkownik przestanie dotykac przycisk
    {
        if (isWhite == true)
            {
                this -> removeChild(background);
        
                background = LayerColor::create(Color4B(COLOR_GREY));
        
                this -> addChild(background);
        
                this -> reorderChild(background, -1);
                
                isWhite = false;
                
            } else {
                
                this -> removeChild(background);
        
                background = LayerColor::create(Color4B(COLOR_WHITE));
        
                this -> addChild(background);
        
                this -> reorderChild(background, -1);
                
                isWhite = true;
            }
    }
}

void DrawingCanvas::colorChangePressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED)
    {
        ui::Button* pressedButton = static_cast<ui::Button*>(pSender);
        Color3B pickedColor = pressedButton -> getColor();
        selectedColor = Color4F(pickedColor);
        
        selected -> setColor(Color3B(pickedColor));
        
        selected -> retain();
        selected -> removeFromParent();
        pressedButton -> addChild(selected);
        selected -> release();
        
        selected -> setPosition(Vec2(0, -5));

        auto moveTo = MoveBy::create(0.2, Vec2(0, 5));
        selected -> runAction(moveTo);
        //auto seq = Sequence::create(moveTo, nullptr);
        
        // run it
        //selected -> runAction(seq);
        
    }
}

void DrawingCanvas::sendStrokeOverNetwork(Vec2 startPoint, Vec2 endPoint, float radius, Color4F color)
{
    JSONPacker::LineData lineData;
    lineData.startPoint = startPoint;
    lineData.endPoint = endPoint;
    lineData.radius = radius;
    lineData.color = color;
    
    std::string json = JSONPacker::packLineData(lineData);
    
    SceneManager::getInstance() -> sendData(json.c_str(), json.length());
}
