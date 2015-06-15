/*
 * Copyright 2014 StreetHawk
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
 */

/**
 * Javascript interface for Streethawk library.
 * Online document https://streethawk.freshdesk.com/solution/categories/5000158959/folders/5000254780
 */

var exec = require('cordova/exec');
var SHLibrary = function() {};

var success = function(){}
var fail = function(){}

var streethawkTags = {
    'sh_email' 			:	'sh_email',             
	'sh_phone'			: 	'sh_phone',              
    'sh_gender'			: 	'sh_gender',             
    'sh_cuid'			:	'sh_cuid',            
    'sh_first_name' 	:	'sh_first_name',          
    'sh_last_name' 		:	'sh_last_name',          
    'sh_date_of_birth' 	:	'sh_date_of_birth',       
    'sh_utc_offset' 	:	'sh_utc_offset'
};

SHLibrary.prototype.streethawkinit = function() {
    console.log("streethawkinit");
    exec(success, fail, 'Streethawk', 'streethawkinit', []);
    document.addEventListener("resume", function() {
        exec(success, fail, 'Streethawk', 'shOnResume', []);
    }, false);
	document.addEventListener("pause",function() {
        exec(success, fail, 'Streethawk', 'shOnPause', []);
    }, false);
    
}

SHLibrary.prototype.tagNumeric = function(string_key, numeric_value) {
    exec(success,fail, 'Streethawk', 'tagNumeric', [string_key, numeric_value]);
}

SHLibrary.prototype.tagString = function(string_key, string_value) {
    exec(success, fail, 'Streethawk', 'tagString', [string_key, string_value]);
}

SHLibrary.prototype.tagDatetime = function(string_key, datetime_value) {
    exec(success, fail, 'Streethawk', 'tagDatetime', [string_key, datetime_value]);
}

SHLibrary.prototype.incrementTag = function(string_key) {
    exec(success, fail, 'Streethawk', 'incrementTag', [string_key]);
}

SHLibrary.prototype.removeTag = function(string_key) {
    exec(success, fail, 'Streethawk', 'removeTag', [string_key]);
}

SHLibrary.prototype.sendLogForTagUser = function(dict_tag) {
    exec(success, fail, 'Streethawk', 'sendLogForTagUser', [dict_tag]);
}

SHLibrary.prototype.currentPage = function(string_pagename) {
    exec(success, fail, 'Streethawk', 'currentPage', [string_pagename]);
}

SHLibrary.prototype.shSendSimpleFeedback = function(string_title, string_message) {
    exec(success, fail, 'Streethawk', 'shSendSimpleFeedback', [string_title, string_message]);
}

SHLibrary.prototype.shCustomActivityList = function(friendlyNameArray) {
    exec(success, fail, 'Streethawk', 'shCustomActivityList', friendlyNameArray);
}

SHLibrary.prototype.getSHLibraryVersion = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'getSHLibraryVersion', []);
}

SHLibrary.prototype.getCurrentFormattedDateTime = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'getCurrentFormattedDateTime', []);
}

SHLibrary.prototype.shSetEnableLogs = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'shSetEnableLogs', [bool_enable]);
}

SHLibrary.prototype.shEnableLogs = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shEnableLogs', []);
}

SHLibrary.prototype.shSetiTunesId = function(string_iTunesid) {
    exec(success, fail, 'Streethawk', 'shSetiTunesId', [string_iTunesid]);
}

SHLibrary.prototype.shiTunesId = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shiTunesId', []);
}

SHLibrary.prototype.shSetDefaultPushNotificationSupport = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'shSetDefaultPushNotificationSupport', [bool_enable]);
}

SHLibrary.prototype.shSetIsPushNotificationEnabled = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'shSetIsPushNotificationEnabled', [bool_enable]);
}

SHLibrary.prototype.shIsPushNotificationEnabled = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shIsPushNotificationEnabled', []);
}

SHLibrary.prototype.shSetDefaultLocationSupport = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'shSetDefaultLocationSupport', [bool_enable]);
}

SHLibrary.prototype.shSetIsUseLocation = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'shSetIsUseLocation', [bool_enable]);
}

SHLibrary.prototype.shIsUseLocation = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shIsUseLocation', []);
}
               
