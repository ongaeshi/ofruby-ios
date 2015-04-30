#import "SyntaxHighlighter.h"

@implementation SyntaxHighlighter

+ (NSAttributedString *)convertAttributedText:(NSString *)code
{
    NSMutableAttributedString *dst = [[NSMutableAttributedString alloc] initWithString:code];
    
    [dst addAttribute:NSForegroundColorAttributeName
                value:[UIColor colorWithRed:0.00 green:0.50 blue:0.00 alpha:1.0]
                range:NSMakeRange(0, 10)];

    return dst;
}

@end
