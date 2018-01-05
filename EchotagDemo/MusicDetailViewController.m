//
//  MusicDetailViewController.m
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 05.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "MusicDetailViewController.h"
#import <EchotagSDK/EchotagSDK.h>

@interface MusicDetailViewController ()

@end

@implementation MusicDetailViewController {
    ETACRCloudManager *_acrCloudManager;
    
    UIScrollView *_scrollView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navigationItem.title = _detailItem.title ? _detailItem.title : @"What's the music?";
    
    _scrollView = [[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)];
    _scrollView.scrollEnabled = YES;
    _scrollView.showsVerticalScrollIndicator = YES;
    
    _acrCloudManager = [[ETACRCloudManager alloc] init];
    
    if (_detailItem) {
        [self showItemDetail];
    } else {
        [self recognizeMusic];
    }
    
    [self.view addSubview:_scrollView];
}

- (void)removeFromScreen {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)showItemDetail {
    [self clearView];
    
    UIImageView *artworkImageView =[[UIImageView alloc] initWithFrame:CGRectMake(10, 17, 80, 80)];
    UITextView *resultView = [[UITextView alloc] initWithFrame:CGRectMake(100, 17, 210, 80)];
    resultView.editable = NO;
    resultView.showsVerticalScrollIndicator = NO;
    resultView.showsHorizontalScrollIndicator = NO;
    resultView.font = [UIFont fontWithName: @"Trebuchet MS" size: 12.0f];
    
    NSString *imageName = @"echotag_placeholder";
    NSURL *thumbnailURL = (NSURL *)_detailItem.artworkUrl;
    UIImage *image = [self imageCacheContainsKey:thumbnailURL.absoluteString];
    if (image)
    {
        artworkImageView.image = image;
        [artworkImageView setContentMode:UIViewContentModeScaleAspectFill];
    }
    else
    {
        [artworkImageView setContentMode:UIViewContentModeScaleAspectFill];
        [artworkImageView setImage:[UIImage imageNamed:imageName]];
        [self downloadImageWithURL:thumbnailURL completionBlock:^(BOOL succeeded, UIImage *image)
         {
             if (succeeded)
             {
                 if (image)
                 {
                     [artworkImageView setImage:image];
                     [artworkImageView setContentMode:UIViewContentModeScaleAspectFill];

                     [_imageCache setObject:image forKey:thumbnailURL.absoluteString];
                 }
             }
         }];
    }
    
    NSString *artist = _detailItem.artist ? [NSString stringWithFormat:@"Artist: %@", _detailItem.artist] : @"";
    NSString *album = _detailItem.album ? [NSString stringWithFormat:@"Album: %@", _detailItem.album] : @"";
    NSString *title = _detailItem.title ? [NSString stringWithFormat:@"Title: %@", _detailItem.title] : @"";
    NSString *genres = _detailItem.genres ? [NSString stringWithFormat:@"Genres: %@", _detailItem.genres] : @"";
    NSString *releaseDate = _detailItem.releaseDate ? [NSString stringWithFormat:@"Release Date: %@", _detailItem.releaseDate] : @"";
    
    NSArray *ra = @[title, artist, album, genres, releaseDate];
    
    NSPredicate *pred = [NSPredicate predicateWithBlock:^BOOL(id str, NSDictionary *unused) {
        return ![str isEqualToString:@""];
    }];
    ra = [ra filteredArrayUsingPredicate:pred];
    
    resultView.text = [ra componentsJoinedByString:@"\n"];
    
    UILabel *warningLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, 100, self.view.frame.size.width - 20, 20)];
    warningLabel.text = @"Listen to this track at the below sources:";
    warningLabel.hidden = YES;
    
    //youtube info show
    if (_detailItem.youtubeId) {
        warningLabel.hidden = NO;
        
        UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectMake(0, 264, self.view.frame.size.width, 200)];
        [webView setAllowsInlineMediaPlayback:YES];
        [webView setMediaPlaybackRequiresUserAction:NO];
        
        [_scrollView addSubview:webView];
        
        NSString* embedHTML = [NSString stringWithFormat:@"\
                               <html>\
                               <body style='margin:0px;padding:0px;'>\
                               <script type='text/javascript' src='http://www.youtube.com/iframe_api'></script>\
                               <script type='text/javascript'>\
                               function onYouTubeIframeAPIReady()\
                               {\
                               ytplayer=new YT.Player('playerId',{events:{onReady:onPlayerReady}})\
                               }\
                               function onPlayerReady(a)\
                               { \
                               \\a.target.playVideo(); \
                               }\
                               </script>\
                               <iframe id='playerId' type='text/html' width='%f' height='%f' src='http://www.youtube.com/embed/%@?enablejsapi=1&rel=0&playsinline=1&autoplay=0' frameborder='0'>\
                               </body>\
                               </html>", self.view.frame.size.width, 200.0, _detailItem.youtubeId];
        [webView loadHTMLString:embedHTML baseURL:[[NSBundle mainBundle] resourceURL]];
    }
    
    [_scrollView addSubview:artworkImageView];
    [_scrollView addSubview:resultView];
    [_scrollView addSubview:warningLabel];
}

- (void)recognizeMusic {
    [self prepareToRecognize];
    
    [_acrCloudManager startFingerprintRecognitionWithCompletionBlock:^(ETMusic *music, NSError *error) {
        [_acrCloudManager stopFingerprintRecognition];
        dispatch_async(dispatch_get_main_queue(), ^{
            if (error) {
                [self failedRecognize];
            } else {
                _detailItem = music;
                [self showItemDetail];
                
                [_apiManager.musics report:music queue:[NSOperationQueue mainQueue] completionBlock:^(BOOL success, NSError *error) {
                    if (error) {
                        [_delegate displayAlertWithTitle:@"EchotagDemo" andMessage:error.localizedDescription];
                    } else {
                        [_delegate updateMusicActivity:music];
                    }
                }];
            }
        });
    }];
}

- (void)prepareToRecognize {
    [self clearView];
    
    UILabel *infoLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 100, self.view.frame.size.width, 20)];
    infoLabel.font = [UIFont fontWithName: @"Trebuchet MS" size: 18.0f];
    infoLabel.textAlignment = NSTextAlignmentCenter;
    infoLabel.text = @"Listening...";
    
    UIActivityIndicatorView *waitIndicator = [[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(240, 100, 20, 20)];
    waitIndicator.color = [UIColor grayColor];
    [waitIndicator startAnimating];
    
    [_scrollView addSubview:infoLabel];
    [_scrollView addSubview:waitIndicator];
}

- (void)failedRecognize {
    [self clearView];
    
    UILabel *infoLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, 100, self.view.frame.size.width, 20)];
    infoLabel.font = [UIFont fontWithName: @"Trebuchet MS" size: 18.0f];
    infoLabel.textAlignment = NSTextAlignmentCenter;
    infoLabel.text = @"Unable to recognize";
    
    UIButton *tryAgainButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 140, self.view.frame.size.width, 20)];
    [tryAgainButton setTitle:@"Try again" forState:UIControlStateNormal];
    [tryAgainButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    [tryAgainButton addTarget:self action:@selector(recognizeMusic) forControlEvents:UIControlEventTouchUpInside];
    
    [_scrollView addSubview:infoLabel];
    [_scrollView addSubview:tryAgainButton];
}

- (void)clearView {
    for (UIView *v in [_scrollView subviews]) {
        [v removeFromSuperview];
    }
}

-(UIImage *)imageCacheContainsKey:(NSString *)key
{
    UIImage *image = [_imageCache objectForKey:key];
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
