NUM = 1

def setup
  @balls = []
  @prev = false
end

def update
  ta = Input.touches.find_all { |e| e.release? }
  ta.each do |t|
    1.step NUM do |i|
      if i == 1
        @balls.push Ball.new t.x, t.y, 0
      else
        @balls.push Ball.new t.x + rand(100) - 50, t.y + rand(100) - 50, 0
      end
    end
  end
  @balls.each { |v| v.update }
end

def draw
  set_color_hex 0
  #text "#{Input.touch(0).x}", 0, 100
  @balls.each { |v| v.draw }
  set_color_hex 0x864040
  rect_rounded 0, 420, 320,20, 10
end

class Ball
  def initialize(x, y, init_speed)
    @x = x
    @y = y
    @accel = 0.098
    @speed = init_speed
    @color = rand(0xffffff)
  end

  def update
    @speed += @accel
    @y += @speed
    if @y > 410
      @y = 410
      @speed *= -0.8
    end
  end

  def draw
    #set_color_hex 0xd73a45
    set_color_hex @color
    set_fill
    circle @x, @y, 10
  end
end
