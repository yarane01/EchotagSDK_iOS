//
//  ETGenres.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 23.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ETResource.h"
#import "ETAPIManager.h"
#import "ETGenre.h"

/**
 The Genres class.
 */
NS_SWIFT_NAME(Genres)
@interface ETGenres : ETResource

/** GenresCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param genres List of genres.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(GenresCompletionBlock)
typedef void (^ETGenresCompletionBlock)(NSArray<ETGenre *> * __nullable genres, NSError * __nullable error);
/**
 * Requests a list of genres
 *
 * @param page Page number.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)itemsWithPage:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETGenresCompletionBlock)completionBlock;

@end

