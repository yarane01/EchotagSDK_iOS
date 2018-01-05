// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMSResolvedContent_h
#define DMSResolvedContent_h

#import "DMSResolvedContentItem.h"

/**
	Represents the resolved content metadata returned from a resolve.
 */

NS_SWIFT_NAME(ResolvedContent)
@interface DMSResolvedContent : NSObject

/** An array of resolved content items that were returned by the resolver. Sorted in order of relevance, so the first item will be the most relevant.
 */
@property(nonatomic, copy, readonly, nonnull) NSArray<DMSResolvedContentItem *> *resolvedContentItems;

/** A complete dictionary object of the raw JSON.
 */
@property(nonatomic, copy, readonly, nullable) NSDictionary *rawResolvedContent;

/** A complete dictionary object of the product details data.
 */
@property(nonatomic, copy, readonly, nullable) NSDictionary *productDetails;

/** A string representation of the logical Digimarc Barcode internal identifier associated with this resolved content in the Digimarc Barcode Manager database. In some cases, the Digimarc Barcode Manager may return the same resolved content for more than one payload. For example, a registered GTIN product code resolved content may have both the Digimarc Image v7 watermark and the equivalent UPC-A/UPC-E/EAN8/EAN13 representations. In this case, the resolver will return the same resolved content for several payload query requests. The application may use the correlation key to detect this scenario and optionally retain only one of the payload/resolved content pairs in their reading history. This field is not always provided by Digimarc Barcode Manager nor by some forms of synthesized resolved content.
 */
@property (nonatomic, retain, readonly, nonnull) NSString * correlationKey;

@end

#endif
