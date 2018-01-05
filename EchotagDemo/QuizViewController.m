//
//  QuizViewController.m
//  EchotagDemo
//
//  Created by Alexandr Shevchuk on 06.12.2017.
//  Copyright © 2017 Echotag Corp. All rights reserved.
//

#import "QuizViewController.h"

int const QUESTION_TITLE_TAG = 20;
int const QUESTION_TAG = 30;

@interface QuizViewController ()

@end

@implementation QuizViewController {
    UIScrollView *_scrollView;
    UIView *_ansewrView;
    CGFloat _globalHeight;
    NSMutableArray *_answersItems;
    NSMutableArray *_sponsorsItems;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    self.navigationItem.title = _detailItem.item.company;
    
    _globalHeight = 15.0f;
    
    _answersItems = [[NSMutableArray alloc] init];
    _sponsorsItems = [[NSMutableArray alloc] init];
    
    _scrollView = [[UIScrollView alloc] initWithFrame:self.view.frame];
    _scrollView.showsVerticalScrollIndicator = YES;
    _scrollView.scrollEnabled = YES;
    [self.view addSubview:_scrollView];
    
    [self displayQuestion];
    [self displayAnswers];
}

- (void)removeFromScreen {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)displayQuestion {
    UIFont *font = [UIFont fontWithName:@"HelveticaNeue" size:14.0f];
    NSDictionary *attributes = @{ NSFontAttributeName:font };
    
    NSString *text = _detailItem.item.title;
    CGSize sizeOfText = [text sizeWithAttributes:attributes];
    UILabel *titleLabel = [[UILabel alloc] initWithFrame:CGRectMake(10, _globalHeight, 300, sizeOfText.height)];
    titleLabel.text = text;
    titleLabel.numberOfLines = 0;
    [titleLabel sizeToFit];
    titleLabel.textAlignment = NSTextAlignmentCenter;
    titleLabel.center = CGPointMake(CGRectGetMidX(_scrollView.bounds), titleLabel.center.y);
    titleLabel.font = font;
    titleLabel.tag = QUESTION_TITLE_TAG;
    _globalHeight += titleLabel.frame.size.height;
    
    UIImageView *imageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, _globalHeight, _scrollView.frame.size.width, 220)];
    [imageView setContentMode:UIViewContentModeScaleAspectFit];
    [imageView setImage:[UIImage imageNamed:@"echotag_placeholder"]];
    [self downloadImageWithURL:_detailItem.item.imageURL completionBlock:^(BOOL succeeded, UIImage *image) {
         if (succeeded && image) {
             [imageView setImage:image];
             [imageView setContentMode:UIViewContentModeScaleAspectFit];
         }
     }];

    _globalHeight += imageView.frame.size.height;
    
    text = _detailItem.item.question;
    sizeOfText = [text sizeWithAttributes:attributes];
    
    UITextView *questionText = [[UITextView alloc] initWithFrame:CGRectMake(10, _globalHeight, _scrollView.frame.size.width - 20, sizeOfText.height)];
    [questionText layoutIfNeeded];
    questionText.text = text;
    questionText.font = font;
    questionText.editable = NO;
    questionText.selectable = NO;
    questionText.textAlignment = NSTextAlignmentCenter;
    questionText.tag = QUESTION_TAG;
    CGRect frame = questionText.frame;
    frame.size.height = questionText.contentSize.height;
    questionText.frame = frame;
    _globalHeight += questionText.frame.size.height;
    
    [_scrollView addSubview:titleLabel];
    [_scrollView addSubview:imageView];
    [_scrollView addSubview:questionText];
}

