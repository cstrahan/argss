# MauMau Bitmap Test for ARGSS

#Load Keys
require('keys')

#One of my Bitmap methods
class Bitmap
  def fill_circle(x, y, raio, cor = Color.new(255, 255, 255))
    r = raio ** 2
    (-raio..raio).each {|i|
      t = Math.sqrt(r - i ** 2).to_i
      self.fill_rect((i <=> x) * i + x, y - t, 1, t * 2, cor)
    }
  end
  
  #-------------------------------------------------------------------------
  # - Desenha Linha
  #-------------------------------------------------------------------------

  def draw_line(x1, y1, x2, y2, width, color = Color.new(255, 255, 255))
    # Reverte todos os paramêtros enviados se x2 for menor que x1
    x1, x2, y1, y2 = x2, x1, y2, y1 if x2 < x1
    # Desenha uma linha Vertical se as coordenadas X forem iguais
    if x1 == x2
      fill_rect(x1 - width, [y1, y2].min, width, (y2-y1).abs, color)
    # Desenha uma linha Horizontal se as coordenadas Y forem iguais
    elsif y1 == y2
      fill_rect(x1, y1 - width, x2-x1, width, color)
    # Desenha uma Linha Oblíqua
    else
      # Cálculos
      xx, yy = x2-x1, y2-y1
      x_increment, y_increment = xx < yy.abs ? [xx/yy.abs.to_f, yy/yy.abs.to_f] : [1, yy/xx.to_f]
      # Enquanto o X inicial for menor que o X final
      while x1 < x2
        # Desenhar caixa de largura-largura e largura-altura
        fill_rect(x1 - width, y1 - width, width, width, color)
        # Incremento em X e Y
        x1 += x_increment
        y1 += y_increment
      end
    end
  end
end

begin

    #Creating the console for debug messages.
    Console.initialize

    #Assigning a black background
    Graphics.backcolor = Color.new(0, 160, 160)

    Graphics.frame_rate = 60

    #Testing
    bmp = Bitmap.new('test6.png')
  bmp.draw_text(0,50,200,200,"The circle is in rev 16")
    sprite = Sprite.new
    sprite.bitmap = bmp
    sprite.tone = Tone.new(64,0,0,255)
    sprite2 = Sprite.new
    sprite2.bitmap = bmp
    sprite2.x = 240
    sprite2.tone = Tone.new(64,0,0,192)
    sprite3 = Sprite.new
    sprite3.bitmap = bmp
    sprite3.y = 240
    sprite3.tone = Tone.new(64,0,0,128)
    sprite4 = Sprite.new
    sprite4.bitmap = bmp
    sprite4.x = 240
    sprite4.y = 240
    sprite4.tone = Tone.new(64,0,0,0)
  # It's the same bitmap for all sprites. Everyone will change!
  sprite4.bitmap.fill_rect(Rect.new(0,0,32,32),Color.new(0,255,0))
  # Another way with effects YEAH
  bmp2 = Bitmap.new(64,64)
  sprite5 = Sprite.new
  sprite5.x = 570
  sprite5.bitmap = bmp2
  20.times {|i|
    sprite5.bitmap.fill_rect(0,0,64-i*2,64-i*2,Color.new(255,i*12+10,0))
  }
  bmp3 = Bitmap.new(64,64)
  sprite6 = Sprite.new
  sprite6.x = 570
  sprite6.y = 100
  sprite6.bitmap = bmp3
  
  # Let's make circles!
  20.times {|i|
    sprite6.bitmap.fill_circle(32,32,32-i*2,Color.new(255,i*12+10,0))
  }
  bmp4 = Bitmap.new(64,64)
  sprite7 = Sprite.new
  sprite7.x = 570
  sprite7.y = 200
  sprite7.bitmap = bmp4
  sprite7.bitmap.fill_rect(0,0,64,64,Color.new(0,255,0))
  sprite7.bitmap.fill_rect(0,0,20,20,Color.new(255,255,0))
  # Let's make some lines here
  20.times {|i|
    sprite7.bitmap.set_pixel(i,i,Color.new(0,0,0))
    sprite7.bitmap.set_pixel(20-i,i,Color.new(0,0,0))
    sprite7.bitmap.draw_line(64,i*2,0,64,1)
  }
  x = -1
  move = false
    loop do
        Graphics.update
        Input.update
    if move
      sprite7.x += 1
      move = false if sprite7.x == 640-sprite7.bitmap.width
    else
      sprite7.x -= 1
      move = true if sprite7.x == 0
    end
    puts x = Input.dir8 if x != Input.dir8
    if x != 0
      case x
      when 1 then sprite6.y += 1; sprite6.x -= 1
      when 2 then sprite6.y += 1
      when 3 then sprite6.y += 1; sprite6.x += 1
      when 4 then sprite6.x -= 1
      when 6 then sprite6.x += 1
      when 7 then sprite6.y -= 1; sprite6.x -= 1
      when 8 then sprite6.y -= 1
      when 9 then sprite6.y -= 1; sprite6.x += 1
      end
    end
  end
# This is a good rescue system :)
rescue
  script, line = $!.backtrace.to_s.split(':')
    puts "#{$!.class} in #{script}, line #{line}"
  puts $!.message, $!.backtrace
ensure
  gets
end