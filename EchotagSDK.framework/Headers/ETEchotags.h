//
//  ETEchotags.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 18.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ETResource.h"
#import "ETAPIManager.h"
#import "ETEchotag.h"

/**
 The Echotags class.
 */
NS_SWIFT_NAME(Echotags)
@interface ETEchotags : ETResource

/** ResolveCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param resolvedContent Echotag object.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(ResolveCompletionBlock)
typedef void (^ETResolveCompletionBlock)(ETEchotag * __nullable resolvedContent, NSError * __nullable error);
/**
 * Requests data for recognized watermak
 *
 * @param payload A payload object to request additional metadata on.
 * @param categories If present the payload object will contain categories for retuned items
 * @param subItems If present the payload object will contain subitems for retuned items
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)resolve:(nonnull DMSPayload*)payload withCategories:(BOOL)categories withSubItems:(BOOL)subItems queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResolveCompletionBlock)completionBlock;

/** ReportCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param url Link to the offer detail page.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(ReportCompletionBlock)
typedef void (^ETReportCompletionBlock)(NSURL * __nullable url, NSError * __nullable error);
/**
 * Reports how many times the user viewed the URL of a recognized item. Calling this method increments metrics for each time the user actually views the content. Applications are required to use this method for proper usage reporting to the Resolver service and content owners. Calling reportAction should not take place until the user clicks through to actually view the payoff URL.
 *
 * @param echotag Echotag object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)report:(nonnull ETEchotag *)echotag queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETReportCompletionBlock)completionBlock;

/** OffersCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param offers Array of offers. Offers are items of the ad type.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(OffersCompletionBlock)
typedef void (^ETOffersCompletionBlock)(NSArray<ETEchotag *> * __nullable offers, NSError * __nullable error);
/**
 * Requests a list of offers for a current user
 *
 * @param categories If present the payload object will contain categories for retuned items
 * @param subItems If present the payload object will contain subitems for retuned items.
 * @param page Page number in the result set.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)itemsWithCategories:(BOOL)categories withSubItems:(BOOL)subItems page:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETOffersCompletionBlock)completionBlock;
/**
 * Запрашивает список топ оферов
 *
 * @param categories Формат ответа с категориями.
 * @param subItems Формат ответа с сабайтемами.
 * @param page Номер страницы.
 * @param perPage Количество айтемов на странице.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)topWithCategories:(BOOL)categories withSubItems:(BOOL)subItems page:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETOffersCompletionBlock)completionBlock;
/**
 * Requests a list of most popular offers
 *
 * @param categories If present the payload object will contain categories for retuned items
 * @param subItems If present the payload object will contain subitems for retuned items.
 * @param page Page number in the result set.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)popularWithCategories:(BOOL)categories withSubItems:(BOOL)subItems page:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETOffersCompletionBlock)completionBlock;
/**
 * Requests a list of the off-line offers
 *
 *  @param categories If present the payload object will contain categories for retuned items
 * @param subItems If present the payload object will contain subitems for retuned items.
 * @param page Page number in the result set.
 * @param perPage Number of items per page.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)offlineWithCategories:(BOOL)categories withSubItems:(BOOL)subItems page:(uint)page perPage:(uint)perPage queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETOffersCompletionBlock)completionBlock;

/**
 * Removes an offer from a list of recognized offers
 *
 * @param echotag Echotag object.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)remove:(nonnull ETEchotag *)echotag queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;
/**
 * Reports the number of clicks and impressions for off-line offers
 *
 * @param report Lists numbers or clicks and impressions
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed. Returns either an error or a resolve result, but not both.
 */
- (void)reportOffline:(nonnull NSArray<NSArray *> *)report queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETResultCompletionBlock)completionBlock;

@end

