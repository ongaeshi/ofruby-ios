WIDTH = 320
HEIGHT = 480
SIZE = 20

def draw
  set_background 255, 255, 255
  set_fill

  0.step(HEIGHT, SIZE*2) do |i| 
    set_color_hex 0xC9E8F1
    rect 0, i, WIDTH, SIZE
    set_color_hex 0xCA3C6E
    rect i, 0, SIZE, HEIGHT
  end
end
