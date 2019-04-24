import shutil #for file copying
degs = 339
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
