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
 Json return type: {code: 0, value: ...}, 0 for successful.
 */
#define CODE_OK                 0

//Change this in build time to turn on/off request log, helpful for debug.
#define LOG_REQUESTS    NO

/**
 All http requests to StreetHawk are made by this object.
 */
typedef void (^StreetHawkRequestHandler)(StreetHawkRequest *request);

/**
 A way to report request progress handler. 
 */
typedef void (^StreetHawkRequestProgressHandler)(StreetHawkRequest *request, NSData *data, long totalReceived, long totalBytes);

/**
 All http requests used to communicate with server uses this class. It's a wrapper of NSURLConnection and easier to use by block callback.
 */
@interface StreetHawkRequest : NSOperation <NSCopying>

/** @name Create */

/**
 Initialises a request with no data converter and no handlers. This request auto released when connection closed. 
 */
+(StreetHawkRequest *)withRequest:(NSURLRequest *)request;

/**
 Initiates a request with a data converter and a request handler. This request auto released when connection closed. 
 */
+(StreetHawkRequest *)withRequest:(NSURLRequest *)request requestHandler:(StreetHawkRequestHandler)requestHandler;

/**
 Initiates a request with a data converter, a request handler and a progress handler. This request auto released when connection closed. 
 */
+(StreetHawkRequest *)withRequest:(NSURLRequest *)request requestHandler:(StreetHawkRequestHandler)requestHandler progressHandler:(StreetHawkRequestProgressHandler)progressHandler;

/**
 The request handler for caller to deal with returned value.
 */
@property (nonatomic, copy) StreetHawkRequestHandler requestHandler;

/**
 The progress handler for caller to deal with progress. It needs server to support return total bytes. 
 */
@property (nonatomic, copy) StreetHawkRequestProgressHandler progressHandler;

/**
 Work in an incremental mode where the data is sent off to the `progressHandler` as it arrives so we are not storing it.
 This is useful when the response data can be really large (eg downloading media) and it is better to handle the data and discard it rather than keep track of it all in memory and overwhelm the amount of device memory.
 This will only take effect if a progressHandler is supplied and this property is true.
 */
@property (nonatomic) BOOL discardPreviousData;

/** @name Start/Cancel functions */

/**
 The Default queue for request to be handled. If `startAsynchronouslyInQueue:` set `queue`=nil, or call `startAsynchronously`, this queue is used. It's concurrent with max number 3.
 */
+(NSOperationQueue *)defaultOperationQueue;

/**
 Add request into default operation queue. It will stay in the queue and start when ready to execute it, or caller to cancel it. Once it's finished or cancelled it's auto released. The result is callback by `requestHandler`.
 */
-(void)startAsynchronously;

/**
 Add the request into the given queue. See `startAsynchronously`.
 @param queue The queue where this operation is added. If set nil it will use the `defaultOperationQueue`.
 */
-(void)startAsynchronouslyInQueue:(NSOperationQueue *)queue;

/**
 Starts the request synchronously. When the request finish, it's dealloc. To start a request asynchronously, use the startAsynchronously method.
 @return The returned NSData value from the request. 
 */
-(NSData *)startSynchronously;

/**
 Cancel the connection and dealloc it. Only asynchronous request can be cancelled. `requestHandler` is invoked with error=`requestCancelledError`. 
 Note: Once a request is cancelled or finished, it cannot be added into queue again, otherwise exception occur.
 */
-(void)cancel;

/** @name Result */

/**
 The response of this request. 
 */
@property (nonatomic, readonly) NSURLResponse *response;

/**
 The HTTP stauts code of response, for example 200 means OK, 404 means page not found.
 */
@property (nonatomic, readonly) NSInteger responseStatusCode;

/**
 The data of received response data. It's appended when connection didReceiveData. It only works for discardPreviousData==NO mode, because if really download large data, the data is not stored in memory and cannot be serialize to string.
 */
@property (nonatomic, readonly) NSMutableData *responseData;

/**
 The NSUTF8StringEncoding string of received response data (`responseData`). It only works for discardPreviousData==NO mode, because if really download large data, the data is not stored in memory and cannot be serialize to string.
 */
@property (nonatomic, readonly) NSString *responseString;

/**
 The error of handling this request. 
 */
@property (nonatomic, readonly) NSError *error;

/**
 Static function to get cancel request error.
 */
+(NSError *)requestCancelledError;

/**
 The JSON returned from server is formatted as {"code"=0, "value"=...}. `resultCode` is the part of "code". It can only be got after successfully parse the JSON.
 */
@property (nonatomic, readonly) int resultCode;

/**
 The JSON returned from server is formatted as {"code"=0, "value"=...}. `resultValue` is the part of "value". It can only be got after successfully parse the JSON.
 */
@property (nonatomic, readonly) NSObject *resultValue;

/** @name Child Class Override */

/**
 Override to create the resultCode, resultValue and error objects. It happens in `connectionDidFinishLoading:`, at this moment the responseData is fully downloaded. Use self.jsonToObjectConverter(self.responseData, &err) can get NSDictionary of {"code"=0, "value"=...}.
 */
-(void)parseResponseForConnection:(NSURLConnection *)theConnection withContentType:(NSString *)contentType;

/**
 Override to process/handle the result_code, result_value and error objects.
 @return YES if invokeHandlerAndRelease should be called, or NO if the child class will invoke it manually when ready (ie in the case of redirects or newly spawned requests).
 */
-(BOOL)processResponseForConnection:(NSURLConnection *)theConnection;

@end

