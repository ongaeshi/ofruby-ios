HIGH_LEVEL = 20

def setup
  set_background_hex 0xffffff

  @score = 0
  @gameover = false

  new_question
end

def update
  return if @gameover

  t = Input.touch(0)

  if t.valid? && t.press?
    touched = @emojis.detect { |e| e.touch?(t) }
    unless touched.nil?
      if touched == @right_emoji
        @score += 1
        new_question
      else
        @gameover = true
      end
    end
  end
end

def draw
  @emojis.each do |e|
    e.draw(@gameover && @right_emoji != e)
  end

  set_color_hex 0x000000
  text "score: #{@score}", 10, 40
  text "#{@right_emoji.name.to_s}?", 50, 280
end

def new_question
  @emojis = []
  @emojis.push Emoji.new(20, 100)
  @emojis.push Emoji.new(120, 100)
  @emojis.push Emoji.new(220, 100)
  if @score >= HIGH_LEVEL
    @emojis.push Emoji.new(70, 200)
    @emojis.push Emoji.new(170, 200)
  end
  
  @right_emoji = @emojis[rand @emojis.length]
end

class Emoji
  SIZE = 36

  attr_reader :name
  
  def initialize(x, y)
    @x = x
    @y = y
    @emoji, @name = Image.rand_emoji
  end

  def touch?(t)
    @x <= t.x && t.x <= @x + SIZE &&
      @y <= t.y && t.y <= @y + SIZE
  end

  def draw(gameover)
    set_color_hex 0xffffff
    @emoji.draw(@x, @y)

    if gameover
      set_color_hex 0x000000, 128
      rect @x, @y, SIZE, SIZE
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
