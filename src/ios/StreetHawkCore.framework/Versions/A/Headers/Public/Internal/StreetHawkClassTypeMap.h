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
 It's a map with class type and object type. Key is NSString of object type, for example @"Product", value is Class type for example StreetHawkProduct.
 This is pre-setting, it's used to generialize code. For example server JSON returns "Product" in a given field, so the code use this to know create StreetHawkProduct object.
 */
@interface StreetHawkClassTypeMap : NSObject

/**
 Add a pair of (obj_type, c), for example (@"Product", StreetHawkProduct). If the obj_type is already in map dictionary, replace it.
 */
-(void)setClass:(Class)c forType:(NSString *)obj_type;

/**
 Add a pair of (obj_type, c), for example (@"Product", StreetHawkProduct). If the obj_type is already in map dictionary, decide to replace it or not using parameter `replace`.
 */
-(void)setClass:(Class)c forType:(NSString *)obj_type replace:(BOOL)replace;

/**
 Get the class type for the given object type string.
 */
-(Class)classForType:(NSString *)obj_type;

@end
