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
#import "../Internal/StreetHawkObjectReal.h" //for protocol definition

/**
 Base class of dealta entities.
 */
@interface StreetHawkObject : NSObject<StreetHawkObject>
{
    StreetHawkObjectSet *images;
}

/** @name Real Class */

/**
 * StreetHawkObject is a wrapper to StreetHawkObjectReal. All the methods are pass through to be executed by real object.
 */
-(StreetHawkObjectReal *)realObject;

/**
 * StreetHawkObject is a wrapper to StreetHawkObjectReal. All the methods are pass through to be executed by real object.
 */
+(Class)realObjectClass;

/** @name Creator */

/**
 * Refer to initWithID:withEngine:withParent:withCreator:.
 */
-(id)initWithID:(NSString *)objid withEngine:(StreetHawkEngine *)engine_;

/**
 * Refer to initWithID:withEngine:withParent:withCreator:.
 */
-(id)initWithID:(NSString *)objid withEngine:(StreetHawkEngine *)engine_ withParent:(id<StreetHawkObject>)parent;

/**
 * Refer to initWithID:withEngine:withParent:withCreator:.
 */
-(id)initWithID:(NSString *)objid withEngine:(StreetHawkEngine *)engine_ withCreator:(id(^)(NSString *objid))creator;

/**
 * Creates instances of the StreetHawkObject.
 * If not specific creator, the StreetHawkObject is a wrapper to a StreetHawkObjectReal, registerred in StreetHawkInstanceTable by objectid.
 * Engine is recored inside StreetHawkObjectReal, objid and parent are used in child classes.
 */
-(id)initWithID:(NSString *)objid withEngine:(StreetHawkEngine *)engine_ withParent:(id<StreetHawkObject>)parent withCreator:(id(^)(NSString *objid))creator;

/**
 * Refer to withID:withEngine:withParent:.
 */
+(id)withID:(NSString *)objid withEngine:(StreetHawkEngine *)engine_;

/**
 * Creates autoreleased instances of the StreetHawkObject, same as initWithID and add AutoRelease.
 * If not specific creator, the StreetHawkObject is a wrapper to a StreetHawkObjectReal, registerred in StreetHawkInstanceTable by objectid.
 * Engine is recored inside StreetHawkObjectReal, objid and parent are used in child classes.
 */
+(id)withID:(NSString *)objid withEngine:(StreetHawkEngine *)engine_ withParent:(id<StreetHawkObject>)user;

/**
 * Refer to fromDictionary:idAttribute:withEngine:withParent:.
 */
+(id)fromDictionary:(NSDictionary *)dict withEngine:(StreetHawkEngine *)engine_;

/**
 * Refer to fromDictionary:idAttribute:withEngine:withParent:.
 */
+(id)fromDictionary:(NSDictionary *)dict idAttribute:(NSString *)id_attrib withEngine:(StreetHawkEngine *)engine_;

/**
 * Refer to fromDictionary:idAttribute:withEngine:withParent:.
 */
+(id)fromDictionary:(NSDictionary *)dict withEngine:(StreetHawkEngine *)engine_ withParent:(id<StreetHawkObject>)parent;

/**
 * Default Helper to load the ID of an object from a dictionary and then create an object that is globally unique with respect to the ID.
 * For not passed in idAttribute, use defaultIDAttribute.
 * "parent" object used for objects that belong to other objects - eg Location, Want and Like objects all most have a user associated with them.
 */
+(id)fromDictionary:(NSDictionary *)dict idAttribute:(NSString *)id_attrib withEngine:(StreetHawkEngine *)engine_ withParent:(id<StreetHawkObject>)parent;

@end

@interface StreetHawkObject (Search)

/**
 Some object such as StreetHawkItem, StreetHawkOffer, StreetHawkShop is location based; other such as StreetHawkProduct, StreetHawkUser, StreetHawkInstall is not location based. If search on non-location based product, the `region` is ignored and not appended as parameters. It's NO by default.
 */
+(BOOL)searchIsLocationBased;

/**
 Searches this StreetHawkObject in a region (latitude, longitude, radius) if `searchIsLocationBased`=YES and order by location. If `searchIsLocationBased`=NO the region is ignored.
 */
+(StreetHawkObjectSet *)searchInRegion:(StreetHawkRegion *)region withParams:(NSArray *)params withEngine:(StreetHawkEngine *)engine;

/**
 General search this StreetHawkObject with the parameters.
 */
+(StreetHawkObjectSet *)searchWithParams:(NSArray *)params withEngine:(StreetHawkEngine *)engine;

@end
