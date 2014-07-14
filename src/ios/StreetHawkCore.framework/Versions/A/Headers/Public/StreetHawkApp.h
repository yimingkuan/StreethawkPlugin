/*
 * Copyright 2012 StreetHawk
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Created by Christine XYS    Jan 08, 2014
 */

#import "StreetHawkPublicFwds.h"
#import "Internal/StreetHawkActor.h"  //for handle actor

/**
 Enum used for register install with certain remote notification setting.
 */
enum StreetHawkApnsMode
{
    /**
     Register install with dev remote notification settings, Apple's sandbox remote notification server and dev certification will be used. This is mostly used when developing App. If you want to delay showing system permission dialog, using `isEnablePushNotification` to control it. Code snippet:
     
     `StreetHawk.isEnablePushNotification = NO;  //set push notification disabled, so when register install permission dialog will not show.`
     `[StreetHawk registerInstallForApp:... withApnsMode:StreetHawkApnsMode_Dev ...];   //this App will using sandbox remote notification, but it does not register now because "isEnablePushNotification" is NO.`
     `StreetHawk.isEnablePushNotification = YES; //later when you decide to show permission dialog, enable it.`
     */
    StreetHawkApnsMode_Dev,
    /**
     Register install with prod remote notification settings, Apple's production remote notification server and production certification will be used. This is mostly used when distribute App. If you want to delay showing system permission dialog, using `isEnablePushNotification` to control it. Code snippet:
     
     `StreetHawk.isEnablePushNotification = NO;  //set push notification disabled, so when register install permission dialog will not show.`
     `[StreetHawk registerInstallForApp:... withApnsMode:StreetHawkApnsMode_Prod ...];   //this App will using production remote notification, but it does not register now because "isEnablePushNotification" is NO.`
     `StreetHawk.isEnablePushNotification = YES; //later when you decide to show permission dialog, enable it.`
     */
    StreetHawkApnsMode_Prod,
    /**
     Register install without using remote notification. `isEnablePushNotification` is meaningless in this situation.
     */
    StreetHawkApnsMode_None,
};
typedef enum StreetHawkApnsMode StreetHawkApnsMode;

/**
 Singleton to access StreetHawkApp
 */
#define StreetHawk          [StreetHawkApp app]

/**
 The StreetHawkApp Class is core of whole SDK. It is responsible for:
 
 - Contains the property "theEngine". theEngine is widely used for sending requests to StreetHawk cloud, accessing location service etc.
 - Initializes default handlers, including push notification, local notification, install, application status change (launch, become active, enter background, enter foreground, terminated).
 - Handles global properties, such as hostAppId, apnsMode, clientVersion etc.
 - Handles action for kickOffAction.
 
 **Normal usage:**
 
 - When your Application starts, usually in `- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions`, after setting global properties such as hostAppId, (if including SHApp SDK there are more facebookAppId, paypalAppId), call  `registerInstallForApp:withDefaultHostRootUrl:withApnsMode:withDebugMode:enableLocationService:enableCrashReport:withiTunesId:` to initialize all required StreetHawk features.
 
     This is simple, here are a few lines of sample code: 
 
        [StreetHawk registerInstallForApp:appId(registered with the StreetHawk Cloud) withDefaultHostRootUrl:nil(Default host url, use nil equals https://api.streethawk.com) withApnsMode:StreetHawkApnsMode_Dev withDebugMode:Yes enableLocationService:YES(whether needs to use location service) enableCrashReport:YES(whether needs to send crash report by StreetHawk SDK) withiTunesId:@"123456"(string id register in AppStore)];

 - In Application's AppDelegate, forward message to its handler. For example:
 
        - (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification
        {
           [StreetHawk handleLocalNotification:notification];
        }
 
 - StreetHawkApp is singleton, access it by `[StreetHawkApp app]` or `StreetHawk`.
 - StreetHawkAction can handle some normal actions, the Application can trigger an action by calling `[StreetHawk kickOffAction:action forObject:objectData forType:objectType withData:assocData fromVC:fromVC];`.
 - Add tag for user is simple, code like:
 
        [StreetHawk tagString:@"a@a.com" forKey:@"sh_email"];
 
 **Necessary project settings:**
 
 To have your StreetHawk-enabled Application work properly, some project settings are necessary. 
 
 - Add "-ObjC" into "Other Linker Flags". It's necessary for using SDK otherwise link error may occur for category methods.
 - Add resource bundle into project. It's necessary for SDK's xib and image resources.
 - Because StreetHawk SDK uses significant location change at background, there is NO need to add "Required background modes" with *location service*.
 
 */
