def rtp_test
  #Creating the console for debug messages.
  Output.console

  #Assigning a background
  Graphics.backcolor = Color.new(0, 0, 0)

  Graphics.frame_rate = 60

  sprite = Sprite.new
  sprite.bitmap = Bitmap.new("Graphics/Gameovers/001-Gameover01")
  sprite2 = Sprite.new
  sprite2.bitmap = Bitmap.new("Graphics/Characters/013-Warrior01")
  sprite3 = Sprite.new
  sprite3.bitmap = Bitmap.new("Graphics/Characters/057-Snake03")
  sprite3.x = sprite2.width
  
  loop do
    Graphics.update
    Input.update
  end
end