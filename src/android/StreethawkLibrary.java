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
 
package com.streethawk;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import com.streethawk.library.base.StreetHawk;
import com.streethawk.library.api.app.StreetHawkAwakeException;
import com.streethawk.library.gcm.ISHPhoneGapObserver;

/*
* Class hosting streethawk's API for phonegap
*/

public class StreethawkLibrary extends CordovaPlugin implements ISHPhoneGapObserver {
	private CallbackContext shCallbackContext;
    @Override
    public boolean execute(String action, JSONArray args, CallbackContext callbackContext) throws JSONException {
        if(action.equals("streethawkinit")) {
            return streethawkInit();
        }
        if(action.equals("tagNumeric")) {
            return tagNumeric(args);
        }
        if(action.equals("tagString")) {
            return tagString(args);
        }
        if(action.equals("tagDatetime")) {
            return tagDatetime(args);
        }
        if(action.equals("incrementTag")) {
            return incrementTag(args);
        }
        if(action.equals("removeTag")) {
            return removeTag(args);
        }
        if(action.equals("shSetAlertSetting")) {
            return shAlertSetting(args);
        }
        if(action.equals("shSetDefaultPushNotificationSupport")) {
            return shSetGcmSupport(args);
        }
        if(action.equals("shSetDefaultLocationSupport")) {
            return shSetLocationSupport(args);
        }
        if(action.equals("shSendSimpleFeedback")) {
            return shSendSimpleFeedback(args);
        }
        if(action.equals("sendLogForTagUser")) {
            return sendLogForTagUser(args);
        }
        if(action.equals("sendLogForTagUser")) {
            return isUseGcm(callbackContext);
        }
        if(action.equals("shIsPushNotificationEnabled")) {
            return isUseGcm(callbackContext);
        }
        if(action.equals("shIsUseLocation")) {
            return isUseLocation(callbackContext);
        }
        if(action.equals("getSHLibraryVersion")) {
            return getSHLibraryVersion(callbackContext);
        }
        if(action.equals("shAlertSettings")) {
            return shGetAlertSettings(callbackContext);
        }
        if(action.equals("shSetEnableLogs")) {
            return shEnableLogs(args);
        }
        if(action.equals("currentPage")) {
            return currentPage(args);
        }
        if(action.equals("getCurrentFormattedDateTime")) {
            return getCurrentFormattedDateTime(callbackContext);
        }
       if(action.equals("shCustomActivityList")) {
            return shCustomActivityList(args);
        }
		if(action.equals("shSetApnsMode")){
			return true;
		}
		if(action.equals("shSetiTunesId")){
			return true;
		}
		if(action.equals("shSetApnsMode")){
			return true;
		}
		if(action.equals("shSetiTunesId")){
			return true;
		}
		if(action.equals("shApnsMode")){
			return true;
		}
		if(action.equals("shiTunesId")){
			return true;
		}
		if(action.equals("shSetIsPushNotificationEnabled")){
			return true;
		}
		if(action.equals("shSetIsUseLocation")){
			return true;
		}
		if(action.equals("shRegisterViewCallback")){
			this.shCallbackContext = callbackContext;
			return true;
		}
		if(action.equals("shGetViewName")){
			return shGetViewName(callbackContext);
		}
		if(action.equals("shOnResume")){
			return shOnResume();
		}
		if(action.equals("shOnPause")){
			return shOnPause();
		}	
        return false;
    }
    private boolean streethawkInit(){
        StreetHawk.INSTANCE.setPhonegapApp(true);
        StreetHawk.INSTANCE.setCurrentActivity(cordova.getActivity());
        StreetHawk.INSTANCE.shPGHtmlReceiver(this);
        StreetHawk.INSTANCE.init(cordova.getActivity().getApplication());
        return true;
    }
    
