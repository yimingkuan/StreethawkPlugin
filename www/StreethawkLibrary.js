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
 * Online document http://api.streethawk.com/v1/docs/phonegap-introduction.html
 */

var exec = require('cordova/exec');
var SHLibrary = function() {};

var success = function(){}
var fail = function(){}

SHLibrary.prototype.streethawkinit = function() {
    exec(success, fail, 'StreethawkLibrary', 'streethawkinit', []);
    document.addEventListener("resume",function(){
    exec(success, fail, 'StreethawkLibrary', 'shOnResume', []);
    }, false);
	document.addEventListener("pause",function(){
    exec(success, fail, 'StreethawkLibrary', 'shOnPause', []);
    }, false);
    
}

SHLibrary.prototype.tagNumeric = function(string_key, numeric_value) {
    exec(success,fail, 'StreethawkLibrary', 'tagNumeric', [string_key, numeric_value]);
}

SHLibrary.prototype.tagString = function(string_key, string_value) {
    exec(success, fail, 'StreethawkLibrary', 'tagString', [string_key, string_value]);
}

SHLibrary.prototype.tagDatetime = function(string_key, datetime_value) {
    exec(success, fail, 'StreethawkLibrary', 'tagDatetime', [string_key, datetime_value]);
}

SHLibrary.prototype.incrementTag = function(string_key) {
    exec(success, fail, 'StreethawkLibrary', 'incrementTag', [string_key]);
}

SHLibrary.prototype.removeTag = function(string_key) {
    exec(success, fail, 'StreethawkLibrary', 'removeTag', [string_key]);
}

SHLibrary.prototype.sendLogForTagUser = function(dict_tag) {
    exec(success, fail, 'StreethawkLibrary', 'sendLogForTagUser', [dict_tag]);
}

SHLibrary.prototype.currentPage = function(string_pagename) {
    exec(success, fail, 'StreethawkLibrary', 'currentPage', [string_pagename]);
}

SHLibrary.prototype.shSendSimpleFeedback = function(string_title, string_message) {
    exec(success, fail, 'StreethawkLibrary', 'shSendSimpleFeedback', [string_title, string_message]);
}

SHLibrary.prototype.shCustomActivityList = function(friendlyNameArray) {
    exec(success, fail, 'StreethawkLibrary', 'shCustomActivityList', friendlyNameArray);
}

SHLibrary.prototype.getSHLibraryVersion = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'StreethawkLibrary', 'getSHLibraryVersion', []);
}

SHLibrary.prototype.getCurrentFormattedDateTime = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'StreethawkLibrary', 'getCurrentFormattedDateTime', []);
}

SHLibrary.prototype.shSetApnsMode = function(int_apnsMode) {
    exec(success, fail, 'StreethawkLibrary', 'shSetApnsMode', [int_apnsMode]);
}

SHLibrary.prototype.shApnsMode = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'StreethawkLibrary', 'shApnsMode', []);
}

SHLibrary.prototype.shSetEnableLogs = function(bool_enable) {
    exec(success, fail, 'StreethawkLibrary', 'shSetEnableLogs', [bool_enable]);
}

SHLibrary.prototype.shEnableLogs = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'StreethawkLibrary', 'shEnableLogs', []);
}

SHLibrary.prototype.shSetiTunesId = function(string_iTunesid) {
    exec(success, fail, 'StreethawkLibrary', 'shSetiTunesId', [string_iTunesid]);
}

SHLibrary.prototype.shiTunesId = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'StreethawkLibrary', 'shiTunesId', []);
}

SHLibrary.prototype.shSetDefaultPushNotificationSupport = function(bool_enable) {
    exec(success, fail, 'StreethawkLibrary', 'shSetDefaultPushNotificationSupport', [bool_enable]);
}

SHLibrary.prototype.shSetIsPushNotificationEnabled = function(bool_enable) {
    exec(success, fail, 'StreethawkLibrary', 'shSetIsPushNotificationEnabled', [bool_enable]);
}

SHLibrary.prototype.shIsPushNotificationEnabled = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'StreethawkLibrary', 'shIsPushNotificationEnabled', []);
}

SHLibrary.prototype.shSetDefaultLocationSupport = function(bool_enable) {
    exec(success, fail, 'StreethawkLibrary', 'shSetDefaultLocationSupport', [bool_enable]);
}

SHLibrary.prototype.shSetIsUseLocation = function(bool_enable) {
    exec(success, fail, 'StreethawkLibrary', 'shSetIsUseLocation', [bool_enable]);
}

SHLibrary.prototype.shIsUseLocation = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'StreethawkLibrary', 'shIsUseLocation', []);
}

SHLibrary.prototype.shSetAlertSetting = function(int_pauseMinutes) {
    exec(success, fail, 'StreethawkLibrary', 'shSetAlertSetting', [int_pauseMinutes]);
}

SHLibrary.prototype.shAlertSettings = function(appSuccess,appFail) {
    exec(appSuccess,appFail,'StreethawkLibrary', 'shAlertSettings', []);
}

SHLibrary.prototype.shGetViewName = function(appSuccess,appFail){
	exec(appSuccess,appFail,'StreethawkLibrary','shGetViewName',[]);
    return true;
}

SHLibrary.prototype.shRegisterViewCallback = function(appSuccess,appFail) {
    exec(appSuccess,appFail, 'StreethawkLibrary', 'shRegisterViewCallback', []);
}





var myplugin = new SHLibrary();
module.exports = myplugin;
