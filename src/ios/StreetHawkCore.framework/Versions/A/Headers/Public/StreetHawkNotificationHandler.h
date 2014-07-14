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

#define FRIENDLYNAME_KEY                    @"FRIENDLYNAME_KEY" //key in user defaults for whole friendly name, it get an array, with each one is a dictionary.
#define FRIENDLYNAME_NAME                   @"FRIENDLYNAME_NAME"  //the register to server name.
#define FRIENDLYNAME_VC                     @"FRIENDLYNAME_VC"  //the view controller class name
#define FRIENDLYNAME_XIB_IPHONE             @"FRIENDLYNAME_XIB_IPHONE"  //the xib for iphone
#define FRIENDLYNAME_XIB_IPAD               @"FRIENDLYNAME_XIB_IPAD"  //the xib for ipad

#define FRIENDLYNAME_REGISTER               @"register"  //reserved friendly name for login UI, push notification code 8006
#define FRIENDLYNAME_LOGIN                  @"login"  //reserved friendly name for login UI, push notification code 8007

#define PHONEGAP_8004_PAGE                  @"PHONEGAP_8004_PAGE"  //when Phonegap receive 8004 at background and launch, store this and it will read by [StreetHawk shGetViewName] when launch

/**
 StreetHawk notification handler for dealing with remote or local notifications.
 */
@interface StreetHawkNotificationHandler : NSObject

/** @name Remote Notification */

/**
 When a remote notification arrives, it first reaches `-(void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo`, where user can put any code to handle this remote notification. User can use their own code of course, or add `[StreetHawk handleRemoteNotification:userInfo];` to leverage StreetHawk SDK's function (log, rate, upgrade, open url etc). 
 
 This method is called to filter `code`. A StreetHawk style remote notification must have positive int value `code`, if not this method will return without any effect. After filter `code`, it calls `-(BOOL)handleRemoteNotificationWithCode:(int)code userInfo:(NSDictionary *)userInfo` to perform action, which is also the recommended place for user to do override.
 */
-(void)didReceiveRemoteNotification:(NSDictionary *)notification;

/**
 The handler for remote notification. It depends on code to do different actions. If the code can be handled completed, return YES; otherwise return NO and finally an alert view with the code and userInfo is show.
 @param code A positive int value to indicate what action should do. StreetHawk defined code has implemented action.
 @param userInfo The whole dictionary from push server.
 */
-(BOOL)handleRemoteNotificationWithCode:(int)code userInfo:(NSDictionary *)userInfo;

/** @name Local Notification */

/**
 A method to deal with local notification. Current it does nothing but set badge to 0.
 */
-(void)didReceiveLocalNotification:(UILocalNotification *)notification;

@end
