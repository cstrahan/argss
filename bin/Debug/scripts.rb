#Load Keys
require('keys.rb')

begin
	#Creating the console for debug messages.
	Console.initialize

	#Assigning a white background
	Graphics.backcolor = Color.new(0, 0, 0)

	Graphics.frame_rate = 60

	#Testing
	SPEED = 1
	bmp = Bitmap.new('test3.png')
	spr = Sprite.new
	spr.bitmap = bmp
	spr.tone = Tone.new(100, 100, 100, 0)

	def spr_down(spr)
		spr.y = ((spr.y + SPEED) >= Graphics.height) ? (-spr.height)     : (spr.y + SPEED)
	end
	def spr_left(spr)
		spr.x = ((spr.x - SPEED) <= -spr.width)      ? (Graphics.width)  : (spr.x - SPEED)
	end
	def spr_right(spr)
		spr.x = ((spr.x + SPEED) >= Graphics.width)  ? (-spr.width)      : (spr.x + SPEED)
	end
	def spr_up(spr)
		spr.y = ((spr.y - SPEED) <= -spr.height)     ? (Graphics.height) : (spr.y - SPEED)
	end

	loop do
		Graphics.update
		Input.update
		case Input.dir8
		when 1
			spr_down(spr)
			spr_left(spr)
		when 2
			spr_down(spr)
		when 3
			spr_down(spr)
			spr_right(spr)
		when 4
			spr_left(spr)
		when 6
			spr_right(spr)
		when 7
			spr_up(spr)
			spr_left(spr)
		when 8
			spr_up(spr)
		when 9
			spr_up(spr)
			spr_right(spr)
		end
		if Input.trigger?(Keys::KP_PLUS)
			Graphics.frame_rate += 10
		elsif Input.trigger?(Keys::KP_MINUS)
			Graphics.frame_rate = [Graphics.frame_rate - 10, 10].max
		end
		if Input.trigger?(Keys::N1)
			Graphics.backcolor = Color.new(0, 0, 0)
		elsif Input.trigger?(Keys::N2)
			Graphics.backcolor = Color.new(255, 255, 255)
		elsif Input.trigger?(Keys::N3)
			Graphics.backcolor = Color.new(128, 128, 128)
		elsif Input.trigger?(Keys::N4)
			Graphics.backcolor = Color.new(rand(256), rand(256), rand(256))
		elsif Input.trigger?(Keys::N5)
			Graphics.backcolor = Color.new(255, 0, 0)
		elsif Input.trigger?(Keys::N6)
			Graphics.backcolor = Color.new(0, 255, 0)
		elsif Input.trigger?(Keys::N7)
			Graphics.backcolor = Color.new(0, 0, 255)
		end
		if Input.trigger?(Keys::Q)
			spr.tone = Tone.new(0, 0, 0, 0)
		elsif Input.trigger?(Keys::W)
			#spr.tone = Tone.new(-128 + rand(255), -128 + rand(255), -128 + rand(255), rand(256))
			spr.tone = Tone.new(-128 + rand(255), -128 + rand(255), -128 + rand(255), 0)
		end

	end
rescue
	p $!.message
end
gets()
