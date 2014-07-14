# Streethawk Phonegap Plugin

[Streethawk](http://www.streethawk.com) phonegap plugin can be integrated in applications created using cordova phonegap. The plugin supports both Android and iOS. For detailed information and API documentation, please refer to [Streethawk Phonegap documentation.](http://api.streethawk.com/v1/docs/phonegap-introduction.html) 

## Steps to integrate Streethawk Phonegap Plugin

Assuming you have an application created using Phonegap, you can integrate Streethawk SDK by following simple steps mentioned below.

* In terminal, browse to root folder of your cordova phonegap application

* Add streethawk plugin by running command
```
cordova plugin add https://streethawk@bitbucket.org/shawk/streethawk-phonegap-plugin.git --variable APP_KEY=<YOUR_APPLICATIONS_APP_KEY>
```
Please note that, above command requires unique app_key of your application registered with Streethawk. If you dont have it , you can register you application's app_key [here](https://api.streethawk.com/static/bb/)

* Build and run your application for iOS by using command
```
cordova run iOS
``` 
* Android requires google-play-services_lib which can be added as follows
```
vi <Application_Root_Dir>/platforms/android/project.properties
```
and adding 
```
android.library.reference.2=../../../../<PATH_TO_ANDROID_SDK>/sdk/extras/google/google_play_services/libproject/google-play-services_lib/
```
in project.properties file.
 
* Build and run your application for Android by using command
```
cordova run android
```

That's it!. Streethawk is integrated in your application. Please refer to [Streethawk Phonegap documentation](http://api.streethawk.com/v1/docs/phonegap-introduction.html) for adding more Streethawk features.
 