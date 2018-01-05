// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMSTypes_h
#define DMSTypes_h 

/// An enum of symbologies that DMSDK supports. Can be used to configure readers, or used to query the originating symbology in a payload.
typedef NS_OPTIONS(NSUInteger, DMSSymbologies) {
    /// An unknown symbology. Generally not used as a configuration option. Instead may be returned from classes when the symbology is ambiguous.
    DMSSymbologyUnknown = 1 << 0,
    /// The Digimarc Barcode image symbology. Compatible with image detectors.
    DMSSymbologyImageDigimarc = 1 << 1,
    /// The UPCA symbology type. Compatible with image detectors.
    DMSSymbologyUPCA = 1 << 2,
    /// The UPCE symbology type. Compatible with image detectors. Please note that using this detector type is subject to additional licensing based on unique user count. Refer to our website for more information or contact Digimarc through the Developer Forum. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyUPCE = 1 << 3,
    /// The EAN13 symbology type. Compatible with image detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyEAN13 = 1 << 4,
    /// The EAN8 symbology type. Compatible with image detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyEAN8 = 1 << 5,
    /// The DataBar symbology type. Compatible with image detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyDataBar = 1 << 6,
    /// The QR code symbology type. Compatible with image detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyQRCode = 1 << 7,
    /// The Code 39 code symbology type. Compatible with image detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyCode39 = 1 << 8,
    /// The Code 128 code symbology type. Compatible with image detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyCode128 = 1 << 9,
    /// Image recognition "symbol" type. Image recognition is a beta feature by invitation only. This symbology type uses cloud services to perform image analysis and match against developer supplied images. Use of this symbol with a detector requires that a image recognition API key also be provided as an option. Contact Digimarc for more information.
    DMSSymbologyImageRecognition = 1 << 10,
    /// A symbology for recognizing Smart Label symbols on packages. SmartLabel™ detection is a beta feature. Contact Digimarc for more information.
    DMSSymbologySmartLabel = 1 << 11,
    /// The Digimarc Barcode for audio symbology. Compatible with audio detectors. Usage is subject to the Traditional Barcode licensing terms.
    DMSSymbologyAudioDigimarc = 1 << 24,
    /// All traditional barcode detection types. Does not include image Digimarc or other invisible codes. This includes symbologies that are subject to the Traditional Barcode licensing terms.
    DMSSymbologyAllBarcodes = DMSSymbologyUPCA | DMSSymbologyUPCE | DMSSymbologyEAN13 | DMSSymbologyEAN8 | DMSSymbologyDataBar | DMSSymbologyQRCode | DMSSymbologyCode39 | DMSSymbologyCode128,
    /// All audio detector types.
    DMSSymbologyAllAudio = DMSSymbologyAudioDigimarc,
    /// All image detector types that can be run local on the device with no cloud interaction. This includes symbologies that are subject to the Traditional Barcode licensing terms.
    DMSSymbologyAllLocalImage = DMSSymbologyAllBarcodes | DMSSymbologyImageDigimarc | DMSSymbologySmartLabel,
    /// All image detector types. This includes symbologies that are subject to the Traditional Barcode licensing terms.
    DMSSymbologyAllImage = DMSSymbologyAllLocalImage | DMSSymbologyImageRecognition
} NS_SWIFT_NAME(Symbologies);

#endif /* Header_h */