@interface StreetHawkApp : NSObject<UIApplicationDelegate>

/** @name Create and initialize */

/**
 Singleton creator of StreetHawkApp.
 @return Singleton StreetHawkApp instance.
 @discussion When launch retailer App, [SHStreetHawk hawk] singleton is called. Although SHStreetHawk inherit from StreetHawkApp, the singleton instances are different. However to make all the properties work in StreetHawk SDK which can only access [StreetHawkApp app], all the global properties changes of SHStreetHawk also forward to a singleton instance of StreetHawkApp.
 */
+(StreetHawkApp *)app;

/**
 Initialize for an Application, setting up the environment.
 @param appId The global name of the app. It's also known as property hostAppId. 
 @param rootUrl The host root url for initialize this App, for example Peeptoe has its own server so setup @"http://peeptoe.streethawk.com". If set nil use the default one. Note: the rootUrl must be complete and with protocal. "www.peeptoe.streethawk.com" is BAD.
 @param apnsMode The mode for push notification. It's also known as property apnsMode.
 @param isDebugMode The mode of whether print NSLog in Xcode console.
 @param isEnableCrashReport Whether needs StreetHawk SDK to handle crash report. If set to YES PLCrashReport is used to trace crash, and report sent to StreetHawk's server by install/crash. Please note: PLCrashReport can only be enabled once, so if your App uses another SDK such as HockeyApp which internal is also PLCrashReport, make sure only enabled one of them, cannot enable both.
 @param iTunesId The App id after register in iTunes, for example 337064413. It used for rating App, if this id is not setup, rating dialog will not promote.
 */
-(void)registerInstallForApp:(NSString *)appId withDefaultHostRootUrl:(NSString *)rootUrl withApnsMode:(StreetHawkApnsMode)apnsMode withDebugMode:(BOOL)isDebugMode enableCrashReport:(BOOL)isEnableCrashReport withiTunesId:(NSString *)iTunesId;

/** @name Global properties and methods */

/**
 This does most of the work when you add StreetHawk to your Application. For details refer to StreetHawkEngine class. 
 */
@property (nonatomic, strong) StreetHawkEngine *theEngine;

/**
 The allocated name or code for this app as set in the StreetHawk Cloud, for example "SHSheridan1". It's mandatory for an Application to work.
 */
@property (nonatomic, strong) NSString *hostAppId;

/**
 The current alive host url. It can be switched to other host at runtime.
 
 * Get: return the local cached alive host root url, if it's empty return default one `hostDefaultRootUrl`.
 * Set: if set nil or empty or same host url, nothing happen; otherwise the alive host root url is changed to new one.
 */
@property (nonatomic, strong) NSString *hostAliveRootUrl;

/**
 Default host url, it's the starting url.
 */
@property (nonatomic, strong) NSString *hostDefaultRootUrl;

/**
 The mode of this app used in push notification, refer to enum definition. It's mandatory for an Application to work.
 */
@property (nonatomic, readonly) StreetHawkApnsMode apnsMode;

/**
 Is currently in debug mode so that xcode prints NSLog.
 */
@property (nonatomic) BOOL isDebugMode;

/**
 Whether needs StreetHawk SDK to handle crash report. If set to YES PLCrashReport is used to trace crash, and report sent to StreetHawk's server by install/crash. Please note: PLCrashReport can only be enabled once, so if your App uses another SDK such as HockeyApp which internal is also PLCrashReport, make sure only enabled one of them, cannot enable both.
 */
