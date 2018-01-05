// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <Foundation/Foundation.h>
#import <CoreMedia/CoreMedia.h>
#import "DMSPayload.h"

#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
#endif


/**
 * The ReaderResult class wraps data that is returned from a Reader class. This includes the payloads, which represent each different symbol found in the processed image frame. A ReaderResult may contain some or no payloads. In addition, a ReaderResult may contain additional metadata that is specific to the detection operation, such as timing information.
 * A ReaderResult may asynchrounously add more Payloads after it's been returned from a reader. Payloads that can be found locally on the device will be immediately available, while payloads that require additional resources such as cloud resources might be added asynchronously. The deferredPayloadResultsQueue contains an operation for each potential payload that is still being search for in the frame. If you would like to syncronize against any potential payloads that are still being processed, there are several options.
 
  -   The waitForAllDeferredPayloads option will pause the current thread and continue execution once the remaining potential payloads have been processed.
  -   The deferredPayloadResultsQueue that will contain an operation for each potential new payload, and can be inspected or have additional task dependencies added by a developer.
  -   The payloads property is KVO compliant, so changes to the payloads can be observed.
 */
NS_SWIFT_NAME(ReaderResult)
@interface DMSReaderResult : NSObject

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * The time at which the reader result was recorded. This time is in the context of the stream that originated the image. If the image that was passed for detection contained no timing metadata, the value is kCMTimeInvalid.
 */
@property CMTime time;
/**
 * The payloads detected by the reader.
 */
@property (nonnull, readonly, copy) NSArray<DMSPayload *> *payloads;
/**
 * Payloads that likely entered into frame, assuming images are being passed in a sequential stream. This includes both payloads being seen for the first time, and payloads that have not been seen for an indeterminate amount of time, but are being seen again. If images are not being passed into the reader sequentially, or the source is not a capture session, this property should be ignored.
 */
@property (nonnull, readonly, copy, getter=newPayloads) NSArray<DMSPayload *> *newPayloads;

/// The sample buffer that the read was performed on. This property is transient, and ReaderResult will not retain the sample buffer. For capture readers, this property will only be available inside of the context of the capture reader delegate result method.
@property (nullable, readonly) CMSampleBufferRef sourceSampleBuffer;

#if TARGET_OS_IOS
/// Returns the source sample buffer as a UIImage. Returns nil if the source sample buffer is not image data, or if the source sample buffer has been released.
-(nullable UIImage *)newImageFromSourceSampleBuffer;
#endif

///  :nodoc:
-(nonnull NSArray<DMSPayload *> *)newPayloads __attribute__((objc_method_family(none)));

/// A queue containing an operation for detection operations that are executing asynchronously. Operations in this queue may be using resources from remote or cloud resources. After a ReaderResult is returned by a reader, new operations will not be added to a queue. All operations in the queue will represent the total amount of outstanding work. If there are no operations in this queue, no deferred payloads will be added.
@property (readonly, nonnull) NSOperationQueue *deferredPayloadResultsQueue;

/// Pauses the current thread until all deferred payloads have been loaded. Returns an array of any new payloads that were found while the thread was paused.
-(NSArray<DMSPayload *> * _Nonnull)waitForAllDeferredPayloads;

/// Array of errors that occured as a result of detection operations. This array could contain multiple errors for different symbology types. KVO compliant.
@property (readonly, nonnull) NSArray<NSError *> * errors;

NS_SWIFT_NAME(ResultMetadataType)
#if defined(NS_EXTENSIBLE_STRING_ENUM)
///Defines the options that can be used with a reader.
typedef NSString * _Nonnull const DMSResultMetadataType NS_EXTENSIBLE_STRING_ENUM;
#else
///Defines the options that can be used with a reader.
typedef NSString * _Nonnull const DMSResultMetadataType;
#endif

///Some grid based payloads that repeat across a plane may have a scale attribute. This attribute is the relative size of the grid to image frame. Payloads with scale do not usually have a clear bounding rectangle for detection. Scale does not currently apply to any audio payloads. The value is a float.
extern const DMSResultMetadataType DMSResultMetadataTypeScale;
///Rotation of a given payload. Rotation may be applicable for payloads that are formed by a repeating grid. These payloads don't have a clear detection bounding box, but the plane of the grid may have an angle relative to the image frame. The value is a float.
extern const DMSResultMetadataType DMSResultMetadataTypeRotation;


/**
 * Rotation of a given payload. Rotation may be applicable for payloads that are formed by a repeating grid. These payloads don't have a clear detection bounding box, but the plane of the grid may have an angle relative to the image frame.
 *
 * @param payload The payload to return the metadata for. The payload must be a member of the read result's payloads and cannot be a copy.
 * @return The metadata dictionary of the payload. The keys of the dictionary are defined by the result metadata types.
 */
-(nonnull NSDictionary<DMSResultMetadataType, id> *)metadataForPayload:(nonnull DMSPayload *)payload;

@end
