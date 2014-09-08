def draw
  draw_push_matrix
  draw_push_matrix_with_block
end

def draw_push_matrix
  @rot ||= 30
  
  push_matrix

  translate(50, 100)
  rotate(@rot += 1)
  rect(0, 0, 10, 10)

  push_matrix

  translate(50, 10)
  rotate(40)
  rect(0, 0, 30, 10)

  pop_matrix

  pop_matrix
end

def draw_push_matrix_with_block
  @rot2 ||= 0

  push_matrix do
    translate width / 2, height / 2

    push_matrix do
      translate(50, 100)
      rotate(@rot2 -= 1)
      rect(0, 0, 10, 10)

      push_matrix do
        translate(50, 10)
        rotate(40)
        rect(0, 0, 30, 10)
        scale(1, 2)
      end
    end
  end

  circle width / 2, height / 2, 100
end

# ---

def assert_in_delta(expected, actual, delta = 0.001)
  unless (expected - actual).abs < delta
    raise
  end
end

def assert_equals(x, y)
  raise unless x == y
end

