//
//  ETEchotag.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 15.07.17.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ETItem.h"

NS_SWIFT_NAME(Echotag)
@interface ETEchotag : NSObject

@property (nonatomic, assign, readonly) uint echotagId;
@property (nonatomic, retain, readonly) NSString * _Nullable payloadId;
@property (nonatomic, assign, readonly) uint echotagType;
@property (nonatomic, assign, readonly) uint countSubitems;
@property (nonatomic, assign, readonly) uint owner;
@property (nonatomic, retain, readonly) NSURL * _Nonnull siteURL;
@property (nonatomic, retain, readonly) NSURL * _Nullable shareURL;
@property (nonatomic, retain, readonly) ETItem * _Nonnull item;
@property (nonatomic, retain, readonly) NSMutableArray * _Nullable subItems;
@property (nonatomic, retain, readonly) NSMutableArray * _Nonnull categories;
@property (nonatomic, retain, readonly) NSString * _Nullable categoryTitle;

@end
