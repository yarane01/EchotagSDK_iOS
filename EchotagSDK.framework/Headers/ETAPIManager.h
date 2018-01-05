//
//  ETAPIManager.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 13.07.17.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <DMSDK/DMSDK.h>
#import "ETEchotags.h"
#import "ETStreams.h"
#import "ETCategories.h"
#import "ETGenres.h"
#import "ETCities.h"
#import "ETAuth.h"
#import "ETMusics.h"

@class ETEchotags;
@class ETStreams;
@class ETCategories;
@class ETGenres;
@class ETCities;
@class ETAuth;
@class ETMusics;

NS_ASSUME_NONNULL_BEGIN

/*-------------------------------------------------------------------------------------*/
#pragma mark - Resolver Error Codes
/*-------------------------------------------------------------------------------------*/

/** Error domain string associated with any NSError objects associated with
 ETAPIManager logic.
 */
NS_SWIFT_NAME(APIErrorDomain)
extern NSString *const ETAPIErrorDomain;

///Error codes that could be returned as part of an error from a resolver
typedef NS_ENUM(NSInteger, ETAPIErrorCode ) {
    /** The resolver was able to return a result, but it could not be parsed for an unknown reason. This could imply the data is being altered in transit.
     */
    ETAPIErrorCodeCouldNotParseResult = 1000
} NS_SWIFT_NAME(APIErrorCode);

NS_ASSUME_NONNULL_END

/**
 * TYPE_AD constant identifier of the content type ad
 */
extern uint const TYPE_AD;
/**
 * TYPE_JINGLE constant identifier of the content type jingle
 */
extern uint const TYPE_JINGLE;
/**
 * TYPE_QUIZ constant identifier of the content type quiz
 */
extern uint const TYPE_QUIZ;
/**
 * TYPE_SURVEY constant identifier of the content type survey
 */
extern uint const TYPE_SURVEY;

/**
 The APIManager class.
 */
NS_SWIFT_NAME(APIManager)
@interface ETAPIManager : NSObject

/**
 * Designated initializer for a resolver. The username and password arguments should be the resolver usename and password for your application. Please sign into your Digimarc Barcode Manager account to generate credentials for your app.  Under the Developers tab, choose “Create Mobile SDK User”.
 *
 * @param accessKey Echotag accessKey.
 * @return A APIManager instance, or nil if parameters are invalid.
 */
- (nullable instancetype)initWithAccessKey:(nonnull NSString *)accessKey;

+ (void)setUserInfo:(NSString *_Nullable)userInfo;
/**
 * Object containing asynchronouse requests for echotags resource.
 */
- (ETEchotags *_Nullable)echotags;
/**
 *  Object containing asynchronouse requests for streams
 */
- (ETStreams *_Nullable)streams;
/**
 *  Object containing asynchronouse requests for categories
 */
- (ETCategories *_Nullable)categories;
/**
 *  Object containing asynchronouse requests for genres
 */
- (ETGenres *_Nullable)genres;
/**
 *  Object containing asynchronouse requests for cities
 */
- (ETCities *_Nullable)cities;
/**
 *  Object containing asynchronouse requests for auth
 */
- (ETAuth *_Nullable)auth;
/**
 *  Object containing asynchronouse requests for musics
 */
- (ETMusics *_Nullable)musics;

@end

