# Set Message Box as output system
Output.msgbox

#Assigning a background
Graphics.backcolor = Color.new(128, 128, 128)

sprite = Sprite.new
sprite.bitmap = Bitmap.new("Graphics/test")
sprite.x = (Graphics.width - sprite.bitmap.width) / 2
sprite.y = (Graphics.height - sprite.bitmap.height) / 2

loop do
  Graphics.update
  Input.update
  sprite.update
  if Input.trigger?(Input::A)
    sprite.flash(Color.new(255, 0, 0, 255), 255)
  end
  if Input.trigger?(Input::B)
    sprite.flash(Color.new(0, 255, 0, 255), 255)
  end
  if Input.trigger?(Input::C)
    sprite.flash(Color.new(0, 0, 255, 255), 255)
  end
  if Input.trigger?(Input::X)
    sprite.flash(Color.new(255, 255, 0, 128), 255)
  end
  if Input.trigger?(Input::Y)
    sprite.flash(Color.new(0, 255, 255, 128), 255)
  end
  if Input.trigger?(Input::Z)
    sprite.flash(Color.new(255, 0, 255, 128), 255)
  end
  if Input.trigger?(Input::L)
    sprite.flash(Color.new(rand(256), rand(256), rand(256), rand(256)), 255)
  end
  if Input.trigger?(Input::R)
    sprite.flash(nil, 255)
  end
  if Input.trigger?(Keys::F)
    sprite.flipx = !sprite.flipx
  end
  if Input.trigger?(Keys::G)
    sprite.flipy = !sprite.flipy
  end
  if Input.trigger?(Keys::H)
    sprite.bitmap.dispose
    sprite.bitmap = Bitmap.new("Graphics/Characters/070-Goblin04")
    sprite.x = (Graphics.width - sprite.bitmap.width) / 2
    sprite.y = (Graphics.height - sprite.bitmap.height) / 2
  end
  if Input.trigger?(Keys::J)
    sprite.bitmap.dispose
    sprite.bitmap = Bitmap.new("Graphics/test")
    sprite.x = (Graphics.width - sprite.bitmap.width) / 2
    sprite.y = (Graphics.height - sprite.bitmap.height) / 2
  end
end
