def setup
  set_no_fill
  set_background_auto false

  @player = Player.new(width/2, 420)
  @ball = Ball.new(width/2, height/2)
  @info = Info.new

  @blocks = []
  0.step 280, 40 do |x|
    0.step 40, 20 do |y|
      @blocks.push Block.new(x, y)
    end
  end

  @fade_alpha = 255
end

def update
  @player.update
  @ball.update(@player, @info)
  @blocks.each { |v| 
    if v.update(@ball)
      @info.inc_score
      break
    end
  }

  clear = !@blocks.find { |v| !v.hide }
  if clear && @ball.pos.y > 200
    @blocks = []
    0.step 280, 40 do |x|
      0.step 40, 20 do |y|
        @blocks.push Block.new(x, y)
      end
    end
    @ball.speed_up
    @fade_alpha -= 40
    @fade_alpha = 40 if @fade_alpha < 40
  end
end

def draw
  fade
  set_no_fill
  set_color 0, 0, 0
  @player.draw
  @ball.draw
  @blocks.each { |v| v.draw }
  @info.draw
end

class Block
  attr_reader :hide
  def initialize(x, y)
    @pos = Pos.new x, y
  end

  def update(ball)
    unless @hide
      if (@pos.x..@pos.x+40).include?(ball.pos.x) &&
         (@pos.y..@pos.y+40).include?(ball.pos.y)
        @hide = true
        ball.hit_block
        return true
      end
    end

    false
  end

  def draw
    unless @hide
      rect @pos.x, @pos.y, 40, 20 
    end
  end
end

class Player
  attr_reader :pos

  def initialize(x, y)
    @pos = Pos.new(x, y)
  end

  def update
    t = Input.touch 0
    if t.valid?
      @pos.x = t.x - 25
    end
  end

  def draw
    rect @pos.x, @pos.y, 50, 10
  end
end

class Ball
  attr_reader :pos

  def initialize(x, y)
    @pos = Pos.new(x, y)
    @speed = Pos.new 4, 4
  end

  def update(player, info)
    @pos += @speed
    @speed.x *= -1 if @pos.x < 0 || @pos.x > width
    @speed.y *= -1 if @pos.y < 0

    x = @pos.x
    y = @pos.y

    pp = player.pos
    
    if (pp.x..pp.x+50).include?(@pos.x) &&
       (pp.y..pp.y+10).include?(@pos.y)
      @speed.y *= -1
    end

    if info.life > 0 && @pos.y > 900
      @pos.y = 150
      info.dec_life
    end
  end

  def draw
    circle @pos.x, @pos.y, 3
  end

   def hit_block
      @speed.y *= -1
   end

   def speed_up
      @speed.x *= 1.2
      @speed.y *= 1.2
    end
end

class Pos
  attr_accessor :x
  attr_accessor :y
  
  def initialize(x, y)
    @x = x
    @y = y
  end

  def +(rhs)
    Pos.new(@x + rhs.x, @y + rhs.y)
  end
end

class Info
  attr_reader :life

  def initialize
    @score = 0
    @life = 3
  end
  
  def dec_life
    @life -= 1
  end

  def inc_score
    @score += 1
  end
  
  def draw
    set_color 0, 0, 0
    text "Score: #{@score}", 10, 15
    text "Life: #{@life}", 10, 35
  end
end

def fade
  set_fill
  #set_color 255, 255, 255, 40
  set_color 255, 255, 255, @fade_alpha
  rect 0, 0, width, height
end
