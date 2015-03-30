module DebugInfo
  def self.fps
    "#{format("%3.2f", get_frame_rate)} fps"
  end

  def self.window
    "window_pos: (#{window_pos_x}, #{window_pos_y}), size: (#{window_width}, #{window_height})"
  end

  def self.mouse
    str = "mouse: "
    str += format("(%4d, %4d)", Input.mouse_x, Input.mouse_y)

    # press?
    str += " press?: "
    str += (0..2).map {|v|
      Input.mouse_press?(v) ? '1' : '0'
    }.join('')

    # down?
    str += " down?: "
    str += (0..2).map {|v|
      Input.mouse_down?(v) ? '1' : '0'
    }.join('')

    # release?
    str += " release?: "
    str += (0..2).map {|v|
      Input.mouse_release?(v) ? '1' : '0'
    }.join('')

    str
  end
end

module Console
  # FONT_HEIGHT = 13 # can't use CONSTANT at inner block
  @font_height = 13 

  def self.init(x, y, width = 600, height = 190)
    @x = x
    @y = y
    @width = width
    @height = height
    @line_num = (height / @font_height).to_i
    @text = []

    # Override Kernel#p
    Kernel.class_eval do
      alias org_p p

      def self.p(*args)
        org_p(*args)
        Console.p(*args)
      end
    end
  end

  def self.p(*arg)
    if arg.instance_of?(Array)
      @text += arg.map{|obj| obj.inspect }
    else
      @text << arg.inspect
    end
    arg
  end

  def self.draw
    return if @text.nil?
    
    @text = @text[@text.length - @line_num, @line_num] if @text.length > @line_num
    
    set_fill
    set_color(255, 255, 255)
    rect(@x, @y, @width, @height)

    set_no_fill
    set_color(0, 0, 0)
    rect(@x, @y, @width, @height)

    @text.each_with_index do |text, index|
      text(text, @x + 5, @y + @font_height + @font_height * index)
    end
  end

  def self.clear
    return if @text.nil?
    @text = []
  end
end

class SequenceShot
  def initialize(interval = 6, limit = 50)
    @interval = interval
    @limit    = limit
    @index    = 0
    @frame    = 0
  end

  def update
    return if @limit > 0 && @index >= @limit
    
    if @frame % @interval == 0
      Image.grab_screen.save("sequence_shot_#{sprintf("%03d", @index)}.png")
      @index += 1
    end
    
    @frame += 1
  end
end
