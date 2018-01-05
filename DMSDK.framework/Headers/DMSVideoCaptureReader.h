// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import "DMSCaptureReader.h"
#import "DMSImageReaderTypes.h"
#import "DMSPayload.h"
#import "DMSImageReaderTypes.h"
#import "DMSReader.h"
#import "DMSSymbologies.h"
#import "DMSReaderResult.h"

#import <Foundation/Foundation.h>

@class DMSVideoCaptureReader;

NS_ASSUME_NONNULL_BEGIN

///Delegate protocol for handling results from a Video Capture Reader.
NS_SWIFT_NAME(VideoCaptureReaderResultsDelegate)
@protocol DMSVideoCaptureReaderResultsDelegate <NSObject>

@required
/**
 * Called when the video capture reader finds one or more results to deliver.
 *
 * @param videoCaptureReader The video capture reader that originated the result.
 * @param result One or more payloads output by the video capture reader.
 */
-(void)videoCaptureReader:(DMSVideoCaptureReader *)videoCaptureReader didOutputResult:(DMSReaderResult *)result;

@end

///The video capture reader interface is ideal for real time capture from an image source such as a camera. It vends a captureOutput that can be hooked to an existing AVFoundation capture tree. A video capture reader will automatically perform buffering and optimization necessary for a capture source. For situations in which a developer wants to have deeper control of how images are buffered or staged for detection, the synchronous image reader interface should be used. 
NS_SWIFT_NAME(VideoCaptureReader)
@interface DMSVideoCaptureReader : DMSCaptureReader

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Initializes a new video capture reader for the given symbologies.
 *
 * @param symbologies The set of symbologies the reader should attempt to detect. This is defined by the DMSSymbology set. The ImageDigimarc detector must be in the list of provided detectors.
 * @param options A dictionary of options for the reader.
 * @return Returns a new video capture reader. May return nil.
 */
-(nullable id)initWithSymbologies:(DMSSymbologies)symbologies options:(nullable NSDictionary<DMSReaderOptionKey, id> *)options;

/**
 * Sets the delegate to deliver results to.
 *
 * @param delegate A delegate to deliver results to.
 * @param queue The queue to return results onto. Applications that need to do UI tasks in response to a detection may want to pass the main queue. If delegate is not nil, passing nil for this argument will cause an exception. If delegate is nil, this argument may be ignored.
 */
-(void)setResultsDelegate:(nullable NSObject<DMSVideoCaptureReaderResultsDelegate> *)delegate queue:(nullable dispatch_queue_t)queue;
/// Returns the results delegate. Will be nil if a delegate has not been set.
@property (weak, readonly, nullable) NSObject<DMSVideoCaptureReaderResultsDelegate> *resultsDelegate;
/// Returns the queue results will be delivered on. Will be nil if a queue has not been set.
@property (readonly, nullable) dispatch_queue_t resultsQueue;

/// The symbologies to use for detection
@property DMSSymbologies symbologies;

/// If set to YES, the video capture reader will automatically apply the best capture settings for the current host to the AVCaptureDevice. Settings are applied either after this property is set to YES, or when the capture output vended by video capture reader is attached to an input device. The capture device settings may be altered multiple times. Defaults to YES.
@property BOOL automaticallyApplyBestCameraSettings;

/// Resets the reader to its default state. Any previously detected payloads will be reported as new payloads again.
-(void)reset;

/**
 * Sets symbologies and reader options.
 *
 * @param symbologies Symbologies to configure the reader to detect.
 * @param options Options to configure the reader with.
 */
-(void)setSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> *)options;

///Limits the detection area to a specific region. rectOfInterest is a normalized value that defines the region of interest between 0..1 for both the height and the width of the image. This rect interoperates with AVFoundation's rectOfInterest class of functions for converting between real pixel values and normalized values.
@property CGRect rectOfInterest;

@end

NS_ASSUME_NONNULL_END
