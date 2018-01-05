// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

#import "DMSReader.h"
#import "DMSReaderResult.h"


///Option key that instructs the reader to attach the frame that the detection was performed on to the read result. The default value is discard all. Frames that are passed as part of the read result will only be valid inside of the result callback block. A delay on the queue that result callbacks are being dispatched to could result in a high amount of memory being consumed as read results wait for processing. Use the frames with results options to mitigate memory usage issues and only return images when necessary. For detectors that require multiple sample buffers, such as audio detectors, the retained sample buffer will be only the most recent sample buffer used to finalize the detection.
extern const DMSReaderOptionKey DMSReaderOptionFrameRetentionKey;

///These option values correspond to the frame retention option for readers.
typedef NS_ENUM(NSUInteger, DMSReaderFrameRetentionOption) {
    ///Discard all sample buffers after processing. Read results will always contain a nil value for the sample buffer property.
    DMSReaderFrameRetentionOptionDiscardAll,
    ///Retain all sample buffers after processing. Read results will always contain a value for the sample buffer property.
    DMSReaderFrameRetentionOptionRetainAll,
    ///Retain all sample buffers after processing when a result is detected in the sample buffer. Read results will contain a value for the sample buffer property only when a detection result is found.
    DMSReaderFrameRetentionOptionRetainSampleBuffersWithResults,
    ///Retain all sample buffers after processing when a result is detected in the sample buffer. Read results will contain a value for the sample buffer property only when a new detection result is found.
    DMSReaderFrameRetentionOptionRetainSampleBuffersWithNewResults
} NS_SWIFT_NAME(ReaderFrameRetentionOption);

NS_SWIFT_NAME(CaptureReader)
/// Capture readers are a family of classes meant to be used directly with AVFoundation capture trees. DMSCaptureReader cannot be instantiated directly. Instead use one of the subclasses.
@interface DMSCaptureReader : NSObject

/**
 * A capture output that can be added to an AVFoundation capture tree. Details about this capture output will depend on the subclass used.
 */
@property (readonly, nonnull) AVCaptureOutput *captureOutput;

/// Enables or disables a capture reader. A disabled capture reader will stop processing frames and no longer output results. Defaults to yes.
@property BOOL enabled;

@end
