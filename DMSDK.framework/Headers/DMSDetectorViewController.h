// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#import <UIKit/UIKit.h>
#import <DMSDK/DMSReaderResult.h>
#import <DMSDK/DMSResolver.h>
#import <DMSDK/DMSResolvedContent.h>
#import <DMSDK/DMSSymbologies.h>

@class DMSDetectorViewController;
/**
 Delegate protocol for returning results from a DMSDetectorViewController. Delegates can implement this protocol to either respond to a new result or a cancel result from a DMSDetectorViewController. Implementors are responsible for dismissing a DMSDetectorViewController as a modal view controller themselves, so the detectorViewControllerDidCancel: delegate method should be used to dismiss the view controller.
 */

NS_SWIFT_NAME(DetectorViewControllerDelegate)
@protocol DMSDetectorViewControllerDelegate <NSObject>

@optional
/**
 Delegate method for deciding if payloads from a result should be resolved. Passes a reader result that contains the found payloads and other metadata about the detection. Returned payloads will be resolved. If this delegate method is not implemented, the detector view controller will default to resolving the first payload returned by the reader result.
 */
-(nullable NSArray <DMSPayload *> *)detectorViewController:(nonnull DMSDetectorViewController *)viewController shouldResolvePayloadsForResult:(nonnull DMSReaderResult *)result;

/**
 Called if the view controller finds content. Responder is responsible for dismissing view controller if necessary.
 */
-(void)detectorViewController:(nonnull DMSDetectorViewController *)viewController resolvedContent:(nonnull DMSResolvedContent *)resolvedContent forPayload:(nonnull DMSPayload *)payload;

/**
 Called if the view controller is presented as a modal and it is cancelled. View controller will dismiss itself.
 */
-(void)detectorViewControllerDidCancel:(nonnull DMSDetectorViewController *)viewController;

/**
 Called if the view controller encounters an error in the Resolver callback or if AV Foundation sent a AVCaptureSessionRuntimeErrorNotification error (session capture error).
 */
-(void)detectorViewController:(nonnull DMSDetectorViewController *)viewController didReceiveError:(nonnull NSError *)error;

@end

/**
View controller for detecting Digimarc audio and image marks, and QR and barcodes. This view controller provides camera and audio detection for Digimarc technologies. If permissions have not been given to the application for camera and audio access, this view controller will request them. The implementor must also set the username and password properties before displaying the view controller. The username and password should be a resolver username and password supplied by Digimarc. The DMSDetectorViewControllerDelegate protocol notifies the delegate application when a payload has been detected, or when a payload has been resolved to a payoff for presentation to the user. The view controller will not automatically dismiss when a mark has been found, the implementor is responsible for defining that behavior. The implementor can do things such as dismissing the view controller after detect, or adding another view controller to the navigation stack.
 
 The detector view controller will only turn on the camera or microphone as needed. If audio or image symbologies are not enabled, the relevant hardware will not be turned on. For example, if all the image symbologies are disabled the camera will be turned off. This can be configured before the view controller is displayed, or re-configured while it is displayed.
 */

NS_SWIFT_NAME(DetectorViewController)
@interface DMSDetectorViewController : UIViewController

/**
 Readonly property that contains a resolver object. May be nil. Implementors can use this resolver to manually resolve payloads, or to manually control resolves. Configured with username and password if those properties have been set.
 */
@property (readonly, nonnull) DMSResolver *resolver;

/**
 Digimarc resolver service user name.  Contact Digimarc Support for unique credentials for your application.
 */
@property (nullable, readonly) IBInspectable NSString *username;

/**
 Digimarc resolver service password.
 */
@property (nullable, readonly) IBInspectable NSString *password;

/**
 Sets the resolver username and password. Both username and password must have a string value, or both must be nil.
 */
-(void)setResolverUsername:(nullable NSString *)username password:(nullable NSString *)password DEPRECATED_MSG_ATTRIBUTE("Use setResolverURL:username:password: instead.");

/**
 Sets the resolver url, username, and password. The URL parameter could be nil but will default to production resolver service. Both username and password must have a string value, or both must be nil.
 */
-(void)setResolverURL:(nullable NSURL *)url username:(nullable NSString *)username password:(nullable NSString *)password;

/**
 Delegate for view controller.
 */
@property (weak, nullable) IBOutlet id <DMSDetectorViewControllerDelegate> delegate;

/**
 Readonly property for the on screen visualizer. Implementors can use this property to remove the visualizer view, add one of their own, or modify the existing visualizer. Value is nil until the view controller loads. The detector view controller will hide this view until the feature becomes available.
 */
@property (readonly, null_unspecified) UIView *audioVisualizerView;

/**
 Readonly property for on screen user guidance. Implementors can use this property to remove the guidance view, add one of their own, or modify the existing view. Value is nil until the view controller loads. The detector view controller will hide this view until the feature becomes available.
 */
@property (readonly, null_unspecified) UIView *userGuidanceView;

/**
 Readonly property for on screen crosshairs that are present when the camera is active. Implementors can use this property to remove the crosshairs view, add one of their own, or modify the existing view. Value is nil until the view controller loads. The detector view controller will hide this view until the feature becomes available.
 */
@property (readonly, null_unspecified) UIView *crosshairsView;

/**
 Types of media that should be handled by the view controller. Defaults to DMSDetectorViewControllerMediaTypeAllTypes.
 */
@property DMSSymbologies symbologies;

/**
 Configures if the detector view controller should be actively detecting and returning results.
 */
@property BOOL detectionEnabled;

/**
 The AVCaptureDevice to use for video detection. Defaults to the rear facing camera, if available.
 */
@property (readonly, nullable) AVCaptureDevice *videoCaptureDevice;

/**
 Sets the video capture device to videoCaptureDevice. Raises an exception if videoCaptureDevice is not a video or muxed device.
 */
-(BOOL)setVideoCaptureDevice:(nullable AVCaptureDevice *)videoCaptureDevice error:(NSError * _Nullable * _Nullable)error;


/**
 Sets the audio capture device to audioCaptureDevice. Raises an exception if audioCaptureDevice is not an audio or muxed device.
 */
-(BOOL)setAudioCaptureDevice:(nullable AVCaptureDevice *)audioCaptureDevice error:(NSError * _Nullable * _Nullable)error;

/**
 * Sets symbologies and reader options.
 *
 * @param symbologies Symbologies to configure the reader to detect.
 * @param options Options to configure the reader with.
 */
-(void)setSymbologies:(DMSSymbologies)symbologies options:(NSDictionary<DMSReaderOptionKey, id> * _Nonnull)options;

/**
 The AVCaptureDevice to use for audio detection. Defaults to the default audio recording device, if available.
 */
@property (readonly, nullable) AVCaptureDevice *audioCaptureDevice;

///Limits the detection area to a specific region. rectOfInterest is a normalized value that defines the region of interest between 0..1 for both the height and the width of the image. This rect interoperates with AVFoundation's rectOfInterest class of functions for converting between real pixel values and normalized values.
@property CGRect rectOfInterest;

@end
