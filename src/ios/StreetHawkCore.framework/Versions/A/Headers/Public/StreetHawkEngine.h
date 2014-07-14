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

#import "StreetHawkPublicFwds.h"

/**
 The engine to do most of works, such as send/receive request, location, log etc.
 */
@interface StreetHawkEngine : NSObject

/** @name Install */

/**
 Before successfully install, it's nil. After install once, it's the install instance. 
 */
@property (nonatomic, strong) StreetHawkInstall *currentInstall;

/**
 A flag to indicate whether a new install is being processing. When newly install an Application, it may call [StreetHawkEngine registerOrUpdateInstallWithParams:withHandler:] many times, for example when send logs to server. Having this flag to avoid register mulitiple installs.
 */
@property (nonatomic) BOOL registering_install;

/**
 Return a singleton StreetHawkLogger associated with one engine.
 */
@property (nonatomic, strong) StreetHawkLogger *logger;

/** @name Location */

/**
 Return a singleton StreetHawkLocationManager associated with one engine.
 */
@property (nonatomic, readonly) StreetHawkLocationManager *locationManager;

/** @name Parse */

/**
 Return a singleton StreetHawkObjectLoader associated with one engine.
 */
@property (nonatomic, readonly) StreetHawkObjectLoader *objectLoader;

/**
 Factory to create objects by class type and Id. Use StreetHawkDefaultObjectFactory or customize new one.
 Code sample:
    `theEngine.objectFactory = [StreetHawkDefaultObjectFactory defaultFactory];`
 */
@property (nonatomic, strong) id<StreetHawkObjectFactory> objectFactory;

/** @name Request search from Server */

/**
 Set header fields of request. By default it's aleady set "IOSAppVersion", "IOSDeviceModel", "IOSSysName", "IOSSysVersion", "User-Agent"=app_key(sh_version). No need to change it if no special needs.
 */
@property (nonatomic, strong) NSMutableDictionary *customHeaders;

/**
 Helper method to create a request object.
 @param path The internal path after root url, for example: "products/product_id/description/".
 @param params A key/value pair, which will format to paramters in URL, for example (@"family", @"tops") will become "?family=tops".
 @param method GET or POST. If pass nil it's GET by default.
 @param headers The header fields sent in request. Pass nil if no header need to set.
 @param body_or_stream Set to post body. It's usually array, dictionary or data.
 @return A request sent to server. 
 */
-(StreetHawkRequest *)requestWithPath:(NSString *)path withParams:(NSArray *)params withMethod:(NSString *)method withHeaders:(NSDictionary *)headers withBodyOrStream:(id)body_or_stream;

/**
 Helper method to create a simple request object.
 @param path The internal path after root url, for example: "products/product_id/description/".
 @param params A key/value pair, which will format to paramters in URL, for example (@"family", @"tops") will become "?family=tops".
 @param method GET or POST. If pass nil it's GET by default. 
 @return A request sent to server.
 */
-(StreetHawkRequest *)requestWithPath:(NSString *)path withParams:(NSArray *)params withMethod:(NSString *)method;

/**
 Helper method to create a simple request object for GET methods.
 @param path The internal path after root url, for example: "products/product_id/description/".
 @param params A key/value pair, which will format to paramters in URL, for example (@"family", @"tops") will become "?family=tops".
 @return A request sent to server.
 */
-(StreetHawkRequest *)requestWithPath:(NSString *)path withParams:(NSArray *)params;

/**
 Helper method to create a simple GET request object.
 @param path The internal path after root url, for example: "products/product_id/description/".
 @return A request sent to server.
 */
-(StreetHawkRequest *)requestWithPath:(NSString *)path;

@end

