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
 * Creates an object given a string ID.
 */
typedef id(^CreatorFromID)(NSString *objid);

#define GET_OR_CREATE_INSTANCEEX(instance_table, obj_id, handler)    \
    [(instance_table) getOrCreateInstance:(obj_id) withCreator:(handler)]

#define GET_OR_CREATE_INSTANCE(instance_table, oclass, oid, eng)    \
    GET_OR_CREATE_INSTANCEEX((instance_table), (oid),               \
        ^(NSString *objid)                                          \
        {                                                           \
            return [[oclass alloc] initWithID:(objid)               \
                                   withEngine:(eng)];               \
        })

/**
 * An instance table allows objects of a particular type to be cached by
 * ID.  Through out the system, we only want one entry for an object (of a
 * particular type) with a given ID.  Why?  Consider a Place with a
 * particular ID.  It may be referenced from anywhere in the system, so
 * updates and refreshes to the place must be visible to all references.
 * So the way this will be done is by having an instance table that keeps
 * track of all created/loaded instances and each object class will create
 * only instance with a particular ID and store them in this table.
 */
@interface StreetHawkInstanceTable : NSObject
{
@private
    NSMutableDictionary *instances;
//    dispatch_queue_t access_queue;
}

/**
 * This method does the following:
 * 1. It can return objects with a given obj_id.
 * 2. If the object does not exist, it will be created with the 
 *    creator method if it exists and THEN returns the created 
 *    instance.  If the creator method is nil then nil is returned.
 */
-(id)retainObject:(NSString *)instanceID withCreator:(CreatorFromID)creator;
-(oneway void)releaseObject:(NSString *)instanceID;

@end

