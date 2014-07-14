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

#ifndef StreetHawkCore_StreetHawkConsts_h
#define StreetHawkCore_StreetHawkConsts_h

#define StreetHawkErrorDomain  @"StreetHawkErrorDomain"

#if (__has_feature(objc_arc))       // ARC ENABLED

#ifndef RETAIN
#define RETAIN(X)           (X)
#endif
#ifndef RELEASE
#define RELEASE(X)          X = nil
#define RELEASE_CONTAINER(X)    [(X) removeAllObjects]; X = nil
#endif
#define RELEASE_NO_NIL(X)
#define AUTORELEASE(X)      X
#define AUTORELEASENR(X)
#define BLOCK_COPY(block)   [block copy]
#define BLOCK_RELEASE(block)
#define SUPER_DEALLOC
#define ns_va_arg(args, type)   (__bridge type)va_arg(args, void *)
#define CREATE_AR_POOL(name)    @autoreleasepool {
#define RELEASE_AR_POOL(name)   }
#define __WEAK              __weak
#define DISPATCH_RELEASE(x)     (x)


#else       // ARC DISABLED

#define __bridge
#define __unsafe_unretained
#define __WEAK
#define strong              retain
#define weak                assign
#define ns_va_arg           va_arg

#ifndef RETAIN
#define RETAIN(X)           [(X) retain]
#endif
#ifndef RELEASE
#define RELEASE(X)          [(X) release] ; X = nil
#define RELEASE_CONTAINER(X)  [(X) removeAllObjects]; [(X) release] ; X = nil
#endif

#define RELEASE_NO_NIL(X)          [(X) release]
#define AUTORELEASE(X)      [(X) autorelease]
#define AUTORELEASENR       AUTORELEASE
#define BLOCK_COPY(block)   [block copy]
#define BLOCK_RELEASE(block)    [block release]
#define SUPER_DEALLOC       [super dealloc];
#define CREATE_AR_POOL(name)   NSAutoreleasePool *(name) = [[NSAutoreleasePool alloc] init]
#define RELEASE_AR_POOL(name)   [(name) release]
#define DISPATCH_RELEASE(x)         dispatch_release(x)

#endif

#define DEFAULT_PRIORITY_QUEUE      dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)
#define MAIN_QUEUE                  dispatch_get_main_queue()
#define DISPATCH_MAIN(block)        dispatch_async(MAIN_QUEUE, block )
#define DISPATCH_MAIN_SYNC(block)   dispatch_sync(MAIN_QUEUE, block )

// A way of copying Y to X while handling memory management.
#define CASSIGN(X,Y)   do  {    \
if ((X) != (Y)) {           \
RELEASE(X);             \
X = [(Y) copy];         \
}                           \
} while (0)

#define MCASSIGN(X,Y)   do  {   \
if ((X) != (Y)) {           \
RELEASE(X);             \
X = [(Y) mutableCopy];  \
}                           \
} while (0)

// A way of retaining Y to X while handling memory management.
#define RASSIGN(X,Y)   do  {    \
if ((X) != (Y)) {           \
RELEASE(X);             \
X = RETAIN(Y);          \
}                           \
} while (0)

#define NOT_IMPLEMENTED     NSAssert(NO, @"Not yet implemented");

#define APP_NAME [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleDisplayName"]

