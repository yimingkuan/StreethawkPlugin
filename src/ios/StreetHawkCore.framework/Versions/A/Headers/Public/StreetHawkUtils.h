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

#ifndef __STREETHAWK__CORE__UTILS__H__
#define __STREETHAWK__CORE__UTILS__H__

#import "StreetHawkPublicFwds.h"

#define ROUND_LAT_TO    3
#define ROUND_LNG_TO    3
#define LAT_TOLERANCE   0.0025
#define LNG_TOLERANCE   0.0025

#define NUMWITHFLOAT(_x_)               [NSNumber numberWithFloat:(_x_)]
#define NUMWITHINT(_x_)                 [NSNumber numberWithInt:(_x_)]
#define NUMWITHDOUBLE(_x_)              [NSNumber numberWithDouble:(_x_)]
#define DICTWITHOBJECT(_key_, _value_)  [NSDictionary dictionaryWithObject:(_value_) forKey:(_key_)]

#define NONULL(str)     ((str && str != (id)[NSNull null]) ? (str) : @"")
#define NOEMPTY(str)    ((str && str.length > 0) ? (str) : nil)

#define CREATE_VA_LIST(args, param1)    va_list args ; va_start(args, param1)
#define DEFAULT_DATETIME_FORMAT @"yyyy-MM-dd HH:mm:ss"

//iOS version
#define OS_ISVERSION_SINCE(X) (BOOL)([[[UIDevice currentDevice] systemVersion] substringToIndex:1].integerValue >= X)

/**
 * Gets the user default that is to be used by the applications.
 * If a value is given then it is set as the user defaults for
 * subsequent invocations.
 */
extern NSUserDefaults *getUserDefaults(NSUserDefaults *newvalue);

extern NSMutableString *makeBaseUrlString(NSString *baseURL, NSString *path);
extern NSMutableString *makeUrlString(NSString *baseURL,
                                      NSString *path,
                                      NSArray *params);
extern NSMutableString *appendUrlParam(NSMutableString *url_string,
                                       NSString *param,
                                       NSObject *value);

/**
 * Converts a byte array into an hex string.
 */
extern NSMutableString *dataToHexString(NSData *data);

/**
 Appends a whole bunch of parameter and values to a string in the form: param1=value1&param2=value2&param3=value3....
 @param params Array listed as [param1, value1, param2, value2, param3, value3, ...], it must be paired.
 @param isForPost If YES only "&" is used; otherwise first append should be "?".
 */
extern NSMutableString *appendParamsArrayToString(NSMutableString *str, NSArray *params, BOOL isForPost);

/**
 Appends a whole bunch of parameter and values to a string in the form: param1=value1&param2=value2&param3=value3....
 @param params Dictionary listed as {param1 = value1, param2 = value2, param3 = value3, ...}, it must be paired.
 @param isForPost If YES only "&" is used; otherwise first append should be "?".
 */
extern NSMutableString *appendParamsDictToString(NSMutableString *str, NSDictionary *params, BOOL isForPost);

/**
 * Adds a parameter to an array.
 */
extern void addParamToArray(NSMutableArray *array, NSString *param, NSObject *value);

extern NSString *makeTagFilter(NSArray *firstArray, ...);

/**
 * Converts a float to a string and optionally rounding to the given decimal places.
 */
extern NSString *floatToStr(double value, int numPlaces, double accuracy);

/**
 * Converts a hex char to int.
 */
extern int hexchar2int(int ch);

/**
 * URL encodes a string leaving slashes and ampersands out.
 */
extern NSString *urlEncodeSimple(NSString *input);

/**
 * URL encodes a string including slashes and ampersands.
 */
extern NSString *urlEncodeFull(NSString *input);

/**
 Create a new instance of NSDateFormatter for the supported date format, timezone and locale. Caller of this function must be responsible for release it.
 @param dateFormat The format string of date, by default (nil) it's yyyy-MM-dd HH:mm:ss, this is also the recognizable date format of server.
 @param timeZone The time zone of format, by default (nil) it's UTC.
 @param locale The locale of format, by default (nil) it's en-US.
 @return A new instance of date formatter.
 */
extern NSDateFormatter *createDateFormatter(NSString *dateFormat, NSTimeZone *timeZone, NSLocale *locale);

