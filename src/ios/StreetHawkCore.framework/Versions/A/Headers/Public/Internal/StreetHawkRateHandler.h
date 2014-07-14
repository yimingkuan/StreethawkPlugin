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
 Handler for rating App, or open App Store to point to the App.
 */
@interface StreetHawkRateHandler : NSObject<UIActionSheetDelegate>

/**
 Promote rate dialog regardless of how many times enter or user dismiss before. 
 @param infoTitle Title show on action sheet, optional. `infoTitle` and `infoMessage` cannot all be empty otherwise action sheet will not show.
 @param infoMessage Message show on action sheet, optional. `infoTitle` and `infoMessage` cannot all be empty otherwise action sheet will not show.
 */
-(void)promoteRateWithTitle:(NSString *)infoTitle withMessage:(NSString *)infoMessage;

/**
 Open AppStore App to rate `itunesAppId`. If `itunesAppId` is nil or empty, or in simulator, it cannot successfully open AppStore to locate the App.
 @param itunesAppId The App's unique id in iTunes.
 */
-(void)rateApp:(NSString *)itunesAppId;

@end
