//
//  ETCity.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 22.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_NAME(City)
@interface ETCity : NSObject

@property (nonatomic, assign, readonly) uint cityId;
@property (nonatomic, retain, readonly) NSString * _Nullable name;

@end
