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

typedef enum
{
    STREETHAWK_FIELD_KEY,  //integer and self increase
    STREETHAWK_FIELD_BOOL,
    STREETHAWK_FIELD_SHORT,
    STREETHAWK_FIELD_INT,
    STREETHAWK_FIELD_DOUBLE,
    STREETHAWK_FIELD_DATETIME,
    STREETHAWK_FIELD_STRING,
    STREETHAWK_FIELD_TEXT,
    STREETHAWK_FIELD_DATA,
    STREETHAWK_FIELD_OBJECT,       //foreign Key Field, saved as StreetHawkItem:ABC
    STREETHAWK_FIELD_COUNT,
} StreetHawkFieldType;

typedef struct {
    StreetHawkFieldType fieldType;
    int fieldLength;
    const char *fieldName;
} StreetHawkField;

/**
 * Helper to create StreetHawk fields for serializable models.
 */
extern StreetHawkField StreetHawkMakeField(StreetHawkFieldType type, int length, const char *name);

@protocol StreetHawkFieldList<NSObject>

/**
 * Get the value of the field at a given index for the instance.
 */
-(NSObject *)fieldValueAtIndex:(int)index;

/**
 * Set the value of a field at a given index.
 */
-(void)setFieldValue:(NSObject *)value forIndex:(int)index;

@end

@protocol StreetHawkModelSchema<NSObject>

/**
 * The default model name for this schema.
 */
-(NSString *)defaultModelName;

/**
 * Name of the model.
 */
-(NSString *)modelNameForInstance:(id)instance;

/**
 * Number of fields.
 */
- (int)fieldCount;

/**
 * Get the field info at a given index.
 */
-(StreetHawkField)fieldAtIndex:(int)index;

/**
 * Gets the field index for a given name.
 */
-(int)fieldIndexByName:(NSString *)name;

/**
 * Gets the fields array.
 */
-(StreetHawkField *)fields;

@end

/**
 * Model objects are those that can be serialized.
 */
@protocol StreetHawkModel<StreetHawkFieldList>

/**
 * Returns the schema for this model.
 */
+(id<StreetHawkModelSchema>)modelSchema;

@property (nonatomic, readonly) id<StreetHawkModelSchema> modelSchema;

/**
 * Name of the model.
 */
@property (nonatomic, readonly) NSString *modelName;

@end

@interface StreetHawkModelSchema : NSObject<StreetHawkModelSchema>
@end
