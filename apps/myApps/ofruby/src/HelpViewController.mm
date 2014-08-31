#import "HelpViewController.h"

@interface HelpViewController ()

@end

@implementation HelpViewController

- (void)viewDidLoad
{
    [super viewDidLoad];

    // TextView
    CGRect rect = self.view.bounds;
    UITextView* textView = [[UITextView alloc]initWithFrame:rect];
    textView.editable = NO;
    textView.textAlignment = UITextAlignmentLeft;
    //textView.font = [UIFont fontWithName:@"Helvetica" size:14];
    //textView.backgroundColor = [UIColor whiteColor];
    textView.autocapitalizationType = UITextAutocapitalizationTypeNone;

    textView.text = @"circle(x, y, radius)\n"
        "ellipse(x, y, width, height)\n"
        "line(x1, y1, x2, y2)\n"
        "rect(x, y, w, h)\n"
        "rect_rounded(x, y, w, h, r)\n"
        "text(str, x, y)\n"
        "triangle(x1, y1, x2, y2, x3, y3)\n"
        "\n"
        "set_circle_resolution(res)\n"
        "set_fill(enable = true)\n"
        "set_no_fill()\n"
        "is_fill()\n"
        "set_line_width(width)\n"
        "set_color(r, g, b, a = 255)\n"
        "set_color_hex(hex, a = 255)\n"
        "set_background(r, g, b)\n"
        "set_background_hex(hex)\n"
        "set_background_auto(flag)\n"
        "\n"
        "get_frame_rate()\n"
        "width()\n"
        "height()\n"
        "window_width()\n"
        "window_height()\n"
        "screen_width()\n"
        "screen_height()\n"
        "\n"
        "srand()\n"
        "srand(seed)\n"
        "rand(max = 1.0)\n"
        "\n"
        "Input\n"
        "  Input.touch(idx)\n"
        "  Input.touches()\n"
        "\n"
        "TouchPoint\n"
        "  valid?\n"
        "  x\n"
        "  y\n"
        "  press?\n"
        "  down?\n"
        "  release?\n"
        ;

    [self.view addSubview:textView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
