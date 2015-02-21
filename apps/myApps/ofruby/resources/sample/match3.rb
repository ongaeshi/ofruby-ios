X = 6; Y = 6
PX = 40; PY = 40
PXH = PX * 0.5; PYH = PY * 0.5

FIRST_KIND = 6

TARGET_POINT = 3000
TARGET_RATE = 1.0
BASE_RATE = 1.2
CHAIN_RATE = 1.2

def setup
  @field = Field.new(X,Y)
  @info = Info.new
  @field.set_info(@info)
  @reset = ResetButton.new(@field)
end

def update
  @field.update
  @info.update
  @reset.update
end

def draw
  @field.draw
  @info.draw
  @reset.draw
  Debugp.draw
end

class Panel
  attr_reader :kind

  def initialize(kind)
    @kind = kind
    @hide = false
  end

  def draw(x, y)
    return if @hide

    case @kind
    when 0
      set_color_hex 0x000000
      set_no_fill
      set_line_width(1)
      circle x + PXH, y + PYH, PXH
    when 1
      set_color_hex 0xb62fcc
      set_fill
      rect x+1, y+1, PX-1, PY-1
    when 2
      set_color_hex 0xff343e
      set_fill
      triangle x + PXH, y, x + PX, y + PY, x, y + PY
    when 3
      set_color_hex 0x5dcc5f
      set_fill
      ellipse x + PXH, y + PYH, PX, PY - 3
    when 4
      set_color_hex 0x457fff
      set_fill
      triangle x + PXH, y, x + PX, y + PYH, x, y + PYH
      triangle x + PXH, y + PY, x, y + PYH, x + PX, y + PYH
    when 5
      set_color_hex 0xfff842
      set_fill
      rect_rounded x+1, y+1, PX-1, PY-1, 10
    when 6
      set_color_hex 0xFF4A8E
      set_fill
      circle x + PXH, y + PYH, PXH
    when 7
      set_color_hex 0x00343e
      set_fill
      triangle x + PXH, y, x + PX, y + PY, x, y + PY
    end
  end

  def ==(rhs)
    kind == rhs.kind
  end

  def vanish
    @vanished = true
  end

  def vanished?
    @vanished
  end

  def blank(frame)
    if @vanished
      @hide = !@hide if frame % 3 == 0
    end
  end

  def hide
    @hide = true if @vanished
  end

  def new_panel(kind)
    reset_panel(kind) if @vanished
  end

  def reset_panel(kind)
    @kind = rand(kind).to_i
    @vanished = nil
    @hide = false
  end
end

class Field
  attr_reader :reset_remain

  def initialize(x, y)
    @kind = FIRST_KIND
    @size = Vec2.new(x, y)
    @table = Array.new(x * y) { Panel.new(rand(@kind).to_i) }
    @mode = :touch
    @reset_remain = 3
  end

  def set_info(info)
    @info = info
  end

  def update
    case @mode
    when :touch
      update_touch
    when :blank
      update_blank
    when :fall
      update_fall
    when :new_panel
      update_new_panel
    end
  end

  def update_touch
    t = Input.touch(0)
    if t.press?
      pos = find_panel(t)
      if pos
        if @cursor
          unless swap?(pos, @cursor)
            @cursor = nil
            return
          end
          swap(pos, @cursor)
          if vanish_all
            @mode = :blank
            @frame = 0
            @chain = 1
          else
            swap(@cursor, pos)
          end
          @cursor = nil
        else
          @cursor = pos
        end
      end
    end
  end

  def update_blank
    if @frame == 0
      vanish_num =  @table.reduce(0) { |t, e| e.vanished? ? t + 1 : t }
      score = calculate_score(vanish_num, @chain)
      @info.add_score(score)
      if @info.level >= 10
        @kind = 8
      elsif @info.level >= 5
        @kind = 7
      end
    end
    @table.each { |e| e.blank(@frame) }
    @frame += 1
    if @frame > 40
      @mode = :fall
      @frame = 0
      @table.each { |e| e.hide }
    end
  end

  def calculate_score(vanish_num, chain)
    score = 0

    chain_rate = 1.0
    2.upto(chain) do
      chain_rate *= CHAIN_RATE
    end

    base_score = 100
    1.upto(vanish_num) do |e|
      base_score *= BASE_RATE if e > 3
      score += (base_score * chain_rate / 10).to_i * 10
    end
    score
  end

  def update_fall
    @frame += 1
    if @frame > 10
      @frame = 0
      @mode = :new_panel
    end
  end

  def update_new_panel
    if @frame == 0
      0.upto(X-1) do |x|
        (Y-2).downto(0) do |y|
          if get(x, y+1).vanished?
            (y+1).upto(Y-1) do |yy|
              if get(x, yy).vanished?
                swap(Vec2.new(x, yy-1), Vec2.new(x, yy))
              end
            end
          end
        end
      end

      @table.each { |e| e.new_panel(@kind) }
    end

    @frame += 1

    if @frame > 5
      if vanish_all
        @mode = :blank
        @frame = 0
        @chain += 1
      else
        @mode = :touch
        @chain = 0
      end
    end
  end

  def get(x, y)
    @table[y * @size.x + x]
  end

  def draw
    0.upto(@size.x-1) do |x|
      0.upto(@size.y-1) do |y|
        get(x, y).draw(sx + x * PX, sy + y * PY)
      end
    end

    if @cursor
      set_color_hex 0x0
      set_no_fill
      set_line_width(5)
      rect sx + @cursor.x * PX, sy + @cursor.y * PY, PX, PY
    end
  end

  def reset
    if @reset_remain > 0
      @table.each { |e| e.reset_panel(@kind) }
      @reset_remain -= 1
    end
  end

  private

  def sx
    width / 2 - PX * 3
  end

  def sy
    height / 2 - PY * 4 + 50
  end

  def find_panel(t)
    if sx < t.x && t.x < sx + PX * X &&
        sy < t.y && t.y < sy + PY * Y
      x = ((t.x - sx) / PX).to_i
      y = ((t.y - sy) / PY).to_i
      Vec2.new(x, y)
    else
      nil
    end
  end

  def set(x, y, v)
    @table[y * @size.x + x] = v
  end

  def swap(a, b)
    tmp = get(a.x, a.y)
    set(a.x, a.y, get(b.x, b.y))
    set(b.x, b.y, tmp)
  end

  def swap?(a, b)
    abs(a.x - b.x) <= 1 && abs(a.y - b.y) <= 0 ||
      abs(a.x - b.x) <= 0 && abs(a.y - b.y) <= 1
  end

  def abs(v)
    v >= 0 ? v : -v
  end

  def vanish_all
    vanished = false

    0.upto(X-1) do |x|
      0.upto(Y-1) do |y|
        vanished = true if vanish(Vec2.new x, y)
      end
    end

    vanished
  end

  def vanish(pos)
    vanished = false

    panel = get(pos.x, pos.y)

    minx = maxx= pos.x

    pos.x.upto(X-1) do |x|
      if panel == get(x, pos.y)
        maxx = x
      else
        break
      end
    end

    pos.x.downto(0) do |x|
      if panel == get(x, pos.y)
        minx = x
      else
        break
      end
    end

    if maxx - minx >= 3 - 1
      (minx..maxx).each do |x|
        get(x, pos.y).vanish
        vanished = true
      end
    end

    miny = maxy = pos.y

    pos.y.upto(Y-1) do |y|
      if panel == get(pos.x, y)
        maxy = y
      else
        break
      end
    end

    pos.y.downto(0) do |y|
      if panel == get(pos.x, y)
        miny = y
      else
        break
      end
    end

    if maxy - miny >= 3 - 1
      (miny..maxy).each do |y|
        get(pos.x, y).vanish
        vanished = true
      end
    end

    vanished
  end
