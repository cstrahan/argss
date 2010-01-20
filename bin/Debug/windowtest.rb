
def window_test
  #Creating the console for debug messages.
  Output.console

  #Assigning a background
  Graphics.backcolor = Color.new(0, 0, 0)

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
  #windows7.contents.draw_text(0, 0, windows7.contents.width, windows7.contents.height, "Testing Window", 1)
  windows7.pause = true
  loop do
    Graphics.update
    Input.update
    windows7.update
    windows7.pause = !windows7.pause if Input.trigger?(Keys::A)
    windows7.stretch = !windows7.stretch if Input.trigger?(Keys::B)
    if Input.press?(Keys::LCTRL)
      windows7.ox -= 1 if Input.repeat?(Keys::LEFT)
      windows7.ox += 1 if Input.repeat?(Keys::RIGHT)
      windows7.oy -= 1 if Input.repeat?(Keys::UP)
      windows7.oy += 1 if Input.repeat?(Keys::DOWN)
    else
      windows7.width -= 10 if Input.repeat?(Keys::LEFT)
      windows7.width += 10 if Input.repeat?(Keys::RIGHT)
      windows7.height -= 10 if Input.repeat?(Keys::UP)
      windows7.height += 10 if Input.repeat?(Keys::DOWN)
    end
    windows7.x = (Graphics.width - windows7.width) / 2
    windows7.y = (Graphics.height - windows7.height) / 2
    
    if Input.press?(Keys::LCTRL)
      windows7.back_opacity += 10 if Input.repeat?(Keys::KP_PLUS)
      windows7.back_opacity -= 10 if Input.repeat?(Keys::KP_MINUS)
    elsif Input.press?(Keys::LALT)
      windows7.contents_opacity += 10 if Input.repeat?(Keys::KP_PLUS)
      windows7.contents_opacity -= 10 if Input.repeat?(Keys::KP_MINUS)
    else
      windows7.opacity += 10 if Input.repeat?(Keys::KP_PLUS)
      windows7.opacity -= 10 if Input.repeat?(Keys::KP_MINUS)
    end
  end
end