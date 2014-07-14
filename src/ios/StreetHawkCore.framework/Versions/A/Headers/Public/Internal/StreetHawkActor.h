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
 The action to launch safari and show a web page. Parameters:
 action = @"opensafari"
 objectData = NSString type, for example @"www.google.com" or @"https://www.some.com". If it does not contain the protocal prefix @"://", default @"http://" will be added. But if it's not http protocal, must have the complete address.
 objectType = nil, not need it.
 assocData = nil, not need it.
 fromVC = nil, not need it. 
 */
#define STREETHAWK_ACTION_OPEN_SAFARI @"opensafari"

/**
 The action to launch AppStore and direct to one App for download or upgrade. Parameters:
 action = @"openappstore"
 objectData = NSString type, app's id, for example @"507040546". If the id is nil, open AppStore for current App (must have StreetHawk.itunesAppId setup).
 objectType = nil, not need it.
 assocData = nil, not need it.
 fromVC = nil, not need it.
 */
#define STREETHAWK_ACTION_OPEN_APPSTORE @"openappstore"

/**
 The action to call a telephone. Parameters:
 action = @"callphone"
 objectData = NSString type, telephone number, for example @"862138653530".
 objectType = nil, not need it.
 assocData = nil, not need it.
 fromVC = nil, not need it.
 */
#define STREETHAWK_ACTION_CALL_PHONE @"callphone"

/**
 The action to show alert settings. Parameters:
 action = @"alertsettings"
 objectData = nil, not need it.
 objectType = nil, not need it.
 assocData = nil, not need it.
 fromVC = nil, not need it. The modal dialog present regardless of current VC.
 */
#define STREETHAWK_ACTION_ALERTSETTINGS   @"alertsettings"

/**
 The callback for feedback input dialog.
 @param isSubmit If user want to continue submit, set YES; otherwise cancel submit.
 @param title The title of this feedback, mandatory.
 @param content The text input in the feedback dialog, optional.
 */
typedef void (^StreetHawkFeedbackInputHandler)(BOOL isSubmit, NSString *title, NSString *content);

/**
 Protocol for all feedback input view controller must implement.
 */
@protocol StreetHawkFeedbackInput <NSObject>

@required

/**
 The handler to notice input result of feedback dialog.
 */
@property (nonatomic, copy) StreetHawkFeedbackInputHandler inputHandler;

@end

/**
 Block handler for dealing with an action.
 @param action Mandatory, must match the action from actor router. For example "view".
 @param objectData Optional, it's the dealing object. For example an StreetHawkProduct object.
 @param objectType Optional, it's the dealing object type. If object is not nil, this can pass nil and also got by [object class]. But sometimes object is nil, thus need to pass type.
 @param assocData Optional, it's a way to pass some data when dealing with this object, most cases are dictionary defined by each behaviour. For example, when open StreetHawkProduct to view, it can pass an shop's telephone number to used by call the store.
 @param fromVC The current VC, which can be used as navigation push or modal present VC. If fromVC=nil, use windows rootVC.
 @return YES means the action is handled; NO means no suitable behaviour for these pass in data.
 */
typedef BOOL (^StreetHawkActionHandler)(NSString *action, id objectData, Class objectType, id assocData, UIViewController *fromVC);

/**
 Actor class for dealing wiht an action.
 */
@interface StreetHawkActor : NSObject

/**
 Refer to `StreetHawkApp` function `-(BOOL)kickOffAction:(NSString *)action forObject:(id)objectData forType:(Class)objectType withData:(id)assocData fromVC:(UIViewController *)fromVC`.
 */
-(BOOL)handleAction:(NSString *)action forObject:(id)objectData forType:(Class)objectType withData:(id)assocData fromVC:(UIViewController *)fromVC;

/**
 Add one display VC and action/object type into dictionary. Key is action and object type [action:object_type], value is display VC class. Set a displayVC=nil remove the existing one in dictionary.
 */
-(void)setDisplayVC:(Class)displayVC forObjectType:(Class)type forAction:(NSString *)action;

/**
 Use action and object type to find display VC.
 */
-(Class)displayVCForType:(Class)type forAction:(NSString *)action;

/**
 Use action and object type to find display VC.
 */
-(Class)displayVCForObject:(id)object forAction:(NSString *)action;

@end

/**
 Refer to `StreetHawkApp` property `actorRouter`.
 */
@interface StreetHawkActorRouter : NSObject

/**
 Refer to `StreetHawkApp` function `-(void)setHandler:(StreetHawkActionHandler)handler forAction:(NSString *)action`.
 */
-(void)setHandler:(StreetHawkActionHandler)handler forAction:(NSString *)action;

/**
 Refer to `StreetHawkApp` function `-(void)setActor:(StreetHawkActor *)actor forAction:(NSString *)action`.
 */
-(void)setActor:(StreetHawkActor *)actor forAction:(NSString *)action;

/**
 According to the action, search for the handler block or actor in dictionary. If cannot find a match one, return nil.
 */
-(id)handlerOrActorForAction:(NSString *)action;

@end


