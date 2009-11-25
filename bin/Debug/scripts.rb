# MauMau Bitmap Test for ARGSS
# Testing Bitmap fill_rect !!

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
end

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a black background
	Graphics.backcolor = Color.new(0, 0, 0)

	Graphics.frame_rate = 60

	#Testing
	bmp = Bitmap.new('test6.png')
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
	10.times {|i|
		sprite5.bitmap.fill_rect(0,0,64-i*4,64-i*4,Color.new(255,i*25+25,0))
	}
	bmp3 = Bitmap.new(64,64)
	sprite6 = Sprite.new
	sprite6.x = 570
	sprite6.y = 100
	sprite6.bitmap = bmp3
	# Let's make circles!
	10.times {|i|
		sprite6.bitmap.fill_circle(32,32,32-i*4,Color.new(255,i*25+25,0))
	}
	bmp4 = Bitmap.new(64,64)
	sprite7 = Sprite.new
	sprite7.x = 570
	sprite7.y = 200
	sprite7.bitmap = bmp4
	sprite7.bitmap.clear(Color.new(0,255,0))
	sprite7.bitmap.fill_rect(0,0,20,20,Color.new(255,255,0))
	# Let's make some lines here
	20.times {|i|
		sprite7.bitmap.set_pixel(i,i,Color.new(0,0,0))
		sprite7.bitmap.set_pixel(20-i,i,Color.new(0,0,0))
	}
	
	x = -1
	loop do
		Graphics.update
		Input.update
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
