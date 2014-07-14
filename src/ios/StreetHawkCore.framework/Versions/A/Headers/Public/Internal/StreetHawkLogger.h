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
#import <sqlite3.h>

//domain
#define LOG_DOMAIN_CUSTOM       @"custom"
#define LOG_DOMAIN_NONE         @""
#define LOG_DOMAIN_METRICS      @"metrics"
#define LOG_DOMAIN_SYSTEM       @"system"
#define LOG_DOMAIN_VIRAL        @"viral"
#define LOG_DOMAIN_LOCATION     @"location"
#define LOG_DOMAIN_PUSH         @"pushack"
#define LOG_DOMAIN_DIAGNOSTICS  @"diagnostics"
#define LOG_DOMAIN_APPSTATUS    @"appstatus"

//normal code
#define LOG_CODE_NONE           0
#define LOG_CODE_REQUEST        6000
#define LOG_CODE_VIEWDETAIL     100

//push message
//Code already used in push message analytics:
//Open url in safari or inside slide: StreetHawkCore(8000). No code in SHApp.
//Update App status: 8003. SHApp not sent log.
//Go to homepage: StreetHawkCore(8004). StreetHawk action refer to LOG_CODE_PUSHCHOICE_VIEW.
//Rate: StreetHawkCore(8005). SHApp action refer to LOG_CODE_RATE_CLICKTHRU/LOG_CODE_RATE_LATER/LOG_CODE_RATE_DISMISS
//Register: StreetHawkCore(8006). Trigger customer registered friendly name = "register".
//Login: StreetHawkCore(8007). Trigger customer registered friendly name = "login".
//Open AppStore: StreetHawk(8008). No code in SHApp.
//Call phone: StreetHawk(8009). No code in SHApp.
//View offer: StreetHawkCore(8030). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_OFFER.
//View retailer: StreetHawkCore(8031). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_RETAILER.
//View product: StreetHawkCore(8032). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_PRODUCT.
//View shop: StreetHawkCore(8033). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_SHOP.
//View item: StreetHawkCore(8034). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_ITEM.
//View offer list: StreetHawkCore(8040). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_OFFERLIST.
//View retailer list: StreetHawkCore(8041). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_RETAILERLIST.
//View product list: StreetHawkCore(8042). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_PRODUCTLIST.
//View shop list: StreetHawkCore(8043). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_SHOPLIST.
//View item list: StreetHawkCore(8044). SHApp action refer to LOG_CODE_PUSHCHOICE_VIEW/LOG_CODE_PUSHCHOICE_ALERT/LOG_CODE_ACTIVITY_ITEMLIST.
//Feedback: (8049).

#define LOG_CODE_TIMEOFFSET          8050

//system code
#define LOG_CODE_SYSTEM_FIRSTRUN     8101
#define LOG_CODE_SYSTEM_START        8102
#define LOG_CODE_SYSTEM_FROMBG       8103
#define LOG_CODE_SYSTEM_TOBG         8104

//view controller enter/exit
#define LOG_CODE_VIEW_ENTER         8108
#define LOG_CODE_VIEW_EXIT          8109

//location
#define LOG_CODE_LOCATION            20
#define LOG_CODE_LOCATION_DENIED     8112
#define LOG_CODE_LOCATION_IBEACON_EXIT      22
#define LOG_CODE_LOCATION_IBEACON_ENTER     23

//share
#define LOG_CODE_SHARE_CLICKED      8510	//Share Clicked (initiated)
#define LOG_CODE_SHARE_DISMISS      8511	//Share Dismissal
#define LOG_CODE_SHARE_EMAIL        8512	//Share Email Complete
#define LOG_CODE_SHARE_FBWALL       8513	//Share Facebook Wall Complete
#define LOG_CODE_SHARE_FBMESSAGE    8514	//Share Facebook Message Complete
#define LOG_CODE_SHARE_TWITTER      8515	//Share Twitter Complete
#define LOG_CODE_SHARE_GOOGLE       8516	//Share Google+ Complete
#define LOG_CODE_SHARE_PINTEREST    8517	//Share Pinterest Complete
#define LOG_CODE_SHARE_INSTAGRAM    8518	//Share Instagram Complete
#define LOG_CODE_SHARE_SMS          8519	//Share SMS Complete
#define LOG_CODE_SHARE_OTHER        8520	//Share Other (add your own text)

//Rate App Response
#define LOG_CODE_RATE_CLICKTHRU          8521
#define LOG_CODE_RATE_LATER              8522
#define LOG_CODE_RATE_DISMISS            8523

//upgrade
#define LOG_CODE_UPGRADE_CLICKED        8524
#define LOG_CODE_UPGRADE_DISMISS        8525

//push message choose
#define LOG_CODE_PUSHCHOICE_VIEW        8530	//View (content as suggested by push)
#define LOG_CODE_PUSHCHOICE_ALERT       8531	//Show Alert Settings

#define LOG_CODE_PROFILE_OWN_VIEW       8540    //User Viewed their own profile
#define LOG_CODE_PROFILE_OWN_CHANGE     8541	//User Changed their own profile
#define LOG_CODE_PROFILE_OTHER_SEARCH   8542	//“data” is typically search-string	User searched other profiles
#define LOG_CODE_PROFILE_OTHER_VIEW 	8543	//“data” is the viewed profile ID	User Viewed their other profile

//user activity to view object and list
#define LOG_CODE_ACTIVITY_OFFER                 8550
#define LOG_CODE_ACTIVITY_OFFERLIST             8560
#define LOG_CODE_ACTIVITY_RETAILER              8551
#define LOG_CODE_ACTIVITY_RETAILERLIST          8561
#define LOG_CODE_ACTIVITY_PRODUCT               8552
#define LOG_CODE_ACTIVITY_PRODUCTLIST           8562
#define LOG_CODE_ACTIVITY_SHOP                  8553
#define LOG_CODE_ACTIVITY_SHOPLIST              8563
#define LOG_CODE_ACTIVITY_ITEM                  8554
#define LOG_CODE_ACTIVITY_ITEMLIST              8564