#define StreetHawkCoreRES_BUNDLE ([[NSBundle mainBundle] URLForResource:@"StreetHawkCoreRes" withExtension:@"bundle"] != nil ? [NSBundle bundleWithURL:[[NSBundle mainBundle] URLForResource:@"StreetHawkCoreRes" withExtension:@"bundle"]] : nil)
#define StreetHawkCoreRES_NAME @"StreetHawkCoreRes.bundle"
#define StreetHawkRES_BUNDLE ([[NSBundle mainBundle] URLForResource:@"StreetHawkRes" withExtension:@"bundle"] != nil ? [NSBundle bundleWithURL:[[NSBundle mainBundle] URLForResource:@"StreetHawkRes" withExtension:@"bundle"]] : nil)
#define StreetHawkRES_NAME @"StreetHawkRes.bundle"
#define SHAPPRES_BUNDLE ([[NSBundle mainBundle] URLForResource:@"SHAppRes" withExtension:@"bundle"] != nil ? [NSBundle bundleWithURL:[[NSBundle mainBundle] URLForResource:@"SHAppRes" withExtension:@"bundle"]] : nil)
#define SHAPPRES_NAME @"SHAppRes.bundle"
enum Bundles
{
    Bundle_Unknown,  //not sure which bundle
    Bundle_Main,     //App's main bundle
    Bundle_SHApp,    //SHAppRes.bundle
    Bundle_StreetHawk,  //StreetHawkRes.bundle
};
typedef enum Bundles Bundles;

/**
 * General methods apply a block onto a queue.
 */
typedef void (*dispatcher_method_t)(dispatch_queue_t queue, dispatch_block_t block);

/**
 * Standard callback handler with a result or an error.
 */
typedef void (^StreetHawkCallbackHandler)(id result, NSError *error);

/**
 * Standard progress handler with a possible error.
 */
typedef void (^StreetHawkProgressHandler)(id source, double percentDone, NSString *message, BOOL completed, NSError *error);

#define USER_DEFAULTS   getUserDefaults(NULL)

#define DOWNLOADER_CONCURRENCY_LEVEL    2

#define RADIANS (3.14159265358979323846 / 180.0)
#define EARTH_RADIUS_IN_MILES 3960.056052
#define EARTH_RADIUS_IN_KM 6372.796924
#define EARTH_RADIUS_IN_METERS 6372796.924
#define NauticalMilesPerLatitude 60.00721
#define NauticalMilesPerLongitude 60.10793
#define MetersPerNauticalMile 1852
#define MetersPerLongitude MetersPerNauticalMile * NauticalMilesPerLongitude
#define MetersPerLatitude NauticalMilesPerLatitude * MetersPerNauticalMile
#define MilesPerNauticalMile 1.15078

// A few time units
#define GMT_OFFSET              [[NSTimeZone localTimeZone] secondsFromGMT]

#define MINUTES_IN_AN_HOUR  60
#define SECONDS_IN_AN_HOUR  3600
#define MINUTES_IN_A_DAY    1440
#define SECONDS_IN_A_DAY    24 * 3600
#define MINUTES_IN_A_WEEK   MINUTES_IN_A_DAY * 7
#define SECONDS_IN_A_WEEK   SECONDS_IN_A_DAY * 7
#define MINUTES_IN_A_MONTH  MINUTES_IN_A_DAY * 30
#define SECONDS_IN_A_MONTH  SECONDS_IN_A_DAY * 30

#define INVALID_LATITUDE    -1000
#define INVALID_LONGITUDE   -1000

// region of our default precinct search - at sydney atm
#define DEFAULT_PRECINCT_RADIUS     50000

/**************************************************
 *
 *      COLOURS AND STYLES FOR SKINNING
 *
 ***************************************************/
#define UICOLORRGBA(r,g,b,a)                [UIColor colorWithRed:((float)r)/255.0 green:((float)g)/255.0 blue:((float)b)/255.0 alpha:((float)a)/255.0]
#define UICOLORRGB(r,g,b)                   UICOLORRGBA(r,g,b,255)

#ifndef __FUNCTION_NAME__
    #ifdef __PRETTY_FUNCTION__
        #define __FUNCTION_NAME__ __PRETTY_FUNCTION__
    #elifdef __FUNCTION__
        #define __FUNCTION_NAME__ __FUNCTION__
    #elifdef __func__
        #define __FUNCTION_NAME__ __func__
    #else
        #define __FUNCTION_NAME__ __func__
    #endif
#endif

#define DEVICE_iPHONE ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPhone)

#endif

