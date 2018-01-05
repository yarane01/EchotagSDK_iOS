//
//  ViewController.m
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 04.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "ViewController.h"
#import "UserCredentials.h"
#import "WebViewController.h"
#import "DataStore.h"
#import "MusicDetailViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self.tableView setDelegate:self];
    [self.tableView setDataSource:self];
    [self.tableView.layer setBorderWidth:0.5];
    [self.tableView.layer setBorderColor:[[UIColor colorWithRed:0.73 green:0.74 blue:0.75 alpha:1.00] CGColor]];
    
    self.imageCache = [[NSCache alloc] init];
    
    self.apiManager = [[ETAPIManager alloc] initWithAccessKey:echotagAccessKey];
//    [ETAPIManager setUserInfo:@"1"];
    
    [self initActivity];
}

- (void)initActivity {
    return;
}

- (BOOL)saveDataForKey:(NSString *)key
{
    return [DataStore storeData:self.activity forKey:key];
}

- (NSMutableArray *)loadDataForKey:(NSString *)key
{
    return [DataStore loadDataForKey:key];
}

#pragma mark - Table View

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return nil;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.activity count];
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    return YES;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 66;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Method is needed for iOS 8 editActionsForRowAtIndexPath actions on UITableViewCells.
}

#pragma mark - Helper Functions: UI

-(void) displayAlertControllerWithTitle:(NSString *)title andMessage:(NSString *)message
{
    dispatch_async(dispatch_get_main_queue(), ^{
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:message preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction *okAction = [UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
            
        }];
        
        [alertController addAction:okAction];
        
        [self presentViewController:alertController animated:YES completion:^{ }];
    });
}

-(void)openURLInWebView:(NSURL *)url withTitle:(NSString *)title
{
    NSString *urlScheme = url.scheme.lowercaseString;
    if ([urlScheme isEqualToString:@"http"] || [urlScheme isEqualToString:@"https"])
    {
        UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
        WebViewController *webViewController = [storyboard instantiateViewControllerWithIdentifier:@"WebViewController"];
        [webViewController setInitialViewControllerTitle:title];
        [webViewController setUrl:url];
        [webViewController setShowsDoneButton:NO];
        [webViewController setShowsActivityIndicatorWhenLoading:YES];
        [webViewController setShowsProgressViewWhenLoading:YES];
        
        [self.navigationController pushViewController:webViewController animated:true];
    }
    else
    {
        [self displayAlertControllerWithTitle:@"Content" andMessage:url.absoluteString];
    }
}

//- (void)openDetailViewForMusic:(ETMusic *)music {
//    MusicDetailViewController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"MusicDetailViewController"];
//
//    vc.detailItem = music;
//    
//    UINavigationController *nc = [[UINavigationController alloc] initWithRootViewController:vc];
//    [vc.navigationItem setLeftBarButtonItem:[[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:vc action:@selector(removeFromScreen)]];
//
//    [self presentViewController:nc animated:YES completion:nil];
//}

#pragma mark - Helper Functions: Images

-(UIImage *) imageCacheContainsKey:(NSString *)key
{
    UIImage *image = [self.imageCache objectForKey:key];
    return image;
}

- (void)downloadImageWithURL:(NSURL *)url completionBlock:(void (^)(BOOL succeeded, UIImage *image))completionBlock
{
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    [NSURLConnection sendAsynchronousRequest:request queue:[NSOperationQueue mainQueue] completionHandler:^(NSURLResponse *response, NSData *data, NSError *error)
     {
         if ( !error )
         {
             UIImage *image = [[UIImage alloc] initWithData:data];
             completionBlock(YES,image);
         }
         else
         {
             completionBlock(NO,nil);
         }
     }];
}

@end
