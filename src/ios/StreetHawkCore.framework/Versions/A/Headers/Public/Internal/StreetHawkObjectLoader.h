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
#import "../Object/StreetHawkObject.h"  //for StreetHawkObjectDelegate definition

/**
 A callback for loading one child inside a StreetHawkObjectSet. Refer to `loadSet:withHandler:`.
 */
typedef void (^SetChildrenLoader)(id<StreetHawkObjectSet> parent, StreetHawkObject *child, NSInteger index, NSError *error, BOOL *stop);

/**
 Key concept in StreetHawk SDK. It's a controller/bring to manipulate StreetHawkObjectSet, StreetHawkObjectStore. It's responsible for "loading" objects, that means if the object is not loaded before or need refresh, request the object from server and then cache to local DB; if the objects is already cached, load from DB. This functions decide it's the center for visiting local cache (add/delete/check objects), requesting server fetch.
 */
@interface StreetHawkObjectLoader : NSObject<StreetHawkObjectDelegate>

/** @name Creator */

/**
 Initialize the object load with engine. Note: the object store is not setup yet, must use `setObjectStore:` separately when store is ready.
 */
-(id)initWithEngine:(StreetHawkEngine *)theEngine;

/**
 Sets the object store. This must done, otherwise loader cannot work properly.
 */
-(void)setObjectStore:(StreetHawkObjectStore *)store;

/**
 Delete the existing SQLite cache DB file, and create a new one.
 */
-(NSError *)resetObjectStore;

/** @name Big Ass Loading */

/**
 Load the object into memory. StreetHawkObject is init with ID, although the object is not nil, the inside information except suid is not ready. If caller directly call the property, nil is returned. This method is to make sure the object is *fully* loaded into memory. The check order is:
 
 - If the object is already in memory and not need refresh, just get it.
 - If the object has not been loaded into memory, try to load it from cache.
 - If the object failed to be loaded from cache, or if it needs a refresh, load it from the server.
 
 Note: For a single StreetHawkObject, calling this fully filled its inside information. However for a StreetHawkObjectSet (which is also a StreetHawkObject), calling it filled the set's offset, length, hasMore, expectedSize etc, and fill the reference to its chilren (technically, use objectAtIndex: can get an non-nil child), but the child itself is not filled till call load for it. To load an StreetHawkObjectSet fully, see `loadSet:withHandler:`.
 */
-(void)load:(id<StreetHawkObject>)object withHandler:(StreetHawkCallbackHandler)load_handler;

/**
 Fully load a StreetHawkObjectSet with its children one by one. It first load the set, and then invoke load the element on the set. After each is loaded, the load_handler is called. 
 @param load_handler It's invoked mulitiple times for the load. Details for the parameters (id<StreetHawkObjectSet> parent, StreetHawkObject *child, int index, NSError *error, BOOL *stop):
 
 - First time is for the set loaded. parent=set, child=set, index=-1, stop=(load this set without error).
 - Next many times for load the child one by one. parent=set, child=child object (fully loaded), index=child index, stop=(load this set without error).
 - Last time is for a signal of finish. parent=set, child=nil, index=set's child count  (out of valid child range) or required index;
 
 At anytime, the caller can set *stop=YES to stop loading; or if caller wants to continue loading after meet an error, set *stop=NO.
 
 Once set *stop=YES, a last callback will receive: parent=set, child=nil, index=index + 1. Use child==nil can handle all the finish loading, either normally load finish or caller set *stop=YES to finish.
 */
-(void)loadSet:(id<StreetHawkObjectSet>)set withHandler:(SetChildrenLoader)load_handler;

/**
 Fully prepare a set at given page index. The set will be loaded from pageOffset=newPage*pageLength. In the callback load_handler, the `id result` is the fully loaded set with its element loaded also.
 */
-(void)gotoPage:(NSInteger)newPage forSet:(id<StreetHawkObjectSet>)set withHandler:(StreetHawkCallbackHandler)load_handler;

/** @name Local DB Cache */

/**
 Loads an object from the cache asynchronously. If the object is StreetHawkObject, the object is created with all the property filled; If the object is StreetHawkObjectSet, the set is created, with pageOffset=TODO, pageLength=SavedSetLength, expectedSize=TODO, and more important the children's pointer (not the whole data) inside this set is also loaded, so when call each child object, the pointer can be got. Later use load to get whole data. 
 */
