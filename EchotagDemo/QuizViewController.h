//
//  QuizViewController.h
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 06.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <EchotagSDK/EchotagSDK.h>

@interface QuizViewController : UIViewController

@property ETAPIManager *apiManager;
@property ETEchotag *detailItem;

- (void)removeFromScreen;

@end
