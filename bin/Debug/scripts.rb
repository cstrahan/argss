#Load Keys
require('keys')

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a black background
	Graphics.backcolor = Color.new(128, 128, 128)

	Graphics.frame_rate = 60

	#Testing
	sprite = Sprite.new
	sprite.bitmap = Bitmap.new(640, 480)
	sprite.bitmap.draw_text(0,0,200,200, "AAA")
	sprite.bitmap.draw_text(0,0,200,200, "AAA",2)
	sprite.bitmap.draw_text(0,0,200,200, "AAA",1)
  
	sprite.bitmap.draw_text(0,0,640,480, "Centered", 1)
	sprite.bitmap.draw_text(100,100,640,480, "Centered2", 1)
  
	sprite.bitmap.draw_text(0,0,50,12, "Test123456789123456789")
	
	sprite.bitmap.draw_text(100,0,50,12, "Test123456789123456789",1)
	
	sprite.bitmap.draw_text(200,0,50,12, "Test123456789123456789",2)
	
	loop do
		Graphics.update
		Input.update
	end
rescue
	script, line = $!.backtrace.to_s.split(':')
	puts "#{$!.class} in #{script}, line #{line}"
	puts $!.message, $!.backtrace
ensure
	gets
end