/**
 Parses date string into NSDate format. It tries to support as much format as possible. Refer to `input` parameters for the supported date time format. 
 @param input Date time string. It supports this kinds of strings:
 
 * yyyy-MM-dd HH:mm:ss, for example 2012-12-20 18:20:50
 * yyyy-MM-dd, for example 2012-12-20
 * dd/MM/yyyy HH:mm:ss, for example 20/12/2012 18:20:50
 * dd/MM/yyyy, for example 20/12/2012
 * MM/dd/yyyy HH:mm:ss, for example 12/20/2012 18:20:50
 * MM/dd/yyyy, for example 12/20/2012
 
 @param offsetSeconds The offsetSeconds parameter tells how many seconds the parsed date is to be offset by.
 */
extern NSDate *parseDate(NSString *input, int offsetSeconds);

/**
 Formats a date into a string in StreetHawk-wide format. Must use this format to be recognizable by server. Format is yyyy-MM-dd HH:mm:ss in UTC timezone.
 @param date The date value to be formatted. 
 @return The return string.
 */
extern NSString *formatStreetHawkDate(NSDate *date);

/**
 * Returns an error object
 */
extern NSError *makeError(NSString *domain, NSInteger code, NSObject *result_value, NSDictionary *userInfo);
extern NSError *makeStreetHawkError(NSInteger code, NSObject *result_value, NSDictionary *userInfo);

/**
 Tells if the error is one that describes a no-connection to the internet and/or host.
 */
extern BOOL isNetworkError(NSError *error);

/**
 * Calculates the square of distance between two lat/longs.
 * Geared for speed over accuracy.
 */
extern double distanceSquared(double lat1, double lng1, double lat2, double lng2);

/**
 * Splits a string with a delimiter and returns only non empty strings.  An
 * empty array is returned if no non-empty strings exist (instead of an
 * array with a single empty string).
 */
extern NSArray* splitStrings(NSString *input, NSString *delimiter);

/**
 * Run the block in the main thread by dispatching to the main queue
 * if current thread is not the main thread.
 * DO NOT use this as a recursive lock.
 */
extern void ensure_main_thread(dispatch_block_t block);
extern void dispatch_to_main(dispatch_block_t block);
extern void ensure_queue(dispatch_queue_t queue, BOOL asynch, BOOL barrier, dispatch_block_t block);

/**
 * Creates a queue with random value surrounded by a prefix and suffix.
 */
extern dispatch_queue_t create_dispatch_queue_with_random_value(const char *prefix, const char *suffix);

/**
 * Given a container which has the objectEnumerator method,
 * joins all the elements with a given seprator and a string
 * maker function.
 */
extern NSString *joinComponentsByString(id<NSObject>container,
                                        NSString *separator,
                                        NSString *(^stringMaker)(id));

/**
 * These method simulate the barrier async functionalities found in Lion.
 */

/**
 * Convert an ASCII encoded c-string to NSString.
 */
extern NSString *cstringToNSString(const char *input);

/**
 * Returns if input string is a valid email address either in a strict or a lax way.
 * See http://blog.logichigh.com/2010/09/02/validating-an-e-mail-address/
 */
extern BOOL isEmailAddressValid(NSString *input, BOOL strict);

/**
 * Wraps a given block within a dispatch wait and dispatch signal block
 * with an optional time out value.
 * This is equivalent to:
 *
 *     dispatch_semaphore_wait(semaphore, timeout);
 *     block();
 *     dispatch_semaphore_signal(semaphore);
 */
extern void dispatch_semaphore_wrap(dispatch_semaphore_t semaphore,
                                    dispatch_time_t timeout,
                                    dispatch_block_t block);


/**
 * Block_copy-ies or retains the handler depending on whether
 * it is a block or a NSObject child.
 */
extern id retainHandlerOrDelegate(id handler_or_delegate);

/**
 * Releases or Block_releases the handler depending on whether
 * it is a block or a NSObject child.
 */
extern void releaseHandlerOrDelegate(id handler_or_delegate);

/**
 * Invokes the ObjectLoadHandler or a StreetHawkObjectDelegate method or a custom selector
 * on the given handler with the object and the error as parameters.
 * Optionally the handler is also released upon invocation.
 */
extern void invokeHandlerOrDelegate(id object, NSError *error, id handler_or_delegate, SEL sel, BOOL release_handler);

/**
 * Loads a StreetHawkObject from a given ID field in a dictionary.
 */
extern StreetHawkObject *loadObjectFromDictionary(StreetHawkEngine *engine,
                                               NSDictionary *dict,
                                               Class objClass,
                                               NSString *id_field);


/**
 * Find the bundle contains the resource with type
 */
