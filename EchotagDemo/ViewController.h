//
//  ViewController.h
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 04.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EchotagSDK/EchotagSDK.h>

@interface ViewController : UIViewController <UITableViewDelegate, UITableViewDataSource>

#pragma mark - UI Elements
@property (weak, nonatomic) IBOutlet UITableView *tableView;

#pragma mark - data
@property NSMutableArray *activity;
@property NSCache *imageCache;

#pragma mark - Echotag
@property ETAPIManager *apiManager;

- (BOOL)saveDataForKey:(NSString *)key;
- (NSMutableArray *)loadDataForKey:(NSString *)key;

- (void)displayAlertControllerWithTitle:(NSString *)title andMessage:(NSString *)message;
- (void)openURLInWebView:(NSURL *)url withTitle:(NSString *)title;
//- (void)openDetailViewForMusic:(ETMusic *)music;

-(UIImage *) imageCacheContainsKey:(NSString *)key;
- (void)downloadImageWithURL:(NSURL *)url completionBlock:(void (^)(BOOL succeeded, UIImage *image))completionBlock;

@end
