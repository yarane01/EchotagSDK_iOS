//
// Digimarc Confidential
// Copyright Digimarc Corporation, 2014-2016
//
// - - - - - - - - - - - - - - - - - - - -
//
// WebViewController.m
// Digimarc Mobile SDK: DMSDemo
//

#import "WebViewController.h"

@interface WebViewController ()
@end

@implementation WebViewController

#pragma mark - Preview Actions

- (NSArray<id<UIPreviewActionItem>> *)previewActionItems
{
    UIPreviewAction *actionSafari = [UIPreviewAction actionWithTitle:@"Open in Safari" style:UIPreviewActionStyleDefault handler:^(UIPreviewAction * _Nonnull action, UIViewController * _Nonnull previewViewController) {
        [self openLinkInSafari];
    }];
    
    NSArray *actions = @[actionSafari];
    return actions;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self.view setClipsToBounds:YES];
    [self.navigationItem setTitle:self.initialViewControllerTitle];
    
    // WKWebView Setup
    self.webView = [[WKWebView alloc] initWithFrame:[self.view frame]];
    [self.webView setNavigationDelegate:self];
    [self.webView setAllowsBackForwardNavigationGestures:YES];
    [self.webView setTranslatesAutoresizingMaskIntoConstraints:NO];
    [self.view addSubview:self.webView];
    [self addWKWebViewUIConstraints];
    
    // UIProgressView Setup
    if (self.showsProgressViewWhenLoading)
    {
        self.progressView = [[UIProgressView alloc] initWithFrame:CGRectMake(1.0, 1.0, 1.0, 2.0)];
        [self.progressView setProgressViewStyle:UIProgressViewStyleBar];
        [self.progressView setTranslatesAutoresizingMaskIntoConstraints:NO];
        [self.view addSubview:self.progressView];
        [self addProgressViewUIConstraints];
    }
    
    // Start Loading
    [self.webView loadRequest:[NSURLRequest requestWithURL:self.url]];
    
    // Done Button Setup
    if (self.showsDoneButton)
    {
        [self setupDoneButton];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self addWKWebViewObservers];
    
    if ([self.webView isLoading])
    {
        [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    [self removeWKWebViewObservers];
    
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

// MARK - WKWebView

-(void)webView:(WKWebView *)webView didFailNavigation:(WKNavigation *)navigation withError:(NSError *)error
{
    NSLog(@"%@", error.localizedDescription);
    
    if (error.code == NSURLErrorNotConnectedToInternet)
    {
        [self.navigationItem setTitle:@"Error"];
        [self displayAlertController:@"Error" error:error];
    }
}

-(void)webView:(WKWebView *)webView didFailProvisionalNavigation:(WKNavigation *)navigation withError:(NSError *)error
{
    NSLog(@"Error: %@ (Code: %ld)", error.localizedDescription, (long)error.code);
    
    if (error.code == NSURLErrorNotConnectedToInternet)
    {
        [self.navigationItem setTitle:@"Error"];
        [self displayAlertController:@"Error" error:error];
    }
    
    // WebKitErrorFrameLoadInterruptedByPolicyChange 102 is not accessible through the API although documented by Apple.
    // This is a fallback where the link will redirect to a URL where the scheme isn't 'HTTP' or 'HTTPS'.
    if ([error.domain isEqualToString:@"WebKitErrorDomain"] && error.code == 102)
    {
        NSDictionary *userInfo = error.userInfo;
        NSString *urlString = userInfo[@"NSErrorFailingURLStringKey"];
        NSURL *url = [NSURL URLWithString:urlString];
        if (url) {
            [[UIApplication sharedApplication] openURL:url];
        }
    }
}

- (void)displayAlertController:(NSString *)title error:(NSError *)error
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:error.localizedDescription preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction *cancelAction = [UIAlertAction actionWithTitle:@"Dismiss" style:UIAlertActionStyleCancel handler:^(UIAlertAction *action) {
        
    }];
    
    [alertController addAction:cancelAction];
    
    [self presentViewController:alertController animated:YES completion:nil];
}

// Done Button

-(void) setupDoneButton
{
    self.doneButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(doneButtonTapped:)];
    
    [self.navigationItem setRightBarButtonItem:self.doneButton];
}

