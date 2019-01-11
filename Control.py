import gpio as GPIO
import math
import time
# GPIO.setmode(GPIO.BOARD)

class Control():
    #initial gpio pins
    def __init__(self):
        self.max_speed       = 72
        self.min_speed       = 70
        self.max_angle       = 45
        self.turn_factor     = 0.35
        self.fan_factor      = 1
        self.servo_dir       = -1 # = 1 or -1
        self.angle = 90
        self.fan_speed = 25
        self.max_dif   = 10
        self.startime = time.time()
        self.max_line_err = 100
        
    #main control method
    def update(self, data):
        
        dir = 0
        data_count = 0
        flag = 0

        for j in range(len(data)):
          if(data[j] != -1000):
            if(j-1>=0):
              if(math.fabs( data[j] - data[j-1]) > self.max_line_err):
                data[j] = -1000
            if(j+1<=len(data)-1):
              if(math.fabs( data[j] - data[j+1]) > self.max_line_err):
                data[j] = -1000

       # sum = data[0]*1 + data[1]*1 + data[2]*0.5 + data[0]*1



        for i in range(len(data)):
            if(data[i] != -1000):
                flag = 1
                if(i == 3):                  
                    dir += data[i]*0.3
                elif(i == 2):
                    dir += data[i]*0.5
                elif(i == 1):
                    dir += data[i]*1
                else:
                    dir += data[i]
                data_count += 1
        if(flag):
          temp_angle = (dir/data_count) * self.turn_factor
        else:
          temp_angle = self.angle
        if( temp_angle > self.max_angle ):
            temp_angle = self.max_angle
        elif( temp_angle < -1*self.max_angle ):
            temp_angle = -1*self.max_angle
        
        
        if( temp_angle - self.angle > self.max_dif ):
          temp_angle = self.angle + self.max_dif
        elif( temp_angle - self.angle < -1*self.max_dif ):
          temp_angle = self.angle - self.max_dif
        

        #temp_fan_speed = self.max_speed - math.fabs(temp_angle)*(self.max_speed - self.min_speed) / (self.max_angle) * self.fan_factor
        if(time.time() - self.startime > 2):
          temp_fan_speed = 69
        else:
          temp_fan_speed = 75
        self.angle = int(temp_angle)
        self.fan_speed = int(temp_fan_speed)
        return 'r' + str(self.servo_dir*self.angle) + 'f' + str(self.fan_speed) + '\n'
        '''
        if( int(temp_angle) != int(self.angle)  or int(temp_fan_speed) != int(self.fan_speed) ):
            self.angle = int(temp_angle)
            self.fan_speed = int(temp_fan_speed)
            return 'r' + str(self.servo_dir*self.angle) + 'f' + str(self.fan_speed) + '\n'
        else:
            return 0
        '''
    #clean up
    def clean(self): 
        GPIO.cleanup()
