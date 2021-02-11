from serial import Serial
import time

arduino = Serial('COM9', 115200, timeout=.1)
arduino.close()
arduino.open()

def close():
    arduino.close()
def write(data):
    out = bytes(data, 'utf-8')
    arduino.write(out)
    time.sleep(.1)
    
def read():
    b = arduino.readline()
    string_n = b.decode()
    string = string_n.rstrip()
    flt = str(string)
    time.sleep(.1)
    return flt

if __name__ == '__main__':
    while True:
        msg = read()
        print(msg)
