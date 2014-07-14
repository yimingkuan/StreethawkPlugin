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

#import "StreetHawkInternalFwds.h"

/**
 View controller for slide in web page for a url.
 */
@interface StreetHawkSlideWebViewController : StreetHawkBaseViewController <StreetHawkSlideContentViewController, UIWebViewDelegate>

@property (retain, nonatomic) IBOutlet UIWebView *webView;
@property (retain, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;

/**
 The url for opening on this web view.
 */
@property (nonatomic, strong) NSString *webpageUrl;

@end
