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
 * Created by Christine XYS
 */

#import "Streethawk.h"
#import <MessageUI/MessageUI.h>

@interface Streethawk () <MFMailComposeViewControllerDelegate>

@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForRegisterView;  //remember command to be used for callback
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForRawJson;
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForPushData;
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForPushResult;
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForOpenUrl;
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForNewFeeds;
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForFetchFeeds;
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForShareUrl;
@property (nonatomic, strong) NSMutableDictionary *dictPushMsgHandler; //remember msg and click handler, to continue between `- (BOOL)onReceive:(PushDataForApplication *)pushData clickButton:(ClickButtonHandler)handler` and `sendPushResult`.

@end

@implementation Streethawk

#pragma mark - functions

- (void)streethawkinit:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    [StreetHawk registerInstallForApp:nil/*read from Info.plist APP_KEY*/ withDebugMode:StreetHawk.isDebugMode withiTunesId:StreetHawk.itunesAppId];
    [StreetHawk shPGHtmlReceiver:self]; //register as html page load observer.
    [StreetHawk shSetCustomiseHandler:self]; //register as customise handler.
    self.dictPushMsgHandler = [NSMutableDictionary dictionary];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)tagNumeric:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && [command.arguments[1] respondsToSelector:@selector(doubleValue)])
        {
            NSString *key = command.arguments[0];
            double value = [command.arguments[1] doubleValue];
            [StreetHawk tagNumeric:value forKey:key];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects string and [1] expects double."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)tagString:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && [command.arguments[1] isKindOfClass:[NSString class]])
        {
            NSString *key = command.arguments[0];
            NSString *value = command.arguments[1];
            [StreetHawk tagString:value forKey:key];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects string and [1] expects string."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)tagDatetime:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && ([command.arguments[1] isKindOfClass:[NSDate class]] || [command.arguments[1] isKindOfClass:[NSString class]]))
        {
            NSString *key = command.arguments[0];
            NSDate *value = nil;
            if ([command.arguments[1] isKindOfClass:[NSDate class]])
            {
                value = command.arguments[1];
            }
            if ([command.arguments[1] isKindOfClass:[NSString class]])
            {
                value = parseDate(command.arguments[1], 0);
            }
            if (value != nil)
            {
                [StreetHawk tagDatetime:value forKey:key];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            }
            else
            {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [1] expects correct datetime format like \"2014-12-26 50:32:17\"."];
            }
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects string and [1] expects datetime."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)incrementTag:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]])
        {
            NSString *key = command.arguments[0];
            [StreetHawk incrementTag:key];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects string."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)removeTag:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]])
        {
            NSString *key = command.arguments[0];
            [StreetHawk removeTag:key];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects string."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)currentPage:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && ((NSString *)command.arguments[0]).length > 0)
        {
            NSString *page = command.arguments[0];
            [StreetHawk shNotifyPageEnter:page];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects a non-empty string."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSendSimpleFeedback:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && [command.arguments[1] isKindOfClass:[NSString class]])
        {
            NSString *title = command.arguments[0];
            NSString *message = command.arguments[1];
            [StreetHawk shSendFeedbackWithTitle:title withContent:message withHandler:nil];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expects [title_string, message_string]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shCustomActivityList:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if ([command.arguments isKindOfClass:[NSArray class]])
    {
        NSArray *arrayDicts = (NSArray *)command.arguments;
        NSMutableArray *arrayFriendlyNames = [NSMutableArray array];
        for (int i = 0; i < arrayDicts.count; i ++)
        {
            if ([arrayDicts[i] isKindOfClass:[NSDictionary class]])
            {
                NSDictionary *dict = (NSDictionary *)arrayDicts[i];
                if (dict.allKeys.count == 1)
                {
                    if ([dict.allKeys[0] isKindOfClass:[NSString class]] && [dict.allValues[0] isKindOfClass:[NSString class]])
                    {
                        SHFriendlyNameObject *obj = [[SHFriendlyNameObject alloc] init];
                        obj.friendlyName = dict.allKeys[0];
                        obj.vc = dict.allValues[0];
                        [arrayFriendlyNames addObject:obj];
                    }
                    else
                    {
                        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"{friendly_name:view_name} both should be string."];
                        break;
                    }
                }
                else
                {
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Expect dictionary {friendly_name:view_name} inside array."];
                    break;
                }
            }
            else
            {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Expect dictionary {friendly_name:view_name} inside array."];
                break;
            }
        }
        if (pluginResult == nil)  //no error happen
        {
            [StreetHawk shCustomActivityList:arrayFriendlyNames];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expects array contains friendy name mapping."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shGetViewName:(CDVInvokedUrlCommand *)command
{
    NSString *viewName  = [StreetHawk shGetViewName];
    if (viewName != nil && viewName.length > 0)  //check not empty to avoid infinit loop
    {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:viewName];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)shRegisterViewCallback:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForRegisterView = command;  //remember this command to be used when 8004 comes at FG.
}

- (void)shRawJsonCallback:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForRawJson = command;  //remember this command to be used when 8049 push json
}

- (void)registerPushDataCallback:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForPushData = command;
}

- (void)sendPushResult:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSNumber class]] && [command.arguments[1] isKindOfClass:[NSNumber class]])
        {
            NSInteger msgId = [command.arguments[0] integerValue];
            NSInteger pushResult = [command.arguments[1] integerValue];
            if (pushResult < -1 || pushResult > 1)
            {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Push result should be: 1 for accept, 0 for postpone, -1 for decline."];
            }
            else
            {
                NSAssert([self.dictPushMsgHandler.allKeys containsObject:@(msgId)], @"Cannot find msgid %ld match.", msgId);
                if ([self.dictPushMsgHandler.allKeys containsObject:@(msgId)])
                {
                    ClickButtonHandler handler = self.dictPushMsgHandler[@(msgId)];
                    handler((SHResult)pushResult);
                    [self.dictPushMsgHandler removeObjectForKey:@(msgId)];
                }
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            }
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expect [int_msgid, int_pushresult]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)registerPushResultCallback:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForPushResult = command;
}

