//
//  ETAuth.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 23.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ETResource.h"
#import "ETAPIManager.h"
#import "ETUser.h"

/**
 The Auth class.
 */
NS_SWIFT_NAME(Auth)
@interface ETAuth : ETResource

/** AuthResultCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param success True if the server accepts inbound parameters and no errors are encountered during processing.
 * @param message Text of a server message.
 * @param errors List of errors caused by inbound parameters
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(AuthResultCompletionBlock)
typedef void (^ETAuthResultCompletionBlock)(BOOL success, NSString * __nullable message, NSDictionary * __nullable errors, NSError * __nullable error);
/**
 * User registration using email and password.
 * After succesful registration the server will send a confirmation email to the user. The email must be confirmed, otherwise an error is returned.
 *
 * @param login User email.
 * @param password User password.
 * @param company User company. Could be blank - in which case a default user is assumed.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)registrationWithLogin:(nonnull NSString *)login andPassword:(nonnull NSString *)password andCompany:(nullable NSString *)company queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthResultCompletionBlock)completionBlock;
/**
 * Assocciating an email with an account.
 * If we are unbable to get user's email from the social network, the server generates a tokey and returns it with the registration via social network responce
 * This method sends user's email along with the token.
 * @param email User email.
 * @param registrationToken - registration token.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)registrationConnectWithEmail:(nonnull NSString *)email andRegistrationToken:(nonnull NSString *)registrationToken queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthResultCompletionBlock)completionBlock;
/**
 * Password reset. A link is sent to a given email with instructions to set a new password.
 * @param email User email.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)forgotPasswordWithEmail:(nonnull NSString *)email queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthResultCompletionBlock)completionBlock;
/**
 * Check company existance.
 *
 * @param company Company name.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)checkCompany:(nonnull NSString *)company queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthResultCompletionBlock)completionBlock;
/**
 * Cofirmation of a registration.
 *
 * @param userId User identificator.
 * @param registrationToken Registration token.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)registrationConfirmWithUser:(nonnull NSString *)userId andRegistrationToken:(nonnull NSString *)registrationToken queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthResultCompletionBlock)completionBlock;

/** AuthByEmailCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param success True if the server accepts inbound parameters and no errors are encountered during processing.
 * @param message Text of a server message.
 * @param errors List of errors caused by inbound parameters
 * @param user ETUser
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(AuthByEmailCompletionBlock)
typedef void (^ETAuthByEmailCompletionBlock)(BOOL success, NSString * __nullable message, NSDictionary * __nullable errors, ETUser * __nullable user, NSError * __nullable error);
/**
 * User authentication with email and password. With successful authentication the method returns user data contained in the object ETUser, otherwise returns error.
 * @param login User email.
 * @param password User password.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)byEmailWithLogin:(nonnull NSString *)login andPassword:(nonnull NSString *)password queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthByEmailCompletionBlock)completionBlock;

/** AuthByProviderCompletionBlock
 *
 * Interface to application-defined block, called on completion of a request.
 * @param success True if the server accepts inbound parameters and no errors are encountered during processing.
 * @param message текст Server error message.
 * @param errors List of inbound parameters errors.
 * @param registration_token Token to be supplied to method registrationConnect.
 * @param error Error code if resolve query failed.
 */
NS_SWIFT_NAME(AuthByProviderCompletionBlock)
typedef void (^ETAuthByProviderCompletionBlock)(BOOL success, NSString * __nullable message, NSDictionary * __nullable errors, NSString * __nullable registration_token, ETUser * __nullable user, NSError * __nullable error);
/**
 * User authentication with email and password. With successful authentication the method returns user data contained in the object ETUser, otherwise returns error.
 *
 * @param token Тoken returned by social network.
 * @param provider Social network name, for example, Facebook).
 * @param email User email. Could be blank, in whick case the server will attempted to get email from the social network.
 * @param company User company. Could be blank, in which case the default company name is used.
 * @param queue The queue that the completion block will be executed on. Defaults to the current queue.
 * @param completionBlock Completion block to be executed when the request is completed.
 */
- (void)byProviderWithToken:(nonnull NSString *)token andProvider:(nonnull NSString *)provider andEmail:(nullable NSString *)email andCompany:(nullable NSString *)company queue:(nullable NSOperationQueue *)queue completionBlock:(nonnull ETAuthByProviderCompletionBlock)completionBlock;

@end

