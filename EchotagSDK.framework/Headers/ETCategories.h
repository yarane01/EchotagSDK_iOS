//
//  ETCategories.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 23.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ETResource.h"
#import "ETAPIManager.h"
#import "ETCategory.h"

/**
 The Categories class.
 */
NS_SWIFT_NAME(Categories)
@interface ETCategories : ETResource

/** CategoriesCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param categories List of categories.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(CategoriesCompletionBlock)
typedef void (^ETCategoriesCompletionBlock)(NSArray<ETCategory *> * __nullable categories, NSError * __nullable error);
/**
 * Requests a list of categories
 *
 * @param page Page number in the result set.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)itemsWithPage:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETCategoriesCompletionBlock)completionBlock;

@end

