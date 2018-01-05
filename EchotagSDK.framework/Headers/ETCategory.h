//
//  ETCategory.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 18.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_NAME(Category)
@interface ETCategory : NSObject

@property (nonatomic, assign, readonly) uint categoryId;
@property (nonatomic, retain, readonly) NSString * _Nullable title;

@end

