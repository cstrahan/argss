Output.console

tests = Dir.entries('Test/Tests scripts')
tests.delete('.')
tests.delete('..')
tests.delete('.svn')

tests.each_index do |i|
  tests[i] = File.basename(tests[i], '.rb')
  print "#{i + 1} for #{tests[i]} test\n"
end

loop do
  print "\nEnter option: "
  opt = gets.to_i
  if opt > 0 && opt <= tests.size
    require("Test/Tests scripts/#{tests[opt - 1]}")
    exit
  else
    print "Invalid option\n"
  end
end