-(void)loadFromCache:(id<StreetHawkObject>)object withHandler:(StreetHawkCallbackHandler)handler;

/**
 Load the children items of this objectSet using the given order or filter asynchronously. Not all the children element loaded, but given the order and filter clause, limite from (pageOffset, expectedSize (>0)/pageLength). The properties of children are also loaded as long as they are in DB.
 @param objectSet The initialized set for loading, the pageOffset/pageLength/expectedSize must be setup correctly.
 @param order_clause The string appended after "Order by", must be surrounded by {}. For example {column1 asc, column2 desc}.
 @param filter_clause The string appended to where as AND, must be surrounded by {}. For example {filter clause}.
 */
-(void)loadChildrenInSetFromCache:(id<StreetHawkObjectSet>)objset usingOrder:(NSString *)order_clause usingFilter:(NSString *)filter_clause withHandler:(StreetHawkCallbackHandler)handler;

/**
 Save an object into cache asynchronously, but because use dispatch_barrier_async all the other DB access is blocked, so save is serial. Note, unlike `loadFromCache:withHandler:`, if the object is StreetHawkObjectSet, only the set information (pageOffset, pageLength, expectedSize, hasMore) is saved, the children information is not saved. 
 @param fields If set fields=nil, all the object properties are saved; If only want to save some fields, for example StreetHawkUser only wants to save "first_name", "last_name", make an array to contain the field names. The name must exactly same as database column name, or the defined name in the object StreetHawkField. When only some fields are updated the refreshed or saved times are not updated.
 */
-(void)saveToCache:(id<StreetHawkObject>)object fields:(NSArray *)fields withHandler:(StreetHawkCallbackHandler)handler;

/**
 Bulk insert or replace homogenous objects of a type asynchronously. Because these objects are the same objClass, the SQL uses transaction to insert them together instead of create each statement for each object, thus improves performance. If save objects for the same type, high recommend to use this one instead of `saveToCache:fields:withHandler:` in loop.
 */
-(void)saveObjects:(NSArray *)objects withType:(Class)objClass withHandler:(StreetHawkCallbackHandler)handler;

/**
 Saves pointers to a list of objects as a "child" range for a parent list container.
 */
-(void)saveChildrenInSet:(id<StreetHawkObjectSet>)objset childItems:(NSArray *)childItems serverOffset:(NSInteger)offset serverLength:(NSInteger)length withHandler:(StreetHawkCallbackHandler)handler;

/**
 Delete the object (on the local cache) asynchronously, but because use dispatch_barrier_async all the other DB access is blocked, so save is serial.
 It's not implemented yet!
 */
-(void)deleteFromCache:(id<StreetHawkObject>)object withHandler:(StreetHawkCallbackHandler)handler;

/**
 Mark this object need refresh by modify __refreshed__ and __saved__ to long time ago.
 This is needed when add/remove object from set, or set one object needsRefresh. Because an object is added/removed, the page number, has more etc need to be synced with server again. Mark this to be need refresh so that next load will call server.
 */
-(void)markObjectNeedRefresh:(StreetHawkObject *)object;

/** @name Object with Set */

/**
 Tells if an object exists in a set and calls the handler once done. Unlike DeaslstObjectSet contains method, this one trigger loadSet to really load the set.
 @param handler If the object exist, result=object; If the object cannot be found from set, result=nil.
 */
-(void)checkObject:(id<StreetHawkObject>)object existsInSet:(id<StreetHawkObjectSet>)objset withHandler:(StreetHawkCallbackHandler)handler;

/**
 Add an object into set, also save to local db cache. 
 The objset will be marked as need refresh, and next time it will load from server again. This is because the set size is changed, and hard to adjust well. 
 */
-(void)addObject:(id<StreetHawkObject>)object intoSet:(id<StreetHawkObjectSet>)objset withHandler:(StreetHawkCallbackHandler)handler;

/**
 Remove a single object from a list, this also removed from local db cache. TODO: check as add, refresh?
 */
-(void)removeObject:(id<StreetHawkObject>)object fromSet:(id<StreetHawkObjectSet>)objset withHandler:(StreetHawkCallbackHandler)handler;

@end

