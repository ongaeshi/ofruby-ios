SIZE = 20
ROTATE = 30
COLOR1 = 0xC9F8F1
COLOR2 = 0xCA3C6E

def setup
  @size = SIZE
  @color1 = COLOR1
  @color2 = COLOR2
end

def draw
  set_background_hex 0xffffff
  set_fill

  if Input.touch(0).valid? && Input.touch(1).valid?
    @size = SIZE
    @color1 = COLOR1
    @color2 = COLOR2
  elsif Input.touch(0).press?
    @size = SIZE + rand(SIZE) - 5
    @color1 = rand(0xffffff)
    @color2 = rand(0xffffff)
  end

  rotate ROTATE

  0.step height, @size*2 do |i|
    set_color_hex @color1
    rect 0, i, width, @size
    set_color_hex @color2
    rect i, 0, @size, height
  end
end
