

#import <Foundation/Foundation.h>
#import <MultipeerConnectivity/MultipeerConnectivity.h>

class NetworkManagerDelegate;

@interface NetworkManager : NSObject <MCSessionDelegate, MCNearbyServiceAdvertiserDelegate, MCNearbyServiceBrowserDelegate>

- (instancetype)init;

- (void)setDelegate:(NetworkManagerDelegate*)delegate;

- (void)attemptToJoinGame;

- (void)sendData:(NSData*)data;

- (void)disconnect;

@end
