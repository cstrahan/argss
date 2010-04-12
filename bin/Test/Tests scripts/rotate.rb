# Set Message Box as output system
Output.msgbox

#Assigning a background
Graphics.backcolor = Color.new(128, 128, 128)

Graphics.frame_rate = 120
# Draw Text
sprite = Sprite.new
sprite.bitmap = Bitmap.new(128, 128)
sprite.bitmap.fill_rect(0, 0, 128, 128, Color.new(255, 0, 0))
sprite.ox = 64
sprite.oy = 64
sprite.x = 70
sprite.y = 70

sprite2 = Sprite.new
sprite2.bitmap = Bitmap.new(64, 128)
sprite2.bitmap.fill_rect(0, 0, 64, 128, Color.new(0, 255, 0))
sprite2.ox = 64
sprite2.oy = 64
sprite2.x = 90
sprite2.y = 200

sprite3 = Sprite.new
sprite3.bitmap = Bitmap.new(64, 128)
sprite3.bitmap.fill_rect(0, 0, 64, 128, Color.new(0, 0, 255))
sprite3.x = 300
sprite3.y = 250

sprites = []
for i in 0..200
  spr = Sprite.new
  spr.bitmap = Bitmap.new("Graphics/test2")
  spr.x = i * (640 / 200)
  spr.y = 32 + (i % 20) * (480 / 20)
  spr.ox = 12
  spr.oy = 12
  sprites << spr
end

loop do
  Graphics.update
  Input.update
  sprite.angle += 1
  sprite2.angle += 1
  sprite3.angle += 1
  
  sprites.each {|s| s.angle += 1}
end
