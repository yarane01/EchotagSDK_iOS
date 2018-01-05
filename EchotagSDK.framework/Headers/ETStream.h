//
//  ETStream.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 22.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ETCity.h"

NS_SWIFT_NAME(Stream)
@interface ETStream : NSObject

@property (nonatomic, assign, readonly) uint streamId;
@property (nonatomic, retain, readonly) NSString * _Nullable company;
@property (nonatomic, retain, readonly) NSString * _Nullable desc;
@property (nonatomic, retain, readonly) NSURL * _Nonnull imageURL;
@property (nonatomic, retain, readonly) NSURL * _Nonnull siteURL;
@property (nonatomic, assign, readonly) int type;
@property (nonatomic, assign, readonly) BOOL like;
@property (nonatomic, retain, readonly) NSMutableArray * _Nullable genres;
@property (nonatomic, retain, readonly) ETCity * _Nullable city;

@end
