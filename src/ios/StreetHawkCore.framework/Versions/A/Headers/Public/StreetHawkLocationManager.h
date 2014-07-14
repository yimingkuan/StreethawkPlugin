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
#import <CoreLocation/CoreLocation.h>

/**
 Notification sent when start standard geolocation monitor. UserInfo is nil. Use `geolocationMonitorState` to know current geo location state.
 */
extern NSString * const StreetHawkLMStartStandardMonitorNotification;

/**
 Notification sent when stop standard geolocation monitor. UserInfo is nil. Use `geolocationMonitorState` to know current geo location state.
 */
extern NSString * const StreetHawkLMStopStandardMonitorNotification;

/**
 Notification sent when start significant geolocation monitor. UserInfo is nil. Use `geolocationMonitorState` to know current geo location state.
 */
extern NSString * const StreetHawkLMStartSignificantMonitorNotification;

/**
 Notification sent when stop significant geolocation monitor. UserInfo is nil. Use `geolocationMonitorState` to know current geo location state.
 */
extern NSString * const StreetHawkLMStopSignificantMonitorNotification;

/**
 Notification sent when start heading monitor. UserInfo is nil. Use `isHeadingMonitoring` to know whether monitor heading.
 */
extern NSString * const StreetHawkLMStartHeadingNotification;

/**
 Notification sent when stop heading monitor. UserInfo is nil. Use `isHeadingMonitoring` to know whether monitor heading.
 */
extern NSString * const StreetHawkLMStopHeadingNotification;

/**
 Notification sent when start monitoring one iBeacon. UserInfo is nil. Use `monitoringBeconRegions` to get current monitoring beacons.
 */
extern NSString * const StreetHawkLMStartBeaconNotification;

/**
 Notification sent when stop monitoring one iBeacon. UserInfo is nil. Use `monitoringBeconRegions` to get current monitoring beacons.
 */
extern NSString * const StreetHawkLMStopBeaconNotification;

/**
 Notification sent when successfully update to a new location, equal `- (void)locationManager:(CLLocationManager *)manager didUpdateToLocation:(CLLocation *)newLocation fromLocation:(CLLocation *)oldLocation` before iOS 6 or `- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray *)locations` since iOS 6. The user information contains `StreetHawkLocationNotification_kNewLocation` and `StreetHawkLocationNotification_kOldLocation` representing CLLocatioin.
 */
extern NSString * const StreetHawkLMUpdateLocationSuccessNotification;

/**
 Notification sent when successfully update to a new heading, equal `- (void)locationManager:(CLLocationManager *)manager didUpdateHeading:(CLHeading *)newHeading`. The user information contains `StreetHawkLMNotification_kNewHeading` representing CLHeading.
 */
extern NSString * const StreetHawkLMUpdateHeadingSuccessNotification;

/**
 Notification sent when fail to update location or heading, equal `- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error`. The user information contains `StreetHawkLocationNotification_kError` representing NSError.
 */
extern NSString * const StreetHawkLMUpdateFailNotification;

/**
 Notification sent when enter one region, equal `- (void)locationManager:(CLLocationManager *)manager didEnterRegion:(CLRegion *)region`. It's called both for geo region or iBeacon region. Use `StreetHawkLMBeaconFoundNotification` for iBeacon. The user information contains `StreetHawkLMNotification_kRegion` representing CLRegion.
 */
extern NSString * const StreetHawkLMEnterRegionNotification;

/**
 Notification sent when exit one region, equal `- (void)locationManager:(CLLocationManager *)manager didExitRegion:(CLRegion *)region`. It's called both for geo region or iBeacon region. The user information contains `StreetHawkLMNotification_kRegion` representing CLRegion.
 */
extern NSString * const StreetHawkLMExitRegionNotification;

/**
 Notification sent when successfully start to monitor one region, equal `- (void)locationManager:(CLLocationManager *)manager didStartMonitoringForRegion:(CLRegion *)region`. It's called both for geo region or iBeacon region. The user information contains `StreetHawkLMNotification_kRegion` representing CLRegion.
 */
extern NSString * const StreetHawkLMMonitorRegionSuccessNotification;

