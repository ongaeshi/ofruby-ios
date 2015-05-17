# Syntax Highlight Test

# aaaa def aaa defined? aaaa

def setup
end

def update
end

def draw
  # set_color 204, 52, 45
  rect 120, 220, 80, 40

  text "aaaaa", 100, 100

  x = 10
  text "x: #{10}", 100, 200 # This is comment
  text "x: #{10}", 100, 200

  text 'aaaa 20', 100, 300
  text 'aaaa #{20}', 100, 320

  # text "#{Input.touch(0).x}", 0, 100
end

class A_Class
  attr_reader :aaa

  def initialize
    @aaa = 2
  end

  def func
    @Symbol # <- Illegal syntax
  end
end
