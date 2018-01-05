//
//  ETMusics.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 23.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ETResource.h"
#import "ETAPIManager.h"
#import "ETMusic.h"

/**
 The Musics class.
 */
NS_SWIFT_NAME(Musics)
@interface ETMusics : ETResource

/** MusicsCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param musics List of musical tracks
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(MusicsCompletionBlock)
typedef void (^ETMusicsCompletionBlock)(NSArray<ETMusic *> * __nullable musics, NSError * __nullable error);
/**
 * Requests a list of musical tracks for the current user
 *
 * @param page Page number.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)itemsWithPage:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETMusicsCompletionBlock)completionBlock;
/**
 * Requests a list of most popular -- whith the platform -- musical tracks
 *
 * @param page Page number.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)popularWithPage:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETMusicsCompletionBlock)completionBlock;

/**
 * Adds musical track to the current user's list
 *
 * @param music ETMusic object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)report:(nonnull ETMusic *)music queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;
/**
 * Removes musical track from the current user's list
 *
 * @param music ETMusic object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)remove:(nonnull ETMusic *)music queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;
/**
 * Marks musical track as favorite
 *
 * @param music ETStream object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)like:(nonnull ETMusic *)music queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;
/**
 * Marks musical track as non-favorite
 *
 * @param music ETStream object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)unlike:(nonnull ETMusic *)music queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;

@end

