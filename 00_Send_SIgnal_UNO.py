import serial
import time

# 시리얼 포트 설정
ser = serial.Serial('COM3', 9600)  # COM3 포트에 9600 보레이트로 연결

while True:
    command = input('Enter your command: ')  # 사용자로부터 커맨드 입력
    if command == 'exit':
        break
    ser.write(command.encode())  # 커맨드를 시리얼 포트로 전송
    time.sleep(1)  # 잠시 기다림

# 시리얼 포트 연결 종료
ser.close()


