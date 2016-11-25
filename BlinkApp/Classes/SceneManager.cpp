//
//  SceneManager.cpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 19.11.2016.
//
//

#include "SceneManager.hpp"
#include "DrawingCanvas.hpp"

using namespace cocos2d;

static SceneManager* sharedSceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (!sharedSceneManager)
    {
        sharedSceneManager = new SceneManager();
    }
    
    return sharedSceneManager;
}

void SceneManager::receivedData(const void* data, unsigned long length)
{
    
}

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state)
    {
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Connection: None");
            break;
            
        case ConnectionState::CONNECTING:
            CCLOG("Connection: Waiting");
            break;
            
        case ConnectionState::CONNECTED:
            CCLOG("Connection: Positive");
            
            if (!drawingCanvas)
            {
                this -> loadDrawingScene(true);
            }
            
            break;
    }
}

SceneManager::SceneManager()
{
    drawingCanvas = nullptr;
    
    networkingWrapper = new NetworkingWrapper();
    networkingWrapper -> setDelegate(this);
}

SceneManager::~SceneManager()
{
    delete networkingWrapper;
}

void SceneManager::enterOneGame()
{
    this -> loadDrawingScene(false);
}

void SceneManager::returnToLobby()
{
    if (drawingCanvas)
    {
        Director::getInstance() -> popScene();
        drawingCanvas = nullptr;
    }
}

void SceneManager::loadDrawingScene(bool networked)
{
    auto scene = Scene::create();
    
    drawingCanvas = DrawingCanvas::create();
    drawingCanvas -> setNetworkedSession(networked);
    
    scene -> addChild(drawingCanvas);
    
    Director::getInstance() -> pushScene(scene);
}

void SceneManager::connectAndEnterNetworkGame()
{
    
    networkingWrapper -> attemptToJoinGame();
    
}