    private boolean tagNumeric(JSONArray args)throws JSONException{
        String key = args.getString(0);	
		int value = args.getInt(1);
        StreetHawk.INSTANCE.tagNumeric(key,value);
        return true;
    }
    private boolean tagString(JSONArray args)throws JSONException{
        String key 	 = args.getString(0);
        String value = args.getString(1);
        StreetHawk.INSTANCE.tagString(key,value);
        return true;
    }
    private boolean tagDatetime(JSONArray args)throws JSONException{
        String key 	 = args.getString(0);
        String value = args.getString(1);
        StreetHawk.INSTANCE.tagDatetime(key,value);
        return true;
    }
    private boolean incrementTag(JSONArray args)throws JSONException{
        String tag 	 = args.getString(0);
        StreetHawk.INSTANCE.incrementTag(tag);
        return true;
    }
    private boolean removeTag(JSONArray args)throws JSONException{
    	String tag 	 = args.getString(0);StreetHawk.INSTANCE.removeTag(tag);
        return true;
    }
    private boolean shAlertSetting(JSONArray args)throws JSONException{
		int pauseMin = args.getInt(0);
    	StreetHawk.INSTANCE.shAlertSetting(pauseMin);
        return true;
    }
    private boolean shSetGcmSupport(JSONArray args)throws JSONException{
        Boolean enable = args.getBoolean(0);
        StreetHawk.INSTANCE.shSetGcmSupport(enable);
        return true;
    }
    private boolean shSetLocationSupport(JSONArray args)throws JSONException{
    	Boolean enable = args.getBoolean(0);
    	StreetHawk.INSTANCE.shSetLocationSupport(enable);
        return true;
    }
    private boolean shSendSimpleFeedback(JSONArray args)throws JSONException{
    	String title 	 = args.getString(0);
        String message = args.getString(1);
        StreetHawk.INSTANCE.shSendSimpleFeedback(title,message);
        return true;
    }
    private boolean sendLogForTagUser(JSONArray args)throws IllegalArgumentException, JSONException{
    	JSONObject jsonObject = (JSONObject) args.get(0);
        //TODO add support for overloaded function
        try{
            StreetHawk.INSTANCE.sendLogForTagUser(jsonObject);
        }catch(StreetHawkAwakeException e){
            
        }
        return true;
    }
    private boolean isUseGcm(CallbackContext callbackContext){
        String result  = Boolean.toString(StreetHawk.INSTANCE.isUseGcm());
        callbackContext.success(result);
        return true;
    }
    
    private boolean isUseLocation(CallbackContext callbackContext){
        String result  = Boolean.toString(StreetHawk.INSTANCE.isUseLocation());
        callbackContext.success(result);
        return true;
    }
    
    private boolean getSHLibraryVersion(CallbackContext callbackContext){
        String shVersion  = StreetHawk.INSTANCE.getSHLibraryVersion();
        callbackContext.success(shVersion);
        return true;
    }
    private boolean shGetAlertSettings(CallbackContext callbackContext){
        int timeRemaining  = (int)StreetHawk.INSTANCE.shGetAlertSettings();
        callbackContext.success(timeRemaining);
        return true;
    }
    private boolean shEnableLogs(JSONArray args)throws JSONException{
    	Boolean enable = args.getBoolean(0);
        StreetHawk.INSTANCE.ENABLE_STREETHAWK_LOGS = enable;
        return true;
    }
    private boolean currentPage(JSONArray args)throws JSONException{
    	String currentPage 	 = args.getString(0);
        StreetHawk.INSTANCE.shPGNotifyNewPage(currentPage);
        return true;
    }
    private boolean getCurrentFormattedDateTime(CallbackContext callbackContext){
     	String result = StreetHawk.getCurrentFormattedDateTime();
    	callbackContext.success(result);
        return true;
    }
    private boolean shCustomActivityList(JSONArray args)throws JSONException{
        StreetHawk.INSTANCE.shCustomActivityList(args);
        return true;
    }
     private boolean shGetViewName(CallbackContext callbackContext){
    	String viewName  = StreetHawk.INSTANCE.shGetviewName();
        callbackContext.success(viewName);
        return true;
    }
    private boolean shOnResume(){
    	StreetHawk.INSTANCE.shActivityResumed(cordova.getActivity());
    	return true;
    }
	private boolean shOnPause(){
    	StreetHawk.INSTANCE.shActivityPaused(cordova.getActivity());
    	return true;
    }
    @Override
	public void shPGDisplayHtmlFileName(String html_fileName) {
		this.shCallbackContext.success(html_fileName);
	}
}

    
