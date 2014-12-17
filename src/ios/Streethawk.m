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

#import "Streethawk.h"

@interface Streethawk ()

@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForRegisterView;  //remember command to be used for callback
@property (nonatomic, strong) CDVInvokedUrlCommand *callbackCommandForRawJson;

@end

@implementation Streethawk

#pragma mark - functions

- (void)streethawkinit:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    StreetHawk.developmentPlatform = SHDevelopmentPlatform_Phonegap;
    [StreetHawk registerInstallForApp:nil/*read from Info.plist APP_KEY*/ withDebugMode:StreetHawk.isDebugMode withiTunesId:StreetHawk.itunesAppId];
    [StreetHawk shPGHtmlReceiver:self]; //register as html page load observer.
    [StreetHawk shSetCustomiseHandler:self]; //register as customise handler.
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

- (void)sendLogForTagUser:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 1)
    {
        if ([command.arguments[0] isKindOfClass:[NSDictionary class]])
        {
            NSDictionary *dict = command.arguments[0];
            [StreetHawk sendLogForTag:dict withDomain:LOG_DOMAIN_CUSTOM withCode:LOG_CODE_CUSTOM_USERTAG_ADD];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameter [0] expects a dictionary."];
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
            [StreetHawk shFeedback:nil needInputDialog:NO withTitle:title withMessage:message withPushMsgid:0 withPushData:nil];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters expects string."];
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

- (void)shSetManualLocation:(CDVInvokedUrlCommand *)command
{
    CDVPluginResult *pluginResult = nil;
    if (command.arguments.count == 2)
    {
        if ([command.arguments[0] isKindOfClass:[NSNumber class]] && ([command.arguments[1] isKindOfClass:[NSNumber class]]))
        {
            double latitude = [(NSNumber *)command.arguments[0] doubleValue];
            double longitude = [(NSNumber *)command.arguments[1] doubleValue];
            [StreetHawk shSetManualLocationAtLatitude:latitude atLongitude:longitude];
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        }
        else
        {
            pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Parameters should be double."];
        }
    }
    else
    {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsString:@"Wrong number of parameters, expect 2."];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

#pragma mark - properties

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

#pragma mark - none iOS implementation

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

#pragma mark - override

- (void)shPGDisplayHtmlFileName:(NSString *)html_fileName
{
    //If Phonegap App js not implement callback function, nothing happen. Not crash App.
    if (self.callbackCommandForRegisterView != nil)
    {
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:html_fileName];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForRegisterView.callbackId];
    }
}

- (void)shRawJsonCallbackWithTitle:(NSString *)title withMessage:(NSString *)message withJson:(NSString *)json
{
    if (self.callbackCommandForRawJson != nil)
    {
        NSMutableDictionary *dict = [NSMutableDictionary dictionary];
        dict[@"title"] = title;
        dict[@"message"] = message;
        dict[@"json"] = json;
        CDVPluginResult *pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:self.callbackCommandForRawJson.callbackId];
    }
}

@end
