//
//  ETUser.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 12.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_NAME(User)
@interface ETUser : NSObject

@property (nonatomic, retain, readonly) NSString * _Nullable userId;
@property (nonatomic, retain, readonly) NSString * _Nullable apiKey;
@property (nonatomic, retain, readonly) NSString * _Nullable name;
@property (nonatomic, retain, readonly) NSString * _Nullable phone;
@property (nonatomic, assign, readonly) BOOL isGuest;

@end
