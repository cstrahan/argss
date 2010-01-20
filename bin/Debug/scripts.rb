#Load Keys
require('keys')

begin
  #Creating the console for debug messages.
  Output.console
  
  print "Wait some secs\n"

  #Assigning a background
  Graphics.backcolor = Color.new(0, 0, 0)

  Graphics.frame_rate = 60
  # Draw Text
  sprite = Sprite.new
  sprite.bitmap = Bitmap.new(200, 125)
  sprite.bitmap.draw_text(0, 0, 200, 25, "Testing draw text") 
  sprite.bitmap.font.bold = true
  sprite.bitmap.draw_text(Rect.new(0, 25, 200, 25), "Centered bold", 1) 
  sprite.bitmap.font.size = 40
  sprite.bitmap.font.bold = false
  sprite.bitmap.draw_text(Rect.new(0, 50, 200, 50), "Bigger Text", 2) 
  sprite.bitmap.font.size = 20
  sprite.bitmap.font.bold = true
  sprite.bitmap.font.italic = true
  sprite.bitmap.draw_text(Rect.new(0, 100, 200, 25), "Large stretched text bold and italic", 1) 
  
  # Fill Rect, clear and blit
  sprite2 = Sprite.new
  sprite2.bitmap = Bitmap.new(200, 125)
  sprite2.x = 200
  sprite2.bitmap.clear(Color.new(128, 128, 128))
  sprite2.bitmap.fill_rect(0, 10, 100, 115, Color.new(255, 0, 0, 192))
  sprite2.bitmap.fill_rect(Rect.new(100, 10, 100, 999), Color.new(0, 255, 0, 192))
  bitmap = Bitmap.new(100, 50)
  bitmap.fill_rect(10, 10, 100, 90, Color.new(0, 0, 255, 255))
  sprite2.bitmap.blt(50, 50, bitmap, Rect.new(0, 0, 999, 99), 192)
  bitmap.dispose
  bitmap = Bitmap.new(50, 50)
  bitmap.fill_rect(1, 1, 48, 48, Color.new(255, 255, 255, 255))
  sprite2.bitmap.blt(125, 75, bitmap, Rect.new(0, 0, 40, 40), 192)
  bitmap.dispose
  
  # Zoom and HSL
  sprite3 = Sprite.new
  sprite3.bitmap = Bitmap.new("test6.png")
  sprite3.bitmap.hue_change(160)
  sprite3.x = 400
  sprite3.zoom_y = 0.523
  sprite4 = Sprite.new
  sprite4.bitmap = Bitmap.new("test6.png")
  sprite4.bitmap.hsl_change(240, -0.5, 1.3)
  sprite4.y = 125
  sprite4.zoom_x = 0.5
  sprite4.zoom_y = 1.479
  
  # StretchBlt and sprite tone
  sprite5 = Sprite.new
  sprite5.bitmap = Bitmap.new("test.png")
  bitmap =  Bitmap.new("test2.png")
  sprite5.bitmap.stretch_blt(Rect.new(32, 48, 32, 48), bitmap, Rect.new(6, 6, 12, 12), 230)
  bitmap.dispose
  sprite5.tone = Tone.new(0, 128, 0, 0)
  sprite5.x = 120
  sprite5.y = 125
  sprite6 = Sprite.new
  sprite6.bitmap = Bitmap.new("test3.png")
  bitmap =  Bitmap.new("test2.png")
  sprite6.bitmap.stretch_blt(Rect.new(0, 0, 128, 192), bitmap, Rect.new(0, 0, 24, 24), 192)
  bitmap.dispose
  sprite6.tone = Tone.new(64, 64, 64, -64)
  sprite6.x = 248
  sprite6.y = 125
  
  # Flip and opacity
  bitmap = Bitmap.new("test6.png")
  sprite7 = Sprite.new
  sprite7.bitmap = Bitmap.new(120, 163)
  sprite7.bitmap.blt(0, 0, bitmap, Rect.new(0, 0, 120, 163))
  bitmap.dispose
  sprite7.x = 120
  sprite7.y = 317
  sprite7.mirror = true
  sprite7.opacity = 240
  sprite8 = Sprite.new
  sprite8.bitmap = sprite7.bitmap
  sprite8.x = 240
  sprite8.y = 317
  sprite8.flipy = true
  sprite8.opacity = 192
  sprite9 = Sprite.new
  sprite9.bitmap = sprite7.bitmap
  sprite9.x = 360
  sprite9.y = 317
  sprite9.flipx = true
  sprite9.flipy = true
  sprite9.bush_depth = 80
  sprite10 = Sprite.new
  bitmap = Bitmap.new("test.png")
  sprite10.bitmap = Bitmap.new(240, 163)
  for i in 0...8
    for j in 0..4
      sprite10.bitmap.blt(i * 32, j * 48, bitmap, Rect.new(0, 0, 32, 48))
    end
  end
  sprite10.x = 480
  sprite10.y = 317
  bitmap.dispose
  sprite11 = Sprite.new
  sprite11.bitmap = Bitmap.new("test2.png")
  sprite11.opacity = 192
  sprite11.x = 500
  sprite11.y = 330
  sprite11.zoom_x = sprite11.zoom_y = 8
  sprite12 = Sprite.new
  sprite12.bitmap = Bitmap.new("test2.png")
  sprite12.opacity = 192
  sprite12.x = 500
  sprite12.y = 330
  sprite12.zoom_x = sprite12.zoom_y = 4
  sprite13 = Sprite.new
  sprite13.bitmap = Bitmap.new("test2.png")
  sprite13.opacity = 192
  sprite13.x = 500
  sprite13.y = 330
  sprite13.zoom_x = sprite13.zoom_y = 2
  sprite13.z = -1

  # Random thing
  sprite11 = Sprite.new
  sprite11.bitmap = Bitmap.new(264 , 192)
  sprite11.bitmap.clear(Color.new(255, 0, 0))
  for i in 0..500
    # If this line is added, a nil to int coversion failed error is raised. WHY? and WHERE?
    #sprite11.bitmap.font.color.set(rand(255), rand(255), rand(255), rand(255))
    sprite11.bitmap.draw_text(rand(264), rand(192), rand(264), rand(192), "A", rand(3))
    sprite11.bitmap.draw_text(rand(264), rand(192), rand(264), rand(192), "R", rand(3))
    sprite11.bitmap.draw_text(rand(264), rand(192), rand(264), rand(192), "G", rand(3))
    sprite11.bitmap.draw_text(rand(264), rand(192), rand(264), rand(192), "S", rand(3))
    sprite11.bitmap.draw_text(rand(264), rand(192), rand(264), rand(192), "S", rand(3))
  end
  sprite11.x = 376
  sprite11.y = 125

  loop do
    Graphics.update
    Input.update
  end
  
rescue
  script, line = $!.backtrace.to_s.split(':')
  str = "#{$!.class} in #{script}, line #{line}\n#{$!.message}\n#{$!.backtrace}\n"
  print str
end

