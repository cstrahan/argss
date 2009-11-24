#Load Keys
require('keys.rb')

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a white background
	Graphics.backcolor = Color.new(0,0,0)

	Graphics.frame_rate = 60

	#Testing
	bmp = Bitmap.new(60, 60)
	bmp.fill_rect(15, 15, 30, 30, Color.new(255, 0, 255, 255))
        bmp.set_pixel(15, 15, Color.new(0, 255, 0, 255))
	p bmp.get_pixel(15, 15)
	p bmp.get_pixel(16, 16)
	p bmp.get_pixel(0, 0)

	spr = Sprite.new
	spr.bitmap = Bitmap.new('test3.png')
	p spr.bitmap.get_pixel(15, 15)
	p spr.bitmap.get_pixel(16, 16)
	p spr.bitmap.get_pixel(0, 0)
	spr.bitmap.blt(50, 50, bmp, Rect.new(0, 0, 60, 60), 255)
	
	spr2 = Sprite.new
	spr2.bitmap = Bitmap.new('test3.png')
	spr2.bitmap.blt(50, 50, bmp, Rect.new(0, 0, 60, 60), 192)
	spr2.x = 128

	spr3 = Sprite.new
	spr3.bitmap = bmp
	spr3.x = 256
	loop do
		Graphics.update
		Input.update
	end
rescue
	p $!.message
end
gets()
