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
 * StreetHawk methods can also be asynchronous if a delegate is passed in.  A
 * delegate must implement the following methods to receive callbacks on
 * StreetHawk actions.
 */
@interface StreetHawkRegion : NSObject
{
    double latitude;
    double longitude;
}

@property (nonatomic, readonly) int attribCount;
@property (nonatomic) double latitude;
@property (nonatomic) double longitude;

/**
 * Number of attributes required to identifier the region (when sent as a
 * request).
 */
-(int)attribCount;

/**
 * Name of the ith request attribute.
 */
-(NSString *)attribName:(int)index;

/**
 * Value of the ith request attribute.
 */
-(NSString *)attribValue:(int)index;

/**
 * Search parameters.
 */
-(NSArray *)searchParams;

@end

@interface StreetHawkCircleRegion : StreetHawkRegion
{
    double radius;
}

@property (nonatomic, readonly) int attribCount;
@property (nonatomic) double radius;

/**
 * Initialises a circular region at a given center and radius.
 */
+(id)atLatitude:(double)latitude atLongitude:(double)longitude withRadius:(double)radius;

/**
 * Number of attributes required to identifier the region (when sent as a
 * request).
 */
-(int)attribCount;

/**
 * Name of the ith request attribute.
 */
-(NSString *)attribName:(int)index;

/**
 * Value of the ith request attribute.
 */
-(NSString *)attribValue:(int)index;

@end
