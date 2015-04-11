X = 4
MOVABLE_RANGE = 50
PAGE = 13

def setup
  set_background 255, 255, 255

  @emojis = []
  EMOJI.each_with_index do |e, i|
    @emojis.push Emoji.new(i, 60 * (i % X) + 10 , (i / X).to_i * 60 + 10)
  end

  @screen_y = 0
  @text_emoji = nil
end

def update
  t = Input.touch(0)
  
  if t.valid? && t.press?
    emoji = @emojis.detect { |e| e.update(t, -@screen_y) }
    if emoji
      @text_emoji = emoji
    elsif t.y > (height - MOVABLE_RANGE)
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
  push_matrix do
    translate 0, @screen_y
    @emojis.each { |e| e.draw }
    @text_emoji.draw_text(10, -@screen_y + height - 10) if @text_emoji
  end
end

class Emoji
  attr_reader :name
  
  def initialize(i, x, y)
    @x = x
    @y = y
    @emoji, @name = Image.emoji_index(i)
  end

  def update(t, offset_y)
    @x <= t.x && t.x <= @x + 32 &&
      @y <= t.y + offset_y && t.y + offset_y <= @y + 32
  end

  def draw
    set_color_hex 0xffffff
    push_matrix do
      translate 10, 0
      @emoji.draw(@x, @y)
    end
  end

  def draw_text(x, y)
    push_matrix do
      set_color_hex 0x000000
      text "#{@name.to_s}", x, y
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
