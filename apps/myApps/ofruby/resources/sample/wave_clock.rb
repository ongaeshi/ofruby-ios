def setup
  # srand 0

  set_background_auto false
  set_no_fill 
  set_line_width 1

  @radius_noise = rand 10
  @angle_noise = rand 10
  @angle = -Math::PI * 0.5
  @color = 254
  @color_speed = -1
  @x_noise = rand 10
  @y_noise = rand 10
end

def draw
  @radius_noise += 0.007
  radius = noise(@radius_noise) * 350 + 1

  @angle_noise += 0.005
  @angle += noise(@angle_noise) * 6 - 3
  @angle -= 360 if @angle > 360
  @angle += 360 if @angle < 0

   @color += @color_speed
   @color_speed = -1 if @color > 254
   @color_speed = 1 if @color < 0
   set_color @color, @color, @color, 60

  @x_noise += 0.01
  @y_noise += 0.01
  centerx = width / 2 + noise(@x_noise) * 64 - 32
  centery = height / 2 + noise(@y_noise) * 64 - 32

  rad = deg_to_rad(@angle)
    
  x1 = centerx + radius * Math.cos(rad)
  y1 = centery + radius * Math.sin(rad)

  opprad = rad + Math::PI
  x2 = centerx + radius * Math.cos(opprad)
  y2 = centery + radius * Math.sin(opprad)

  line x1, y1, x2, y2
end