@property (nonatomic) BOOL isEnableCrashReport;

/**
 The App id after register in iTunes, for example 337064413. It used for rating App, if this id is not setup, rating dialog will not promote.
 */
@property (nonatomic, strong) NSString *itunesAppId;

/**
The build version of current Application, shortcut for [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleVersion"]. This is version for Application project, not for SDK. Use `sdkFrameworkVersion` to get StreetHawkCore.framework SDK version.
*/
@property (nonatomic, readonly) NSString *clientVersion;

/**
 Version for StreetHawkCore.framework SDK, formatted as [server api version] / [framework version] (X.Y.Z), for example "1/1.2.5". In Finder [framework version] is visible by view framework file info.
 */
@property (nonatomic, readonly) NSString *version;

/**
 StreetHawkBaseViewController logs VC "enter/exit" when viewWillAppear and viewWillDisappear. This flag control whether log both or just log "enter".
 Set to YES so that both "enter" and "exit" is logged. It's default setting.
 Set to NO so that only "enter" is logged.
 */
@property (nonatomic) BOOL logBothVCEnterExit;

/**
 Regular logs are cached locally and will be sent in a batch after there are certain number. This flag controls whether VC enter/exit logs should be sent immediately or wait for sent in batch. 
 Set to YES so that once log a VC enter/exit, all local logs are sent. Be careful to use that because if user open VC quickly, the logs will be sent very frequently.
 Set to NO so that VC enter/exit logs work like regular logs, sent in batch. This is default setting.
 */
@property (nonatomic) BOOL sendVCEnterExitLogsImmediately;

/** @name Location Service */

/**
 Default value to initialise `isLocationServiceEnabled`, it's called once when App first launch to set to `isLocationServiceEnabled`. A typical usage is to delay asking for location allow permission (*** would like to use your current location (Don't allow/OK)):
 
 `StreetHawk.isDefaultLocationServiceEnabled = NO; //not trigger location service when App launch.`
 `[registerInstallForApp... ];   //do register without trigger location service`
 `StreetHawk.isLocationServiceEnabled = YES; //later trigger location service when need it.`
 */
@property (nonatomic) BOOL isDefaultLocationServiceEnabled;

/**
 Property to control using location service or not. Geo-location update, iBeacon, region update needs this to be enabled to work. Internal CLLocation is not released when disable location service, but all functions not trigger StreetHawk's notification.
 */
@property (nonatomic) BOOL isLocationServiceEnabled;

/**
 Controlled by /core/app/status. If "location_updates"=false, local notification still works but not send install/log to server.
 */
@property (nonatomic) BOOL enableUploadLocationChange;

/** @name Remote Notification */

/**
 Default value to initialise `isPushNotificationEnabled`, it's called once when App first launch to set to `isPushNotificationEnabled`. A typical usage is to delay asking for push notification permission:
 
 `StreetHawk.isDefaultPushNotificationEnabled = NO; //not trigger remote notification when App launch.`
 `[registerInstallForApp... withApnsMode:dev/prod/none...];   //do register with proper apns mode`
 `StreetHawk.isPushNotificationEnabled = YES; //later trigger remote notification when need it.`
 */
@property (nonatomic) BOOL isDefaultPushNotificationEnabled;

/**
 Property to control enabling push notification. 
 
 1. If user set `isDefaultPushNotificationEnabled = NO` before calling `registerInstallForApp...`, push notification is not register and system permission dialog not promote.
 2. Call `registerInstallForApp... withApnsMode:dev/prod/none` by setting proper apns mode.
 3. Later when user wants to do register, set `isPushNotificationEnabled = YES` and system permission dialog promote.
 4. Step 1 is optional. If not manually set `isDefaultPushNotificationEnabled = NO`, it's YES by default and system permission dialog show when `registerInstallForApp`.
 5. Set `isPushNotificationEnabled = NO` again after `isPushNotificationEnabled = YES` makes StreetHawk server receive `revoked`, and cause StreetHawk server not send push to client. But it does not call system unregisterForRemoteNotification, so this App can still receive push notification from other way.
 */