- (void)shDeeplinking:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForOpenUrl = command; //remember this command to be used when open url happen
    StreetHawk.openUrlHandler = ^(NSURL *openUrl)
    {
        if (self.callbackCommandForOpenUrl != nil)
        {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:openUrl.absoluteString];
            [pluginResult setKeepCallbackAsBool:YES];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForOpenUrl.callbackId];
        }
    };
}

- (void)notifyNewFeedCallback:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForNewFeeds = command;
    StreetHawk.newFeedHandler = ^()
    {
        if (self.callbackCommandForNewFeeds != nil)
        {
            CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            [pluginResult setKeepCallbackAsBool:YES];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForNewFeeds.callbackId];
        }
    };
}

- (void)registerFeedItemCallback:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForFetchFeeds = command;
}

- (void)shGetFeedDataFromServer:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSNumber class]])
        {
            NSInteger offset = [command.arguments[0] integerValue];
            [StreetHawk feed:offset withHandler:^(NSArray *arrayFeeds, NSError *error)
            {
                if (self.callbackCommandForFetchFeeds)
                {
                    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsArray:arrayFeeds];
                    [pluginResult setKeepCallbackAsBool:YES];
                    [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForFetchFeeds.callbackId];
                }
            }];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expect [int_offset]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shReportFeedRead:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSNumber class]] && [command.arguments[1] isKindOfClass:[NSNumber class]])
        {
            NSInteger feedId = [command.arguments[0] integerValue];
            NSInteger feedResult = [command.arguments[1] integerValue];
            if (feedResult < -1 || feedResult > 1)
            {
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Feed result should be: 1 for accept, 0 for postpone, -1 for decline."];
            }
            else
            {
                [StreetHawk sendLogForFeed:feedId withResult:(SHResult)feedResult];
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
            }
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expect [int_feedid, int_feedresult]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getShareUrlForAppDownload:(CDVInvokedUrlCommand *)command
{
    self.callbackCommandForShareUrl = command;
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && [command.arguments[1] isKindOfClass:[NSString class]])
        {
            NSString *campaign = command.arguments[0];
            NSString *deeplinking = command.arguments[1];
            NSURL *deeplinkingUrl = nil;
            if (deeplinking != nil && deeplinking.length > 0)
            {
                deeplinkingUrl = [NSURL URLWithString:deeplinking];
                if (deeplinkingUrl == nil)
                {
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Command 2 is not valid url format, correct it or set empty."];
                    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                    return;
                }
            }
            [StreetHawk originateShareWithCampaign:campaign shareUrl:deeplinkingUrl streetHawkGrowth_object:^(id result, NSError *error)
             {
                 if (self.callbackCommandForShareUrl != nil) //do automatically handling
                 {
                     CDVPluginResult *pluginResult = nil;
                     if (error == nil)
                     {
                         pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:result];
                     }
                     else
                     {
                         pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:error.localizedDescription];
                     }
                     [pluginResult setKeepCallbackAsBool:YES];
                     [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForShareUrl.callbackId];
                 }
             }];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expect [campaign_string, deeplinkUrl_string]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    if (pluginResult != nil)
    {
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)InviteFriendsToDownloadApplication:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 4)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]] && [command.arguments[1] isKindOfClass:[NSString class]] && [command.arguments[2] isKindOfClass:[NSString class]] && [command.arguments[3] isKindOfClass:[NSString class]])
        {
            NSString *campaign = command.arguments[0];
            NSString *deeplinking = command.arguments[1];
            NSString *emailTitle = command.arguments[2];
            NSString *emailBody = command.arguments[3];
            NSURL *deeplinkingUrl = nil;
            if (deeplinking != nil && deeplinking.length > 0)
            {
                deeplinkingUrl = [NSURL URLWithString:deeplinking];
                if (deeplinkingUrl == nil)
                {
                    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Command 2 is not valid url format, correct it or set empty."];
                    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                    return;
                }
            }
            [StreetHawk originateShareWithCampaign:campaign shareUrl:deeplinkingUrl streetHawkGrowth_object:^(id result, NSError *error)
             {
                 presentErrorAlert(error, YES);
                 if (error == nil)
                 {
                     dispatch_async(dispatch_get_main_queue(), ^
                        {
                            NSString *shareUrl = result;
                            if ([MFMailComposeViewController canSendMail])
                            {
                                MFMailComposeViewController *mc = [[MFMailComposeViewController alloc] init];
                                mc.mailComposeDelegate = self;
                                [mc setMessageBody:[NSString stringWithFormat:@"%@\n\n%@", emailBody, shareUrl] isHTML:NO];
                                [mc setSubject:emailTitle];
                                UIWindow *window = [UIApplication sharedApplication].windows[0];
                                [window.rootViewController presentViewController:mc animated:YES completion:nil];
                            }
                            else
                            {
                                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"share_guid_url" message:shareUrl delegate:nil cancelButtonTitle:nil otherButtonTitles:@"OK", nil];
                                [alert show];
                            }
                        });
                 }
             }];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expect [campaign_string, deeplinkUrl_string, emailSubject_string, emailBody_string]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 4."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - properties

