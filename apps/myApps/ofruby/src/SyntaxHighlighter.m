#import "SyntaxHighlighter.h"

@implementation SyntaxHighlighter

+ (NSAttributedString *)convertAttributedText:(NSString *)src
{
    NSMutableAttributedString *dst = [[NSMutableAttributedString alloc] initWithString:src];
    NSRange srcRange = NSMakeRange(0,[src length]);

    NSArray* syntaxArray = [[NSArray alloc] initWithObjects:
        //                                pattern,            color
        [[NSArray alloc] initWithObjects: @"#[^\r\n]*[\r\n]", [UIColor colorWithRed:0.00 green:0.50 blue:0.00 alpha:1.0], nil],
        nil
        ];

    for (NSArray* highlightRule in syntaxArray) {
        NSRegularExpression* regex = [NSRegularExpression regularExpressionWithPattern:highlightRule[0]
                                                                               options:NSRegularExpressionDotMatchesLineSeparators
                                                                                 error:nil];
        NSArray* matches = [regex matchesInString:src options:0 range:srcRange];

        for (NSTextCheckingResult* match in matches) {
            [dst addAttribute:NSForegroundColorAttributeName
                        value:highlightRule[1]
                        range:[match rangeAtIndex:0]];
        }
    }

    return dst;
}

@end
