
# Load Keys module
require('Test/keys')

Output.console

TESTS = ["tone","bmpsprite", "window", "maumau", "rtp",
              "rotate", "flashflip", "blend", "game"]

TESTS.each_index do |i|
  print "#{i + 1} for #{TESTS[i]} test\n"
end

loop do
  print "\nEnter option: "
  opt = gets.to_i
  if opt > 0 && opt <= TESTS.size
    require("Test/#{TESTS[opt - 1]}test")
    exit
  else
    print "Invalid option\n"
  end
end
