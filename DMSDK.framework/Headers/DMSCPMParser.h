// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <Foundation/Foundation.h>
#import "DMSSymbologies.h"

/*-------------------------------------------------------------------------------------*/
#pragma mark - CPM Path Components
/*-------------------------------------------------------------------------------------*/

/// Defines the fields returned by the pathComponents array
typedef NS_ENUM(NSInteger, DMSCPMComponent) {
    ///The grid value of the CPM path
    DMSCPMComponentGrid,
    //Protocol is a reserved word in Swift, can't name an enum member that right now.
    ///The protocol value of the CPM path
    DMSCPMComponentProtocol NS_SWIFT_NAME(CPMProtocol),
    ///The key value of the CPM path
    DMSCPMComponentKey,
    ///The version value of the CPM path
    DMSCPMComponentVersion,
    ///The value component of the CPM path. Represents the raw value the CPM path carries.
    DMSCPMComponentValue
} NS_SWIFT_NAME(CPMComponent);

NS_ASSUME_NONNULL_BEGIN

/// Class for parsing CPM paths. This is for very advanced usage of CPM. Most developers will not need to parse CPM, and some CPM values are not usable without additional processing. Unless there is a very specific need for parsing a CPM field, the Payload class can provide values for most usages. Generally, developers should treat CPM as a generic identifier and not need to deconstruct the format.
NS_SWIFT_NAME(CPMParser)
@interface DMSCPMParser : NSObject
/// Initializes with a CPM path. Returns nil if the CPM path is not valid.
-(nullable id)initWithCPMPath:(nonnull NSString *)CPMPath;
/// Returns an array of path components. DMSCPMComponent describes the component at each index.
@property (readonly) NSArray<NSString *> *pathComponents;
/// Returns the Subtype of a given CPM Path if applicable. If the subtype isn't available, 0 is returned.
@property (readonly) NSString * _Nonnull subtype;
/// Returns the value of a given subtype for a given payload version. Returns nil if not applicable to the CPM path.
-(nullable NSString *)valueForVersion:(NSString *)version subtype:(NSString *)subtype;

@end

NS_ASSUME_NONNULL_END
