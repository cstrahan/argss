#================================================================================
# Set the Console as output system
#================================================================================
Output.console

#================================================================================
# Config
#================================================================================
TIMES_A = 1
TIMES_B1 = 1
TIMES_B2 = 1
TIMES_C = 2
TIMES_D = 2
TIMES_E = 20

#================================================================================
# Load Win32API and declare API
#================================================================================
require('Test/Win32API')

GetCurrentProcess = Win32API.new('kernel32', 'GetCurrentProcess', '', 'L')
$proccess_id = GetCurrentProcess.call()

begin
  GetProcessMemoryInfo = Win32API.new('kernel32', 'GetProcessMemoryInfo', 'LPL', 'L')
rescue
  GetProcessMemoryInfo = Win32API.new('psapi', 'GetProcessMemoryInfo', 'LPL', 'L')
end

#================================================================================
# Get memory usage method
#================================================================================
def get_memory_usage()
  buffer = "\0" * 40
  GetProcessMemoryInfo.call($proccess_id, buffer, 40)
  buffer.unpack('L10')[3]
end

#================================================================================
# Print memery difference
#================================================================================
$mem_current = $mem_last = 0
def print_mem_diff(diff = true)
  sleep(0.01)
  $mem_current = get_memory_usage() / (2 ** 20).to_f
  print sprintf("Memory usage: %4.2f MB\n", $mem_current)
  print sprintf("Difference: %4.2f MB\n", $mem_current - $mem_last) if diff
  print "\n"
  $mem_last = $mem_current
end

#================================================================================
# Bitmap are cached for OpenGL when displayed, this is for excluding the first
# bitmap cache when it is displayed on screen
#================================================================================
GC.enable
bmp = Bitmap.new(32, 32)
bmp.fill_rect(0, 0, 32, 32, Color.new(255, 0, 0))
spr = Sprite.new
spr.bitmap = bmp
Graphics.update
spr.dispose
spr = nil
Graphics.update
GC.start

#================================================================================
# Start Test A
#================================================================================
print "=" * 30 + "\n Test A - Graphical objects creation\n" + "=" * 30 + "\nInitial "
print_mem_diff(false)
$mem_initial = $mem_last

[Sprite, Plane, Tilemap, Window].each do |c|
  print "===== #{c} test\n"
  TIMES_A.times do
    o = c.new
    o.dispose
    o = nil
    GC.start
  end
  print_mem_diff()
end

#================================================================================
# Start Test B
#================================================================================
print "=" * 30 + "\n Test B - Graphical objects display\n" + "=" * 30 + "\nInitial "
print_mem_diff(false)

[Sprite, Plane].each do |c|
  Graphics.update
  print "===== #{c} test\n"
  TIMES_B1.times do
    o = c.new
    o.bitmap = bmp
    Graphics.wait(TIMES_B2)
    o.dispose
    o = nil
    GC.start
  end
  print_mem_diff()
end
Graphics.update
print "===== Tilemap test\n"
class Table; attr_accessor :data; end
TIMES_B1.times do
  o = Tilemap.new
  o.tileset = bmp
  o.map_data = Table.new(20, 15, 3)
  o.map_data.data = [384] * 20 * 15 * 3
  o.priorities = Table.new(385)
  o.priorities.data = [0] * 385
  Graphics.wait(TIMES_B2)
  o.dispose
  o = nil
  GC.start
end
print_mem_diff()
Graphics.update
print "===== Window test\n"
TIMES_B1.times do
  o = Window.new
  o.windowskin = bmp
  o.width = 100
  o.height = 100
  Graphics.wait(TIMES_B2)
  o.dispose
  o = nil
  GC.start
end
print_mem_diff()

Graphics.update

#================================================================================
# Start Test C
#================================================================================
print "=" * 30 + "\n Test C - Bitmaps\n" + "=" * 30 + "\nInitial "
print_mem_diff(false)

