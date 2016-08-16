# -*- coding: utf-8 -*-
import re
import sys
import math

#print 'Argument List:', str(sys.argv)
arglist = sys.argv
#print (arglist[1])
#print (arglist[2])
#foldername = "Images/5ms/"
foldername = arglist[1] + "/" + arglist[2] + "/" # uncomment this for shell script
#print foldername
filename = arglist[3]				  # uncomment this for shell script
f = open(foldername + filename , 'r')		  # uncomment this for shell script
#filename = "Images/0ms/5msresults.txt"
#f =  open(filename, 'r')

###############################################################################
# 	reading file and storing data in arrays 
num_lines = sum(1 for line in open(foldername + filename ))		# uncomment this for shell script
#num_lines = sum(1 for line in open(filename))
#print num_lines

delimiters = " ", "\t", "\n"
array = {}
i = 0
for line in f:
	row = re.split(" |\t|\n",line)
	array[i] = row 
	i = i + 1
###############################################################################	


###############################################################################
#	Finding brightest value
x = 0
brightest_value = 0
while x < num_lines:
	if float(array[x][2]) > float(brightest_value):
		brightest_value = array[x][2] 	
	x = x+1

#print ("brightest_value")
#print brightest_value
###############################################################################


###############################################################################
#	normalising
mod_array= {}

f1 = open(foldername + 'normalised_' + filename , 'w') # uncomment this for shell script
#f1 = open(filename + '_normalised', 'w') # uncomment this for shell script
x = 0
while x < num_lines:
	a = float(array[x][2])
	b = float(brightest_value)
	c = a/b
	d =  float(array[x][0])
	f1.write(str(d))
	f1.write("\t")
	f1.write(str(c) )
	f1.write("\n")
	x = x+1
	mod_array[x] = c
###############################################################################


# testing std and mean
Start_frame=99 # offset in frame number between array and filenames 
Drop_frame = 0
Last_frame = num_lines
Laser_off_frame = 0
Molasses_frame = 0
zero_image = 0

###############################################################################
# find drop
x = 1
stop = 0
drop = 0
checkdrop = 0
scan_range = 50
stop_scan = 0
mean_before = 0
mean_after = 0
compare_drop = 0

while (x < num_lines-1): 
  n = mod_array[x]
  n1 = mod_array[x+1]
  #print x
 #print n - n1
  if(n - n1 > compare_drop):
    compare_drop = n - n1  
    Drop_frame = x+1
  x= x +1
print (Drop_frame + Start_frame)  

   #while (checkdrop == 0)
    #while (scan_range > 0 && stop_scan == 0):
     # if (Drop_frame - scan_range < 0):
	#scan_range = scan_range - 1
      #else: 
	##mean before drop and mean after drop
	#x_b = 0
	#while (x_b < Drop_frame ): 
	  #sum_before_drop_frames = sum_before_drop_frames  + mod_array[x_b] 
	  #x_b = x_b +1
	  #number_of_frame_used = number_of_frame_used + 1
	#mean_beforedrop = sum_before_drop_frames / number_of_frame_used
	#number_of_frame_used = 0
  
        #x_a = Drop_frame 
	#while (x_a < Last_frame): 
	 # sum_after_drop_frames = sum_after_drop_frames  + mod_array[x_a] 
	  #x_a = x_a + 1
	  #number_of_frame_used = number_of_frame_used + 1
	#mean_after_drop = sum_after_drop_frames / number_of_frame_used
	
#print ("Drop_frame:")
#print (Drop_frame + Start_frame)
#print (" ")


number_of_frame_used = 0
###############################################################p################
###############################################################p################
# find mean and standard deviation of frames after drop to end
clearance = 10 # clearance from drop
x = Drop_frame + clearance
# check if you can add 10 to drop_frame and be less than last_frame
if ( Drop_frame + clearance > Last_frame):
    x = Drop_frame - clearance
mean = 0
sum_deviation= 0
standard_deviation = 0

number_of_frame_used = 0
sum_end_frames = 0
while (x < Last_frame): 
	n = mod_array[x]
	sum_end_frames = sum_end_frames  + n 
	x= x +1
	number_of_frame_used = number_of_frame_used + 1

mean = sum_end_frames / number_of_frame_used
print ("mean")
print mean

x = Drop_frame + clearance
while (x < Last_frame): 
      n = mod_array[x]
      sum_deviation = sum_deviation + (n-mean)*(n-mean)
      x= x +1

standard_deviation = math.sqrt(sum_deviation/number_of_frame_used)
#print ("standard_deviation")
#print standard_deviation
#print (" ")
##############################################################
## if the video is just noise or not useable
noise = False
if ((mod_array[1] < (mean + 6*standard_deviation)) and  (mod_array[1] > (mean - 6*standard_deviation)) ):
    print ("0")
    noise = True 


##############################################################
#finding Lasers off
x = Drop_frame 
N_std = 3
while (x < Last_frame and stop == 0 and noise == False ): 
      n = mod_array[x]
      if (n < mean + N_std*standard_deviation):
	  Laser_off_frame = x
	  print("lasers off")
	  print  (Laser_off_frame + Start_frame)
	  print (" ")
	  stop = 1
      x = x + 1
stop = 0

##############################################################

###############################################################################
# Looking for molasses or zero point frame
molasses_stage = 1
if ((Laser_off_frame - 1) > Drop_frame and noise ==  False ):
    Molasses_frame = Laser_off_frame - 1
    zero_image = Molasses_frame 
if( (Laser_off_frame - 1) == Drop_frame):
    print("no molasses close drop and laser")
    zero_image = Drop_frame
else:
    molasses_stage = 0
    print("no molasses")
    print((mean + 6*standard_deviation))
    if (mod_array[Drop_frame] < (mean + 6*standard_deviation)):
      zero_image = Drop_frame - 1
    print("Last MOT at:")
    print (zero_image + Start_frame)
    print (" ")
    

if(noise ==  False and molasses_stage == 1):
  print ("Zero_image")
  if (mod_array[zero_image] < (mean + 5*standard_deviation)):
      zero_image = Drop_frame - 1
  print (zero_image + Start_frame)
  print ("   ")
###############################################################################


          