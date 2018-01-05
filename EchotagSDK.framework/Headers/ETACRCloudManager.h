//
//  ETACRCloudManager.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 05.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ETAPIManager.h"

/**
 The ACRCloudManager class.
 */
NS_SWIFT_NAME(ACRCloudManager)
@interface ETACRCloudManager : NSObject

@property(nonatomic, copy) void(^ _Nullable completionBlock)(ETMusic * __nullable resolvedContent, NSError * __nullable error);

/** ACRCloudCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param resolvedContent ETMusic object.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(ACRCloudCompletionBlock)
typedef void (^ETACRCloudCompletionBlock)(ETMusic * __nullable resolvedContent, NSError * __nullable error);
/**
 * Start ACRCloud recognation
 *
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)startFingerprintRecognitionWithCompletionBlock:(_Nonnull ETACRCloudCompletionBlock)completionBlock;
/**
 * Stop ACRCloud recognation
 */
- (void)stopFingerprintRecognition;

@end
