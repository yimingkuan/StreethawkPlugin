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
#import <sqlite3.h>

/**
 Convert a string to object. This is used when deserialize an object from string read from cache DB.
 */
typedef NSObject *(^DataReader)(NSString *);

/**
 Convert an object into string. This is used when serializing an object into string and save to cache DB.
 */
typedef NSString *(^DataWriter)(NSObject *);

/* 
 The local db that does caching and synchronisation of search results and objects that are persisted on the server. 
 It implemented on SQLite, which mainly for two kinds of objects here:
 1. Individual objects that can be loaded and saved by ID.
 2. Result sets - list of objects that can be loaded and saved on bulk, for example searches, image list. These in turn would be a bunch of individual objects that could be cached.
 */
@interface StreetHawkObjectStore : NSObject
{
    sqlite3 *database;
}

/** @name Create and Initialize */

/**
 Initialises the object store with an sqlite file.
 */
-(id)initWithPath:(NSString *)dbPath;

/**
 Initialize a database from the given path. This would close the current database and open a new one with the one at the given path. If the refresh parameter is true, the given path is cleared/erased and started afresh.
 @param dbPath A complete SQLite file path. If the file not exist, a new SQLite file will be created; otherwise open the existing one.
 @param refresh Need to delete existing file and initialize fresh new one.
 */
-(NSError *)initialiseDatabaseWithPath:(NSString*)dbPath refresh:(BOOL)refresh;

/**
 Resets the object store to be "empty". It equals to `initialiseDatabaseWithPath:dbPath refresh:YES`.
 */
-(NSError *)reset;

/**
 Convert a string to object. This is used when deserialize an object from string read from cache DB.
 A typical usage is to read from JSON string and create object, for example:
    `objectStore.dataReader = ^(NSString *input) {`
        `return (NSObject *)[input objectFromJSONString];`
    `};`
 */
@property (nonatomic, copy) DataReader dataReader;

/**
 Convert an object into string. This is used when serializing an object into string and save to cache DB.
 A typical usage is to serialize object into JSON string, for example:
    `objectStore.dataWriter = ^(NSObject *input) {`
        `return [input JSONString];`
    `};`
 */
@property (nonatomic, copy) DataWriter dataWriter;

/** @name Load Objects */

/**
 The object is created with id, but other fields are empty. Load from DB to populate its fields. It only fills the properties of this object directly from table, nothing do with children if the object is StreetHawkObjectSet. Use `loadChildrenInSet` to do load children item part.
 @return YES if the object is founded by id. NO if there is no object found in DB by id.
 */
-(BOOL)loadObject:(StreetHawkObject *)object usingFactory:(id<StreetHawkObjectFactory>)obj_factory;

/**
 Load the children items of this objectSet using the given order or filter. The objectSet must be initialize with right pageOffset/pageLength/expectedSize setup, use `loadObject:usingFactory:` can guarantee this. Not all the children element loaded, but given the order and filter clause, limite from (pageOffset, expectedSize (>0)/pageLength). The properties of children are also loaded as long as they are in DB.
 @param objectSet The initialized set for loading, the pageOffset/pageLength/expectedSize must be setup correctly.
 @param order_clause The string appended after "Order by", must be surrounded by {}. For example {column1 asc, column2 desc}.
 @param filter_clause The string appended to where as AND, must be surrounded by {}. For example {filter clause}.
 @return The loaded children item count.
 */
-(int)loadChildrenInSet:(StreetHawkObjectSet *)objectSet usingOrder:(NSString *)order_clause usingFilter:(NSString *)filter_clause usingFactory:(id<StreetHawkObjectFactory>)obj_factory;

/** @name Save Objects */

/**
 Save an object into cache. If the object is StreetHawkObjectSet, only the set information (pageOffset, pageLength, expectedSize, hasMore) is saved, the children information is not saved. If the fields==nil, the object will be inserted if not exist, or updated if exist; if the fields!=nil, the record must exist because only update will happen.
 @param fields If set fields=nil, all the object properties are saved; If only want to save some fields, for example StreetHawkUser only wants to save "first_name", "last_name", make an array to contain the field names. The name must exactly same as database column name, or the defined name in the object StreetHawkField. When only some fields are updated the refreshed or saved times are not updated.
 */
-(void)saveObject:(StreetHawkObject *)object fields:(NSArray *)fields;

/**
 Bulk saves homogeneous objects of a particular type. The performance is much higher than save the objects in a loop using `saveObject:fields:`. 
 @param objects The array of objects, for example an array of objects in a set.
 @param objClass The type of the individual object in the array.
 */
-(void)saveObjects:(NSArray *)objects withType:(Class)objClass;

/**
 Save pointers to children into object set table as "owner_id", "child_type", "child_id", "page", meantime update the page table. But this does not save the individual child object.
 */
-(void)saveChildrenInSet:(StreetHawkObjectSet *)objectSet childItems:(NSArray *)childItems serverOffset:(NSInteger)offset;

/** @name Handle Set */

/**
 Add an object into set and save the set children reference pointer table with page table.
 @return YES if the object not exist in objectSet and really added it. 
 */
-(BOOL)addObject:(StreetHawkObject *)object intoSet:(StreetHawkObjectSet *)objectSet;

/**
 Remove an object from set and update set children reference pointer table with page table.
 @return YES if the object exist in objectSet and really remove it. 
 */
-(BOOL)removeObject:(StreetHawkObject *)object fromSet:(StreetHawkObjectSet *)objectSet;

/**
 Mark this object need refresh by modify __refreshed__ and __saved__ to long time ago.
 This is needed when add/remove object from set. Because an object is added/removed, the page number, has more etc need to be synced with server again. Mark this to be need refresh so that next load will call server. 
 */
-(void)markObjectNeedRefresh:(StreetHawkObject *)object;

/**
 Checks if an object exists in a set pointer reference table.
 */
-(BOOL)checkObject:(StreetHawkObject *)object existsInSet:(StreetHawkObjectSet *)objectSet;

@end