[
  [:blt, [0, 0, bmp, bmp.rect, 128]],
  [:blt, [0, 0, bmp, bmp.rect]],
  [:stretch_blt, [Rect.new(0, 0, 128, 128), bmp, bmp.rect, 128]],
  [:stretch_blt, [Rect.new(0, 0, 128, 128), bmp, bmp.rect]],
  [:fill_rect, [0, 0, 128, 128, Color.new(128, 128, 128, 128)]],
  [:clear, []],
  [:clear, [Color.new(0, 255, 0)]],
  [:set_pixel, [0, 0, Color.new(0, 255, 255)]],
  [:hue_change, [90]],
  [:draw_text, [0, 0, 128, 128, "Test TEST"]],
  [:text_size, ["Test TEST"]]
].each do |m|
  print "===== #{m[0]} test\n"
  TIMES_C.times do
    o = Bitmap.new(128, 128)
    o.method(m[0]).call(*(m[1]))
    o.dispose
    o = nil
    GC.start
  end
  print_mem_diff()
end

#================================================================================
# Start Test D
#================================================================================
print "=" * 30 + "\n Test D - Bitmaps part II\n" + "=" * 30 + "\nInitial "
testd_bmp = Bitmap.new(128, 128)
print_mem_diff(false)

[
  [:blt, [0, 0, bmp, bmp.rect, 128]],
  [:blt, [0, 0, bmp, bmp.rect]],
  [:stretch_blt, [Rect.new(0, 0, 128, 128), bmp, bmp.rect, 128]],
  [:stretch_blt, [Rect.new(0, 0, 128, 128), bmp, bmp.rect]],
  [:fill_rect, [0, 0, 128, 128, Color.new(128, 128, 128, 128)]],
  [:clear, []],
  [:clear, [Color.new(0, 255, 0)]],
  [:set_pixel, [0, 0, Color.new(0, 255, 255)]],
  [:hue_change, [90]],
  [:draw_text, [0, 0, 128, 128, "Test TEST"]],
  [:text_size, ["Test TEST"]]
].each do |m|
  print "===== #{m[0]} test\n"
  TIMES_D.times do
    testd_bmp.method(m[0]).call(*(m[1]))
  end
  print_mem_diff()
end
testd_bmp.dispose

#================================================================================
# Start Test E
#================================================================================
print "=" * 30 + "\n Test D - Bitmap and Sprite\n" + "=" * 30 + "\nInitial "
teste_bmp = Bitmap.new(128, 128)
teste_spr = Sprite.new
teste_spr.bitmap = teste_bmp
Graphics.update
print_mem_diff(false)

[
  [:blt, [0, 0, bmp, bmp.rect, 128]],
  [:blt, [0, 0, bmp, bmp.rect]],
  [:stretch_blt, [Rect.new(0, 0, 128, 128), bmp, bmp.rect, 128]],
  [:stretch_blt, [Rect.new(0, 0, 128, 128), bmp, bmp.rect]],
  [:fill_rect, [0, 0, 128, 128, Color.new(128, 128, 128, 128)]],
  [:clear, []],
  [:clear, [Color.new(0, 255, 0)]],
  [:set_pixel, [0, 0, Color.new(0, 255, 255)]],
  [:hue_change, [90]],
  [:draw_text, [0, 0, 128, 128, "Test TEST"]],
  [:text_size, ["Test TEST"]]
].each do |m|
  print "===== #{m[0]} test\n"
  TIMES_E.times do
    teste_bmp.method(m[0]).call(*(m[1]))
    Graphics.update
    Graphics.wait(5)
  end
  print_mem_diff()
end
testd_bmp.dispose

#================================================================================
# End
#================================================================================
print "=" * 30 + "\n Finished all Tests\n" + "=" * 30 + "\nFinal and initial memory comparison:\n"
$mem_last = $mem_initial
print_mem_diff()

print "Press a key to continue...\n"

gets()