def game_test
  #Creating the console for debug messages.
  Output.msgbox

  #Assigning a background
  Graphics.backcolor = Color.new(0, 0, 0)

  Graphics.frame_rate = 40
  
  require("zlib")
  require("Win32API")
  
  scripts = load_data("Data/Scripts.rxdata")
  scripts.each do |s|
    eval(Zlib::Inflate.inflate(s[2]), nil, s[1])
  end
end