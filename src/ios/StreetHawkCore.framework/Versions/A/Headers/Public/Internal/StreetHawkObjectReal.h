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

#import <Foundation/Foundation.h>

/**
 handler block typedefs.
 */
typedef void (^ImageUploadCallback)(NSString *image_name, NSString *uploaded_url, NSData *imageData, NSError *error);
typedef void (^BatchLoadHandler)(NSString *idlist, NSDictionary *values, NSError *error);

/**
 Delegates responsible for handling object load, save and deletion events.
 */
@protocol StreetHawkObjectDelegate <NSObject>

@optional

-(void)objectLoaded:(StreetHawkObject *)object withError:(NSError *)error;
-(void)objectSaved:(StreetHawkObject *)object withError:(NSError *)error;
-(void)objectDeleted:(StreetHawkObject *)object withError:(NSError *)error;

@end

/**
 Default factory method to create an instance of the object unique to the the given ID.  Either use this in the .m file or manually implement it in the .m file.
 */
#define DEFAULT_ITABLE_METHOD                                       \
+(StreetHawkInstanceTable *)instanceTable                          \
{                                                               \
static StreetHawkInstanceTable *instance_table = nil;          \
static dispatch_once_t onceToken;                           \
dispatch_once(&onceToken, ^{                                \
instance_table = [[StreetHawkInstanceTable alloc] init];   \
});                                                         \
return instance_table;                                      \
}                                                               \


#define INITIALISER_DECLARATATIONS(classname)

/**
 Protocol for objects that have a lat/lng.
 */
@protocol StreetHawkGeoObject<NSObject>

/**
 Coordinates of the mappable.
 */
@property (nonatomic) double latitude;

/**
 Coordinates of the mappable.
 */
@property (nonatomic) double longitude;

@end

/**
 Protocol for objects that are cacheable, can be persisted and expired.
 */
@protocol StreetHawkCacheable<NSObject>

@required

/**
 Tells if the object is being refreshed from the server.
 */
@property (nonatomic) BOOL isRefreshing;

/**
 Tells when the object was last refreshed from the StreetHawk Server.
 */
@property (nonatomic, copy) NSDate *lastRefreshed;

/**
 Tells whether the object needs a refresh or not based on cache interval and other class specific parameters.
 */
@property (nonatomic) BOOL needsRefresh;

/**
 The interval after which the item will need a refresh.
 */
@property (nonatomic) NSTimeInterval refreshInterval;

@end

/**
 Protocol for objects that are proxies for an object on the server.
 */
@protocol StreetHawkServerObject <NSObject>

@required

/**
 The server side ID of this object. Used for batch load, for example, ID1,ID2,ID3...
 By default it's objectId, assigned in init. Child class can reset it.
 */
@property (nonatomic, copy) NSString *serverID;

/** @name Load from Server */

/**
 The URL that is used to load this object from the server.
 */
-(NSString *)serverLoadURL;

/**
 Loads the object details from a dictionary.
 */
-(void)loadFromDictionary:(NSDictionary *)dictionary;

/**
 Refresh the object by reloading from the StreetHawk server.
 */
-(StreetHawkRequest *)loadFromServer:(StreetHawkCallbackHandler)load_handler;

/**
 The URL for batch loading objects of this type.
 */
-(NSString *)batchLoadURL;

/**
 Returns YES if a particular child can be batch loaded.
 */
-(BOOL)canBatchLoadChild:(id<StreetHawkObjectSet>)child;

/**
 Batch loads objects from the server.
 */
-(StreetHawkRequest *)batchLoadFromServer:(NSString *)idlist forChild:(id<StreetHawkObjectSet>)child withHandler:(BatchLoadHandler)load_handler;

/**
 Loads a child container from the server.
 */
-(StreetHawkRequest *)loadChildrenFromServer:(id<StreetHawkObjectSet>)child atOffset:(NSInteger)offset length:(NSInteger)length withHandler:(StreetHawkCallbackHandler)load_handler;

/**
 Gets the URL at the server to which a post would save this object.
 */
-(NSString *)serverSaveURL;

/**
 Gets the parameter list used to "save" this object.
 */
-(NSArray *)serverSaveParams;

/**
 Gets the parameter list used to "save" this object.
 */
-(NSObject *)serverSaveBody;

/**
 Tells when the object was last saved to the StreetHawk server
 */
@property (nonatomic, copy) NSDate *lastSaved;

/**
 Trigers a save to the server.
 */
-(StreetHawkRequest *)saveToServer:(StreetHawkCallbackHandler)save_handler;

/**
 Save the object (by writing to the StreetHawk server) only the specific fields.
 */
-(StreetHawkRequest *)saveToServerWithFields:(NSArray *)params withHandler:(StreetHawkCallbackHandler)save_handler;
-(StreetHawkRequest *)saveToServerWithBody:(NSObject *)body_or_stream withHandler:(StreetHawkCallbackHandler)save_handler;
-(StreetHawkRequest *)saveToServerWithFields:(NSArray *)params withBody:(NSObject *)body_or_stream withHandler:(StreetHawkCallbackHandler)save_handler;

/**
 Gets the URL at the server to which a post would delete this object.
 */
-(NSString *)serverDeleteURL;

/**
 Delete the object (on the server side).
 */
-(StreetHawkRequest *)deleteFromServer:(StreetHawkCallbackHandler)delete_handler;

@end

/**
 Super protocol of all objects that have data whose source of truth is at the server. Essentially any call to the server should be encapsulated in a StreetHawkObject.
 */
@protocol StreetHawkObject<StreetHawkModel, StreetHawkCacheable, StreetHawkServerObject>

@required

/**
 Engine of the object.
 */
@property (nonatomic, weak) StreetHawkEngine *engine;

/**
 Unique Id.
 */
@property (nonatomic, strong) NSString *suid;

/**
 Title for the object. It's the display name, for example, tag name, brand name.
 */
@property (nonatomic, strong) NSString *title;

@property (nonatomic) BOOL loaded;
@property (nonatomic) BOOL isLoading;

@end

/**
 Every instance of a StreetHawkObject must also have a StreetHawkObjectReal, eg StreetHawkItem/StreetHawkItemReal, StreetHawkProduct/StreetHawkProductReal etc. Think of the StreetHawkXYZ as the wrapper and StreetHawkXYZReal as the implementation. Why are these needed?  Because different parts of the application can refer to a particular Product with id 123 (via [StreetHawkProduct withID:123]). These will be different instances of the StreetHawkProduct however they both need to refer to the same underlying data object - which is the StreetHawkProductReal object. This will ensure that when changes are made to the product from one part of the application, it is instantly visible to the other parts dealing with the StreetHawkProduct instance.
 */
@interface StreetHawkObjectReal : NSObject<StreetHawkObject>

/**
 The name of the attribute that can return the ID of an object from a dictionary returned by the server.
 Defaults to "id" but can be overidden by child classes.
 */
+(NSString *)defaultIDAttribute;

/**
 Creates instances of the StreetHawkObjectReal.
 */
-(id)initWithID:(NSString *)objid withEngine:(StreetHawkEngine *)engine;

/**
 Creates instances of the StreetHawkObjectReal.
 */
-(id)initWithID:(NSString *)objid withEngine:(StreetHawkEngine *)engine withParent:(StreetHawkObjectReal *)parent;

@end
