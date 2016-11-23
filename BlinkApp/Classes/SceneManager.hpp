//
//  SceneManager.hpp
//  BlinkApp
//
//  Created by Tobiasz Dobrowolski on 19.11.2016.
//
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include "NetworkingWrapper.h"
#include "DrawingCanvas.hpp"

class DrawingCanvas;

class SceneManager : public NetworkingDelegate
{
    
public:
    static SceneManager* getInstance();
    
    void enterOneGame();
    void returnToLobby();
    
    
private:
    void receivedData(const void* data, unsigned long length) override;
    void stateChanged(ConnectionState state) override;
    
    SceneManager();
    ~SceneManager();
    
    DrawingCanvas* drawingCanvas;
    
    void loadDrawingScene(bool networked);
    
};

#endif /* SceneManager_hpp */
