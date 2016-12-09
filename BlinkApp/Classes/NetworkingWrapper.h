

#ifndef __Blink__NetworkingWrapper__
#define __Blink__NetworkingWrapper__

#include "NetworkManagerDelegate.h"

#ifdef __OBJC__
@class NetworkManager;
#else
typedef struct objc_object NetworkManager;
#endif

// Classes that want to be notified by networking activity should inherit from this class
// and set themselves as the delegate

class NetworkingDelegate
{
public:
    virtual void receivedData(const void* data, unsigned long length) = 0;
    virtual void stateChanged(ConnectionState state) = 0;
};

class NetworkingWrapper : public NetworkManagerDelegate
{
public:
    NetworkingWrapper();
    ~NetworkingWrapper();
    
    void setDelegate(NetworkingDelegate* delegate);
    
    void attemptToJoinGame();
    
    void sendData(const void* data, unsigned long length);
    
    void disconnect();
    
private:
    NetworkManager* networkManager;
    NetworkingDelegate* delegate;
    
    void receivedData(const void* data, unsigned long length);
    void stateChanged(ConnectionState state);
};

#endif /* defined(__Blink__NetworkingWrapper__) */
