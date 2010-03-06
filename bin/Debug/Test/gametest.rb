# Set Message Box as output system
Output.msgbox

#Assigning a black background
Graphics.backcolor = Color.new(0, 0, 0)

Graphics.frame_rate = 40

$DEBUG = true

require("Test/zlib")
require("Test/Win32API")

$DEBUG = true

scripts = load_data("Data/Scripts.rxdata")
scripts.each do |s|
  eval(Zlib::Inflate.inflate(s[2]), nil, s[1])
end
