//
//  Lobby.cpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 30.10.2016.
//
//

#include "Lobby.hpp"
#include "DrawingCanvas.hpp"
#include "Constants.h"
#include "SceneManager.hpp"

using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init())
    {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(COLOR_WHITE)); //tworze tlo dla Lobby
    this -> addChild(background); //dodaje tlo do sceny
    
    return true;
}

void Lobby::onEnter()
{
    Node::onEnter();
    setupUI();
}

void Lobby::setupUI()
{
    Size visibleSize = Director::getInstance() -> getVisibleSize(); //pytam sie o rozdzielczosc
    
    Sprite* logo = Sprite::create("logo.png");
    logo -> setAnchorPoint(Vec2(0.0f, 0.5f));
    
    logo -> setPosition(Vec2(visibleSize.width * 1.0f, visibleSize.height * 0.7f));
    
    this -> addChild(logo); //dodaje logo do sceny
    
    
    Sprite* background = Sprite::create("background.png");
    background -> setAnchorPoint(Vec2(0, 0));
    
    background -> setScale(1.05);
    
    background -> setPosition(Vec2(150, 0));
    
    this -> addChild(background); //dodaje logo do sceny
    
    
    ui::Button* oneButton = ui::Button::create();
    oneButton -> setAnchorPoint(Vec2(0.0f, 1.0f));
    oneButton -> setPosition(Vec2(visibleSize.width * 1.0f, visibleSize.height * 0.28f));
    oneButton -> loadTextures("oneButton.png", "oneButton.png");
    oneButton -> addTouchEventListener(CC_CALLBACK_2(Lobby::onePressed, this)); //dodaje metode powiazana z nacisnieciem przycisku
    this -> addChild(oneButton); //dodaje przycisk 1 do sceny
    
    ui::Button* twoButton = ui::Button::create();
    twoButton -> setAnchorPoint(Vec2(0.0f, 1.0f));
    twoButton -> setPosition(Vec2(visibleSize.width * 1.335f, visibleSize.height * 0.28f));
    twoButton -> loadTextures("twoButton.png", "twoButton.png");
    twoButton -> addTouchEventListener(CC_CALLBACK_2(Lobby::twoPressed, this)); //dodaje metode powiazana z nacisnieciem przycisku
    this -> addChild(twoButton); //dodaje przycisk 2 do sceny
}

void Lobby::onePressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) //przejscie do danego trybu jesli uzytkownik przestanie dotykac przycisk
    {
        SceneManager::getInstance() -> enterOneGame();
    }
}

void Lobby::twoPressed(Ref *pSender, ui::Widget::TouchEventType eEventType)
{
    
}