- (void)displayAnswers {
    for (ETEchotag *subItem in _detailItem.subItems) {
        if (subItem.echotagType == TYPE_AD) {
            [_sponsorsItems addObject:subItem];
        } else if (subItem.echotagType == TYPE_QUIZ || subItem.echotagType == TYPE_SURVEY) {
            [_answersItems addObject:subItem];
        }
    }
    UIFont *font = [UIFont fontWithName:@"HelveticaNeue" size:14.0f];
    _ansewrView = [[UIView alloc] initWithFrame:CGRectMake(10, _globalHeight, _scrollView.frame.size.width, 186)];
    
    ETEchotag *echotag;
    for (int i = 0; i < [_answersItems count]; i++) {
        echotag = [_answersItems objectAtIndex:i];
        
        UIButton *answerButton;
        answerButton = [UIButton buttonWithType:UIButtonTypeSystem];
        answerButton.frame = CGRectMake(0, i * 70, _scrollView.frame.size.width -20, 60);
        
        UIView *answerButtonView = [[UIView alloc] initWithFrame:CGRectMake(0, 0, _scrollView.frame.size.width - 20, 60)];
        answerButtonView.userInteractionEnabled = NO;
    
        answerButton.backgroundColor = [UIColor lightGrayColor];
        
        UILabel *numberAnswerLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, 18, 20, 20)];
        numberAnswerLabel.font = [UIFont fontWithName:@"HelveticaNeue" size:20.0f];
        numberAnswerLabel.text = [NSString stringWithFormat:@"%d", i + 1];
        [answerButtonView addSubview:numberAnswerLabel];
        
        UITextView *answerText = [[UITextView alloc] initWithFrame:CGRectMake(50, 0, 300, 60)];
        [answerText layoutIfNeeded];
        answerText.text = echotag.item.answer;
        answerText.font = font;
        answerText.backgroundColor = [UIColor clearColor];
        answerText.editable = NO;
        answerText.selectable = NO;
        
        CGFloat topCorrect = ([answerText bounds].size.height - [answerText contentSize].height * [answerText zoomScale])/2.0;
        topCorrect = ( topCorrect < 0.0 ? 0.0 : topCorrect );
        answerText.contentOffset = (CGPoint){.x = 0, .y = -topCorrect};
        
        [answerButtonView addSubview:answerText];
        
        answerButton.tag = i;
        [answerButton addTarget:self action:@selector(answerTapDetected:) forControlEvents:UIControlEventTouchUpInside];
        
        [answerButton addSubview:answerButtonView];
        
        [_ansewrView addSubview:answerButton];
    }
    
    _globalHeight += _ansewrView.frame.size.height;
    [_scrollView addSubview:_ansewrView];
    _scrollView.contentSize = CGSizeMake(self.view.frame.size.width, _globalHeight);
}

- (void)answerTapDetected:(UIButton *)sender {
    ETEchotag *echotag = [_answersItems objectAtIndex:(NSUInteger) sender.tag];
    
    [[_apiManager echotags] report:echotag queue:[NSOperationQueue mainQueue] completionBlock:^(NSURL *url, NSError *error) {
        if (error) {
            NSLog(@"Error: %@", error.localizedDescription);
        }
    }];
    
    for (UIView *v in [_ansewrView subviews]) {
        [v removeFromSuperview];
    }
    
    UILabel *resultTitleLable = [[UILabel alloc] initWithFrame:CGRectMake(0, 50, _ansewrView.frame.size.width, 30)];
    resultTitleLable.text = echotag.item.afterAnswer;
    resultTitleLable.font = [UIFont fontWithName:@"HelveticaNeue" size:16.0f];
    resultTitleLable.textAlignment = NSTextAlignmentCenter;
    
    UIButton *resultButton = [[UIButton alloc] initWithFrame:CGRectMake(0, 110, 80, 20)];
    [resultButton setTitle:@"Done" forState:UIControlStateNormal];
    [resultButton setTitleColor:[UIColor blueColor] forState:UIControlStateNormal];
    [resultButton addTarget:self action:@selector(removeFromScreen) forControlEvents:UIControlEventTouchUpInside];
    resultButton.center = CGPointMake(CGRectGetMidX(self.view.bounds), 110);
    
    [_ansewrView addSubview:resultTitleLable];
    [_ansewrView addSubview:resultButton];
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
