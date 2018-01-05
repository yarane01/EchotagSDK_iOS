// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <DMSDK/DMSDK.h>

@class DMSAudioCaptureReader;

NS_ASSUME_NONNULL_BEGIN

///Delegate protocol for handling results from an Audio Capture Reader.
NS_SWIFT_NAME(AudioCaptureReaderResultsDelegate)
@protocol DMSAudioCaptureReaderResultsDelegate <NSObject>

@required
/**
 * Called when the audio capture reader finds one or more results to deliver.
 *
 * @param audioCaptureReader The audio capture reader that originated the result.
 * @param result A reader result output by the audio capture reader.
 */
-(void)audioCaptureReader:(DMSAudioCaptureReader *)audioCaptureReader didOutputResult:(DMSReaderResult *)result;

@end

///The audio capture reader interface is ideal for real time capture from an audio source such as a microphone. It vends a captureOutput that can be hooked to an existing AVFoundation capture tree. An audio capture reader will automatically perform buffering and optimization necessary for a capture source. For situations in which a developer wants to have deeper control of how audio is buffered or staged for detection, the synchronous audio reader interface should be used.
NS_SWIFT_NAME(AudioCaptureReader)
@interface DMSAudioCaptureReader : DMSCaptureReader

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Initializes a new image reader for the given symbologies.
 *
 * @param symbologies The set of symbologies the reader should attempt to detect. This is defined by the DMSSymbology set.
 * @param options A dictionary of options for the reader.
 * @return Returns a new audio detector. May return nil.
 */
-(nullable id)initWithSymbologies:(DMSSymbologies)symbologies options:(nullable NSDictionary<DMSReaderOptionKey, id> *)options;

/**
 * Sets the delegate to deliver results to.
 *
 * @param delegate A delegate to deliver results to.
 * @param queue The queue to return results onto. Applications that need to do UI tasks in response to a detection may want to pass the main queue. If delegate is not nil, passing nil for this argument will cause an exception. If delegate is nil, this argument may be ignored.
 */
-(void)setResultsDelegate:(nullable NSObject<DMSAudioCaptureReaderResultsDelegate> *)delegate queue:(nullable dispatch_queue_t)queue;
/// Returns the results delegate. Will be nil if a delegate has not been set.
@property (weak, readonly, nullable) NSObject<DMSAudioCaptureReaderResultsDelegate> *resultsDelegate;
/// Returns the queue results will be delivered on. Will be nil if a queue has not been set.
@property (readonly, nullable) dispatch_queue_t resultsQueue;

/// The symbologies to use for detection
@property DMSSymbologies symbologies;

/// Resets the reader to its default state. Any previously detected payloads will be reported as new payloads again.
-(void)reset;

/**
 * Sets symbologies and reader options.
 *
 * @param symbologies Symbologies to configure the reader to detect.
 * @param options Options to configure the reader with.
 */
-(void)setSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> *)options;

@end

NS_ASSUME_NONNULL_END
