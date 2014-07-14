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

#import "../StreetHawkPublicFwds.h"

/**
 Normally one delegate can only set to one object, for example UITableView needs to setup one delegate, usually it's set to a UIViewController. However now some common object for handling UITableView is involved, such as StreetHawkInfinyTableViewDriver. The expected behavior is: StreetHawkInfinyTableViewDriver controls behavior of UITableView, and UIViewController can supplement some of the detail functions, for example create cell. It's like the delegate can have two choices, StreetHawkInfinyTableViewDriver is first choice, UIViewController is backup choice. In this case, this StreetHawkInterceptor is needed. It has `firstResponder` for the first choice, `backupResponder` for the second choice. Create one instance of StreetHawkInterceptor, and set StreetHawkInfinyTableViewDriver as `firstResponder`, set UIViewController as `backupResponder`, make this instance as UITableView's delegate. More widely this can handle more than two choices by setup `firstResponder` or `backupResponder` to be StreetHawkInterceptor.
 
 A good quetion maybe: why use StreetHawkInfinyTableViewDriver as firstResponder, why not UIViewControlelr? This is because: StreetHawkInfinyTableViewDriver needs to control the UITableView for sure. If use UIViewController as firstResponder, some key function may get rid of StreetHawkInfinyTableViewDriver so that it cannot function well. If StreetHawkInfinyTableViewDriver needs to consider UIViewController at higher priority, it can call `backupResponder responseTo...` to let UIViewController do first. If some function not implement in StreetHawkInfinyTableViewDriver but implement in UIViewController, it still get called.
 */
@interface StreetHawkInterceptor : NSObject

/**
 Setup the first choice Responder.
 */
@property (nonatomic, weak) id firstResponder;

/**
 Setup the backup second choice Responder.
 */
@property (nonatomic, weak) id backupResponder;

/**
 Most cases the first Responder is not changed, and usually it's can be init when the controller object created, use this init for convenience.
 */
- (id)initWithFirstResponder:(id)responder;

@end
