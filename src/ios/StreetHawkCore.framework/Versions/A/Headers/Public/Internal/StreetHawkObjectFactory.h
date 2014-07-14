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

/* 
 * With the object store we need a way to create objects given the object class and ID. This factory does that.  
 * It creates instances of known objects and returns them un-initialised.  The caller must initialise it as it sees fit.
 */
@protocol StreetHawkObjectFactory

/**
 * Loads the object.
 */
-(StreetHawkObject *)objectForClass:(NSString *)obj_class withID:(NSString *)obj_id withEngine:(StreetHawkEngine *)engine_;

@end