extern NSBundle *findBundleForResource(NSString *resourceName, NSString *type, BOOL mandatory);

/**
 * Search for localized string for a `key`, first search in App's bundle, then search StreetHawkCoreRes.bundle. If nothing match return `defaultStr`.
 */
extern NSString *localizedString(NSString *key, NSString *defaultStr);

/**
 * Image url needs to have size=XXX appended. This function make sure it has the right size.
 */
extern NSString *ensureImageUrlSize(NSString *imageUrl, NSUInteger size);

/**
 * Calculate display string for the target date, for example XXX day XXX hour.
 */
extern NSString *displayRemainingTime(NSDate *targetDate);

/**
 Call phone number. If success return YES else return NO.
 */
extern BOOL callPhoneNumber(NSString *phone);

/**
 Get mac address of current device, the output is for example: 00:23:32:CB:AB:80
 */
extern NSString *getMacAddress();

/**
 Get carrier's name from current device, for example "AT&T", "China Mobile" etc. If current device does not connect to carrier, for example iPad Wifi, return "Other".
 */
extern NSString *getCarrierName();

/**
 Get device's screen resolution, for example "640*480".
 */
extern NSString *getScreenResolution();

/**
 Parse the string or json object to a dictionary. It handles as much situation as possible, for example, the obj is a right dictionary, or the obj is a string, or the string obj contains wrong "\"" etc.
 */
extern NSDictionary *parseObjectToDict(NSObject *obj);

/**
 A common way to present error by showing an alert view with error details.
 @param error The error to present. If error is nil nothing happen.
 @param announceNetworkError If the error is network problem, this decides whether to show the alert view or not.
 */
extern void presentStreetHawkError(NSError *error, BOOL announceNetworkError);

/**
 Get corresponding view controller for a view.
 */
extern UIViewController *getViewController(UIView *view);

/**
 Dismiss all message views, including UIAlertView, UIActionSheet, UIModalView.
 */
extern void dismissAllMessageView();

/**
 Enum for where this App running.
 */
enum SHAppLocation
{
    /**
     The App is downloaded from AppStore. This kind of App does not have embedded profile.
     */
    SHAppLocation_AppStore,
    /**
     The App is running on simulator.
     */
    SHAppLocation_Simulator,
    /**
     None of above cases. It may be debugging running, or running from distribute platform such as TestFlight.
     */
    SHAppLocation_Other,
};
typedef enum SHAppLocation SHAppLocation;

/**
 Return where the running App is from. It possible return: AppStore, Simulator, Other.
 */
extern SHAppLocation appLocation();

@interface NSArray (StreetHawkExt)
- (NSString *)componentsJoinedByString:(NSString *)separator
                       withStringMaker:(NSString * (^)(id object))stringMaker;
/**
 * Return a new array by apply a "transformer" method to each entry of an array.
 */
- (NSArray *)mapTransformer:(id (^)(id input, BOOL *skip, BOOL *stop))transformer;
-(void)mapInto:(NSMutableArray *)output withTransformer:(id (^)(id input, BOOL *skip, BOOL *stop))transformer;
/**
 * Return the array to an item by applying the given reductor
 * to the items from the left.
 */
-(id)foldLeftWithReductor:(id (^)(id a, id b))reductor;
-(id)foldRightWithReductor:(id (^)(id a, id b))reductor;
-(id)foldInReverse:(BOOL)reverse withReductor:(id (^)(id a, id b))reductor;
@end

@interface NSDictionary (StreetHawkExt)
/**
 * Returns the dictionary contents as an array containing
 * key1,value1,key2,value2....keyn,valuen
 */
-(NSArray *)interleavedKeysAndValues;
-(NSString *)componentsJoinedBy:(NSString *)keySeperator
                    andValuesBy:(NSString *)valueSeperator;
@end

@interface NSSet (StreetHawkExt)
- (NSString *)componentsJoinedByString:(NSString *)separator;
- (NSString *)componentsJoinedByString:(NSString *)separator
                       withStringMaker:(NSString * (^)(id object))stringMaker;
@end

//_______________________________________________________________________
// This category provides convenience methods to make it easier to use an
// NSIndexPath to represent a column as well as a section and a row.
@interface NSIndexPath (StreetHawkColumedIndexPath)

+ (NSIndexPath *)indexPathForRow:(NSInteger)row
                      withColumn:(NSInteger)column
                       inSection:(NSInteger)section;
@property(nonatomic,readonly) NSInteger column;

@end

#endif
