#Load Keys
require('keys.rb')

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a white background
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
	loop do
		Graphics.update
		Input.update
	end
rescue
	p $!.message
end
gets()