end

class Info
  attr_reader :level

  def initialize
    @score = @next_score = @level = 0
    @target_point = TARGET_POINT
    level_up
    @score_infos = []
  end

  def update
    @score_infos.each { |e| e.update }
    @score_infos = @score_infos.find_all { |e| !e.dead? }
  end

  def draw
    set_color_hex 0x0
    text "Level: #{@level}", 30, 30
    text "Score: #{@score}", 30, 50

    set_color_hex 0x88f088
    set_fill
    rate = 1.0 - (@next_score - @score) / (@target_point).to_f
    rect 30, 80, rate * 250, 30

    set_color_hex 0
    set_line_width 3
    set_no_fill
    rect 30, 80, 250, 30

    @score_infos.each { |e| e.draw }
  end

  def add_score(score)
    @score += score
    @score_infos << ScoreInfo.new("#{score}!", 120, 60, 0x0)
    level_up if @score >= @next_score
  end

  private

  def level_up
    @level += 1
    @target_point *= TARGET_RATE if @level > 1
    @next_score += @target_point
    @score_infos << ScoreInfo.new("Level Up!", 30, 120, 0x0) if @level > 1
    # Debugp.p @next_score
  end
end

class ScoreInfo
  def initialize(msg, x, y, color)
    @msg = msg
    @pos = Vec2.new(x, y)
    @color = color
    @lifetime = 40
  end

  def update
    @lifetime -= 1 if @lifetime > 0
  end

  def draw
    set_color_hex @color

    push_matrix do
      translate @pos.x, @pos.y
      scale 4, 4
      text @msg, 0, 0
    end
  end

  def dead?
    @lifetime == 0
  end
end

class ResetButton
  def initialize(field)
    @pos = Vec2.new(170, 20)
    @size = Vec2.new(90, 30)
    @field = field
  end

  def update
    t = Input.touch(0)
    if t.press?
      if @pos.x <= t.x && t.x <= @pos.x + @size.x &&
          @pos.y <= t.y && t.y <= @pos.y + @size.y
        @field.reset
      end
    end
  end

  def draw
    set_color_hex 0x0
    set_line_width 1
    text "Reset #{@field.reset_remain}", @pos.x + 15, @pos.y + 20
    rect_rounded @pos.x, @pos.y, @size.x, @size.y, 10
  end
end

class Vec2
  attr_accessor :x
  attr_accessor :y

  def initialize(x, y)
    @x = x
    @y = y
  end

  def +(rhs)
    Vec2.new(@x + rhs.x, @y + rhs.y)
  end
end

class Debugp
  @texts = []

  def self.p(msg)
    msg = msg.to_s unless msg.is_a?(String)
    @texts << msg
    @texts = [] if @texts.length > 30
  end

  def self.draw
    set_color_hex 0x000000
    @texts.each_with_index do |e, index|
      text e, 0, index * 15 + 10
    end
  end
end
