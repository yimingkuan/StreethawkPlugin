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
 StreetHawkObjectSet fetch data from server. This callback is used in constructor to create a StreetHawkObjectSet. It's called by StreetHawkObjectLoader load, to really connect to server and deal with the return json.
 @see property `serverObjectSetLoader`
 */
typedef StreetHawkRequest *(^ServerObjectSetLoader)(id<StreetHawkObjectSet> objectSet, NSInteger offset, NSInteger length, StreetHawkCallbackHandler load_handler);

/**
 StreetHawkObjectSet fetch data from server. This callback is used in constructor to create a StreetHawkObjectSet. It's called by StreetHawkObjectLoader load, to really connect to server and deal with the return json.
 @see property `serverObjectSetBatchLoader`
 */
typedef StreetHawkRequest *(^ServerObjectSetBatchLoader)(id<StreetHawkObjectSet> objectSet, NSString *idlist, BatchLoadHandler load_handler);

/**
 Once parse Json into an array of dictionary, call processChildrenDictFromServer... to create child StreetHawkObject and add into object set.
 */
typedef StreetHawkObject *(^ObjectSetChildMaker)(NSDictionary *dict);

/**
 Key concept in StreetHawk SDK. It contains an array of StreetHawkObject, and can responsible for load the objects from server. 
 Note: The objects inside StreetHawkObjectSet is not permanent, it's only from pageOffset to pageOffset+pageLength. Next time when load from server, it's cleaned and reassigned new objects according to new pageOffset. So the caller needs to host those objects, for example StreetHawkInfinyTableViewDriver needs to have a cache for whole data, as its sourceSet only for a page.
 */
@protocol StreetHawkObjectSet<StreetHawkObject>

/** @name Creator */

/**
 Creates an object list for a particular owner with a given key with the default pageLength and server fetch limits. By default page offset is 0, page length is DEFAULT_PAGE_LENGTH (10), server multiple is DEFAULT_SERVER_FETCH_MULTIPLE (2), refresh interval is an hour.
 @param theOwner See property `owner`.
 @param attributeKey See property `attribute`. 
 @param loader See property `serverObjectSetLoader`. 
 */
-(id)initForOwner:(StreetHawkObject *)theOwner withAttributeKey:(NSString *)attributeKey withEngine:(StreetHawkEngine *)theEngine withLoader:(ServerObjectSetLoader)loader;

/**
 StreetHawkObjectSet fetch data from server. This callback is used in constructor to create a StreetHawkObjectSet. It's called by StreetHawkObjectLoader load, to really connect to server and deal with the return json.
 @discuss The object needs to get from server or local cache, so it cannot be fully filled when initialize it. Only a few things, such as `key` known at beginning. Later when try to really visit the object inside this set, a request needs to send to server to get it. `serverObjectSetLoader` or `serverObjectSetBatchLoader` is such a place holder. For example for `serverObjectSetLoader`, the code would be:
    `set.serverObjectSetLoader = ^(StreetHawkObjectSet *set, int offset, int length, ObjectLoadHandler load_handler)`
    `{`
        `Form a request for the given offset, length, send to server, process the returned JSON and fill into set`
    `};`
 */
@property (nonatomic, copy) ServerObjectSetLoader serverObjectSetLoader;

/**
 StreetHawkObjectSet fetch data from server. This callback is used in constructor to create a StreetHawkObjectSet. It's called by StreetHawkObjectLoader load, to really connect to server and deal with the return json.
 @see property `serverObjectSetLoader`
 */
@property (nonatomic, copy) ServerObjectSetBatchLoader serverObjectSetBatchLoader;

/**
 Set this property when creating to decide the order of requesting data. By default it's asc. It must surround by {}. Code sample:
    `set.orderClause = @"{brand_name}";` The requesting data will order by brand_name in asc.
    `set.orderClause = @"{brand_name desc}";` The requesting data will order by brand_name in desc.
 */
@property (nonatomic, strong) NSString *orderClause;

/**
 Set this property when creating to decide the filter. It must surround by {}. Code sample:
    `set.filterClause = [NSString stringWithFormat:@"{expires_at >= datetime('%@') AND dist_squared(latitude, longitude, %f, %f) < %f}", formatStreetHawkDate([NSDate date]), lat, lng, (radius * radius)];`
    `set.filterClause = @"{enabled not in ('no', 'false', 0, '0')}";`
 */
@property (nonatomic, strong) NSString *filterClause;

/**
 Set this property when creating. It's highly recommended to set this if the set contains a certain kind of child. By setting this the child object can be handled in batch (save to local DB), so that improve the performance much! Code sample:
    `set.childrenType = StreetHawkItem.class;`
 */
@property (nonatomic, assign) Class childrenType;

/** @name Metadata Properties */

/**
 A set may, or may not have an owner, decide by the needs. For example, one item can have many images, the item is owner for these images; a search set does not have owner.
 This is readonly, can only be set when initialize set.
 */
@property (nonatomic, readonly, strong) StreetHawkObject *owner;

/**
 All set have `attribute` string. It's a brief introduction of what this set for. It's readonly, can only be set by `attributeKey` when initialize set.
 
 * If this set have an owner, the final `attribute` will add the owner's information, (OwnerClassName:OwenerId:attributeKey). For example: StreetHawkRetailer:XFVT8P:images.
 * If this set has no owner, the `attribute` is `attributeKey`. For example: /items?tags=Quilts&retailer_id=XFVT8P&latitude=-33.870&longitude=151.208&radius=100000&orderby=location.
 */
