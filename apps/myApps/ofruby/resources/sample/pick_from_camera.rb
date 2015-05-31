COLOR = 0xdd4b64

def setup
  set_background_hex 0x000000

  # Image.pick_from_camera
  Image.pick_from_library

  @points = []
end

def update
  if @img.nil?
    @img ||= Image.receive_picked

    if @img
      sca = width / @img.width
      @img.resize width, @img.height * sca
    end
  end

  t = Input.touch(0)
  if t.valid?
    @points.push Point.new(t.x, t.y)
  end
end

def draw
  set_color_hex 0xffffff
  @img.draw(0, img_y) if @img

  set_color_hex COLOR
  @points.each do |point|
    circle point.x, point.y, 10
  end
end

#--------
def img_y
  if @img.height < height
    (height - @img.height) * 0.5
  else
     0
  end
end

class Point
  attr_reader :x, :y
  def initialize(x, y)
    @x, @y = x, y
  end
end
