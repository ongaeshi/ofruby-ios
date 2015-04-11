X = 4
MOVABLE_RANGE = 200
PAGE = 13

def setup
  set_background 255, 255, 255

  @emojis = []
  EMOJI.each_with_index do |e, i|
    @emojis.push Emoji.new(i, 60 * (i % X) + 10 , (i / X).to_i * 60 + 10)
  end

  @screen_y = 0
end

def update
  t = Input.touch(0)
  
  if t.valid? && t.press?
    if t.y > (height - MOVABLE_RANGE)
      if @screen_y > height * -(PAGE - 1)
        @screen_y -= height
      end
    elsif t.y < MOVABLE_RANGE
      if @screen_y < 0
        @screen_y += height
      end
    end
  end
end

def draw
  push_matrix do |x|
    translate 0, @screen_y
    @emojis.each { |e| e.draw }
  end
end

class Emoji
  def initialize(i, x, y)
    @x = x
    @y = y
    @emoji, @name = Image.emoji_index(i)
  end

  def draw
    set_color_hex 0xffffff
    @emoji.draw(@x, @y)

    push_matrix do
      translate @x, @y + 50
      scale(1, 1)
      set_color_hex 0x000000
      # text "#{@name.to_s}", 0, 0
    end
  end
end

class Image
  def self.rand_emoji
    array = EMOJI.to_a
    v = array[rand(array.length)]
    return emoji(v[0]), v[0]
  end

  def self.emoji_index(i)
    array = EMOJI.to_a
    v = array[i]
    return emoji(v[0]), v[0]
  end
end
