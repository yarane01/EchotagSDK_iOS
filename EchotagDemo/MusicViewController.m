//
//  MusicViewController.m
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 18.11.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "MusicViewController.h"
#import "MusicDetailViewController.h"

static NSString *const controllerKey = @"music";

@interface MusicViewController () <MusicDetailViewControllerDelegate>

@end

@implementation MusicViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    [self.imageCache setName:@"Music Image Cache"];
    [self.imageCache setCountLimit:100];
    
    [self createRightMenuButton];
}

- (void)initActivity {
    self.activity = [self loadDataForKey:controllerKey];
    if (self.activity.count == 0) {
        [[self.apiManager musics] itemsWithPage:0 perPage:0 queue:[NSOperationQueue mainQueue] completionBlock:^(NSArray * __nullable offers, NSError * __nullable error) {
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

- (void)createRightMenuButton {
    UIButton *rightButton = [UIButton buttonWithType:UIButtonTypeCustom];
    rightButton.frame = CGRectMake(0, 0, 25.0, 25.0);
    [rightButton setBackgroundImage:[UIImage imageNamed:@"target"] forState:UIControlStateNormal];
    [rightButton addTarget:self action:@selector(clickRightMenuButton) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithCustomView:rightButton];
}

- (void)clickRightMenuButton {
//    [self openDetailViewForMusic:nil];
    [self performSegueWithIdentifier:@"recognizingMusic" sender:self];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
    UINavigationController *navController = (UINavigationController *)segue.destinationViewController;
    MusicDetailViewController *musicDVC = (MusicDetailViewController *)navController.topViewController;
    musicDVC.delegate = self;
    [musicDVC.navigationItem setLeftBarButtonItem:[[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:musicDVC action:@selector(removeFromScreen)]];
    ETMusic *music = (ETMusic *)self.activity[indexPath.row];
    musicDVC.imageCache = self.imageCache;
    musicDVC.apiManager = self.apiManager;
    if ([[segue identifier] isEqualToString:@"showMusicDetail"]) {
        musicDVC.detailItem = music;
    } else if ([[segue identifier] isEqualToString:@"recognizingMusic"]) {
        musicDVC.detailItem = nil;
    }
}

#pragma mark - Table View

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    ETMusic *music = (ETMusic *)self.activity[indexPath.row];
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"customcell"];
    [cell setBackgroundColor:[UIColor clearColor]];
    [cell.contentView setBackgroundColor:[UIColor clearColor]];
    
    UIImageView *imageView = (UIImageView *)[cell viewWithTag:1];
    UILabel *artistLabel = (UILabel *)[cell viewWithTag:2];
    UILabel *titleLabel = (UILabel *)[cell viewWithTag:3];
    UILabel *albumLabel = (UILabel *)[cell viewWithTag:4];
    
    [artistLabel setFont:[UIFont preferredFontForTextStyle:UIFontTextStyleBody]];
    [albumLabel setFont:[UIFont preferredFontForTextStyle:UIFontTextStyleFootnote]];
    
    [artistLabel setTextColor:[UIColor blackColor]];
    [albumLabel setTextColor:[UIColor darkGrayColor]];
    [titleLabel setTextColor:[UIColor blackColor]];
    
    [artistLabel setNumberOfLines:1];
    [albumLabel setNumberOfLines:1];
    [titleLabel setNumberOfLines:1];
    
    NSString *artistString = ([music.artist length] == 0) ? @" " : music.artist;
    NSString *albumString = ([music.album length] == 0) ? @" " : music.album;
    NSString *titleString = ([music.title length] == 0) ? @" " : music.title;
    NSString *imageName = @"echotag_placeholder";
    
    [artistLabel setText:artistString];
    [albumLabel setText:albumString];
    [titleLabel setText:titleString];
    
    NSURL *thumbnailURL = (NSURL *)music.artworkUrl;
    
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
//    ETMusic *music = (ETMusic *)self.activity[indexPath.row];
//    [self openDetailViewForMusic:music];
    [self performSegueWithIdentifier:@"showMusicDetail" sender:self];
}

- (NSArray<UITableViewRowAction *> *)tableView:(UITableView *)tableView editActionsForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewRowAction *deleteAction = [UITableViewRowAction rowActionWithStyle:UITableViewRowActionStyleDestructive title:@"Delete" handler:^(UITableViewRowAction *action, NSIndexPath *indexPath) {
        ETMusic *music = (ETMusic *)self.activity[indexPath.row];
        
        [self.tableView setEditing:NO animated:YES];
        [self.activity removeObjectAtIndex:indexPath.row];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
        
        [[self.apiManager musics] remove:music queue:[NSOperationQueue mainQueue] completionBlock:^(BOOL result, NSError *error) {
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

#pragma mark - MusicDetailViewControllerDelegate methods

- (void)updateMusicActivity:(ETMusic *)music {
    [self.activity insertObject:music atIndex:0];
    [self.tableView reloadData];
    [self saveDataForKey:controllerKey];
}

- (void)displayAlertWithTitle:(NSString *)title andMessage:(NSString *)message {
    [self displayAlertWithTitle:title andMessage:message];
}

@end