/**
 Notification sent when fail to monitor one region, equal `- (void)locationManager:(CLLocationManager *)manager monitoringDidFailForRegion:(CLRegion *)region withError:(NSError *)error`. It's called both for geo region or iBeacon region. The user information contains `StreetHawkLMNotification_kRegion` representing CLRegion and `StreetHawkLMNotification_kError` representing NSError.
 */
extern NSString * const StreetHawkLMMonitorRegionFailNotification;

/**
 Notification sent when beacons changes, equal `- (void)locationManager:(CLLocationManager *)manager didRangeBeacons:(NSArray *)beacons inRegion:(CLBeaconRegion *)region`. The above delegate happens frequently even beacons are not changed, and if no real change happen this notification is not sent. The user information contains `StreetHawkLMNotification_kRegion` representing CLRegion and `StreetHawkLMNotification_kBeacons` representing NSArray of CLBeacon. If beacons array is empty, it means no beacons nearby can reach the device.
 */
extern NSString * const StreetHawkLMBeaconChangedNotification;

/**
 Notification sent when fail to monitor one iBeacon region, equal `- (void)locationManager:(CLLocationManager *)manager rangingBeaconsDidFailForRegion:(CLBeaconRegion *)region withError:(NSError *)error`. The user information contains `StreetHawkLMNotification_kRegion` representing CLRegion and `StreetHawkLMNotification_kError` representing NSError.
 */
extern NSString * const StreetHawkLMBeaconRangeFailNotification;

/**
 Notification sent when authorization status change, equal `- (void)locationManager:(CLLocationManager *)manager didChangeAuthorizationStatus:(CLAuthorizationStatus)status`. The user information contains `StreetHawkLMNotification_kAuthStatus` representing CLAuthorizationStatus.
 */
extern NSString * const StreetHawkLMChangeAuthorizationStatusNotification;

/**
 Keys for StreetHawkLocation notifications.
 */
extern NSString * const StreetHawkLMNotification_kNewLocation; //string @"NewLocation", get CLLocation.
extern NSString * const StreetHawkLMNotification_kOldLocation; //string @"OldLocation", get CLLocation.
extern NSString * const StreetHawkLMNotification_kNewHeading; //string @"NewHeading", get CLHeading.
extern NSString * const StreetHawkLMNotification_kError; //string @"Error", get NSError.
extern NSString * const StreetHawkLMNotification_kRegion; //string @"Region", get CLRegion.
extern NSString * const StreetHawkLMNotification_kBeacons; //string @"Beacons", get NSArray for CLBeacon.
extern NSString * const StreetHawkLMNotification_kAuthStatus;  //string @"AuthStatus", get NSNumber for int representing CLAuthorizationStatus.

/**
 The state of current geolocation update.
 */
enum StreetHawkGeoLocationMonitorState
{
    /**
     Not monitor geolocation.
     */
    StreetHawkGeoLocationMonitorState_Stopped,
    /**
     Monitor geolocation in standard way, called by `startUpdatingLocation`.
     */
    StreetHawkGeoLocationMonitorState_MonitorStandard,
    /**
     Monitor geolocation in significant change way, called by `startMonitoringSignificantLocationChanges`.
     */
    StreetHawkGeoLocationMonitorState_MonitorSignificant,
};
typedef enum StreetHawkGeoLocationMonitorState StreetHawkGeoLocationMonitorState;

