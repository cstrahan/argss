#Load Keys
require('keys')

begin
  #Creating the console for debug messages.
  Console.initialize

  #Assigning a background
  Graphics.backcolor = Color.new(0, 128, 0)

  Graphics.frame_rate = 60

  #Testing
  windows7 = Window.new
  windows7.windowskin = Bitmap.new("001-Blue01.png")
  windows7.width = 160
  windows7.height = 100
  windows7.x = (Graphics.width - windows7.width) / 2
  windows7.y = (Graphics.height - windows7.height) / 2
  windows7.contents = Bitmap.new(windows7.width - 32, windows7.height - 32)
  windows7.contents.fill_rect(0, 0, windows7.contents.width, windows7.contents.height, Color.new(255, 0, 0, 128))
  windows7.contents.draw_text(0, 0, windows7.contents.width, windows7.contents.height, "Testing Window", 1)
  windows7.pause = true
  
  loop do
    Graphics.update
    Input.update
    windows7.update
    windows7.pause = !windows7.pause if Input.trigger?(Keys::A)
    if Input.press?(Keys::LCTRL)
      windows7.ox -= 1 if Input.repeat?(Keys::LEFT)
      windows7.ox += 1 if Input.repeat?(Keys::RIGHT)
      windows7.oy -= 1 if Input.repeat?(Keys::UP)
      windows7.oy += 1 if Input.repeat?(Keys::DOWN)
    else
      windows7.width -= 1 if Input.repeat?(Keys::LEFT)
      windows7.width += 1 if Input.repeat?(Keys::RIGHT)
      windows7.height -= 1 if Input.repeat?(Keys::UP)
      windows7.height += 1 if Input.repeat?(Keys::DOWN)
    end
    windows7.x = (Graphics.width - windows7.width) / 2
    windows7.y = (Graphics.height - windows7.height) / 2
  end
rescue
  script, line = $!.backtrace.to_s.split(':')
  puts "#{$!.class} in #{script}, line #{line}"
  puts $!.message, $!.backtrace
ensure
  gets
end
