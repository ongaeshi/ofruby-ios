def setup
  set_background 128, 128, 128
  @y = 0
end

def update
  @y += 1
end

def draw
  set_color 50, 200, 50
  circle 160, 200, 100

  set_color 200, 50, 50
  circle 200, @y, 50

  set_color 0, 0, 0
  text "Hello world!", 120, 160
end

