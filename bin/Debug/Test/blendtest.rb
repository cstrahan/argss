# Set the Console as output system
Output.msgbox

#Assigning a background
Graphics.backcolor = Color.new(128, 128, 128)

sprite1 = Sprite.new
sprite1.bitmap = Bitmap.new("Graphics/test6")
sprite1.blend_type = 0
sprite2 = Sprite.new
sprite2.bitmap = Bitmap.new("Graphics/test6")
sprite2.blend_type = 1
sprite2.x = 240
sprite3 = Sprite.new
sprite3.bitmap = Bitmap.new("Graphics/test6")
sprite3.blend_type = 2
sprite3.y = 240
sprite4 = Sprite.new
sprite4.bitmap = Bitmap.new("Graphics/test6")
sprite4.blend_type = 2
sprite4.x = 240
sprite4.y = 240
sprite4.opacity = 64

loop do
  Graphics.update
  Input.update
end
