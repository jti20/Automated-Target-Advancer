#this should run on startup, no need for it to be run by webserver
#can update weather data at all times rather than when webpage updates
import serial
import time
import shutil #for file copying

def change_arrow(degs):
        current_arrow = 'current_arrow.jpg'
        new_arrow = 'current_arrow.jpg'
        # diagonals get 1 extra degree priority over hard left right forward or back
        if((degs>=0 and degs<22) or (degs<=360 and degs>338)):
            # within 22 degrees of "forward of the target" or
            # blowing into the "face" of the target
            new_arrow = 'forward.jpg'
        elif(degs>=22 and degs <=68):
            # within 23 degrees of forward and to the right
            new_arrow = 'forward_right.jpg'
        elif(degs>68 and degs <112):
            # within 22 degrees of right the target 
            new_arrow = 'right.jpg'
        elif(degs>=112 and degs <=158):
            # within 23 degrees of back and to the right
            new_arrow = 'back_right.jpg'
        elif(degs>158 and degs <202):
            # within 22 degrees of straight back (into the face
            # of the shooter)
            new_arrow = 'back.jpg'
        elif(degs>=202 and degs <=248):
            # within 23 degrees of back and to the left
            new_arrow = 'back_left.jpg'
        elif(degs>248 and degs <292):
            # within 22 degrees of left
            new_arrow = 'left.jpg'
        elif(degs>=292 and degs <=338):
            # within 23 degrees of forward and to the left
            new_arrow = 'forward_left.jpg'
        else:
            #should never reach here. Should always be 0 to 360 display old data instead
            new_arrow = 'current_arrow.jpg'
        shutil.copyfile(new_arrow,current_arrow)
        

ser = serial.Serial(port='/dev/ttyS0',
	baudrate=9600,
	parity=serial.PARITY_NONE,
	stopbits=serial.STOPBITS_ONE,
	bytesize=serial.EIGHTBITS,
	timeout=1)
while True:	
	#read in the serail line
	weather=ser.readline()
	#split the string into the data parts
	data = weather.split("!")
	if(len(data)==5):
		text_file = open("/var/www/html/weather.txt",'w')
	#list should always be 5 long 
		text_file.write("Humidty: " + data[0] +"%\n") 
		text_file.write("Pressure: " +data[1]+"kPa\n")
		text_file.write("Temp: " +data[2]+"F\n")
		text_file.write("Speed: " +data[3] +"mph\n")
		#text_file.write("Dir: " +data[4] + "deg")
		#instead of writing degree number do arrow instead
		text_file.close()
		change_arrow(int(data[4]))
	else:
		print "Error Reading serial port"
	time.sleep(1)
