X = 5
NUM = 25
MOVABLE_RANGE = 50
PAGE = EMOJI.size / NUM - 1
TEXT_SCALE = 1.5
EMOJI_SIZE = 36

def setup
  set_background 255, 255, 255

  change_page(0)

  @text_emoji = nil

  @arrow_up = Image.emoji(:white_circle)
  @arrow_down = Image.emoji(:white_circle)
end

def change_page(page_no)
  @page_no = page_no
  @text_emoji = nil
  start_index = @page_no * NUM

  @emojis = []
  start_index.upto(start_index + NUM - 1) do |index|
    i = index - start_index

    if index < EMOJI.size 
    @emojis.push Emoji.new(
      index, 
      60 * (i % X) + 20 ,
      (i / X).to_i * 60 + 100
      )
    end
  end
end

def update
  t = Input.touch(0)
  
  if t.valid? && t.down?
    emoji = @emojis.detect { |e| e.update(t) }
    if emoji
      @text_emoji = emoji
      return
    end
  end

  if t.valid? && t.press?
    if t.y > (height - MOVABLE_RANGE)
      if @page_no < PAGE
        change_page(@page_no + 1)
      end
    elsif t.y < MOVABLE_RANGE
      if @page_no > 0
        change_page(@page_no - 1)
      end
    end
  end
end

def draw
  @emojis.each { |e| e.draw(@text_emoji) }

  push_matrix do
    translate width / 2 - EMOJI_SIZE / 2, 10
    scale 0.5, 0.5
    @arrow_up.draw(0, 0) if @page_no > 0
  end

  push_matrix do
    translate width / 2 - EMOJI_SIZE / 2, height - 30
    scale 0.5, 0.5
    @arrow_down.draw(0, 0) if @page_no < PAGE
  end

  @text_emoji.draw_text(10, 80) if @text_emoji
end

class Emoji
  attr_reader :name
  
  def initialize(i, x, y)
    @x = x
    @y = y
    @emoji, @name = Image.emoji_index(i)
  end

  def update(t)
    @x <= t.x && t.x <= @x + EMOJI_SIZE &&
      @y <= t.y && t.y <= @y + EMOJI_SIZE
  end

  def draw(text_emoji)
    if self == text_emoji
      set_color_hex 0xf000f0, 32
      w = 10
      rect_rounded @x - w/2, @y - w/2, EMOJI_SIZE + w, EMOJI_SIZE + w, 10
   end
    set_color_hex 0xffffff
    @emoji.draw(@x, @y)
  end

  def draw_text(x, y)
    push_matrix do
      scale TEXT_SCALE, TEXT_SCALE 
      set_color_hex 0x000000
      text "#{@name.to_s}", x/TEXT_SCALE,  y/TEXT_SCALE 
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
