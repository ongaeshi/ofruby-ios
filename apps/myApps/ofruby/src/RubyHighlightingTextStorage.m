#import "RubyHighlightingTextStorage.h"

@implementation RubyHighlightingTextStorage
{
	NSMutableAttributedString* mStr;
}

- (id)init
{
	self = [super init];
	
	if (self) {
		mStr = [NSMutableAttributedString new];
	}
	
	return self;
}

- (NSString *)string
{
	return mStr.string;
}

- (NSDictionary *)attributesAtIndex:(NSUInteger)location effectiveRange:(NSRangePointer)range
{
	return [mStr attributesAtIndex:location effectiveRange:range];
}

- (void)replaceCharactersInRange:(NSRange)range withString:(NSString *)str
{
	[mStr replaceCharactersInRange:range withString:str];
	[self edited:NSTextStorageEditedCharacters range:range changeInLength:(NSInteger)str.length - (NSInteger)range.length];
}

- (void)setAttributes:(NSDictionary *)attrs range:(NSRange)range
{
	[mStr setAttributes:attrs range:range];
	[self edited:NSTextStorageEditedAttributes range:range changeInLength:0];
}

- (void)processEditing
{
	static NSRegularExpression *iExpression;
	iExpression = iExpression ?: [NSRegularExpression regularExpressionWithPattern:@"#[^\r\n]*[\r\n]" options:0 error:NULL];
	
	NSRange paragaphRange = [self.string paragraphRangeForRange: self.editedRange];
	[self removeAttribute:NSForegroundColorAttributeName range:paragaphRange];
	
	[iExpression enumerateMatchesInString:self.string options:0 range:paragaphRange usingBlock:^(NSTextCheckingResult *result, NSMatchingFlags flags, BOOL *stop) {
            [self addAttribute:NSForegroundColorAttributeName value:[UIColor colorWithRed:0.00 green:0.50 blue:0.00 alpha:1.0] range:result.range];
        }];
  
    [super processEditing];
}

@end
