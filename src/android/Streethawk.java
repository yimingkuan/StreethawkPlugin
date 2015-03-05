package com.streethawk.plugin;

import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.CallbackContext;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import com.streethawk.library.StreetHawk;
import com.streethawk.library.ISHObserver;
import org.apache.cordova.PluginResult;
import android.util.Log;
import android.content.Intent;
import org.apache.cordova.CordovaActivity;


public class Streethawk extends CordovaPlugin implements ISHObserver {

    private CallbackContext mSHCallbackContext;
	private int mCallBackID  = 0;
	private CallbackContext shRawJsonCallback;
	private final String TAG = "StreethawkPlugin";
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
            return true;
        }
        if(action.equals("shIsPushNotificationEnabled")) {
            return isUseGcm(callbackContext);
        }
        if(action.equals("shIsUseLocation")) {
            return isUseLocation(callbackContext);
        }
        if(action.equals("shGetAppKey")) {
            return getAppKey(callbackContext);
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
        if(action.equals("shSetGcmSenderId")){
            return setgcmSenderId(args);
        }
		if(action.equals("shSetIsPushNotificationEnabled")){
			return true;
		}
		if(action.equals("shSetIsUseLocation")){
			return true;
		}
		if(action.equals("shRegisterViewCallback")){
			this.mSHCallbackContext = callbackContext;
			return true;
		}
		if(action.equals("shDeeplinking")){
			processDeeplinkRequest(callbackContext);
			return true;
		}
		if(action.equals("shRawJsonCallback")){
			this.shRawJsonCallback = callbackContext;
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
		if(action.equals("shEnterBeacon")){
			return shEnterBeacon(args);
		}
		if(action.equals("shExitBeacon")){
			return shExitBeacon(args);
		}
		if(action.equals("shSetBeaconSupport")){
			return shSetBeaconSupport(args);
		}
		if(action.equals("shSetManualLocation")){
			return shSetManualLocation(args);
		}
		if(action.equals("displayBadge")){
			return displayBadge(args);
		}
			
        return false;
    }
    private boolean streethawkInit(){
        StreetHawk.INSTANCE.setCurrentActivity(cordova.getActivity());
        StreetHawk.INSTANCE.init(cordova.getActivity().getApplication());
        StreetHawk.INSTANCE.setAppPageReceiver(this);
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
    private boolean shSetBeaconSupport(JSONArray args)throws JSONException{
    	Boolean enable = args.getBoolean(0);
    	StreetHawk.INSTANCE.shSetBeaconSupport(enable);
        return true;
    }
    private boolean setgcmSenderId(JSONArray args)throws JSONException{
        String senderId = args.getString(0);
        StreetHawk.INSTANCE.setGcmSenderId(senderId);
        return true;
    }
    private boolean shSendSimpleFeedback(JSONArray args)throws JSONException{
    	String title 	 = args.getString(0);
        String message = args.getString(1);
        StreetHawk.INSTANCE.shSendSimpleFeedback(title,message);
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
    
    private boolean getAppKey(CallbackContext callbackContext){
        String app_key  = StreetHawk.getAppKey(cordova.getActivity().getApplicationContext());
        callbackContext.success(app_key);
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
        StreetHawk.INSTANCE.shNotifyPageEntered(currentPage);
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
    	String viewName  = StreetHawk.INSTANCE.getAppPage();
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
    private boolean shEnterBeacon(JSONArray args)throws JSONException{
    	String UUID 	 = args.getString(0);
        int major 		 = args.getInt(1);
        int minor 		 = args.getInt(2);
        double distance  = args.getInt(3);
        StreetHawk.INSTANCE.shEnterBeacon(cordova.getActivity().getApplicationContext(),UUID,major,minor,distance);
    	return true;
    }
    private boolean shExitBeacon(JSONArray args)throws JSONException{
    	String UUID 	 = args.getString(0);
        int major 		 = args.getInt(1);
        int minor 		 = args.getInt(2);
        StreetHawk.INSTANCE.shExitBeacon(cordova.getActivity().getApplicationContext(),UUID,major,minor);
    	return true;
    }
    private boolean shSetManualLocation(JSONArray args)throws JSONException{
    	double lat  = args.getDouble(0);
    	double lng	= args.getDouble(1);
        StreetHawk.INSTANCE.shSetLocation(lat,lng);
    	return true;
    }
    
    private boolean displayBadge(JSONArray args)throws JSONException{
    	int count  = args.getInt(0);
        StreetHawk.INSTANCE.displayBadge(cordova.getActivity().getApplicationContext(),count);
    	return true;
    }
    
    private void processDeeplinkRequest(CallbackContext callbackContext){
    	if(null==callbackContext)
    		return;
    	final Intent intent = ((CordovaActivity) this.webView.getContext()).getIntent();
        String url = null;
        if(null!=intent){
            url =intent.getDataString();
        }
        callbackContext.sendPluginResult(new PluginResult(PluginResult.Status.OK, url));
    }
    
    @Override
	public void shNotifyAppPage(String html_fileName) {
    	if(null!=this.mSHCallbackContext){
    		PluginResult result = new PluginResult(PluginResult.Status.OK,html_fileName);
    		result.setKeepCallback(true);
    		this.mSHCallbackContext.sendPluginResult(result);
    		}
	}
    
    @Override
    public void shReceivedRawJSON(String title, String message, String json){
    	if(null!=this.shRawJsonCallback){
    	    try{
    	    JSONObject customJson = new JSONObject();
    	    customJson.put("title",title);
    	    customJson.put("message",message);
    	    customJson.put("json",json);
    		PluginResult result = new PluginResult(PluginResult.Status.OK,customJson);
    		result.setKeepCallback(true);
    		this.shRawJsonCallback.sendPluginResult(result);
    		}catch(JSONException e){
    			Log.e(TAG,"JSONException "+e);
    		}
    	}
    }
}
