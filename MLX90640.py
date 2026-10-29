'''
Author: LunarW
Date: 2024-03-27 22:39:21
LastEditors: LunarW
LastEditTime: 2024-03-31 18:39:53
FilePath: \Codes\BS4\MLX90640.py
Description: 

Copyright (c) 2024 by LunarW, All Rights Reserved. 
'''
import serial
import matplotlib.pyplot as plt
import numpy as np
from scipy import interpolate

# 创建一个串口实例
ser = serial.Serial('COM16', 115200, timeout=0.5)  # 请根据实际情况修改串口号和波特率

# 定义帧头和帧尾
frame_header = '==Start==\n'
frame_footer = '==Stop==\n'

# 读取数据
data = ""
count = 0
plt.ion()  # 打开交互模式
for i in range(100):    # 忽略前100行数据
    temp = ser.readline()

while True:
    line = ser.readline().decode('utf-8')  # 解码字节串为字符串
    if line == frame_header:
        # 开始读取数据
        data = ""
    elif line == frame_footer:
        # 结束读取数据
        # print(data)
        if count >= 5: # 忽略前5帧数据
            lines = data.split('\n')
            numbers = [[float(x) for x in line.split()] for line in lines]
            numbers.pop()  # 删除最后一个空行
            numbers = np.array(numbers) # 转换为numpy数组
            # break

            plt.clf()  # 清除当前图像
            plt.imshow(numbers, cmap='jet', interpolation='nearest')
            plt.colorbar()
            plt.show()
            plt.pause(0.001)  # 暂停一段时间，不然画得太快会卡住显示不出来
        else:
            count += 1
    else:
        # 读取数据
        data += line
        
    # print(line)  # 打印读取到的数据
    # print(line == frame_footer)
    

# 存储数据
# with open("data.bin", "wb") as f:
#     f.write(data)
#     ser.close()
