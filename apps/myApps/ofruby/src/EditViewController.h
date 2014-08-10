//
//  EditViewController.h
//  ofruby
//
//  Created by ongaeshi on 2014/08/09.
//
//

#import <UIKit/UIKit.h>

@interface EditViewController : UIViewController<UITextViewDelegate> {
@private
    NSString* mFileName;
    UITextView* mTextView;
}

- (id) initWithFileName:(NSString*)aFileName;

@end
;
