import serial
import datetime
import threading
import time

frame_w = int(768 / 2)
frame_h = int(592 / 2)
frame = bytearray(100) # frame_w * frame_h)

# Make sure to run this script before connecting the MCU USB (Keep the UART USB connected, so the port doesn't close.)
# Max baudrate = 3000000
serialPort = serial.Serial(port = "COM6", baudrate = 3000000, bytesize = 8, timeout = None, stopbits = serial.STOPBITS_ONE)
t_before = datetime.datetime.now()

ppf = serialPort.readinto(frame)

t_after = datetime.datetime.now()
t_diff = (t_after - t_before).total_seconds()
t_msec = t_diff.microseconds