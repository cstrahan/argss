#Load Keys
require('keys')

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a black background
	Graphics.backcolor = Color.new(0, 0, 0)

	Graphics.frame_rate = 60

	#Testing
	sprite = Sprite.new
	sprite.bitmap = Bitmap.new(100, 100)
	sprite.bitmap.draw_text(0, 0, 100, 100, "Test")
	
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
