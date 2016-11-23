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
    
}

SceneManager::SceneManager()
{
    drawingCanvas = nullptr;
}

SceneManager::~SceneManager()
{
    
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