- (void)setAppKey:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]])
        {
            StreetHawk.appKey = command.arguments[0];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expect [appKey_string]."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getSHLibraryVersion:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:StreetHawk.version];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)getCurrentFormattedDateTime:(CDVInvokedUrlCommand *)command
{
    NSString *dateStr = formatStreetHawkDate([NSDate date]);
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:dateStr];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetEnableLogs:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] respondsToSelector:@selector(boolValue)])
        {
            BOOL isEnabled = [command.arguments[0] boolValue];
            StreetHawk.isDebugMode = isEnabled;
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects bool."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shEnableLogs:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:StreetHawk.isDebugMode];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetiTunesId:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSString class]])
        {
            StreetHawk.itunesAppId = command.arguments[0];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects string."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shiTunesId:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:StreetHawk.itunesAppId];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetDefaultPushNotificationSupport:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] respondsToSelector:@selector(boolValue)])
        {
            StreetHawk.isDefaultNotificationEnabled = [command.arguments[0] boolValue];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects bool."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetIsPushNotificationEnabled:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] respondsToSelector:@selector(boolValue)])
        {
            StreetHawk.isNotificationEnabled = [command.arguments[0] boolValue];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects bool."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shIsPushNotificationEnabled:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:StreetHawk.isNotificationEnabled];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetDefaultLocationSupport:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] respondsToSelector:@selector(boolValue)])
        {
            StreetHawk.isDefaultLocationServiceEnabled = [command.arguments[0] boolValue];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects bool."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetIsUseLocation:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] respondsToSelector:@selector(boolValue)])
        {
            StreetHawk.isLocationServiceEnabled = [command.arguments[0] boolValue];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects bool."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shIsUseLocation:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:StreetHawk.isLocationServiceEnabled];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetAlertSetting:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] respondsToSelector:@selector(intValue)])
        {
            [StreetHawk shSetAlertSetting:[command.arguments[0] intValue] finish:nil];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects int."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 1."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shAlertSettings:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:(int)[StreetHawk getAlertSettingMinutes]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shGetAppKey:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:StreetHawk.appKey];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - none iOS implementation

- (void)sendLogForTagUser:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetManualLocation:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shOnResume:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shOnPause:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)setUseCustomDialog:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shEnterBeacon:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shExitBeacon:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetBeaconSupport:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)displayBadge:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)shSetGcmSenderId:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)forcePushToNotificationBar:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - override

- (void)shPGDisplayHtmlFileName:(NSString *)html_fileName
{
    //If Phonegap App js not implement callback function, nothing happen. Not crash App.
    if (self.callbackCommandForRegisterView != nil)
    {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:html_fileName];
        [pluginResult setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForRegisterView.callbackId];
    }
}

- (void)shRawJsonCallbackWithTitle:(NSString *)title withMessage:(NSString *)message withJson:(NSString *)json
{
    if (self.callbackCommandForRawJson != nil)
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        dict[@"title"] = NONULL(title);
        dict[@"message"] = NONULL(message);
        dict[@"json"] = NONULL(json);
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
        [pluginResult setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForRawJson.callbackId];
    }
}

