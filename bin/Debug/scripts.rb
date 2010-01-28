
#Load Keys
require('keys')

require('tonetest')
require('bmpspritetest')
require('windowtest')
require('maumautest')
require('rtptest')
require('gametest')

Output.console

print "1 for Tone test\n"
print "2 for Bitmap and Sprite test\n"
print "3 for Window test\n"
print "4 for Mau Mau test\n"
print "5 for RTP test\n"
print "6 for game test\n"

test = 0
until test != 0
  print "\nEnter option: "
  opt = gets.to_i
  if opt > 0 && opt < 7
    test = opt 
  else
    print "Invalid option\n"
  end
end

case test
when 1
  tone_test
when 2
  bmpsprite_test
when 3
  window_test
when 4
  maumau_test
when 5
  rtp_test
when 6
  game_test
end