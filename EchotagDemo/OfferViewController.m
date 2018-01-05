//
//  OfferViewController.m
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 10.07.17.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "OfferViewController.h"
#import <AVFoundation/AVFoundation.h>
#import "QuizViewController.h"

#define TIME_TO_REMOVE_ACTIVITY (60)

static NSString *const controllerKey = @"offers";

#pragma mark INTERFACE

@interface OfferViewController ()

#pragma mark - DMS
@property AVCaptureSession *audioCaptureSession;
@property DMSAudioCaptureReader *audioCaptureReader;
@property DMSResolver *resolver;
@property (nonatomic) dispatch_queue_t audioSessionQueue;
@property DMSSymbologies audioSymbologies;

@end

#pragma mark - IMPLEMENTATION

@implementation OfferViewController

#pragma mark - UIViewController Methods

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Communicate with the session and other session objects on this queue.
    self.audioSessionQueue = dispatch_queue_create("audio session queue", DISPATCH_QUEUE_SERIAL);
    
    self.audioSymbologies = DMSSymbologyAudioDigimarc;
    
    self.resolver = [[DMSResolver alloc] initWithURL:[DMSResolver resolverLabsService] username:@"" password:@""];
    
    [self registerNotifications];
    [self registerCaptureSessionNotifications];
    [self setupAndRunDMSAudioCaptureReader];
    
    [self.imageCache setName:@"Offers Image Cache"];
    [self.imageCache setCountLimit:100];
}

- (void)initActivity {
    self.activity = [self loadDataForKey:controllerKey];
    if (self.activity.count == 0) {
        [[self.apiManager echotags] itemsWithCategories:YES withSubItems:YES page:0 perPage:0 queue:[NSOperationQueue mainQueue] completionBlock:^(NSArray * __nullable offers, NSError * __nullable error) {
            if (error) {
                [self displayAlertControllerWithTitle:@"EchotagDemo" andMessage:error.localizedDescription];
            } else {
                self.activity = [NSMutableArray arrayWithArray:offers];
                [self.tableView reloadData];
                [self saveDataForKey:controllerKey];
            }
        }];
    }
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    // Restart the capture session to begin detecting video and audio as originally configured.
    
    [self startCaptureSession];
    
    // Restore the results delegate for audio capture readers.
    
    if (![[self audioCaptureReader] resultsDelegate]) {
        [[self audioCaptureReader] setResultsDelegate:self queue:dispatch_get_main_queue()];
    }
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self stopCaptureSession];
}

- (void)dealloc
{
    if (self.audioCaptureReader)
    {
        self.audioCaptureReader = nil;
    }
    
    if (self.resolver)
    {
        [self.resolver cancelAllResolves];
        self.resolver = nil;
    }
    
    [self unregisterNotifications];
}

#pragma mark - DMS Setup and Handling

- (void)setupAndRunDMSAudioCaptureReader
{
    // Request AVMediaTypeAudio
    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
        if (granted) {
            dispatch_async(self.audioSessionQueue, ^{
                NSError *error;
                [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryRecord error:&error];
                [[AVAudioSession sharedInstance] setActive:YES error:&error];
                
                self.audioCaptureSession = [[AVCaptureSession alloc] init];
                [self.audioCaptureSession beginConfiguration];
                self.audioCaptureReader = [[DMSAudioCaptureReader alloc] initWithSymbologies:self.audioSymbologies options:@{}];
                AVCaptureDevice *audioCaptureDevice = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeAudio];
                AVCaptureDeviceInput *audioCaptureDeviceInput = [AVCaptureDeviceInput deviceInputWithDevice:audioCaptureDevice error:&error];
                
                if (error)
                {
                    NSLog(@"%@", error);

                    [self.resolver cancelAllResolves];
                    NSLog(@"AVCaptureDeviceInput Error: %@", error.localizedDescription);
                    
                    [self.audioCaptureSession commitConfiguration];
                    return;
                }
                
                if ([self.audioCaptureSession canAddInput:audioCaptureDeviceInput])
                {
                    [self.audioCaptureSession addInput:audioCaptureDeviceInput];
                }
                else
                {
                    NSLog(@"Couldn't add audio capture device input.");
                    
                    [self.audioCaptureSession commitConfiguration];
                    return;
                }
                
                [self.audioCaptureReader setResultsDelegate:self queue:dispatch_get_main_queue()];
                [self.audioCaptureSession addOutput:self.audioCaptureReader.captureOutput];
                [self.audioCaptureSession commitConfiguration];
                
#if !(TARGET_IPHONE_SIMULATOR)
                [self.audioCaptureSession startRunning];
#endif
            });
        }
    }];
}

