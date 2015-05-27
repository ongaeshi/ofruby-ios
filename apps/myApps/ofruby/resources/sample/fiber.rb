def setup
  @rect = Rect.new
end

def update
  @rect.update
end

def draw
  @rect.draw
end

# ------------------------------
def wait(frame)
  1.upto(frame) { Fiber.yield }
end

class Rect
  attr_accessor :x
  
  def initialize
    @x = 0
    
    @fiber = Fiber.new do
      while true
        @x = 0
        wait 30
        
        @x = 50
        set_color_hex 0xc00000
        wait 30
        
        @x = 100
        set_color_hex 0x00c000
        wait 30
        
        @x = 150
        set_color_hex 0x0000c0
        wait 30
        
        @x = 200
        set_color_hex 0x000000
        wait 30
        
        @x = 250
        set_color_hex 0xffffff
        wait 30
        
        @x = 400
        wait 30
      end
    end
  end
  
  def update
    @fiber.resume if @fiber.alive?
  end
  
  def draw
    rect @x, 220, 80, 40
  end
end
