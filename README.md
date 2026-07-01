# ESP32-2432S028R-Mini_Reader
Making a Mini_Reader by using Board ESP32-2432S028R


############## CMD ##############
C:\Users\dongt\AppData\Local\Arduino15\packages\esp32\tools\mklittlefs\3.0.0-gnu12-dc7f933>mklittlefs.exe -c C:\Users\dongt\OneDrive\Documents\Arduino\Mini_Reader\data -s 0x100000 

C:\Users\dongt\AppData\Local\Arduino15\packages\esp32\tools\esptool_py\4.5.1\esptool.exe --chip esp32 --port COM9 write_flash -z 0x290000 C:\Users\dongt\OneDrive\Documents\Arduino\Mini_Reader\littlefs.bin

# ONLY NOTICE IN Mini_Reader file
