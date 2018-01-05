//
//  DataStore.h
//  EchotagDEMO
//
//  Created by Alexandr Shevchuk on 13.07.17.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface DataStore : NSObject <NSKeyedArchiverDelegate, NSKeyedUnarchiverDelegate>

+ (NSMutableArray *)loadDataForKey:(NSString *)key;
+ (BOOL)storeData:(NSMutableArray *)data forKey:(NSString *)key;

@end
