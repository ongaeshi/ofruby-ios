module DebugInfo
  def self.fps
    "#{format("%3.2f", get_frame_rate)} fps"
  end

  def self.window
    "window_pos: (#{window_pos_x}, #{window_pos_y}), size: (#{window_width}, #{window_height})"
  end

  def self.mouse
    str = "mouse: "
    str += format("(%4d, %4d)", Input.mouse_x, Input.mouse_y)

    # press?
    str += " press?: "
    str += (0..2).map {|v|
      Input.mouse_press?(v) ? '1' : '0'
    }.join('')

    # down?
    str += " down?: "
    str += (0..2).map {|v|
      Input.mouse_down?(v) ? '1' : '0'
    }.join('')

    # release?
    str += " release?: "
    str += (0..2).map {|v|
      Input.mouse_release?(v) ? '1' : '0'
    }.join('')

    str
  end
end

module Console
  # FONT_HEIGHT = 13 # can't use CONSTANT at inner block
  @font_height = 13 

  def self.init(x, y, width = 600, height = 190)
    @x = x
    @y = y
    @width = width
    @height = height
    @line_num = (height / @font_height).to_i
    @text = []

    # Override Kernel#p
    Kernel.class_eval do
      alias org_p p

      def self.p(*args)
        org_p(*args)
        Console.p(*args)
      end
    end
  end

  def self.p(*arg)
    if arg.instance_of?(Array)
      @text += arg.map{|obj| obj.inspect }
    else
      @text << arg.inspect
    end
    arg
  end

  def self.draw
    return if @text.nil?
    
    @text = @text[@text.length - @line_num, @line_num] if @text.length > @line_num
    
    set_fill
    set_color(255, 255, 255)
    rect(@x, @y, @width, @height)

    set_no_fill
    set_color(0, 0, 0)
    rect(@x, @y, @width, @height)

    @text.each_with_index do |text, index|
      text(text, @x + 5, @y + @font_height + @font_height * index)
    end
  end

  def self.clear
    return if @text.nil?
    @text = []
  end
end

class SequenceShot
  def initialize(interval = 6, limit = 50)
    @interval = interval
    @limit    = limit
    @index    = 0
    @frame    = 0
  end

  def update
    return if @limit > 0 && @index >= @limit
    
    if @frame % @interval == 0
      Image.grab_screen.save("sequence_shot_#{sprintf("%03d", @index)}.png")
      @index += 1
    end
    
    @frame += 1
  end
end

