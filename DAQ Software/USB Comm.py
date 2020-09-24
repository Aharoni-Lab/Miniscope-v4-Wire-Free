import datetime
import serial

serialPort = serial.Serial(port = "COM6", baudrate = 9600, bytesize = 8, timeout = 0, stopbits = serial.STOPBITS_ONE)
t_before = datetime.datetime.now()

serialString = ""
if (serialPort.in_waiting > 0):
    serialString = serialPort.readline()

t_after = datetime.datetime.now()
t_diff = t_after - t_before
t_msec = t_diff.microseconds

print(serialString, t_msec, len(serialString)/t_msec)