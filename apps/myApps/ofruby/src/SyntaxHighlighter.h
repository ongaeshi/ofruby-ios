#import <UIKit/UIKit.h>

@interface SyntaxHighlighter : NSObject

+ (NSAttributedString *)convertAttributedText:(NSString *)code;

@end
