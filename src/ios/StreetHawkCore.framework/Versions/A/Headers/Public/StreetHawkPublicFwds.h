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

#ifndef StreetHawkCore_StreetHawkPublicFwds_h
#define StreetHawkCore_StreetHawkPublicFwds_h

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

//AlertSettings
@class          StreetHawkAlertSettings;

//Actor
@class          StreetHawkActor;

//App
@class          StreetHawkApp;

//Cache
@protocol       StreetHawkCache;

//ClassTypeMap
@class          StreetHawkClassTypeMap;

//CrashHandler
@class          StreetHawkCrashHandler;

//Downloader
@class          StreetHawkDownloader;

//Engine
@class          StreetHawkEngine;

//FriendlyName
@class          StreetHawkFriendlyNameObject;

//Install
@class          StreetHawkInstall;
@class          StreetHawkInstallHandler;

//InstanceTable
@class          StreetHawkInstanceTable;

//Interceptor
@class          StreetHawkInterceptor;

//LocationManager
@class          StreetHawkLocationManager;

//Logger
@class          StreetHawkLogger;

//NotificationHandler
@class          StreetHawkNotificationHandler;

//Model
@protocol       StreetHawkFieldList;
@protocol       StreetHawkModelSchema;
@protocol       StreetHawkModel;
@class          StreetHawkModelSchema;

//Object
@protocol       StreetHawkObjectDelegate;
@protocol       StreetHawkGeoObject;
@protocol       StreetHawkCacheable;
@protocol       StreetHawkServerObject;
@protocol       StreetHawkObject;
@class          StreetHawkObject;
@protocol       StreetHawkObjectSet;
@class          StreetHawkObjectSet;

//ObjectFactory
@protocol       StreetHawkObjectFactory;

//ObjectLoader
@class          StreetHawkObjectLoader;

//ObjectStore
@class          StreetHawkObjectStore;

//Region
@class          StreetHawkRegion;

//RateHandler
@class          StreetHawkRateHandler;

//Request
@class          StreetHawkRequest;

//User
@class          StreetHawkUser;

//UI
@class          StreetHawkAlertView;
@class          StreetHawkBaseTableViewController;
@class          StreetHawkSlideViewController;

#endif
