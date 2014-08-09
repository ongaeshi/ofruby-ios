RADIUS = 100
SPEED  = 1

def setup
  # set_window_size(640, 480)
  # set_window_pos(0, 0)
  set_background(127, 127, 127)

  @y = RADIUS
  @speed = SPEED

  @x = RADIUS * 0.5
  @speed_x = SPEED * 1.5
end

def update
  @y += @speed
  @speed *= -1.0 if @y > 480 - RADIUS || @y < RADIUS

  @x += @speed_x
  @speed_x *= -1.0 if @x > 320 - RADIUS * 0.5 || @x < RADIUS * 0.5
end

def draw
  # shape
  set_fill
  set_line_width(1)
  set_color(150, 195, 17)
  circle(150, @y, RADIUS)

  set_color(240, 60, 60)
  circle(@x, 240, RADIUS * 0.5)

  # text
  set_color(0, 0, 0)
  text("Hello world!", 100, 240)
  
  # debug info
  # set_color(0, 0, 0)
  # text(DebugInfo.fps, 10, 15)
  # text(DebugInfo.window, 10, 30)
  # text(DebugInfo.mouse, 10, 45)
end