EMOJI = {
  hash: '23-20e3',
  zero: '30-20e3',
  one: '31-20e3',
  two: '32-20e3',
  three: '33-20e3',
  four: '34-20e3',
  five: '35-20e3',
  six: '36-20e3',
  seven: '37-20e3',
  eight: '38-20e3',
  nine: '39-20e3',
  copyright: 'a9',
  registered: 'ae',
  bangbang: '203c',
  interrobang: '2049',
  tm: '2122',
  information_source: '2139',
  left_right_arrow: '2194',
  arrow_up_down: '2195',
  arrow_upper_left: '2196',
  arrow_upper_right: '2197',
  arrow_lower_right: '2198',
  arrow_lower_left: '2199',
  leftwards_arrow_with_hook: '21a9',
  arrow_right_hook: '21aa',
  watch: '231a',
  hourglass: '231b',
  fast_forward: '23e9',
  rewind: '23ea',
  arrow_double_up: '23eb',
  arrow_double_down: '23ec',
  alarm_clock: '23f0',
  hourglass_flowing_sand: '23f3',
  m: '24c2',
  black_small_square: '25aa',
  white_small_square: '25ab',
  arrow_forward: '25b6',
  arrow_backward: '25c0',
  white_medium_square: '25fb',
  black_medium_square: '25fc',
  white_medium_small_square: '25fd',
  black_medium_small_square: '25fe',
  sunny: '2600',
  cloud: '2601',
  telephone: '260e',
  phone: '260e',
  ballot_box_with_check: '2611',
  umbrella: '2614',
  coffee: '2615',
  point_up: '261d',
  relaxed: '263a',
  aries: '2648',
  taurus: '2649',
  gemini: '264a',
  cancer: '264b',
  leo: '264c',
  virgo: '264d',
  libra: '264e',
  scorpius: '264f',
  sagittarius: '2650',
  capricorn: '2651',
  aquarius: '2652',
  pisces: '2653',
  spades: '2660',
  clubs: '2663',
  hearts: '2665',
  diamonds: '2666',
  hotsprings: '2668',
  recycle: '267b',
  wheelchair: '267f',
  anchor: '2693',
  warning: '26a0',
  zap: '26a1',
  white_circle: '26aa',
  black_circle: '26ab',
  soccer: '26bd',
  baseball: '26be',
  snowman: '26c4',
  partly_sunny: '26c5',
  ophiuchus: '26ce',
  no_entry: '26d4',
  church: '26ea',
  fountain: '26f2',
  golf: '26f3',
  sailboat: '26f5',
  boat: '26f5',
  tent: '26fa',
  fuelpump: '26fd',
  scissors: '2702',
  white_check_mark: '2705',
  airplane: '2708',
  email: '2709',
  envelope: '2709',
  fist: '270a',
  raised_hand: '270b',
  hand: '270b',
  v: '270c',
  pencil2: '270f',
  black_nib: '2712',
  heavy_check_mark: '2714',
  heavy_multiplication_x: '2716',
  sparkles: '2728',
  eight_spoked_asterisk: '2733',
  eight_pointed_black_star: '2734',
  snowflake: '2744',
  sparkle: '2747',
  x: '274c',
  negative_squared_cross_mark: '274e',
  question: '2753',
  grey_question: '2754',
  grey_exclamation: '2755',
  heavy_exclamation_mark: '2757',
  exclamation: '2757',
  heart: '2764',
  heavy_plus_sign: '2795',
  heavy_minus_sign: '2796',
  heavy_division_sign: '2797',
  arrow_right: '27a1',
  curly_loop: '27b0',
  loop: '27bf',
  arrow_heading_up: '2934',
  arrow_heading_down: '2935',
  arrow_left: '2b05',
  arrow_up: '2b06',
  arrow_down: '2b07',
  black_large_square: '2b1b',
  white_large_square: '2b1c',
  star: '2b50',
  o: '2b55',
  wavy_dash: '3030',
  part_alternation_mark: '303d',
  congratulations: '3297',
  secret: '3299',
  mahjong: '1f004',
  black_joker: '1f0cf',
  a: '1f170',
  b: '1f171',
  o2: '1f17e',
  parking: '1f17f',
  ab: '1f18e',
  cl: '1f191',
  cool: '1f192',
  free: '1f193',
  id: '1f194',
  new: '1f195',
  ng: '1f196',
  ok: '1f197',
  sos: '1f198',
  up: '1f199',
  vs: '1f19a',
  cn: '1f1e8',
  de: '1f1e9',
  es: '1f1ea',
  fr: '1f1eb',
  uk: '1f1ec',
  gb: '1f1ec',
  it: '1f1ee',
  jp: '1f1ef',
  kr: '1f1f0',
  ru: '1f1f7',
  us: '1f1fa',
  koko: '1f201',
  sa: '1f202',
  u7121: '1f21a',
  u6307: '1f22f',
  u7981: '1f232',
  u7a7a: '1f233',
  u5408: '1f234',
  u6e80: '1f235',
  u6709: '1f236',
  u6708: '1f237',
  u7533: '1f238',
  u5272: '1f239',
  u55b6: '1f23a',
  ideograph_advantage: '1f250',
  accept: '1f251',
  cyclone: '1f300',
  foggy: '1f301',
  closed_umbrella: '1f302',
  night_with_stars: '1f303',
  sunrise_over_mountains: '1f304',
  sunrise: '1f305',
  city_sunset: '1f306',
  city_sunrise: '1f307',
  rainbow: '1f308',
  bridge_at_night: '1f309',
  ocean: '1f30a',
  volcano: '1f30b',
  milky_way: '1f30c',
  earth_africa: '1f30d',
  earth_americas: '1f30e',
  earth_asia: '1f30f',
  globe_with_meridians: '1f310',
  new_moon: '1f311',
  waxing_crescent_moon: '1f312',
  first_quarter_moon: '1f313',
  moon: '1f314',
  waxing_gibbous_moon: '1f314',
  full_moon: '1f315',
  waning_gibbous_moon: '1f316',
  last_quarter_moon: '1f317',
  waning_crescent_moon: '1f318',
  crescent_moon: '1f319',
  new_moon_with_face: '1f31a',
  first_quarter_moon_with_face: '1f31b',
  last_quarter_moon_with_face: '1f31c',
  full_moon_with_face: '1f31d',
  sun_with_face: '1f31e',
  star2: '1f31f',
  stars: '1f320',
  chestnut: '1f330',
  seedling: '1f331',
  evergreen_tree: '1f332',
  deciduous_tree: '1f333',
  palm_tree: '1f334',
  cactus: '1f335',
  tulip: '1f337',
  cherry_blossom: '1f338',
  rose: '1f339',
  hibiscus: '1f33a',
  sunflower: '1f33b',
  blossom: '1f33c',
  corn: '1f33d',
  ear_of_rice: '1f33e',
  herb: '1f33f',
  four_leaf_clover: '1f340',
  maple_leaf: '1f341',
  fallen_leaf: '1f342',
  leaves: '1f343',
  mushroom: '1f344',
  tomato: '1f345',
  eggplant: '1f346',
  grapes: '1f347',
  melon: '1f348',
  watermelon: '1f349',
  tangerine: '1f34a',
  lemon: '1f34b',
  banana: '1f34c',
  pineapple: '1f34d',
  apple: '1f34e',
  green_apple: '1f34f',
  pear: '1f350',
  peach: '1f351',
  cherries: '1f352',
  strawberry: '1f353',
  hamburger: '1f354',
  pizza: '1f355',
  meat_on_bone: '1f356',
  poultry_leg: '1f357',
  rice_cracker: '1f358',
  rice_ball: '1f359',
  rice: '1f35a',
  curry: '1f35b',
  ramen: '1f35c',
  spaghetti: '1f35d',
  bread: '1f35e',
  fries: '1f35f',
  sweet_potato: '1f360',
  dango: '1f361',
  oden: '1f362',
  sushi: '1f363',
  fried_shrimp: '1f364',
  fish_cake: '1f365',
  icecream: '1f366',
  shaved_ice: '1f367',
  ice_cream: '1f368',
  doughnut: '1f369',
  cookie: '1f36a',
  chocolate_bar: '1f36b',
  candy: '1f36c',
  lollipop: '1f36d',
  custard: '1f36e',
  honey_pot: '1f36f',
  cake: '1f370',
  bento: '1f371',
  stew: '1f372',
  egg: '1f373',
  fork_and_knife: '1f374',
  tea: '1f375',
  sake: '1f376',
  wine_glass: '1f377',
  cocktail: '1f378',
  tropical_drink: '1f379',
  beer: '1f37a',
  beers: '1f37b',
  baby_bottle: '1f37c',
  ribbon: '1f380',
  gift: '1f381',
  birthday: '1f382',
  jack_o_lantern: '1f383',
  christmas_tree: '1f384',
  santa: '1f385',
  fireworks: '1f386',
  sparkler: '1f387',
  balloon: '1f388',
  tada: '1f389',
  confetti_ball: '1f38a',
  tanabata_tree: '1f38b',
  crossed_flags: '1f38c',
  bamboo: '1f38d',
  dolls: '1f38e',
  flags: '1f38f',
  wind_chime: '1f390',
  rice_scene: '1f391',
  school_satchel: '1f392',
  mortar_board: '1f393',
  carousel_horse: '1f3a0',
  ferris_wheel: '1f3a1',
  roller_coaster: '1f3a2',
  fishing_pole_and_fish: '1f3a3',
  microphone: '1f3a4',
  movie_camera: '1f3a5',
  cinema: '1f3a6',
  headphones: '1f3a7',
  art: '1f3a8',
  tophat: '1f3a9',
  circus_tent: '1f3aa',
  ticket: '1f3ab',
  clapper: '1f3ac',
  performing_arts: '1f3ad',
  video_game: '1f3ae',
  dart: '1f3af',
  slot_machine: '1f3b0',
  _8ball: '1f3b1',
  game_die: '1f3b2',
  bowling: '1f3b3',
  flower_playing_cards: '1f3b4',
  musical_note: '1f3b5',
  notes: '1f3b6',
  saxophone: '1f3b7',
  guitar: '1f3b8',
  musical_keyboard: '1f3b9',
  trumpet: '1f3ba',
  violin: '1f3bb',
  musical_score: '1f3bc',
  running_shirt_with_sash: '1f3bd',
  tennis: '1f3be',
  ski: '1f3bf',
  basketball: '1f3c0',
  checkered_flag: '1f3c1',
  snowboarder: '1f3c2',
  runner: '1f3c3',
  running: '1f3c3',
  surfer: '1f3c4',
  trophy: '1f3c6',
  horse_racing: '1f3c7',
  football: '1f3c8',
  rugby_football: '1f3c9',
  swimmer: '1f3ca',
  house: '1f3e0',
  house_with_garden: '1f3e1',
  office: '1f3e2',
  post_office: '1f3e3',
  european_post_office: '1f3e4',
  hospital: '1f3e5',
  bank: '1f3e6',
  atm: '1f3e7',
  hotel: '1f3e8',
  love_hotel: '1f3e9',
  convenience_store: '1f3ea',
  school: '1f3eb',
  department_store: '1f3ec',
  factory: '1f3ed',
  lantern: '1f3ee',
  izakaya_lantern: '1f3ee',
  japanese_castle: '1f3ef',
  european_castle: '1f3f0',
  rat: '1f400',
  mouse2: '1f401',
  ox: '1f402',
  water_buffalo: '1f403',
  cow2: '1f404',
  tiger2: '1f405',
  leopard: '1f406',
  rabbit2: '1f407',
  cat2: '1f408',
  dragon: '1f409',
  crocodile: '1f40a',
  whale2: '1f40b',
  snail: '1f40c',
  snake: '1f40d',
  racehorse: '1f40e',
  ram: '1f40f',
  goat: '1f410',
  sheep: '1f411',
  monkey: '1f412',
  rooster: '1f413',
  chicken: '1f414',
  dog2: '1f415',
  pig2: '1f416',
  boar: '1f417',
  elephant: '1f418',
  octopus: '1f419',
  shell: '1f41a',
  bug: '1f41b',
  ant: '1f41c',
  bee: '1f41d',
  honeybee: '1f41d',
}

class Image
  def self.emoji(name)
    sample("emoji/#{EMOJI[name]}.png")
  end
end
