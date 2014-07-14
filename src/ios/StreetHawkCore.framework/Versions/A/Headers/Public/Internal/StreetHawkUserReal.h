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
#import "StreetHawkObjectReal.h"  //for inherit from StreetHawkObjectReal

/**
 Registerred user in StreetHawk. The user account works across retailers.
 */
@interface StreetHawkUserReal : StreetHawkObjectReal

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
 Refer to StreetHawkClassTypeMap.
 */
+(StreetHawkClassTypeMap *)followClassMap;

@end
