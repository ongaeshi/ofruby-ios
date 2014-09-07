def setup
  test_dist
  test_dist_squared
  test_deg_to_rad
  test_rad_to_deg
end

def test_dist
  assert_in_delta 0, dist(0, 0, 0, 0)
  assert_in_delta 100, dist(0, 0, 100, 0), 0.01
  assert_in_delta 100, dist(0, 0, 0, 100), 0.01
  assert_in_delta 23.32, dist(30, 20, 50, 8), 0.01
end

def test_dist_squared
  assert_in_delta 0, dist_squared(0, 0, 0, 0)
  assert_in_delta 10000, dist_squared(0, 0, 100, 0), 0.01
  assert_in_delta 10000, dist_squared(0, 0, 0, 100), 0.01
  assert_in_delta 544, dist_squared(30, 20, 50, 8), 0.01
end

def test_deg_to_rad
  assert_in_delta 0.0, deg_to_rad(0.0)
  assert_in_delta Math::PI / 6, deg_to_rad(30.0)
  assert_in_delta Math::PI / 4, deg_to_rad(45.0)
  assert_in_delta Math::PI / 2, deg_to_rad(90.0)
  assert_in_delta Math::PI, deg_to_rad(180.0)
  assert_in_delta Math::PI / 180.0 * 280.0, deg_to_rad(280.0)
end

def test_rad_to_deg
  assert_in_delta 0, rad_to_deg(0)
  assert_in_delta 30, rad_to_deg(Math::PI / 6)
  assert_in_delta 45, rad_to_deg(Math::PI / 4)
  assert_in_delta 90, rad_to_deg(Math::PI / 2)
  assert_in_delta 180, rad_to_deg(Math::PI)
  assert_in_delta 280, rad_to_deg(Math::PI / 180.0 * 280.0)
end

def assert_in_delta(expected, actual, delta = 0.001)
  unless (expected - actual).abs < delta
    raise
  end
end

def assert_equals(x, y)
  raise unless x == y
end

