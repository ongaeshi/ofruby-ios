def setup
  set_background 255, 255, 255

  @emojis = []
  @emojis.push Emoji.new(0, 0)
  @emojis.push Emoji.new(0, 60)
  @emojis.push Emoji.new(0, 120)
  @emojis.push Emoji.new(0, 180)
  @emojis.push Emoji.new(0, 240)
  @emojis.push Emoji.new(0, 300)
  @emojis.push Emoji.new(0, 360)
  @emojis.push Emoji.new(0, 420)

  @emojis.push Emoji.new(100, 0)
  @emojis.push Emoji.new(100, 60)
  @emojis.push Emoji.new(100, 120)
  @emojis.push Emoji.new(100, 180)
  @emojis.push Emoji.new(100, 240)
  @emojis.push Emoji.new(100, 300)
  @emojis.push Emoji.new(100, 360)
  @emojis.push Emoji.new(100, 420)

  @emojis.push Emoji.new(200, 0)
  @emojis.push Emoji.new(200, 60)
  @emojis.push Emoji.new(200, 120)
  @emojis.push Emoji.new(200, 180)
  @emojis.push Emoji.new(200, 240)
  @emojis.push Emoji.new(200, 300)
  @emojis.push Emoji.new(200, 360)
  @emojis.push Emoji.new(200, 420)


end

def draw
  @emojis.each { |e| e.draw }
end

class Emoji
  def initialize(x, y)
    @x = x
    @y = y
    @emoji, @name = Image.rand_emoji    
  end

  def draw
    set_color_hex 0xffffff
    @emoji.draw(@x, @y)

    push_matrix do
      translate @x, @y + 50
      scale(1, 1)
      set_color_hex 0x000000
      text "#{@name.to_s}", 0, 0
    end
  end
end

class Image
  def self.rand_emoji
    array = EMOJI.to_a
    v = array[rand(array.length)]
    return emoji(v[0]), v[0]
  end
end
