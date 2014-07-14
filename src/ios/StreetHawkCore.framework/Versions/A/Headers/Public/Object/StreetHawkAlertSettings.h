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
 If set pause_minutes >= StreetHawk_AlertSettings_Forever, it treats as pause forever.
 */
#define StreetHawk_AlertSettings_Forever 129600  //3 month

@interface StreetHawkAlertSettings : StreetHawkObject 

/**
 The UTC pause until time, it's calculated by server and return to client.
 */
@property (nonatomic, strong) NSDate *pause_until;

/**
 The client setup minutes pass to server. Server will calculate pause time according to it. If set pause_minutes >= StreetHawk_AlertSettings_Forever or pause_minutes < 0, it treats as pause forever.
 */
@property (nonatomic) int pause_minutes;

@end