@property (nonatomic, readonly, strong) NSString *attribute;

/**
 Some sets can allow loading multiple items by a comma separated list of IDs. This is used in the big ass set loading to determine which URL to post a comma separated list of IDs to, to fetch multiple objects.
 
 It's decided by the following conditions: (current no set can batch loading yet)
 1. This set has set `serverObjectSetBatchLoader`.
 2. This set has valid `batchLoadURL`.
 3. This set's owner allows batch load child. 
 */
@property (nonatomic, readonly) BOOL supportsBatchLoading;

/**
 The pagination offset.
 */
@property (nonatomic) NSInteger pageOffset;

/**
 The number of results we want to show in a "page" of results.
 */
@property (nonatomic) NSInteger pageLength;

/**
 Server fetch multiple of pageLength at one time.
 @discuss Server query is paginate. It's better to query in a section, for example (0~20), (20~40), (40~60) etc, not random such as (6~15). For this reason introduce `serverFetchMultiple`, it should be an integer > 1.
 Assume pageLength = 10, serverFetchMultiple = 2, when really send request to server:
 serverPageLength = serverFetchMultiple * pageLength = 20;
 serverPageOffset = pageOffset - (pageOffset % serverPageLength); 
 This is interesting. If pageOffset=5, the really wanted objects is (5~15), so server request is (0~20); If pageOffset=23, the really wanted object is (23~33), so server request is (20~40).
 */
@property (nonatomic) NSInteger serverFetchMultiple;

/**
 Tells if there are more children outside the pageOffset+pageLength. Usally  will be set if the server returned more items than requested in `processChildrenDictFromServer:withHandler:withChildMaker:`.
 */
@property (nonatomic) BOOL hasMoreResults;

/**
 The real number of objects inside this set. For example, a set with pageOffset=20, pageLength=10, but server may only have 25 items. After process the set has 5 objects inside it. So the expectedSize=5. 
 It comes from two ways:
 1. When load from server, `expectedSize` is the finaly valid object number after process. 
 2. When load from DB, `expectedSize` is the num_items column, indicate how many objects should be loaded. 
 */
@property (nonatomic) NSInteger expectedSize;

/** @name Child Objects */

/**
 StreetHawkObjectSet has an array to contain the children objects. Just return the one of index if not out of range. If out of range, assert and return nil.
 Note: If the children is not read from server, the array is empty. StreetHawkObjectLoader should be used first to load the objects otherwise nothing can get.
 */
-(StreetHawkObject *)objectAtIndex:(NSInteger)index;

/**
 How many child items are there totally in the array.
 Note: If the children is not read from server, the array is empty. StreetHawkObjectLoader should be used first to load the objects otherwise nothing can get.
 */
-(NSUInteger)childCount;

/**
 Tells if a particular object exists inside the memory array. 
 Note: If the children is not read from server, the array is empty. StreetHawkObjectLoader should be used first to load the objects otherwise nothing can get.
 */
-(BOOL)containsObject:(StreetHawkObject *)object;

/**
 Returns a copy of the children. The caller must release this.
 */
-(NSArray *)childrenCopy;

/**
 Gets the enumerator for the object.
 */
-(NSEnumerator *)objectEnumerator;

/**
 Add an object to the set. It only added if the object not exist.
 @return YES if the object not exist in objectSet and really added it. If the object already exist, return NO.
 */
-(BOOL)addObject:(StreetHawkObject *)object;

/**
 Remove an existing object from the set.
 @return YES if the object exist in objectSet and really remove it. If the object is not in the set, return NO.
 */
-(BOOL)removeObject:(StreetHawkObject *)object;

/**
 Remove all objects in the set.
 */
-(void)removeAllObjects;

/** @name Load and Process from Server */

/**
 Loads items from the server in batch with a given set of IDs.
 */
-(StreetHawkRequest *)batchLoadFromServer:(NSString *)idlist withHandler:(BatchLoadHandler)load_handler;

/**
 Called by the parent object or the loader block after it has received children from the server, so that this container can process the returned array for the purposes of pagination etc.
 */
-(void)processChildrenDictFromServer:(NSArray *)childrenDictArray withHandler:(StreetHawkCallbackHandler)load_handler withChildMaker:(ObjectSetChildMaker)child_maker;

@end

/**
 Key concept in StreetHawk SDK. It contains an array of StreetHawkObject, and can responsible for load the objects from server.
 Note: The objects inside StreetHawkObjectSet is not permanent, it's only from pageOffset to pageOffset+pageLength. Next time when load from server, it's cleaned and reassigned new objects according to new pageOffset. So the caller needs to host those objects, for example StreetHawkInfinyTableViewDriver needs to have a cache for whole data, as its sourceSet only for a page.
 */
@interface StreetHawkObjectSet : StreetHawkObject<StreetHawkObjectSet>

/**
 Creates an auto released object set. It's `initForOwner:withAttributeKey:withEngine:withLoader:` wrappered by autorelease.
 */
+(StreetHawkObjectSet *)setForOwner:(StreetHawkObject *)theOwner withAttributeKey:(NSString *)attributeKey withEngine:(StreetHawkEngine *)theEngine withLoader:(ServerObjectSetLoader)loader;

@end