SHLibrary.prototype.setUseCustomDialog = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'setUseCustomDialog', [bool_enable]);
}

SHLibrary.prototype.shEnterBeacon = function(string_uuid,int_majorNo,int_minorNo,double_distance) {
    exec(success, fail, 'Streethawk', 'shEnterBeacon', [string_uuid,int_majorNo,int_minorNo,double_distance]);
}

SHLibrary.prototype.shExitBeacon = function(string_uuid,int_majorNo,int_minorNo) {
    exec(success, fail, 'Streethawk', 'shExitBeacon', [string_uuid,int_majorNo,int_minorNo]);
}

SHLibrary.prototype.shSetBeaconSupport = function(bool_enable) {
    exec(success, fail, 'Streethawk', 'shSetBeaconSupport', [bool_enable]);
}
               
SHLibrary.prototype.shSetAlertSetting = function(int_pauseMinutes) {
    exec(success, fail, 'Streethawk', 'shSetAlertSetting', [int_pauseMinutes]);
}

SHLibrary.prototype.shAlertSettings = function(appSuccess, appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shAlertSettings', []);
}

SHLibrary.prototype.shGetViewName = function(appSuccess, appFail){
	exec(appSuccess,appFail,'Streethawk', 'shGetViewName',[]);
    return true;
}

SHLibrary.prototype.shRegisterViewCallback = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'shRegisterViewCallback', []);
}

SHLibrary.prototype.shRawJsonCallback = function(appSuccess, appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'shRawJsonCallback', []);
}

SHLibrary.prototype.shSetManualLocation = function(double_lat,double_lng) {
    exec(success,fail, 'Streethawk', 'shSetManualLocation', [double_lat,double_lng]);
}

SHLibrary.prototype.displayBadge = function(int_count) {
    exec(success,fail, 'Streethawk', 'displayBadge', [int_count]);
}

SHLibrary.prototype.shSetGcmSenderId = function(string_senderKey) {
    exec(success,fail, 'Streethawk', 'shSetGcmSenderId', [string_senderKey]);
}

SHLibrary.prototype.shGetAppKey = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shGetAppKey', []);
}

SHLibrary.prototype.shDeeplinking = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'Streethawk', 'shDeeplinking', []);
}

SHLibrary.prototype.pushResultCallback = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'registerPushResultCallback', []);
}

SHLibrary.prototype.pushDataCallback = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'registerPushDataCallback', []);
}

SHLibrary.prototype.feedItemCallback = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'registerFeedItemCallback', []);
}

SHLibrary.prototype.reportFeedRead = function(int_feedid,int_result) {
    exec(success,fail, 'Streethawk', 'shReportFeedRead', [int_feedid, int_result]);
}

SHLibrary.prototype.sendPushResult = function(String_msgId,int_result) {
    exec(success,fail, 'Streethawk', 'sendPushResult', [String_msgId, int_result]);
}

SHLibrary.prototype.InviteFriendsToDownloadApplication = function(String_ID,String_deeplinkUrl,String_EmailSubject,String_EmailBody) {
    exec(success,fail, 'Streethawk', 'InviteFriendsToDownloadApplication', [String_ID,String_deeplinkUrl,String_EmailSubject,String_EmailBody]);
}

SHLibrary.prototype.forcePushToNotificationBar = function(bool_status) {
    exec(success,fail, 'Streethawk', 'forcePushToNotificationBar', [bool_status]);
}

SHLibrary.prototype.shGetFeedDataFromServer = function(int_offset) {
    exec(success,fail, 'Streethawk', 'shGetFeedDataFromServer', [int_offset]);
}

SHLibrary.prototype.notifyNewFeedCallback = function(appSuccess, appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'notifyNewFeedCallback', []);
}

SHLibrary.prototype.originateShareWithCampaign = function(string_ID,string_shareUrl,appSuccess, appFail) {
    exec(appSuccess,appFail, 'Streethawk', 'getShareUrlForAppDownload', [string_ID,string_shareUrl]);
}

SHLibrary.prototype.setAppKey = function(string_AppKey) {
	console.log("StreetHawk setAppKey");
    exec(success, fail, 'Streethawk', 'setAppKey', [string_AppKey]);
}

var myplugin = new SHLibrary();
module.exports = myplugin;
