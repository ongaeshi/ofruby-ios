SIZE = 20

def setup
  @size = SIZE
end

def draw
  set_background_hex 0xffffff
  set_fill

  if Input.touch(0).valid? && Input.touch(1).valid?
    # Do nothing
  elsif Input.touch(0).valid?
    @size += 3
  else
    @size -= 5
    @size = SIZE if @size < SIZE
  end

  0.step height, @size*2 do |i|
    set_color_hex 0xC9F8F1
    rect 0, i, width, @size
    set_color_hex 0xCA3C6E
    rect i, 0, @size, height
  end
end