/**
A core class to monitor location change. By default process of StreetHawk SDK, it works in the following way:

- When the App is in foreground, it uses startUpdatingLocation to monitor location position and change. The StreetHawkLocationManagerUpdateLocation notification is sent after fgMinTimeBetweenEvents (default: 1 minute) and fgMinDistanceBetweenEvents (default: 100 meters).
- When App is in background, it uses startMonitoringSignificantLocationChanges to monitor location change. The StreetHawkLocationManagerUpdateLocation notification sent after bgMinTimeBetweenEvents (default: 5 minute) and bgMinDistanceBetweenEvents (default: 500 meters).
- These defaults can be overriden for your specific application.
- The StreetHawkLocationManager automatically manages/monitors the foreground/background state, so there is no requirement from the App developer. It should be noted that if the screen is turned off while the App is in the foreground, this is treated as a transition to background.
- Even if the App crashes or is terminated, or phone power off/on, the App will be woken up and put in background because significant location monitoring.
- Once location update notification occur, (according to the algorithm above) logs are post to server immediately, and install updated.
- The User can set their location to be manual (`useManualLocation`=YES). For example by location picker to choose one favorite location (either by lookup or via map interaction)
  The device location service is NOT stopped and logs continue to be posted for the user's location change, but install/update is not called.
  `useManualLocation` set back to NO when:
    1. user chooses a 'Near Me" option in a location picker
    2. The App is restarted.
 
 **Default Values by Application state**
 <table>
    <tr>
        <th>Parameter</th>
        <th>Background</th>
        <th>Foreground</th>
    </tr>
    <tr>
        <td>(bg/fg)MinDistanceBetweenEvents</td>
        <td>500m</td>
        <td>100m</td>
    </tr>
    <tr>
        <td>(bg/fg)MinTimeBetweenEvents</td>
        <td>5mins</td>
        <td>1min</td>
    </tr>
 </table>
 
 **Related project settings:**
    In "Required background modes" there is a choice for location service (Location updates). Note: this is ONLY for keeping standard location service to run at background; it has NO effect for significant location service. With or without this setting checked, significant location service keeps running at background, or even App is terminated or Phone power off/on. Because StreetHawk SDK uses standard location update in foreground, uses significant location update in background, there is NO need to check this setting.
 
 **Debug Tips:**
 * Xcode can simulate location, but it only works for standard location service, not works for significant location service (both simulator and device). To test significant location update, the only way is to travel with device.
 * Even without background mode checked, standard location service not stop immediately when click home button to put App go to background. When the App is in background, you can still see location update delegate triggered. But once you lock screen, the standard location service stop.
 * If kill App in Xcode, significant location cannot wake up automatically. Need to turn App on, even manually kill it in device.
 
 Normally caller does not need to start/stop location service, or set the properties. Caller just need to visit the location properties. But the control API also provided.
 */
@interface StreetHawkLocationManager : NSObject<CLLocationManagerDelegate>

/** @name Creator */

/**
 Singleton instance. Caller normally only needs to use [StreetHawkLocationManager sharedInstance], or StreetHawk.theEngine.locationManager (they are same) to visit the location properties. 
 */
+(StreetHawkLocationManager *)sharedInstance;

/** @name Geo Location Detection Result */

@property (nonatomic, readonly) StreetHawkGeoLocationMonitorState geolocationMonitorState;

/**
 latitude for working location. If useManualLocation=YES, they are from lastManualLatitude, if useManualLocation=NO, they are from lastDeviceLatitude.
 */
@property (nonatomic, readonly) double latitude;

/**
 longitude for working location. If useManualLocation=YES, they are from lastManualLongitude, if useManualLocation=NO, they are from lastDeviceLongitude.
 */
@property (nonatomic, readonly) double longitude;

/**
 Working location, it's formatted as (`latitude`, `longitude`).
 */
@property (nonatomic, readonly) CLLocationCoordinate2D location;

/**
 Last detected device latitude. If location update since app launch, it's for the newly detective device location; else when initialize it's from NSUserDefaults saved last location. If this device never detect location, use 0.
 */
@property (nonatomic) double lastDeviceLatitude;

/**
 Last detected device longitude. If location update since app launch, it's for the newly detected device location; else when initialize it's from NSUserDefaults saved last location. If this device never detect location, use 0.
 */
@property (nonatomic) double lastDeviceLongitude;

/**
 Device location, it's formatted as (`lastDeviceLatitude`, `lastDeviceLongitude`).
 */
@property (nonatomic, readonly) CLLocationCoordinate2D lastDeviceLocation;

/**
 This location manager also records user chosen location for example in location picker. `useManualLocation` is a flag to know whether device location or chosen location should be used.
 */
@property (nonatomic) BOOL useManualLocation;

/**
 User picked manual latitude in location picker. 
 */
@property (nonatomic) double lastManualLatitude;