-(void)audioCaptureReader:(DMSAudioCaptureReader *)audioCaptureReader didOutputResult:(DMSReaderResult *)result
{
    if ([result.payloads count] > 0)
    {
        for (DMSPayload *payload in result.payloads)
        {
            
            //
            // 1. Check to see if the item currently exists in the data array.
            //
            NSUInteger indexOfItem = [self.activity indexOfObjectPassingTest:^BOOL(id obj, NSUInteger index, BOOL *stop)
                                      {
                                          if ([((ETEchotag *)obj).payloadId isEqualToString:[payload identifier]])
                                          {
                                              *stop = YES;
                                              return YES;
                                          }
                                          
                                          return NO;
                                      }];
            
            //
            // 2. If the item exists in the data array, attempt to re-resolve it if it is marked as contentSynthesized.
            //
            if (indexOfItem != NSNotFound)
            {
                ETEchotag *item = (ETEchotag *)[self.activity objectAtIndex:indexOfItem];
                
                //
                // 3. If the item exists and it is also not marked as contentSynthesized, it just needs to move to the front.
                //
                if (indexOfItem != 0)
                {
                    [self.activity removeObjectAtIndex:indexOfItem];
                    [self.activity insertObject:item atIndex:0];
                    
                    [self.tableView reloadData];
                    
                    //
                    // NOTE: End of line for this case, so we need to save the order and unpause the results delegate.
                    //
                    [self saveDataForKey:controllerKey];
                    [self.audioCaptureReader setResultsDelegate:self queue:dispatch_get_main_queue()];
                }
                else
                {
                    [self.audioCaptureReader setResultsDelegate:self queue:dispatch_get_main_queue()];
                }
            }
            else
            {
                //
                // 4. Or this is simply a new item that just needs to be sent to the resolver.
                //
                // Pausing detection
                [self.audioCaptureReader setResultsDelegate:nil queue:dispatch_get_main_queue()];
                
                [self resolvePayload:payload];
            }
        }
    }
}

- (void)processResolvedContent:(id)resolvedContent error:(NSError *)error
{
    dispatch_async(dispatch_get_main_queue(), ^{
        if (error)
        {
            [self displayAlertControllerWithTitle:@"EchotagDemo" andMessage:error.localizedDescription];
        }
        else
        {
            [self updateActivityForItem:resolvedContent];
        }
        [self.audioCaptureReader setResultsDelegate:self queue:dispatch_get_main_queue()];
    });
}

- (void)resolvePayload:(DMSPayload *)payload
{
    [[self.apiManager echotags] resolve:payload withCategories:YES withSubItems:YES queue:[NSOperationQueue mainQueue] completionBlock:^(id _Nonnull resolvedContent, NSError * _Nullable error) {
        [self processResolvedContent:resolvedContent error:error];
    }];
}

- (void)updateActivityForItem:(ETEchotag *)item {
    //
    // 1. Check to see if the this payload is already in the data array.
    //
    NSUInteger indexOfItem = [self.activity indexOfObjectPassingTest:^BOOL(id obj, NSUInteger index, BOOL *stop)
                              {
                                  if ([((ETEchotag *)obj).payloadId isEqualToString:item.payloadId])
                                  {
                                      *stop = YES;
                                      return YES;
                                  }
                                  
                                  return NO;
                              }];
    
    if (item.echotagType == TYPE_AD) {
        //
        // 2. If the item isn't in the data array, add it to the array and save to disk.
        //
        if (indexOfItem == NSNotFound)
        {
            [self.activity insertObject:item atIndex:0];
        }
        else
        {
            [self.activity removeObjectAtIndex:indexOfItem];
            [self.activity insertObject:item atIndex:0];
        }
        
        [self saveDataForKey:controllerKey];
        [self.tableView reloadData];
    } else if (item.echotagType == TYPE_QUIZ || item.echotagType == TYPE_SURVEY) {
        // Show Quiz View
        [self openQuizViewForItem:item];
    }
}

