# Set Message Box as output system
Output.msgbox

#Assigning a background
Graphics.backcolor = Color.new(0, 0, 0)

Graphics.frame_rate = 60

sprite = Sprite.new
sprite.bitmap = Bitmap.new("Graphics/test6")
sprite2 = Sprite.new
sprite2.bitmap = sprite.bitmap
sprite2.tone = Tone.new(192, 0, 0, 0)
sprite2.x = 240
sprite3 = Sprite.new
sprite3.bitmap = sprite.bitmap
sprite3.tone = Tone.new(0, 192, 0, 0)
sprite3.x = 480
sprite4 = Sprite.new
sprite4.bitmap = sprite.bitmap
sprite4.tone = Tone.new(0, 0, 192, 0)
sprite4.y = 240
sprite5 = Sprite.new
sprite5.bitmap = sprite.bitmap
sprite5.tone = Tone.new(0, 0, 0, 192)
sprite5.x = 240
sprite5.y = 240
sprite6 = Sprite.new
sprite6.bitmap = sprite.bitmap
sprite6.tone = Tone.new(0, 0, 0, 255)
sprite6.x = 480
sprite6.y = 240

Graphics.brightness = 0
Graphics.update
Graphics.fadein(255)

loop do
  Graphics.update
  Input.update
end
