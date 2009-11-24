#Load Keys
require('keys.rb')

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a white background
	Graphics.backcolor = Color.new(0,0,0)

	Graphics.frame_rate = 60

	#Testing
	spr = Sprite.new
	spr.bitmap = Bitmap.new('test3.png')
	
	spr2 = Sprite.new
	spr2.bitmap = Bitmap.new('test3.png')
	spr2.x = 128
	loop do
		Graphics.wait(10)
		Input.update
		spr.bitmap.dispose
		spr.bitmap = Bitmap.new('test3.png')
		spr.bitmap.hsl_change(0, -1, 1.5, Rect.new(30, 30, 30, 30))
	end
rescue
	p $!.message
end
gets()
