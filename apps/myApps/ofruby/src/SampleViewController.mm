#include "SampleViewController.h"

@interface SampleViewController ()

@end

@implementation SampleViewController

- (id)init
{
    self = [super initWithFileDirectory: [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"sample"]
                                  title: @"Sample"];
    return self;
}

@end

