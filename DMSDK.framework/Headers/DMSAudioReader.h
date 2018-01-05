// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <Foundation/Foundation.h>
#import <DMSDK/DMSReader.h>
#import <DMSDK/DMSSymbologies.h>
#import <DMSDK/DMSReaderResult.h>

/// Audio readers synchronously process images and will return an array of payload classes that reflect the results found. An audio reader takes a CMSampleBuffer as input.
NS_SWIFT_NAME(AudioReader)
@interface DMSAudioReader : DMSReader

NS_ASSUME_NONNULL_BEGIN

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/**
 * Initializes a new image reader for the given symbologies.
 *
 * @param symbologies The set of symbologies the reader should attempt to detect. This is defined by the DMSSymbology set.
 * @param options A dictionary of options for the reader. No keys are currently defined.
 * @return Returns a new audio detector. May return nil.
 */
-(nullable id)initWithSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> *)options;

/**
 * Processes a single sample buffer and returns either an empty array, or an array of results as payload objects.
 *
 * @param buffer The sample buffer to process. Should be YpCbCr8:420 Bi Planar for maximum performance.
 * @param error An error resulting from processing the sample buffer. Examples of errors include being unable to handle the CMSampleBuffer, or being passed a sample buffer that does not contain an image.
 * @return A reader result containing zero or more payloads. Returns null if an error occurred.
 */
-(nullable DMSReaderResult *)processSampleBuffer:(CMSampleBufferRef)buffer error:(NSError  * __nonnull * _Nullable)error;

/// Resets the reader to its default state. Any previously detected payloads will be reported as new payloads again.
-(void)reset;

/**
 * Sets symbologies and reader options.
 *
 * @param symbologies Symbologies to configure the reader to detect.
 * @param options Options to configure the reader with.
 */
-(void)setSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> *)options;

/// The symbologies to use for detection
@property DMSSymbologies symbologies;

NS_ASSUME_NONNULL_END

@end
