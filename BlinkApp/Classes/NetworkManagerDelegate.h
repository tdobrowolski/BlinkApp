

#ifndef __Blink__NetworkManagerDelegate__
#define __Blink__NetworkManagerDelegate__

enum class ConnectionState
{
    NOT_CONNECTED,
    CONNECTING,
    CONNECTED
};

class NetworkManagerDelegate
{
public:
    virtual void receivedData(const void* data, unsigned long length) = 0;
    virtual void stateChanged(ConnectionState state) = 0;
};

#endif /* Blink(__Doodler__NetworkManagerDelegate__) */
