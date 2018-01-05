//
//  DataStore.h
//  EchotagDEMO
//
//  Created by Alexandr Shevchuk on 13.07.17.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "DataStore.h"

@implementation DataStore

+ (NSMutableArray *)loadDataForKey:(NSString *)key
{
    NSMutableArray *savedData = [[NSMutableArray alloc] init];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectoryPath = [paths objectAtIndex:0];
    NSString *filePath = [documentsDirectoryPath stringByAppendingString:[NSString stringWithFormat:@"/%@", key]];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSData *data = [NSData dataWithContentsOfFile:filePath];
        savedData = [NSKeyedUnarchiver unarchiveObjectWithData:data];
    }
    
    return savedData;
}

+ (BOOL)storeData:(NSMutableArray *)data forKey:(NSString *)key
{
    if (data)
    {
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectoryPath = [paths objectAtIndex:0];
        NSString *filePath = [documentsDirectoryPath stringByAppendingString:[NSString stringWithFormat:@"/%@", key]];
        
        BOOL didFinish = [NSKeyedArchiver archiveRootObject:data toFile:filePath];
        
        return didFinish;
    }
    
    return false;
}

- (void)archiverDidFinish:(NSKeyedArchiver *)archiver
{
    NSLog(@"archiverDidFinish");
}

- (void)unarchiverDidFinish:(NSKeyedUnarchiver *)unarchiver
{
    NSLog(@"unarchiverDidFinish");
}

@end
