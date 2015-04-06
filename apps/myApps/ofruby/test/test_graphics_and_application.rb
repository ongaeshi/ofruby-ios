def setup
  set_background_auto true
  set_circle_resolution 128

  set_window_pos 100, 200
  set_window_size 640, 480
end

def update
end

def draw
  set_no_fill
  
  if is_fill
    set_color_hex 0xf0c000 
  else
    set_color_hex 0xffffff
  end
  rect 10, 10, 50, 30

  set_fill

  set_color_hex 0x00f0c0
  triangle 70, 10, 80, 30, 60, 30

  circle 90, 20, 10

  ellipse 110, 20, 10, 20

  set_color_hex 0x00c0ff
  line 130, 10, 150, 40

  rect_rounded 160, 10, 50, 30, 20

  set_color 0, 0, 0
  text "width: #{width}, height: #{height}", 10, 60
  text "frame_rate: #{frame_rate}", 10, 80
  text "window_pos: #{window_pos_x}, #{window_pos_y}", 10, 100
  text "window_size: #{window_width}, #{window_height}", 10, 120
  text "screen_size: #{screen_width}, #{screen_height}", 10, 140
  text "size: #{width}, #{height}", 10, 160
end
