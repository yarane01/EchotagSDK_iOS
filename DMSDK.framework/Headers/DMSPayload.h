// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <Foundation/Foundation.h>
#import "DMSSymbologies.h"

NS_SWIFT_NAME(Payload)
/// Payload is an object that contains the result of a detection. It will contain the symbology that originated the result, an identifier unique to the symbology and the data that was found, and different possible representations of the data this code contains. 
@interface DMSPayload : NSObject <NSCoding>

#if defined(NS_EXTENSIBLE_STRING_ENUM)
NS_SWIFT_NAME(PayloadRepresentationType)
///Defines the possible representations that can be derived from a payload.
typedef NSString * _Nonnull DMSPayloadRepresentationType NS_EXTENSIBLE_STRING_ENUM;
#else
///Defines the possible representations that can be derived from a payload.
typedef NSString * _Nonnull DMSPayloadRepresentationType;
#endif

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Initializes a payload with a valid payload identifier. Will return nil if the identifier is not valid. Use a payload's identifier property to get the identifier for an existing payload. This is the designated initializer.
 *
 * @param identifier The identifier string to initialize the payload with. Must conform to Digimarc's CPM standard.
 * @return A payload object. If identifier does not conform to the CPM protocol defined by Digimarc, this initializer may return nil.
 */
-(nullable instancetype)initWithIdentifier:(nonnull NSString *)identifier NS_DESIGNATED_INITIALIZER;
/// Returns NSURL for FastPath with the given server string if it is applicable.
-(nullable NSURL *)fastPathWithServer:(nullable NSURL *)serverURL;
/// Returns the identifier for a payload. Identifiers are unique for the origin symbology and the data carried within the symbol.
@property (readonly, nonnull) NSString * identifier;
/// A map of different known representations of the data carried by the payload. See the DMPayloadRepresentationType constants for possible keys.
@property (readonly, nonnull) NSDictionary<DMSPayloadRepresentationType, NSString *> * representations;
/**
 * The symbology type that originated this payload. See the DMSSymbology enum for possible values.
 *
 * @return The symbology associated with the payload. If the payload was initialized with a valid identifier that does not conform to a known symbology, this function will return a symbology type of "unknown".
 */
@property (readonly) DMSSymbologies symbology;

@end

/*-------------------------------------------------------------------------------------*/
#pragma mark - Representation types
/*-------------------------------------------------------------------------------------*/

/// The UPCA formatted value of the payload. Available if the payload's contents are compatible with the UPCA specification.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeUPCA;
/// The UPCE formatted value of the payload. Available if the payload's contents are compatible with the UPCE specification.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeUPCE;
/// The EAN13 formatted value of the payload. Available if the payload's contents are compatible with the EAN13 specification.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeEAN13;
/// The EAN8 formatted value of the payload. Available if the payload's contents are compatible with the EAN8 specification.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeEAN8;
/// The GTIN14 formatted value of the payload. Available if the payload's contents are compatible with the GTIN4 specification.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGTIN14;
/// Contains the raw text value of the QR code. Available if the symbology is a QR code.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeQRCode;
/// Contains the raw text value of the Code 39 code. Available if the symbology is a Code 39 code.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeCode39;
/// Contains the raw text value of the Code 128 code. Available if the symbology is a Code 128 code.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeCode128;
/// Contains the raw text value of the DataBar code. Available if the symbology is a DataBar code.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeDataBar;
/// Contains the CPM path of the Digimarc audio payload. Available if the symbology is audio Digimarc.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeAudioDigimarc;
/// Contains the CPM path of the Digimarc image payload. Available if the symbology is image Digimarc.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeImageDigimarc;
/// Contains the raw value of the payload. Applies to payload types that are unstructured, such as QR codes, Code39, or Code128.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeUnstructuredData;

//SGTIN definitions

/// Key for the SGTIN96 standard value. The standard value is in the format [Company Prefix].[Indicator Digit].[Item Reference].[Serial Number]
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSGTIN96StandardFormat;
/// Key for the SGTIN96 company prefix.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSGTIN96CompanyPrefix;
/// Key for the SGTIN96 serial number.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSGTIN96SerialNumber;
/// Key for the SGTIN96 item reference.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSGTIN96ItemReference;
/// Key for the SGTIN96 indicator digit.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSGTIN96IndicatorDigit;
/// Key for the SGTIN96 filter value.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSGTIN96FilterValue;

/// Key for the DataBar formatted list value.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeDataBarFormattedList;

/*-------------------------------------------------------------------------------------*/
#pragma mark - GS1 Representations
/*-------------------------------------------------------------------------------------*/

/// The price of the item in local currency. Corresponds to GS1 AI 3922 - Amount payable for variable measure trade.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGS1AIAmountPayable;
/// The weight of the item in pounds. Corresponds to GS1 AI 3203 - Net Weight (lbs).
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGS1AIWeightInPounds;
/// The weight of the item in kilograms. Corresponds to GS1 AI 3103 - Net Weight (kg).
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGS1AIWeightInKilograms;
/// The count of items. Corresponds to GS1 AI 30 - Variable Count.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGS1AICount;
/// The sell by date. Corresponds to GS1 AI 16 - Sell by Date.
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGS1AISellByDate;

/*-------------------------------------------------------------------------------------*/
#pragma mark - Simple Product ID
/*-------------------------------------------------------------------------------------*/
/// Extra data contained in a Simple Product ID 96
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeSimpleProductID96ExtraData;

/*-------------------------------------------------------------------------------------*/
#pragma mark - Variable Measure
/*-------------------------------------------------------------------------------------*/
/// Variable Measure
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeVariableMeasure;

/*-------------------------------------------------------------------------------------*/
#pragma mark - GIAI
/*-------------------------------------------------------------------------------------*/
/// Global Individual Asset Identifier
extern const DMSPayloadRepresentationType DMSPayloadRepresentationTypeGIAI;


