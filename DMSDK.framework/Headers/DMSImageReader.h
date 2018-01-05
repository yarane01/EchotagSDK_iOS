// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import "DMSReaderResult.h"
#import "DMSImageReaderTypes.h"
#import "DMSReader.h"
#import "DMSSymbologies.h"
#import <AVFoundation/AVFoundation.h>


/*-------------------------------------------------------------------------------------*/
#pragma mark - Image Reader Options
/*-------------------------------------------------------------------------------------*/

///Option key for setting the inverted read interval rate as an NSNumber. Some symbologies, such as the barcode symbologies, need to be configured to detect white-on-black codes in addition to black-on-white codes. Inverted codes will be read at an interval of 1/value, where 0 will configure applicable symbologies to never detect inverted symbols.
extern const DMSReaderOptionKey DMSImageReaderOptionInvertedReadIntervalKey;
///Option key for setting a strategy. The strategy will control how the reader performs detections, and how often it performs detections.
extern const DMSReaderOptionKey DMSImageReaderOptionStrategyKey;

///Option key for setting the Server key for image recognition services. The image recognition feature is beta, and available by invitation only. If the image recognition symbology is set, a Server key must be provided. Contact Digimarc for more information.
extern const DMSReaderOptionKey DMSImageReaderOptionImageRecognitionServerKey;

///Option key for setting the API key/token to authenticate to the image recognition server. If the Digimarc production or labs servers are being used, this key is unncessary.
extern const DMSReaderOptionKey DMSImageReaderOptionImageRecognitionTokenKey;

NS_SWIFT_NAME(ImageRecognitionServerKey)
#if defined(NS_EXTENSIBLE_STRING_ENUM)
NS_SWIFT_NAME(ImageRecognitionServerKey)
///Defines the server key type for image recognition
typedef NSString * _Nonnull const DMSImageRecognitionServer NS_EXTENSIBLE_STRING_ENUM;
#else
///Defines the server key type for image recognition
typedef NSString * _Nonnull const DMSImageRecognitionServer;
#endif

//The Digimarc production image recognition server. Access to this server is provided by invitation only, and the image recognition feature is beta. Contact Digimarc for more information.
extern const DMSImageRecognitionServer _Nonnull DMSImageRecognitionServerProduction;
//The Digimarc pre-production image recognition server. Access to this server is provided by invitation only, and the image recognition feature is beta. Contact Digimarc for more information.
extern const DMSImageRecognitionServer _Nonnull DMSImageRecognitionServerLabs;




///The available strategies to use with an image reader. Strategies control how many frames are processed and how efficient a reader will be.
typedef NS_ENUM(NSInteger, DMSReaderStrategy)
{
    ///Optimize the reader for performing detections on a stream of images from a device such as a camera, and drop frames as necessary to improve device energy consumption and battery life.
    DMSReaderStrategyManagedStream,
    ///Optimize the reader for performing detections on a stream of images from a device such as a camera, and perform a detection on every single frame without skipping any frames. This is more expensive, and might do more processing than is necessary for detection, but could be more optimal for an existing image pipeline that does its own frame handling and dropping.
    DMSReaderStrategyUnmanagedStream,
    ///Assume that each image is entirely discrete and not part of a series or stream. This is useful for detecting on image files. The reader may follow more expensive or more comprehensive paths that are not useful for camera detection but are useful for file detection, including detection at multiple scales and multiple resolutions.
    DMSReaderStrategyDiscreteImages
};

NS_SWIFT_NAME(ImageReader)
/// Image readers synchronously process images and will return an array of payload classes that reflect the results found in the image. An image reader takes a CMSampleBuffer as input, which is the native media type of camera and video frames on iOS. The image will accept CMSampleBufferRefs that contain any image format, but the reader will work the most efficiently when the sample buffers contain an image in a YpCbCr8:420 Bi Planar format. AVFoundation can be configured to return CMSampleBufferRefs in this format directly.
@interface DMSImageReader : DMSReader

NS_ASSUME_NONNULL_BEGIN

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Initializes a new image reader for the given symbologies.
 *
 * @param symbologies The set of symbologies the reader should attempt to detect. This is defined by the DMSSymbology set. The ImageDigimarc detector must be in the list of provided detectors.
 * @param options A dictionary of options for the reader. 
 * @return Returns a new image detector. May return nil.
 */
-(nullable instancetype)initWithSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> *)options;

/**
 * Processes a single sample buffer and returns either an empty array, or an array of results as payload objects.
 *
 * @param buffer The sample buffer to process. Should be YpCbCr8:420 Bi Planar for maximum performance.
 * @param error An error resulting from processing the sample buffer. Examples of errors include being unable to handle the CMSampleBuffer, or being passed a sample buffer that does not contain an image.
 * @return A reader result containing zero or more payloads. Returns null if an error occurred.
 */
-(nullable DMSReaderResult *)processSampleBuffer:(CMSampleBufferRef)buffer error:(NSError  * _Nullable * _Nullable)error;

#ifdef TARGET_OS_IOS
/**
 * Processes a single UIImage and returns either an empty array, or an array of results as payload objects. Processing UIImages is much slower than processing CMSampleBufferRefs due to the required conversions. Performance may not be adequate for real time processing. If frames are received originally as a CMSampleBufferRef from a source like AVFoundation, it's highly recommended to use the CMSampleBufferRef, ideally in YpCbCr. UIImages received by the image reader will be processed as part of the same image stream of any CMSampleBufferRefs. Results from UIImages passed to the image reader could impact results from the CMSampleBuffers. If you are processing images from two separate sources at once it is highly recommended that you create an image reader for each source.
 *
 * @param image The UIImage to process.
 * @param error An error resulting from processing the sample buffer. Examples of errors include being unable to handle the CMSampleBuffer, or being passed a sample buffer that does not contain an image.
 * @return An reader result containing zero or more payloads. Returns null if an error occurred.
 */
-(nullable DMSReaderResult *)processImage:(UIImage *)image error:(NSError  * _Nullable * _Nullable)error;
#endif

/// Resets the reader to its default state. Any previously detected payloads will be reported as new payloads again.
-(void)reset;

/// The symbologies that the image reader is configured to detect.
@property DMSSymbologies symbologies;

/**
 * Sets symbologies and reader options.
 *
 * @param symbologies Symbologies to configure the reader to detect.
 * @param options Options to configure the reader with.
 */
-(void)setSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> *)options;

///Limits the detection area to a specific region. rectOfInterest is a normalized value that defines the region of interest between 0..1 for both the height and the width of the image. This rect interoperates with AVFoundation's rectOfInterest class of functions for converting between real pixel values and normalized values.
@property CGRect rectOfInterest;

NS_ASSUME_NONNULL_END

@end
