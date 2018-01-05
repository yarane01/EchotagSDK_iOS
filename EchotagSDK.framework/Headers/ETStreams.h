//
//  ETStreams.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 22.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ETResource.h"
#import "ETAPIManager.h"
#import "ETStream.h"
#import "ETCity.h"
#import "ETGenre.h"

/**
 The Streams class.
 */
NS_SWIFT_NAME(Streams)
@interface ETStreams : ETResource

/** StreamsCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param streams Список стримов.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(StreamsCompletionBlock)
typedef void (^ETStreamsCompletionBlock)(NSArray<ETStream *> * __nullable streams, NSError * __nullable error);
/**
 * Requests a list of streams given stream's city and genre
 *
 * @param city ETCity object.
 * @param genre ETGenre object.
 * @param page Page number.
 * @param perPage Number of items per page
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)itemsWithCity:(ETCity *_Nullable)city andGenre:(ETGenre *_Nullable)genre page:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETStreamsCompletionBlock)completionBlock;
/**
 * Requests a list of user's favorite streams
 *
 * @param page НPage number.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)favoritesWithPage:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETStreamsCompletionBlock)completionBlock;

/**
 * Marks a stream as favorite
 *
 * @param stream ETStream object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)like:(nonnull ETStream *)stream queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;
/**
 * Marks a stream as non-favorite
 *
 * @param stream ETStream object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)unlike:(nonnull ETStream *)stream queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;

@end

