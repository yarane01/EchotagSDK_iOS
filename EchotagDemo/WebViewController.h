//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -
//
// WebViewController.h
// Digimarc Mobile SDK: DMSDemo
//

#import <UIKit/UIKit.h>
#import "WebKit/WebKit.h"

@interface WebViewController : UIViewController <WKNavigationDelegate>

@property WKWebView *webView;
@property UIBarButtonItem *doneButton;
@property UIProgressView *progressView;

@property NSString *initialViewControllerTitle;
@property NSURL *url;

@property BOOL showsProgressViewWhenLoading;
@property BOOL showsActivityIndicatorWhenLoading;
@property BOOL showsDoneButton;

@end