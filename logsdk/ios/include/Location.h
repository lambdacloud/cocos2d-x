#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

@interface Location : NSObject <CLLocationManagerDelegate>
@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) NSString *userID;

+ (id)sharedInstance;
- (id)init;
- (void)start:(NSString *)userId;
- (void)stop;

@end