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

#ifndef __STREETHAWK_DOWNLOADER_H__
#define __STREETHAWK_DOWNLOADER_H__

enum
{
    /**
     Downloaded files are cached in /Library/Caches/StreetHawk/MediaCache/FileCache. If download with this option the cached file is not used. It downloads new from server.
     */
    DISABLE_CACHE               = 1,
    /**
     Downloaded files are cached in /Library/Caches/StreetHawk/MediaCache/FileCache. If download with this option the cached file is used if found; only download from server when there is no local cache.
     */
    ENABLE_CACHED               = 2,
    /**
     Use this option so that the handler is not called after download finish.
     */
    DISABLE_HANDLER_QUEUEING    = 4,
};
typedef int DownloaderOptions;

/**
 Handlers on download completion or failures.
 */
typedef void (^DownloadHandler)(NSString *url, NSData *contents, NSError *error);

/**
 A class to download contents of URLs into a cache. Only one download of multiple instances of the same URL happens at a time.
 */
@interface StreetHawkDownloader : NSObject

/** @name Create */

/**
 Returns the global default downloader. Normally use this is enough.
 */
+(StreetHawkDownloader *)sharedDownloader;

/**
 Initialize a downloaer with a cache.
 */
-(id)initWithCache:(id<StreetHawkCache>)theCache;

/**
 The cache in which the downloader keeps all its files.
 */
@property (nonatomic, strong) id<StreetHawkCache> cache;

/** @name Download tasks */

/**
 Downloads a url.
 Following modes of downloads are possible:
 1. If disableCache is selected or if the url is not in the cache or if the URl is not downloaded, then download from the URL asynchronously and the handler is called later.
 2. Otherwise, if the url is already downloaded into cache, return the data immediately.
 @param url The complete downloadable url. Normally it's for an image. It cannot be nil.
 @param downloaderQueue The queue for downloading. Set it to nil will use the default global `downloaderQueue`.
 @param options Some options if need. If not need any option, set this to be 0, or use simpler API `downloadURL:inQueue:withHandler:`.
 @param download_handler The callback when download finish.
 @return YES means the file not downloaded from server again; NO means the file really downloaded. 
 */
-(BOOL)downloadURL:(NSString *)url inQueue:(NSOperationQueue *)downloaderQueue withOptions:(DownloaderOptions)options withHandler:(DownloadHandler)download_handler;

/**
 Call `downloadURL:inQueue:withOptions:withHandler:` with ENABLE_CACHED=YES.
 */
-(BOOL)downloadURL:(NSString *)url inQueue:(NSOperationQueue *)downloaderQueue withHandler:(DownloadHandler)download_handler;

/**
 Cancels all download requests.
 */
-(void)cancellAllDownloads;

/**
 Cancel the download of a particular url and notifies handlers.
 */
-(void)cancelDownload:(NSString *)url;

@end

#endif
