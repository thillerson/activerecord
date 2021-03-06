////////////////////////////////////////////////////////////////////////////////////////////
//
//  ARRelationship.h
//   ARRelationship is an abstract superclass for defining relationships
//   between models.
//
////////////////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2007, Fjölnir Ásgeirsson
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, 
// are permitted provided that the following conditions are met:
// 
// Redistributions of source code must retain the above copyright notice, this list of conditions
// and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, this list of
// conditions and the following disclaimer in the documentation and/or other materials provided with 
// the distribution.
// Neither the name of Fjölnir Ásgeirsson, ninja kitten nor the names of its contributors may be 
// used to endorse or promote products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef _ARRELATIONSHIP_H_
#define _ARRELATIONSHIP_H_

#import <Foundation/Foundation.h>
#import <ActiveRecord/ARBase.h>

/*!
 * The abstract superclass for writing ActiveRecord relationships.
 * ARRelationship itself implements no relationship, that's handled by it's subclassses\n
 * You will most likely not need to use a relationship directly (except when creating it) since
 * ARBase's retrieval/sending methods handle finding and writing to relationships
 */
@interface ARRelationship : NSObject {
  NSString *name;
  NSString *className;
  ARBase *record;
}
@property(readwrite, retain) NSString *name, *className;
@property(readwrite, retain) ARBase *record;

/*!
 * Creates a relationship with a given name using the passed class
 * (instead of determining the class name from the relationship name. <b>Currently unimplemented</b>)
 * @param aName The name of the relationship,
 * @param aClassName The class name to use (nil => class name determined from relationship name)
 */
+ (id)relationshipWithName:(NSString *)aName className:(NSString *)aClassName;
/*!
 * Creates a relationship with a given name.
 * @param aName The name of the relationship,
 */
+ (id)relationshipWithName:(NSString *)aName;
/*! @copydoc relationshipWithName: */
- (id)initWithName:(NSString *)aName className:(NSString *)aClassName;

/*!
 * Returns wether the relationship supports the passed key and wether it supports adding/removing for it
 * @param supportsAddingRet A BOOL pointer, will be set to YES/NO depending on wether adding/removing is supported
 */
- (BOOL)respondsToKey:(NSString *)key supportsAdding:(BOOL *)supportsAddingRet;
/*!
 * Returns wether the relationship supports the passed key 
 */
- (BOOL)respondsToKey:(NSString *)key;
/*! Retrieves a record for a given key */
- (id)retrieveRecordForKey:(NSString *)key;
/*! 
 * Retrieves a record for a given key by applying the passed filters 
 * @param key A valid key, can refer to either a column or a relationship
 * @param whereSQL A valid SQL WHERE statement (omitting the actual "WHERE")
 * @param orderSQL A valud SQL ORDER statement (omitting the actual "ORDER BY")
 * @param limit The maximum number of records to retrieve
 */
- (id)retrieveRecordForKey:(NSString *)key 
										filter:(NSString *)whereSQL 
										 order:(NSString *)orderSQL
										 limit:(NSUInteger)limit;																								 
- (void)sendRecord:(id)record forKey:(NSString *)key;
- (void)addRecord:(id)record forKey:(NSString *)key;
- (void)removeRecord:(id)record forKey:(NSString *)key;
@end

@interface ARBase (Relationships)
- (NSArray *)relationshipsOfType:(NSString *)type;
@end
#endif /* _ARRELATIONSHIP_H_ */
