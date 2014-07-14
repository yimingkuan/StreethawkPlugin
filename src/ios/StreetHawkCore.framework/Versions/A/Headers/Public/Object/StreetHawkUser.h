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
 The int value for each follow type. Note: the int value cannot be changed as it matches to server.
 */
typedef enum
{
    FollowTypeUnknown = -1,
    FollowTypeLike = 0,
    FollowTypeShare = 1,
} FollowType;

/**
 The int value for each follow object. Note: the int value cannot be changed as it matches to server.
 */
typedef enum
{
    FollowedObjectUser = 0,
    //FollowedObjectDeal = 1,  //comment some object as they are not supported now, but cannot affect the int value it matches to.
    //FollowedObjectPlace = 2,
    FollowedObjectRetailer = 3,
    //FollowedObjectShop = 4,
    FollowedObjectProduct = 5,
    //FollowedObjectItem = 6,
    //FollowedObjectOffer = 7,
} FollowedObjectType;

#define FollowTypeCount 2
#define FollowedObjectCount 8
extern const NSString *FollowedTypeNames[FollowTypeCount];
extern const NSString *FollowedObjectNames[FollowedObjectCount];

/**
 Registerred user in StreetHawk. The user account works across retailers.
 */
@interface StreetHawkUser : StreetHawkObject<StreetHawkObject>

/**
 When this user registered successfully.
 */
@property (nonatomic, strong) NSDate *created;

/**
 The email address user registered with. Tagged as "sh_email".
 */
@property (nonatomic, strong) NSString *email;

/**
 Gender of the user (“male”, “female”). Tagged as "sh_gender".
 */
@property (nonatomic, strong) NSString *gender;

/**
 First name of user. Tagged as "sh_first_name".
 */
@property (nonatomic, strong) NSString *first_name;

/**
 Last name of user. Tagged as "sh_last_name".
 */
@property (nonatomic, strong) NSString *last_name;

/**
 Full path to users profile image. This is set using the /users/<userid>/images API calls. Conversion to a thumbnail is a background process, so may take some time to come available in search queries.
 */
@property (nonatomic, strong) NSString *thumbnail_url;

/**
 The year of birth day (for example “1977-04-23”). Tagged as "sh_date_of_birth".
 */
@property (nonatomic, strong) NSString *year_of_birth;

/**
 * Gets all objects of a given type liked by a user.
 */
-(id<StreetHawkObjectSet>)likesByType:(FollowedObjectType)type;

/**
 * Gets all objects of a given type shared by a user.
 */
-(id<StreetHawkObjectSet>)sharesByType:(FollowedObjectType)type;

/**
 * Sends a message to multiple users - either inside or outside the system.
 */
-(StreetHawkRequest *)sendMessageTo:(NSArray *)receivers withType:(NSString *)msg_type withParams:(NSDictionary *)params withHandler:(StreetHawkCallbackHandler)handler;

@end

@interface StreetHawkObject(StreetHawkFollowings)

#pragma mark - Following objects

/**
 * The api url for following or unfollowing this object.
 */
-(NSString *)serverFollowURL:(BOOL)follow;

/**
 * Follows or unfollows this object.
 */
-(void)followOrUnFollow:(BOOL)follow withFollowType:(int)type withHandler:(StreetHawkCallbackHandler)follow_handler;

/**
 * Likes or unlikes this object.
 */
-(void)likeOrUnlike:(BOOL)like withHandler:(StreetHawkCallbackHandler)like_handler;

/**
 * Share tracking API for a deal. Note that this does not do the "share" itself.
 * That is done in the calling code (for FaceBook or others)
 */
-(void)shareOrUnshare:(BOOL)share withHandler:(StreetHawkCallbackHandler)like_handler;

@end