@property (nonatomic) BOOL isPushNotificationEnabled;

/**
 Property to define what kind of types will register for remote notification. It's combine of UIRemoteNotificationType, default value is UIRemoteNotificationTypeAlert|UIRemoteNotificationTypeBadge|UIRemoteNotificationTypeSound. Customer is free to change the types, and make sure setting up this property before registering for remote notification, such as before calling [registerForInstall...].
 */
@property (nonatomic) NSUInteger notificationTypes;

/**
 The token assigned by Apple for push notification.
 Previous device token is cached in NSUserDefaults key "APNS_DEVICE_TOKEN". If current data is nil, it's ignored and previous used. 
 When setting a different device token, an install update sent immediately for updating server's token.
 @param value the set value. If it's nil it's ignored and nothing happen.
 */
- (void)setApnsDeviceToken:(NSData *)value;

/**
 Get current saved apns device token as NSString. 
 */
- (NSString *)apnsDeviceToken;

/** @name Handlers */

/**
 Handler for installing stuff. Override by child class if child class has another handler.
 */
@property (nonatomic, strong) StreetHawkInstallHandler *installHandler;

/**
 Handler for notification stuff. Override by child class if child class has another handler.
 */
@property (nonatomic, strong) StreetHawkNotificationHandler *notificationHandler;

/**
 Handler for crash report stuff. Override by child class if child class has another handler.
 */
@property (nonatomic, strong) StreetHawkCrashHandler *crashHandler;

/**
 Hanlder for rating. Override by child class if child class has another handler.
 */
@property (nonatomic, strong) StreetHawkRateHandler *rateHandler;

/** @name Global properties and methods */

/**
 Decide whether this App is running on dev sandbox, to show some debug information.
 */
-(BOOL)runningOnDevSandbox;

/**
 App status could change for some reason, so the App needs to check current one in some situation, (start to run, from background to foreground, handle push message 8003), these are handled by StreetHawk automatically. This call is a utility function to do the check. It runs a timeout 3 second request to query current_host/core/app/status to find the app status, including: a) whether new host is available, if found new host, set to local `hostRootUrl` so later calls goes to new server. b) library fuction is allowed or forbidden. c) whether send location update. Note: this function may happen before initialize engine, so cannot use StreetHawk functions such as StreetHawkRequest. It is synchronize not asynchronze to block all request until alive host is checked, but to make sure not crash when start, limit to 3 seconds timeout.
 @param force This can be run frequently if user lock screen or go to background, so avoid checking in less 30 minutes if not force. 
 @return YES: if successfully get response and parse the status dictionary; NO: if fail to get response or fail to parse status dictionary.
 */
-(BOOL)checkAppStatus:(BOOL)force;

/**
 API to trigger feedback. It behaves in this way:
 
 * If define option choice list by `arrayChoice`, a choice list will show first, after user select one of the option: a) If `needInput` is Yes, an input UI with the selected choice is displayed for user to input free text; b) If `needInput` is No user's selected choice is posted to server directly.
 * If `arrayChoice` = nil or empty, input free text UI is displayed for user to type.
 * Choice title is mandatory, free text detail content is optional.
 @param arrayChoice The option choice list. For example, @[@"Product not Available", @"Wrong Address", @"Description mismatch"]. It can be nil.
 @param needInput Whether need to show free text input dialog. If `arrayChoice` is nil or empty always show input dialog regardless of this settings.
 @param infoTitle The title display on choice list. If nil shows "<App Name> loves Feedback!".
 @param infoMessage The message display on choice list. It can be nil or empty.
 */
-(void)shFeedback:(NSArray *)arrayChoice needInputDialog:(BOOL)needInput withTitle:(NSString *)infoTitle withMessage:(NSString *)infoMessage;

