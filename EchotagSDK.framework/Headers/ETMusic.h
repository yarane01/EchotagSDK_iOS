//
//  ETMusic.h
//  EchotagSDK
//
//  Created by Alexandr Shevchuk on 23.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_SWIFT_NAME(Music)
@interface ETMusic : NSObject

@property (nonatomic, assign, readonly) uint musicId;
@property (nonatomic, retain, readonly) NSString *data;
@property (nonatomic, assign, readonly) BOOL like;

@property (nonatomic, retain, readonly) NSString *acrId;
@property (nonatomic, retain, readonly) NSString *title;
@property (nonatomic, retain, readonly) NSString *album;
@property (nonatomic, retain, readonly) NSString *artist;
@property (nonatomic, retain, readonly) NSString *youtubeId;
@property (nonatomic, retain, readonly) NSString *releaseDate;
@property (nonatomic, retain, readonly) NSString *genres;
@property (nonatomic, retain, readonly) NSURL *artworkUrl;
@property (nonatomic, retain, readonly) NSString *itunesTrackId;
@property (nonatomic, retain, readonly) NSString *itunesAlbumId;

@end
