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
 * Created by Christine XYS. 
 */

#import "StreetHawkPublicFwds.h"

#define FRIENDLYNAME_KEY                    @"FRIENDLYNAME_KEY" //key in user defaults for whole friendly name, it get an array, with each one is a dictionary.
#define FRIENDLYNAME_NAME                   @"FRIENDLYNAME_NAME"  //the register to server name.
#define FRIENDLYNAME_VC                     @"FRIENDLYNAME_VC"  //the view controller class name
#define FRIENDLYNAME_XIB_IPHONE             @"FRIENDLYNAME_XIB_IPHONE"  //the xib for iphone
#define FRIENDLYNAME_XIB_IPAD               @"FRIENDLYNAME_XIB_IPAD"  //the xib for ipad

#define FRIENDLYNAME_REGISTER               @"register"  //reserved friendly name for login UI, push notification code 8006
#define FRIENDLYNAME_LOGIN                  @"login"  //reserved friendly name for login UI, push notification code 8007

#define PHONEGAP_8004_PAGE                  @"PHONEGAP_8004_PAGE"  //when Phonegap receive 8004 at background and launch, store this and it will read by [StreetHawk shGetViewName] when launch
#define PHONEGAP_8004_MSGID                 @"PHONEGAP_8004_MSGID" //together with PHONEGAP_8004_PAGE.

/**
 An enum for notification action. Since iOS 8 user can directly reply on notification, and here is the pre-defined action.
 */
enum SHNotificationActionResult
{
    SHNotificationActionResult_Unknown,
    SHNotificationActionResult_Yes,
    SHNotificationActionResult_NO,
    SHNotificationActionResult_Later,
};
typedef enum SHNotificationActionResult SHNotificationActionResult;

/**
 An enum to treat App in FG or BG. Normally uses `SHAppFGBG_Unknown` to let App decide by `[UIApplication sharedApplication].applicationState`, however Titanium always return `UIApplicationStateActive`, and instead imlement FG or BG by its own payload, so extent API to be able to decide FG or BG.
 */
enum SHAppFGBG
{
    SHAppFGBG_Unknown,
    SHAppFGBG_FG,
    SHAppFGBG_BG,
};
typedef enum SHAppFGBG SHAppFGBG;

/**
 StreetHawk notification handler for dealing with remote or local notifications.
 */
@interface SHNotificationHandler : NSObject

/**
 System defined some code and actions, register by default. 
 */
- (NSMutableSet *)registerDefinedCategoryAndActions;

/**
 App delegate for click button get action id, convert it to be action type.
 */
- (SHNotificationActionResult)actionResultFromId:(NSString *)actionId;

/**
 Check whether this push is from StreetHawk's defined code. If yes process StreetHawk's handling, if no should just return.
 */
- (BOOL)isDefinedCode:(NSDictionary *)userInfo;

/**
 This method is called to filter `code`. A StreetHawk style remote notification must have positive int value `code`, if not this method will return without any effect. After filter `code`, it calls `- (BOOL)handleDefinedCode:(int)code userInfo:(NSDictionary *)userInfo withAction:(SHNotificationAction)action treatAppAs:(SHAppFGBG)appFGBG` to perform action.
 
 @param userInfo Server remote notification payload, or local notification payload by response.
 @param action If response on notification directly here is the answer, at this time App state is inactive.
 @param appFGBG Treat this remote notification handled as FG or BG.
 @return YES if this notification is handleable by StreetHawk SDK; NO if it's not recognizable or not as expected as StreetHawk SDK.
 */
- (BOOL)handleDefinedUserInfo:(NSDictionary *)userInfo withAction:(SHNotificationActionResult)action treatAppAs:(SHAppFGBG)appFGBG;

@end