/**
 Push notification 8004/8006/8007 is to launch a certain view controller, however it's difficult for server to know "how to launch the view controller". In iOS platform it requires the following elements to initialize a view controller:
 
 * view controller class name -- mandatory, must be a class inherit from UIViewController.
 * xib for iPhone -- optional, used for intialize the view controller on iPhone device, and xib name is different from class name; if nil use class name as the xib name.
 * xib for iPad -- optional, used for intialize the view controller on iPad device, and xib name is different from class name; if nil use class name as the xib name.
 
 For Phonegap App, it can be load an html page. Refer to `shPGHtmlReceiver` and `shPGLoadHtml`.
 
 Server may have problem to send push notification, because:
 
 * iOS and Android possibly have different class name, different mechanism to launch view controller. Need to consider the platform details.
 * Applications even running on the same platform can have different ac/vc names in different versions.
 
 To make server simpler in this aspect, client side provide a way to register "friendly name", while locally store the map for vc and xib. For example, client side can register: friendly name = "login", vc = "MyLoginViewController", xib_iphone = "MyLoginViewController_iphone", xib_ipad = "MyLoginViewController_ipad", so server display "login" in web console when sending push notification. After client side receive this notification, find vc and xib locally to initialize view controller. 
 
 **Note 1: Friendly names will be visible in StreetHawk web interface and they should be the same across different platforms (ios, android etc.).**
 **Note 2: Use friendly name = "register" (FRIENDLYNAME_REGISTER) for register page, which can be specifically handled by 8006 push notification.
 **Note 3: Use friendly name = "login" (FRIENDLYNAME_LOGIN) for login page, which can be specifically handled by 8007 push notification.
 **Note 4: The friendly name will be submitted when next `checkAppStatus` with "submit_views" = true.
 @param arrayFriendlyNameObj The array with each object defines a friendly name object.
 @return If the format is correct for register friendly name, return YES; otherwise return NO, and error information can refer to console log output (withDebugMode:YES).
 */
-(BOOL)shCustomActivityList:(NSArray *)arrayFriendlyNameObj;

/**
 Create a new page according to pass in `vcClassName` and show it if current visible page does is not this one. If current has navigation controller, push in navigation stack; otherwise show in modal way.
 @param vcClassName The name of the subclass of UIViewController, must have, for example: @"MyViewController". If it's empty, or it's typo and cannot create the VC, return NO.
 @param iPhoneXib The xib name for the page in iPhone, optional, for example "MyViewController_iPhone". If it uses same name as `vcClassName`, use nil.
 @param iPadXib The xib name for the page in iPad, optional, for example "MyViewController_iPad". If it uses same name as `vcClassName`, use nil.
 @param infoTitle The title display on alert view, optional.
 @param infoMessage The message display on alert view, optional.
 @return If successfully create VC and need display, return YES; otherwise, if fail to create, or no need to display, return NO.
 */
-(BOOL)shLaunchPageForVC:(NSString *)vcClassName withiPhoneXib:(NSString *)iPhoneXib withiPadXib:(NSString *)iPadXib withTitle:(NSString *)infoTitle withMessage:(NSString *)infoMessage;

/**
 Register observer for phonegap App to load html page when receive 8004 push notification.
 @param phonegapObserver Instance class of `ISHPhonegapObserver` to load html on customer's phonegap web view.
 */
-(void)shPGHtmlReceiver:(id<ISHPhonegapObserver>)phonegapObserver;

/**
 Get stored view name for push 8004, this is used for App launches and check whether a 8004 push notification occured. If this App is waken up by 8004 push notification, the view name is stored locally and read by this function, so that App knows a specific page should be loaded.
 @return Locally stored view name when 8004 comes. It's read only once, after read local cache is cleared.
 */
- (NSString *)shGetViewName;

/**
 Trigger phonegap observer to load html page. This is used for 8004 notification which can map friendly name to html file name.
 @param htmlFile The html page register by `shCustomActivityList`.
 */
