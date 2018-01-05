// - - - - - - - - - - - - - - - - - - - -
//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -

#ifndef DMSResolver_h
#define DMSResolver_h

#import <Foundation/Foundation.h>

#import "DMSPayload.h"
#import "DMSResolvedContent.h"


NS_ASSUME_NONNULL_BEGIN

/*-------------------------------------------------------------------------------------*/
#pragma mark - Resolver Error Codes
/*-------------------------------------------------------------------------------------*/

/** Error domain string associated with any NSError objects associated with
	DMSResolver logic.
 */
NS_SWIFT_NAME(ResolverErrorDomain)
extern NSString *const DMSResolverErrorDomain;

///Error codes that could be returned as part of an error from a resolver
typedef NS_ENUM(NSInteger, DMSResolverErrorCode ) {

    /** This payload type was not recognized, or is not supported by the resolver.
     */
    DMSResolverErrorCodeUnknownPayloadType = 401,

    /** The resolve request was canceled.
     */
    DMSResolverErrorCodeRequestCanceled = 402,
    
    
    /** The resolver was able to return a result, but it could not be parsed for an unknown reason. This could imply the data is being altered in transit.
     */
    DMSResolverErrorCodeCouldNotParseResult = 1000
} NS_SWIFT_NAME(ResolverErrorCode);

/**
    The Resolver class retrieves additional metadata that is not available locally from the Digimarc Barcode Resolver.
 */
NS_SWIFT_NAME(Resolver)
@interface DMSResolver : NSObject { }

/** Returns the normal, load balanced, high availability, production Resolver intended for use by your completed application.
 */
+ (nonnull NSURL *) resolverProductionService;

/** Returns the URL to the pre-production resolver with its own separate database, for use in building and testing your application before deployment.
 */
+ (nonnull NSURL *) resolverLabsService;

/** Returns the configured service URL for the resolver.
 */
@property (nonatomic, copy, nonnull, readonly) NSURL* serviceURL;

///Configured username for authentication to the resolver.
@property (nonatomic, retain, nonnull, readonly) NSString* username;

///Configured password for authentication to the resolver.
@property (nonatomic, retain, nonnull, readonly) NSString*	password;

///  :nodoc:
- (nonnull instancetype)init NS_UNAVAILABLE;

/** 
* Designated initializer for a resolver. The username and password arguments should be the resolver usename and password for your application. Please sign into your Digimarc Barcode Manager account to generate credentials for your app.  Under the Developers tab, choose “Create Mobile SDK User”.
*
* @param serviceURL The URL of the resolver service to use. If nil is passed, defaults to the production service.
* @param username Digimarc Barcode Manager resolver username.
* @param password Digimarc Barcode Manager resolver password.
* @return A resolver instance, or nil if parameters are invalid.
*/
- (nullable instancetype)initWithURL:(nullable NSURL *)serviceURL
                            username:(nonnull NSString *)username
                            password:(nonnull NSString *)password;

/** ResolveCompletionBlock
*
* Interface to application-defined block, called on completion of a resolve.
* @param resolvedContent The DMSResolvedContent wrapping incoming DMSPayload, resulting DMSResolvedContent, and status information.
* @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(ResolveCompletionBlock)
typedef void (^DMSResolveCompletionBlock)(DMSResolvedContent* __nullable resolvedContent, NSError * __nullable error);

/** 
* Start a resolve for an incoming DMSPayload to a DMSResolvedContent. This is an asynchronous network method that can take up to several seconds to complete, depending on network conditions. If active content is found, then a resolve result will be returned. Otherwise returns nil.
*
* @param payload A payload object to request additional metadata on.
* @param queue The queue that the completion block will be executed on. Defaults to the current queue.
* @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
-(void) resolve:(nonnull DMSPayload*)payload queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull DMSResolveCompletionBlock)completionBlock;

/** Cancels all resolves in progress.
 */
- (void) cancelAllResolves;

/**
* Interface to application-defined block, called on completion of reporting a UI viewing of a resolved payoff.
*
* @param error Error code if report action failed.
*/
NS_SWIFT_NAME(ReportActionCompletionBlock)
typedef void (^DMSReportActionCompletionBlock)( NSError * __nullable error);

/** 
* Report of the user's viewing of a resolve result's URL. Calling this method records metrics for each time the user actually views the content. Applications are required to use this method for proper usage reporting to the Resolver service and content owners. Calling reportAction should not take place until the user clicks through to actually view the payoff URL.
*
* @param actionToken The actionToken for the analytics event to report. This is provided by a resolve result's actionToken property.
* @param queue The queue that the completion block will be executed on. Defaults to the current queue.
* @param completionBlock Completion block to be executed when the request is completed.
*/
- (void) reportAction:(nonnull NSString*)actionToken queue:(nullable NSOperationQueue *)queue completionBlock:(nullable  DMSReportActionCompletionBlock)completionBlock;

@end

NS_ASSUME_NONNULL_END
#endif  // DMSResolver_h