-(void) doneButtonTapped:(UIBarButtonItem *)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(void) addWKWebViewUIConstraints
{
    // Top Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.webView
                              attribute:NSLayoutAttributeTop
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.topLayoutGuide
                              attribute:NSLayoutAttributeTop
                              multiplier:1.0
                              constant:0.0]];
    
    // Bottom Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.webView
                              attribute:NSLayoutAttributeBottom
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.bottomLayoutGuide
                              attribute:NSLayoutAttributeBottom
                              multiplier:1.0
                              constant:0.0]];
    
    // Leading (Left) Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.webView
                              attribute:NSLayoutAttributeLeading
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.view
                              attribute:NSLayoutAttributeLeading
                              multiplier:1.0
                              constant:0.0]];
    
    // Trailing (Right) Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.webView
                              attribute:NSLayoutAttributeTrailing
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.view
                              attribute:NSLayoutAttributeTrailing
                              multiplier:1.0
                              constant:0.0]];
}

- (void)addProgressViewUIConstraints
{
    // Top Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.progressView
                              attribute:NSLayoutAttributeTop
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.topLayoutGuide
                              attribute:NSLayoutAttributeBottom
                              multiplier:1.0
                              constant:0.0]];
    
    // Leading (Left) Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.progressView
                              attribute:NSLayoutAttributeLeading
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.view
                              attribute:NSLayoutAttributeLeading
                              multiplier:1.0
                              constant:0.0]];
    
    // Trailing (Right) Constraint
    [self.view addConstraint:[NSLayoutConstraint
                              constraintWithItem:self.progressView
                              attribute:NSLayoutAttributeTrailing
                              relatedBy:NSLayoutRelationEqual
                              toItem:self.view
                              attribute:NSLayoutAttributeTrailing
                              multiplier:1.0
                              constant:0.0]];
}

// MARK: - KVO Add/Remove Observers

-(void) addWKWebViewObservers
{
    [self.webView addObserver:self forKeyPath:@"estimatedProgress" options:NSKeyValueObservingOptionNew context:nil];
    [self.webView addObserver:self forKeyPath:@"loading" options:NSKeyValueObservingOptionNew context:nil];
    [self.webView addObserver:self forKeyPath:@"title" options:NSKeyValueObservingOptionNew context:nil];
}

-(void) removeWKWebViewObservers
{
    [self.webView removeObserver:self forKeyPath:@"estimatedProgress"];
    [self.webView removeObserver:self forKeyPath:@"loading"];
    [self.webView removeObserver:self forKeyPath:@"title"];
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if ([keyPath isEqual: @"estimatedProgress"])
    {
        if (self.showsProgressViewWhenLoading)
        {
            if ([self.progressView progress] < [self.webView estimatedProgress])
            {
                [self.progressView setProgress:[self.webView estimatedProgress] animated:YES];
            }
        }
    }
    
    if ([keyPath isEqual: @"loading"])
    {
        if ([self.webView isLoading])
        {
            [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
            
            if (self.showsProgressViewWhenLoading)
            {
                [self.progressView setAlpha:1];
            }
        }
        else
        {
            [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
            
            if (self.showsProgressViewWhenLoading)
            {
                [self.progressView setAlpha:0];
            }
        }
    }
    
    if ([keyPath isEqual: @"title"])
    {
        NSString *updatedWebpageTitle = [self.webView title];
        
        if (updatedWebpageTitle)
        {
            [self.navigationItem setTitle:updatedWebpageTitle];
        }
    }
}

- (void) openLinkInSafari
{
    [[UIApplication sharedApplication] openURL:self.url];
}

@end