- (void)openQuizViewForItem:(ETEchotag *)item {
    QuizViewController *vc = [self.storyboard instantiateViewControllerWithIdentifier:@"QuizViewController"];

    vc.detailItem = item;
    vc.apiManager = self.apiManager;

    UINavigationController *nc = [[UINavigationController alloc] initWithRootViewController:vc];
    [vc.navigationItem setLeftBarButtonItem:[[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:vc action:@selector(removeFromScreen)]];

    [self presentViewController:nc animated:YES completion:nil];
}

- (void)startCaptureSession
{
    if ([self resolver])
    {
        [self.resolver cancelAllResolves];
    }
    
    dispatch_async(self.audioSessionQueue, ^{
        if (self.audioCaptureSession)
        {
            if (![self.audioCaptureSession isRunning])
            {
#if !(TARGET_IPHONE_SIMULATOR)
                [self.audioCaptureSession startRunning];
#endif
            }
        }
    });
}

- (void)stopCaptureSession
{
    [self.resolver cancelAllResolves];
    
    dispatch_async(self.audioSessionQueue, ^{
        if (self.audioCaptureSession)
        {
            if ([self.audioCaptureSession isRunning])
            {
                [self.audioCaptureSession stopRunning];
            }
        }
    });
}

#pragma mark - Table View

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ETEchotag *echotag = (ETEchotag *)self.activity[indexPath.row];
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"customcell"];
    [cell setBackgroundColor:[UIColor clearColor]];
    [cell.contentView setBackgroundColor:[UIColor clearColor]];
    
    UIImageView *imageView = (UIImageView *)[cell viewWithTag:1];
    UILabel *textLabel = (UILabel *)[cell viewWithTag:2];
    UILabel *detailLabel = (UILabel *)[cell viewWithTag:3];
    UILabel *categoryLabel = (UILabel *)[cell viewWithTag:4];
    
    [textLabel setFont:[UIFont preferredFontForTextStyle:UIFontTextStyleBody]];
    [detailLabel setFont:[UIFont preferredFontForTextStyle:UIFontTextStyleFootnote]];
    
    [textLabel setTextColor:[UIColor blackColor]];
    [categoryLabel setTextColor:[UIColor darkGrayColor]];
    [detailLabel setTextColor:[UIColor blackColor]];
    
    [textLabel setNumberOfLines:1];
    [categoryLabel setNumberOfLines:1];
    [detailLabel setNumberOfLines:1];
    
    NSString *titleString = ([echotag.item.company length] == 0) ? @" " : echotag.item.company;
    NSString *categoryString = ([echotag.categoryTitle length] == 0) ? @" " : echotag.categoryTitle;
    NSString *detailString = ([echotag.item.title length] == 0) ? @" " : echotag.item.title;
    NSString *imageName = @"echotag_placeholder";
    
    [textLabel setText:titleString];
    [categoryLabel setText:categoryString];
    [detailLabel setText:detailString];
    
    NSURL *thumbnailURL = (NSURL *)echotag.item.imageURL;
    
    UIImage *image = [self imageCacheContainsKey:thumbnailURL.absoluteString];
    if (image)
    {
        [imageView setImage:image];
        [imageView setContentMode:UIViewContentModeScaleAspectFill];
    }
    else
    {
        [imageView setContentMode:UIViewContentModeScaleAspectFill];
        [imageView setImage:[UIImage imageNamed:imageName]];
        [self downloadImageWithURL:thumbnailURL completionBlock:^(BOOL succeeded, UIImage *image)
         {
             if (succeeded)
             {
                 UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
                 if (cell && image)
                 {
                     [imageView setImage:image];
                     [imageView setContentMode:UIViewContentModeScaleAspectFill];
                     [self.tableView reloadData];
                 }
                 
                 if (image)
                 {
                     [self.imageCache setObject:image forKey:thumbnailURL.absoluteString];
                 }
             }
         }];
    }
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    ETEchotag *echotag = (ETEchotag *)self.activity[indexPath.row];
    
    [[self.apiManager echotags] report:echotag queue:[NSOperationQueue mainQueue] completionBlock:^(NSURL *url, NSError *error) {
        if (error) {
            [self displayAlertControllerWithTitle:@"EchotagDemo" andMessage:error.localizedDescription];
        } else {
            [self openURLInWebView:url withTitle:echotag.item.title];
            [self.tableView deselectRowAtIndexPath:indexPath animated:YES];
        }
    }];
}

