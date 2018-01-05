//
//  ETResource.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 23.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ETResource : NSObject
/** ResultCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param result True if the server has accepted the call parameters and no exceptions were thrown during the processing
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(ResultCompletionBlock)
typedef void (^ETResultCompletionBlock)(BOOL result, NSError * __nullable error);
@end