- (BOOL)onReceive:(PushDataForApplication *)pushData clickButton:(ClickButtonHandler)handler
{
    if (self.callbackCommandForPushData != nil)
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        dict[@"action"] = @(pushData.action);
        dict[@"msgid"] = @(pushData.msgID);
        dict[@"title"] = NONULL(pushData.title);
        dict[@"message"] = NONULL(pushData.message);
        dict[@"data"] = NONULL(pushData.data.description);
        dict[@"portion"] = @(pushData.portion);
        dict[@"orientation"] = @(pushData.orientation);
        dict[@"speed"] = @(pushData.speed);
        dict[@"sound"] = NONULL(pushData.sound);
        dict[@"badge"] = @(pushData.badge);
        dict[@"displaywihtoutdialog"] = @(pushData.displayWithoutDialog);
        //insert into memory cache
        if (handler)
        {
            NSAssert(![self.dictPushMsgHandler.allKeys containsObject:@(pushData.msgID)], @"msg id %ld is inside cache.", pushData.msgID);
            if (![self.dictPushMsgHandler.allKeys containsObject:@(pushData.msgID)])
            {
                [self.dictPushMsgHandler setObject:handler forKey:@(pushData.msgID)];
            }
        }
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
        [pluginResult setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForPushData.callbackId];
        return YES; //not able to get return value from js, so once implement `registerPushDataCallback` all confirm dialog use js, not like native sdk which can override some and leave others not affected.
    }
    return NO;
}

- (void)onReceiveResult:(PushDataForApplication *)pushData withResult:(SHResult)result
{
    if (self.callbackCommandForPushResult != nil)
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        dict[@"result"] = @(result);
        dict[@"action"] = @(pushData.action);
        dict[@"msgid"] = @(pushData.msgID);
        dict[@"title"] = NONULL(pushData.title);
        dict[@"message"] = NONULL(pushData.message);
        dict[@"data"] = NONULL(pushData.data.description);
        dict[@"portion"] = @(pushData.portion);
        dict[@"orientation"] = @(pushData.orientation);
        dict[@"speed"] = @(pushData.speed);
        dict[@"sound"] = NONULL(pushData.sound);
        dict[@"badge"] = @(pushData.badge);
        dict[@"displaywihtoutdialog"] = @(pushData.displayWithoutDialog);
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
        [pluginResult setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForPushResult.callbackId];
    }
}

#pragma mark - MFMailComposeViewControllerDelegate

- (void)mailComposeController:(MFMailComposeViewController *)controller didFinishWithResult:(MFMailComposeResult)result error:(NSError *)error
{
    if (!error)
    {
        [controller dismissViewControllerAnimated:YES completion:nil];
    }
}

@end