- (NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewRowAction *deleteAction = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleDestructive title:@"Delete" handler:^(UITableViewRowAction *action, NSIndexPath *indexPath) {
        ETEchotag *echotag = (ETEchotag *)self.activity[indexPath.row];
        
        [self.tableView setEditing:NO animated:YES];
        [self.activity removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
        
        [[self.apiManager echotags] remove:echotag queue:[NSOperationQueue mainQueue] completionBlock:^(BOOL result, NSError *error) {
            if (error) {
                [self displayAlertControllerWithTitle:@"EchotagDemo" andMessage:error.localizedDescription];
            } else {
                [self saveDataForKey:controllerKey];
            }
        }];
    }];
    deleteAction.backgroundColor = [UIColor colorWithRed:0.98 green:0.13 blue:0.14 alpha:1.0];
    
    return @[deleteAction];
}

#pragma mark - Notification Center - AppDelegate

- (void) registerNotifications
{
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(applicationDidEnterBackgroundNotificationHandler:)
                                                 name:UIApplicationDidEnterBackgroundNotification
                                               object:nil];
}

- (void) unregisterNotifications
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void) applicationDidEnterBackgroundNotificationHandler:(NSNotification*)notification
{

}

#pragma mark - Notification Center - AVFoundation

- (void) registerCaptureSessionNotifications
{
    // Audio Capture Session Object
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(captureSessionRuntimeError:)
                                                 name:AVCaptureSessionRuntimeErrorNotification
                                               object:self.audioCaptureSession];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(captureSessionWasInterrupted:)
                                                 name:AVCaptureSessionWasInterruptedNotification
                                               object:self.audioCaptureSession];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(captureSessionInterruptionEnded:)
                                                 name:AVCaptureSessionInterruptionEndedNotification
                                               object:self.audioCaptureSession];
}

- (void) captureSessionRuntimeError:(NSNotification *)notification
{
    NSError *error = notification.userInfo[AVCaptureSessionErrorKey];
    NSLog(@"EchotagDemo - Capture Session Runtime Error: %@ (%ld)", error.localizedDescription, (long)error.code);
    
    self.audioSessionQueue = dispatch_queue_create("audio session queue", DISPATCH_QUEUE_SERIAL);

    self.audioCaptureSession = nil;
    self.audioCaptureReader = nil;
    
    [self setupAndRunDMSAudioCaptureReader];
}

- (void) captureSessionWasInterrupted:(NSNotification *)notification
{
    NSDictionary *userInfo = notification.userInfo;
    if (&AVCaptureSessionInterruptionReasonKey) // This constant only exists in iOS 9 or higher.
    {
        AVCaptureSessionInterruptionReason reason = (AVCaptureSessionInterruptionReason)[userInfo valueForKey:AVCaptureSessionInterruptionReasonKey];
        if (reason == AVCaptureSessionInterruptionReasonVideoDeviceNotAvailableWithMultipleForegroundApps)
        {
            // Typically, you cannot run the AV hardware until the other app using it releases them.
            NSLog(@"EchotagDemo - Capture Session: Device Not Available With Multiple Foreground Apps.");
        }
    }
}

- (void) captureSessionInterruptionEnded:(NSNotification *)notification
{
    // Start running the capture sessions again.
    [self startCaptureSession];
}

@end