//user activity to purchase
#define LOG_CODE_ACTIVITY_PURCHASE_INITIATE     8571  //Initiate purchasing activity on a Product/Item
#define LOG_CODE_ACTIVITY_PURCHASE_CANCEL       8572  //Cancel purchasing activity
#define LOG_CODE_ACTIVITY_PURCHASE_INAPP        8573  //Purchase In-App selected, now is pay by PayPal
#define LOG_CODE_ACTIVITY_PURCHASE_ONLINE       8574  //Purchase Online selected
#define LOG_CODE_ACTIVITY_PURCHASE_INSTORE      8575  //Purchase In-Store selected
#define LOG_CODE_ACTIVITY_PURCHASE_PREORDER     8576  //Purchase Pre-Pay (usually for pickup) selected
#define LOG_CODE_ACTIVITY_CHECKOUT_ENTER        8581  //Enter Checkout Click
#define LOG_CODE_ACTIVITY_CHECKOUT_PAY          8582  //Checkout Pay Click
#define LOG_CODE_ACTIVITY_CHECKOUT_CANCEL       8583  //Checkout Cancel Click
#define LOG_CODE_ACTIVITY_CHECKOUT_SUCCESS      8584  //Checkout Succeed
#define LOG_CODE_ACTIVITY_CHECKOUT_FAIL         8585  //Checkout Fail
#define LOG_CODE_ACTIVITY_REDEEM_INITIATE       8591  //Initiate Redeem activity on an Offer/Voucher
#define LOG_CODE_ACTIVITY_REDEEM_CANCEL         8592  //Cancel Redeem of an Offer/Voucher
#define LOG_CODE_ACTIVITY_REDEEM_COMPLETE       8592  //Complete Redeem of an Offer/Voucher

//user activity to fave/unfave
#define LOG_CODE_ACTIVITY_FAVE_OFFER            8600
#define LOG_CODE_ACTIVITY_FAVE_RETAILER         8601
#define LOG_CODE_ACTIVITY_FAVE_PRODUCT          8602
#define LOG_CODE_ACTIVITY_FAVE_SHOP             8603
#define LOG_CODE_ACTIVITY_FAVE_ITEM             8604
#define LOG_CODE_ACTIVITY_UNFAVE_OFFER          8610
#define LOG_CODE_ACTIVITY_UNFAVE_RETAILER       8611
#define LOG_CODE_ACTIVITY_UNFAVE_PRODUCT        8612
#define LOG_CODE_ACTIVITY_UNFAVE_SHOP           8613
#define LOG_CODE_ACTIVITY_UNFAVE_ITEM           8614
#define LOG_CODE_ACTIVITY_FAVE_OFFERLIST        8620  //fave/unfave list does not have implementation.
#define LOG_CODE_ACTIVITY_FAVE_RETAILERLIST     8621
#define LOG_CODE_ACTIVITY_FAVE_PRODUCTLIST      8622
#define LOG_CODE_ACTIVITY_FAVE_SHOPLIST         8623
#define LOG_CODE_ACTIVITY_FAVE_ITEMLIST         8624
#define LOG_CODE_ACTIVITY_UNFAVE_OFFERLIST      8630
#define LOG_CODE_ACTIVITY_UNFAVE_RETAILERLIST   8631
#define LOG_CODE_ACTIVITY_UNFAVE_PRODUCTLIST    8632
#define LOG_CODE_ACTIVITY_UNFAVE_SHOPLIST       8633
#define LOG_CODE_ACTIVITY_UNFAVE_ITEMLIST       8634  //end fave/unfave list

//custom
#define LOG_CODE_CUSTOM_USERTAG_ADD             8999
#define LOG_CODE_CUSTOM_USERTAG_REMOVE          8998

//app status
#define LOG_CODE_APPSTATUS_FAIL                 2000  //fail to get app/status or parse
#define LOG_CODE_APPSTATUS_HOST_CHANGE          2001  //successfully get app/status and host changed

#ifndef STREETHAWK_LOG_H
#define STREETHAWK_LOG_H

FOUNDATION_EXPORT void DebugLog(NSString *format, ...);

#endif

/**
 This is responsible for logging App's events and send to server. The events are logged in local database, once they have enough number (LOG_UPLOAD_INTERVAL (50)), they are uploaded to server automatically. Some special events (domain=LOG_DOMAIN_LOCATION) upload local to server immediatly regardless local number. To record an event, the sample code is:
 
 * [StreetHawk sendLog:withCode:withComment:]
 */
@interface StreetHawkLogger : NSObject
{
    sqlite3 *database; 
}

@end

#import "../StreetHawkApp.h"

/**
 Internal implementation for StreetHawkApp (StreetHawkLoggerExt).
 */
@interface StreetHawkApp (LoggerExtImp)

/**
 Asynchronously log into local database, and follow the rule of StreetHawkLogger to upload to server. 
 @param handler After finish this operation, trigger handler. 
 
 "finish this operation" means: 
 
   * if only need to save to database according to rule, trigger this handler after save to database.
   * if need to upload to server according to rule, trigger this handler after request finish sending to server.
 */
-(void)sendLog:(NSString *)domain withCode:(NSInteger)code withComment:(NSString *)comment withFilename:(NSString *)fileName withFunction:(NSString *)function withLinenumber:(NSInteger)linenumber forMsgid:(NSInteger)msgid withHandler:(StreetHawkCallbackHandler)handler;

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
