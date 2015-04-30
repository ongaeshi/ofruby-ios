#import "SyntaxHighlighter.h"

@implementation SyntaxHighlighter

+ (NSAttributedString *)convertAttributedText:(NSString *)src
{
    NSMutableAttributedString *dst = [[NSMutableAttributedString alloc] initWithString:src];
    NSRange srcRange = NSMakeRange(0,[src length]);
    
    NSRegularExpression* regex = [NSRegularExpression regularExpressionWithPattern:@"#[^\r\n]*[\r\n]"
                                                                           options:NSRegularExpressionDotMatchesLineSeparators
                                                                             error:nil];
    NSArray* matches = [regex matchesInString:src options:0 range:srcRange];

    for (NSTextCheckingResult* match in matches) {
        [dst addAttribute:NSForegroundColorAttributeName
                    value:[UIColor colorWithRed:0.00 green:0.50 blue:0.00 alpha:1.0]
                    range:[match rangeAtIndex:0]];
    }

    return dst;
}

@end
