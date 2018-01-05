// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2016
//
// - - - - - - - - - - - - - - - - - - - -


#import <Foundation/Foundation.h>
#import "DMSPayload.h"

#if defined(NS_EXTENSIBLE_STRING_ENUM)
NS_SWIFT_NAME(DMSDataBarAI)
///Type that defines the possible application identifers that can be parsed from a DataBar encoded payload.
typedef NSString * _Nonnull const DMSDataBarAI NS_EXTENSIBLE_STRING_ENUM;
#else
///Type that defines the possible application identifers that can be parsed from a DataBar encoded payload.
typedef NSString * _Nonnull const DMSDataBarAI;
#endif


/*-------------------------------------------------------------------------------------*/
#pragma mark - DataBar Application Identifier Types
/*-------------------------------------------------------------------------------------*/

/** Key to the GS1 Application Identifier (AI).
 */
extern const DMSDataBarAI DMSDataBarAINumber;

/** Key for the DataBar value
 */
extern const DMSDataBarAI DMSDataBarAIValue;

/** Key for the English Description
 */
extern const DMSDataBarAI DMSDataBarAIDescription;

/** Inspects payloads that contain DataBar information.
 */
NS_SWIFT_NAME(DataBarParser)
@interface DMSDataBarParser : NSObject

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/** 
* The DataBar application identifier as an array of dictionaries.
*
* @return Array of dictionaries whose contents are described by the DataBar AI dictionary keys.
*/
@property (nonnull, readonly) NSArray<NSDictionary<DMSDataBarAI, NSString *> *>* dataBarAIs;


/**
* Formats and prints the list of DataBar Application (AI) in parenthesized format
*
* @return String of the DataBar with the AI's surrounded with parenthesis and followed by the value.
*/
@property (nonnull, readonly) NSString* formattedAIString;


/** 
* Convenience initializer for creating a parser.
*
* @param payload A DataBar payload. If the payload does not contain DataBar information, nil will be returned.
* @return A newly created DataBar info object. If the payload does not contain DataBar information, returns nil.
*/
+ (nullable instancetype) parserWithPayload:(nonnull DMSPayload*)payload;

/**
* Initializer for creating a parser.
*
* @param payload A DataBar payload. If the payload does not contain DataBar information, nil will be returned.
* @return A newly created DataBar info object. If the payload does not contain DataBar information, returns nil.
*/
- (nullable instancetype) initWithPayload:(nonnull DMSPayload*)payload;

@end