/**
 User picked manual longitude in location picker.
 */
@property (nonatomic) double lastManualLongitude;

/**
 Manual location, it's formatted as (`lastManualLatitude`, `lastManualLongitude`).
 */
@property (nonatomic) CLLocationCoordinate2D lastManualLocation;

/**
 Sets the user's "manual" location.
 */
-(void)setManualLocationAtLatitude:(double)latitude atLongitude:(double)longitude;

/** @name Set Geo Location Service Properties */

/**
 Properties for setting up CLLocationManager.
 */
@property (nonatomic) CLLocationAccuracy desiredAccuracy;

/**
 Properties for setting up CLLocationManager.
 */
@property (nonatomic) CLLocationDistance distanceFilter;

/**
 Foreground minimum time between events, if last event till now less than this, location update notification will not happen. default = 60 (seconds)
 */
@property (nonatomic) NSTimeInterval fgMinTimeBetweenEvents;

/**
 Background minimum time between events, if last event till now less than this, location update notification will not happen. default = 300 (seconds)
 */
@property (nonatomic) NSTimeInterval bgMinTimeBetweenEvents;

/**
 Foreground minimum distance between events, if last event to current location less than this, location update notification will not happen. default = 100.0 (metres)
 */
@property (nonatomic) float fgMinDistanceBetweenEvents;

/**
 Background minimum distance between events, if last event to current location less than this, location update notification will not happen. default = 500.0 (metres)
 */
@property (nonatomic) float bgMinDistanceBetweenEvents;

/** @name Heading Detection Result */

/**
 Whether monitoring heading now.
 */
@property (nonatomic, readonly) BOOL isHeadingMonitoring;

/*
 When a new heading is available, this property decides whether to display heading calibration info. The display will remain until heading is calibrated, unless dismissed early via dismissHeadingCalibrationDisplay. It's used in `- (BOOL)locationManagerShouldDisplayHeadingCalibration:(CLLocationManager *)manager`.
 */
@property (nonatomic) BOOL shouldDisplayHeadingCalibration;

/**
 Current monitoring iBeacon regions. It's added by `- (void)startMonitorBeacon:(CLBeaconRegion *)beaconRegion` and removed by `- (void)stopMonitorBeacon:(CLBeaconRegion *)beaconRegion`.
 */
@property (nonatomic, readonly) NSArray *monitoringBeconRegions;

/** @name Operation */

/**
 Start detecting the location change. Normally you don't need to call this because the StreetHawkApp will call this and related functions based on application state (foreground uses standard location service, background uses significant location service). However you may wish to control this, for example in foreground you may wish to switch to significant location service, so call `startDetectingLocationStandard:NO inForeground:YES`. After detecting successfully, observe `StreetHawkLMUpdateLocationSuccessNotification` to get the result.
 @param standard - use standard GPS style location tracking otherwise significant.
 @return YES if started OK. NO if failed - this is usually due to a user disabling location services. Your application should check and prompt the user to change this option.
 */
- (BOOL)startMonitorGeoLocationStandard:(BOOL)standard;

/**
 Stop geo location detection if it is in progress. It stops standard location service or significant location service. If the location service is not started yet, call this do nothing without error.
 */
- (void)stopMonitorGeoLocation;

/**
 Start detecting the heading. After detecting successfully, observe `StreetHawkLMUpdateHeadingSuccessNotification` to get the result.
 @return YES if start OK. NO if failed - this is usually due to a user disabling heading services. Your application should check and prompt the user to change this option.
 */
- (BOOL)startMonitorHeading;

/**
 Stop heading service.
 */
- (void)stopMonitorHeading;

/**
 Start to monitor one iBeacon region. If this iBeacon is already monitoring, do nothing.
 @return YES if the beacon region is not monitoring yet. NO if the beacon region is already in the list.
 */
- (BOOL)startMonitorBeacon:(CLBeaconRegion *)beaconRegion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

/**
 Stop monitoring one iBeacon region. Nothing happen even the iBeacon is not monitoring now. 
 */
- (void)stopMonitorBeacon:(CLBeaconRegion *)beaconRegion __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_7_0);

@end
