//
//  ETItem.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 31.07.17.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_NAME(Item)
@interface ETItem : NSObject

@property (nonatomic, retain, readonly) NSString * _Nonnull company;
@property (nonatomic, retain, readonly) NSString * _Nonnull title;
@property (nonatomic, retain, readonly) NSString * _Nullable desc;
@property (nonatomic, retain, readonly) NSURL * _Nullable imageURL;
@property (nonatomic, retain, readonly) NSString * _Nullable phoneNumber;
@property (nonatomic, retain, readonly) NSString * _Nullable email;
@property (nonatomic, retain, readonly) NSString * _Nullable address;
@property (nonatomic, retain, readonly) NSString * _Nullable question;
@property (nonatomic, retain, readonly) NSString * _Nullable answer;
@property (nonatomic, retain, readonly) NSString * _Nullable afterAnswer;

@end
