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

#import "../StreetHawkPublicFwds.h"

/**
 A handler for install notifications.
 */
@interface StreetHawkInstallHandler : NSObject

/** @name Register/Unregister Remote Notification */

/**
 According to system and customer code's setting, call system API to register remote notification or update revoked.
 
 * If customer code set apnsMode=None, means not need remote notification at all, do nothing.
 * If customer code set apnsMode=dev/prod, call system API to register remote notification unless `StreetHawk.isEnablePushNotification=NO`.
 * If customer code set apnsMode=dev/prod, check system enable push notification or `StreetHawk.isEnablePushNotification=NO` to update flag `revoked` in StreetHawk server. This flag can stop StreetHawk server from sending push notification.
 */
-(void)registerForRemoteNotificationAndNotifyServer;

/** @name Install notification handlers */

/**
 Called when install/register finish successfully.
 */
- (void)installRegistrationSucceeded:(NSNotification *)aNotification;

/**
 Called when install/register finish with error.
 */
- (void)installRegistrationFailure:(NSNotification *)aNotification;

/**
 Called when install/update finish successfully.
 */
- (void)installUpdateSucceeded:(NSNotification *)aNotification;

/**
 Called when install/update finish with error.
 */
- (void)installUpdateFailure:(NSNotification *)aNotification;

@end