-(void)shPGLoadHtml:(NSString *)htmlFile;

/**
 Functions for handling notifications and url. It directly forwards calls to relative handler. 
 */
-(void)handleRemoteNotification:(NSDictionary *)userInfo;

/**
 Functions for handling notifications and url. It directly forwards calls to relative handler.
 */
-(void)handleLocalNotification:(UILocalNotification *)notification;

/**
 Functions for handling notifications and url. It directly forwards calls to relative handler.
 */
-(BOOL)handleURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

/** @name Actions */

/**
 "Action" is a unique concept in StreetHawk SDK. It is a pre-defined "word" to trigger some "behavior". For example, view some object or list, show alert settings, call phone or open other App etc. By calling [StreetHawk kickOffAction:...] the behaviour can be archived easily, without need to know which VC should be created, how to pass data, how to initialize. Besides easy to call, using action has the following benifit:
 
 * Server return json can define the behaviour. For example menu json returned from server can define the home page and what to do.
 * End user App can override default VC. For example, by setting [setDisplayVC:forObjectType:forAction:] the display VC can be replaced. It's like a plug-in.
 
 Implementation of actor router is a dictionary: key is `action`, object is `behaviour`. Behaviour actually is a method to know `handleAction:forObject:forType:withData:fromVC`. Depending on the use scenario, there are two kinds:
 
 * StreetHawkActionHandler: it's a simple and light-weight block, to handle a simple case. For example to do action "callphone", the behaviour is just a few lines of code. It can be put in a block, thus use `setHandler:forAction:` to plug in.
 * StreetHawkActor: it's to handle more complicate case. For example action "openurl", it needs to check login and has some button event. In this case, create a new class inherit from StreetHawkActor to host those code, and use `setActor:forAction:` to plug in.
 */
@property (nonatomic, strong) StreetHawkActorRouter* actorRouter;

/**
 Light-weight case for plug in action handler. It register a block to handle the action. Later set will override existing one in dictionary. Refer to action=callphone as an example. If set a nil for an action, it's to remove current handler from dictionary.
 */
-(void)setHandler:(StreetHawkActionHandler)handler forAction:(NSString *)action;

/**
 Register an actor to handle the action. Later set will override existing one in dictionary. Refer to action=openurl as an example. If set a nil for an action, it's to remove current actor from dictionary.
 */
-(void)setActor:(StreetHawkActor *)actor forAction:(NSString *)action;

/**
 Search for the actor of this action, and register its display VC.
 */
-(void)setDisplayVC:(Class)displayVC forObjectType:(Class)type forAction:(NSString *)action;

/**
 Handler a action.
 @param action Mandatory, must match the action from actor router. For example "view".
 @param objectData Optional, it's the dealing object. For example an StreetHawkProduct object.
 @param objectType Optional, it's the dealing object type. If object is not nil, this can pass nil and also got by [object class]. But sometimes object is nil, thus need to pass type.
 @param assocData Optional, it's a way to pass some data when dealing with this object, most cases are dictionary defined by each behaviour. For example, when open StreetHawkProduct to view, it can pass an shop's telephone number to used by call the store.
 @param fromVC The current VC, which can be used as navigation push or modal present VC. If fromVC=nil, use windows rootVC.
 @return YES means the action is handled; NO means no suitable behaviour for these pass in data.
 */
-(BOOL)kickOffAction:(NSString *)action forObject:(id)objectData forType:(Class)objectType withData:(id)assocData fromVC:(UIViewController *)fromVC;

/** @name Child class override methods */

/**
 Setup class configurations. Such as follow classes.
 Override by child class if child class needs to setup more.
 */
-(void)setupBackendClasses;

/**
 Setup observer for system event, such as applicationDidFinishLaunching, Resign Active, EnterBackground, EnterForeground etc.
 Override by child class if child class needs to setup more.
 */
-(void)setupSystemNotifications;

/**
 Initialize engine, setup objectFactory, apns mode etc. This must be called after setup hostAppId.
 */
