import serial
import time

class SerialCommunicator():
    def __init__(self,port_num) -> None:
        self.open(port_num)

    def open(self,port_num):
        port_string = f'COM{port_num}'
        self.ser = serial.Serial(port_string, 9600)

    def read(self):
        cnt = 0
        while True:
            if self.ser.in_waiting > 0:
                line = self.ser.readline().decode('utf-8').rstrip()
                print(line)
                cnt += 1
                if cnt > 10:
                    break
        return line
    def read_once(self):
        line = ''
        if self.ser.in_waiting > 0:
            line = self.ser.readline().decode('utf-8').rstrip()
            print(line)
        return line
        
    
    def write(self,ch_num):
        send_str = f'101,{ch_num},0\n'
        print(send_str,end='')
        command = send_str
        # self.ser.writelines(command.encode())
        self.ser.write(command.encode()) 
        return
    
    def close(self):
        self.ser.close()

    def main(self):
        time.sleep(3)

        for i in range(0,16):
            self.write(i) # 101 is protocol id. and 1 is turn on.
            time.sleep(2)
            while True:
                ret = self.read_once()
                if ret.split(',')[-1] == '1':
                    avg_voltage = ret.split(',')[-2]
                    id = ret.split(',')[-3]
                    print(f'CH{id} Voltage : {avg_voltage}V')
                    break

    

if __name__ == "__main__":
    ser_inst = SerialCommunicator(3)
    ser_inst.main()

    # time.sleep(3) # Need to wait connection.

    # for i in range(0,16):
    #     ser_inst.write(i) # 101 is protocol id. and 1 is turn on.
    #     time.sleep(2)
    #     while True:
    #         ret = ser_inst.read_once()
    #         if ret.split(',')[-1] == '1':
    #             avg_voltage = ret.split(',')[-2]
    #             id = ret.split(',')[-3]
    #             print(f'CH{id} Voltage : {avg_voltage}V')
    #             break





