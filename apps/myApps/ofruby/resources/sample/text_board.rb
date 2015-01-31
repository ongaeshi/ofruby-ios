TEXT = "Hello, ofruby!"
# TEXT = "abcdefghijklmnopqrstuvwxyzANCDEFGHIJKLMNOPQRSTIVWXYZ1234567890-/:;()&@.,?!'"
TEXT_WIDTH = 8
SCALE = 3
SPEED = 3
COLOR = rand 0xffffff
BACK = 0x000000

def setup
  set_background_hex BACK
  @texts = []
  @texts.push Texter.new(TEXT)
end

def update
  @texts.each { |e| e.update }
end

def draw
    @texts.each { |e| e.draw }
end

class Texter
  def initialize(text)
    @text = text
    @width = text.length * TEXT_WIDTH * SCALE
    @x = 0
    @y = height / 2
    @rot = 0
  end

  def update
    @x += SPEED
    @x = -@width if @x > width + @width
  end

  def draw
    push_matrix do
      translate @x, @y
      scale SCALE, SCALE * 2
      set_color_hex COLOR
      text @text, 0, 0
    end
  end
end
