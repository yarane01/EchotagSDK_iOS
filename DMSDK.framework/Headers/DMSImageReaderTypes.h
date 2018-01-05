//
//  DMSImageReaderTypes.h
//  DMSDK
//
//  Created by Cornaby, Colin on 3/14/16.
//  Copyright © 2016 Digimarc. All rights reserved.
//

#ifndef DMSImageReaderTypes_h
#define DMSImageReaderTypes_h

#import <Foundation/Foundation.h>

///Error codes that could be returned as part of an error from an ImageReader
typedef NS_ENUM(NSInteger, DMSImageReaderErrorCode) {
    ///Signifies that the image passed is not in a format that can be read.
    DMSImageReaderErrorCodeInvalidFormat
} NS_SWIFT_NAME(ImageReaderErrorCode);

#endif /* DMSImageReaderTypes_h */
