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

//domain
#define LOG_DOMAIN_CUSTOM       @"custom"
#define LOG_DOMAIN_SYSTEM       @"system"
#define LOG_DOMAIN_LOCATION     @"location"
#define LOG_DOMAIN_PUSHACK      @"pushack"
#define LOG_DOMAIN_PUSHRESULT   @"pushresult"
#define LOG_DOMAIN_PUSHERROR    @"pusherror"
#define LOG_DOMAIN_DIAGNOSTICS  @"diagnostics"

//normal code
#define LOG_CODE_TIMEOFFSET          8050
#define LOG_CODE_HEARTBEAT           8051

//system code
#define LOG_CODE_SYSTEM_FIRSTRUN     8101
#define LOG_CODE_SYSTEM_START        8102
#define LOG_CODE_SYSTEM_FROMBG       8103
#define LOG_CODE_SYSTEM_TOBG         8104

//view controller enter/exit
#define LOG_CODE_VIEW_ENTER         8108
#define LOG_CODE_VIEW_EXIT          8109

//location
#define LOG_CODE_LOCATION_GEO        20
#define LOG_CODE_LOCATION_IBEACON    21
#define LOG_CODE_LOCATION_DENIED     8112
#define LOG_CODE_LOCATION_MORE       19

//custom
#define LOG_CODE_CUSTOM_USERTAG_ADD             8999
#define LOG_CODE_CUSTOM_USERTAG_REMOVE          8998

//remote notification result
#define LOG_RESULT_CANCEL       -1
#define LOG_RESULT_LATER        0
#define LOG_RESULT_ACCEPT       1

#ifndef SH_LOG_H
#define SH_LOG_H

FOUNDATION_EXPORT void SHLog(NSString *format, ...);

#endif

#define LAST_POST_LOG_TIME      @"LAST_POST_LOG_TIME"  //time interval since reference date for last successfully post log.

/**
 This is responsible for logging App's events and send to server. The events are logged in local database, once they have enough number (LOG_UPLOAD_INTERVAL (50)), they are uploaded to server automatically. Some special events upload local to server immediatly regardless local number. To record an event, the sample code is:
 
 * [StreetHawk sendLog:withCode:withComment:]
 */
@interface SHLogger : NSObject

/**
 Static function to get log database file path. This is independent on SHLogger instance so must make it static. It's /Library/StreetHawk/logs.db, this path can be backup by iTunes.
 @return Path to SQLite database path.
 */
+ (NSString *)databasePath;

/**
 If local SQLite db not exist, or max logid not match history, needs to clear NSUserDefaults such as `INSTALL_SUID_KEY` to treat as a new install.
 @return If refresh current install to be new install return YES; otherwise return NO.
 */
+ (BOOL)checkClearNSUserDefaultsForMismatchLogdb;

@end

#import "StreetHawkApp.h"

/**
 Internal implementation for SHApp (SHLoggerExt).
 */
@interface SHApp (LoggerExtImp)

/**
 Send logline once for: code=20, domain=location, loc_is_manual=true, loc_lat/loc_lng use pass in value, and not stop automatic location update. It not affect install's loc_lat/loc/lng either.
 @param latitude The manual latitude.
 @param longitude The manual longitude.
 */
- (void)shSetManualLocationAtLatitude:(double)latitude atLongitude:(double)longitude;

/**
 Asynchronously log into local database, and follow the rule of SHLogger to upload to server. 
 @param handler After finish this operation, trigger handler. 
 
 "finish this operation" means: 
 
   * if only need to save to database according to rule, trigger this handler after save to database.
   * if need to upload to server according to rule, trigger this handler after request finish sending to server.
 */
-(void)sendLog:(NSString *)domain withCode:(NSInteger)code withComment:(NSString *)comment forMsgid:(NSInteger)msgid withResult:(NSInteger)pushResult withHandler:(SHCallbackHandler)handler;

/**
 Send log for tagging a user (add or remove). For example, you can send user's birthday as {"key": "sh_date_of_birth", "value": "2012-12-12 11:11:11", "type": "datetime"}.
 @param dict The dictionary contains user profile information. It must in the format of: 1. add tag: {"key": key_string, "value": data_value, "type": type_string} (case sensitive). type_string supports: string, numeric and datetime. data_value follows type. If data_value is a dictionary, use "string" as its type. 2. remove tag: {"key": key_string}.
 
 Code sample for add tag:
 `NSDictionary *dictWhen = [NSDictionary dictionaryWithObjectsAndKeys:@"When", @"key", [NSDate date], @"value", @"datetime", @"type", nil];`
 `NSDictionary *dictAction = [NSDictionary dictionaryWithObjectsAndKeys:@"Action", @"key", isLogin ? @"Login" : @"Logout", @"value", @"string", @"type", nil];`
 `NSDictionary *dictUser = [NSDictionary dictionaryWithObjectsAndKeys:@"User", @"key", NONULL(username), @"value", @"string", @"type", nil];`
 `NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:@"loginButtonClick", @"key", [NSArray arrayWithObjects:dictWhen, dictAction, dictUser, nil], @"value", @"string", @"type", nil];`
 `[StreetHawk sendLogForTag:dict withDomain:@"custom" withCode:8999];`
 
 Code sample for remove tag:
 `NSDictionary *dict = [NSDictionary dictionaryWithObjectsAndKeys:@"sh_email", @"key", nil];`
 `[StreetHawk sendLogForTag:dict withDomain:@"custom" withCode:8998];`
 */
-(void)sendLogForTag:(NSDictionary *)dict withDomain:(NSString *)domain withCode:(NSInteger)code;

@end