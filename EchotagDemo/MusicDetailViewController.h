//
//  MusicDetailViewController.h
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 05.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EchotagSDK/EchotagSDK.h>
#import "MusicViewController.h"

@protocol MusicDetailViewControllerDelegate <NSObject>
@required
- (void)updateMusicActivity:(ETMusic *)music;
- (void)displayAlertWithTitle:(NSString *)title andMessage:(NSString *)message;
@end

@interface MusicDetailViewController : UIViewController
@property ETAPIManager *apiManager;
@property NSCache *imageCache;
@property ETMusic *detailItem;
@property (nonatomic, weak) id<MusicDetailViewControllerDelegate> delegate;
- (void)removeFromScreen;
@end