-(void)setupEngine;

/**
 Setup internal handlers, such as installHanlder, notification handler, location manager etc.
 */
-(void)setupInternalHandlers;

/**
 Setup external classes, such as Facebook, PayPal etc.
 */
-(void)setupExternalClients;

/**
 Override system notification handler
 */
- (void)applicationDidFinishLaunching:(NSNotification *)notification;
- (void)applicationWillResignActive:(NSNotification *)notification;
- (void)applicationDidEnterBackground:(NSNotification *)notification;
- (void)applicationWillEnterForeground:(NSNotification *)notification;
- (void)applicationDidBecomeActive:(NSNotification *)notification;
- (void)applicationWillTerminate:(NSNotification *)notification;
- (void)applicationDidReceiveMemoryWarning:(NSNotification *)notification;

@end

/**
 **Extension for logs:**
 
 * The Profile for this install will be tagged with the given values. You can use these tags to run campaigns.
 
 [StreetHawk tagString:@"a@a.com" forKey:@"sh_email"];
 
 * Remove a tagged profile if not need it anymore.
 
 [StreetHawk removeTag:@"sh_email"];
 
 * Send logs to StreetHawk server for trace actions.
 
 [StreetHawk sendLog:@"ActionTrace" withCode:1080 withComment:@"Question A is answered."];
 */
@interface StreetHawkApp (LoggerExt)

/**
 Asynchronously log into local database, and follow the rule of StreetHawkLogger to upload to server.
 */
-(void)sendLog:(NSString *)domain withCode:(NSInteger)code withComment:(NSString *)comment;

/**
 Send log with domain="custom", code=8999. It's used for tagging a string value for user. For example, you can tag user's email as by:
 
 `[StreetHawk tagString:@"a@a.com" forKey:@"sh_email"];`
 
 This will send log comment as {"key": "sh_email", "value": @"a@a.com", "type": "string"}.
 
 @param value The value for tag to the user profile. Cannot be empty. It can be NSString, or NSDictionary, or NSArray. 
 @param key The key for tag to the user profile. Cannot be empty.
 */
-(void)tagString:(NSObject *)value forKey:(NSString *)key;

/**
 Send log with domain="custom", code=8999. It's used for tagging a number value for user. For example, you can tag user's favourite product count by:
 
 `[StreetHawk tagNumeric:8 forKey:@"fave_product"];`
 
 This will send log comment as {"key": "fave_product", "value": [NSNumber numberWithDouble:8], "type": "numeric"}.
 
 @param value The number value for tag to the user profile.
 @param key The key for tag to the user profile. Cannot be empty.
 */
-(void)tagNumeric:(double)value forKey:(NSString *)key;

/**
 Send log with domain="custom", code=8999. It's used for tagging a date value for user. For example, you can tag user's visit time by:
 
 `[StreetHawk tagDatetime:[NSDate date] forKey:@"visit_time"];`
 
 This will send log comment as {"key": "visit_time", "value": [NSDate date], "type": "datetime"}.
 
 @param value The date value for tag to the user profile. Cannot be empty.
 @param key The key for tag to the user profile. Cannot be empty.
 */
-(void)tagDatetime:(NSDate *)value forKey:(NSString *)key;

/**
 This is opposite function of `tagString` or `tagNumeric` or `tagDatetime`. It's to remove a user tag by the key, for example `tagDatetime` adds {"key": "sh_date_of_birth", "value": "2012-12-12 11:11:11", "type": "datetime"}, so this `removeUserTag` can remove the tag by key = "sh_date_of_birth". It send log with domain="custom", code=8998, comment = "{key : "sh_date_of_birth"}".
 @param key Key for existing tag. Cannot be empty.
 */
-(void)removeTag:(NSString *)key;

/**
 Send log with domain="custom", code=8999, comment={"key": "<key>", "value": 1, "operator": "+", "type": "numeric"}.
 @param key Key for existing tag. Cannot be empty.
 */
-(void)incrementTag:(NSString *)key;

@end
