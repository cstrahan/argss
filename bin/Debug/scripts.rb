#Load Keys
require('keys')

require('tonetest')
require('bmpspritetest')
require('windowtest')
require('maumautest')

Output.console

print "1 for Tone test\n"
print "2 for Bitmap and Sprite test\n"
print "3 for Window test\n"
print "4 for Mau Mau test\n"

test = 0
until test != 0
  print "\nEnter option: "
  opt = gets.to_i
  if opt > 0 && opt < 5
    test = opt 
  else
    print "Invalid option\n"
  end
end

=begin
print "Press F1 for Tone test\n"
print "Press F2 for Bitmap and Sprite test\n"
print "Press F3 for Window test\n"
print "Press F4 for Mau Mau test\n"

test = 0
until test != 0
  Graphics.update
  Input.update
  test = 1 if Input.press?(Keys::F1)
  test = 2 if Input.press?(Keys::F2)  
  test = 3 if Input.press?(Keys::F3)
  test = 4 if Input.press?(Keys::F4)
end
=end

case test
when 1
  tone_test
when 2
  bmpsprite_test
when 3
  window_test
when 4
  maumau_test
end