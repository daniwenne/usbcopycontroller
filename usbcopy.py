import serial
import os
with serial.Serial('/dev/ttyUSB0', 9600, timeout=None) as ser:
    while True:
        num_cop=int(ser.read())
        ser.write(b'S')
        os.system("scanimage --resolution 300 --mode Gray --compression None -o /tmp/copia.png")
        os.system("lp -o media=a4 -o fit-to-page -n {} /tmp/copia.png".format(str(num_cop)))
        os.system("rm /tmp/copia.png")
        ser.write(b'E')
