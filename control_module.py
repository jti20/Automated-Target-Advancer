from tkinter import *
from PIL import Image, ImageTk 
import urllib.request
import os
from socket import timeout

# filepath where the photo of the target is stored
TARGET_IMAGE_PATH = 'image.jpg'

# filepath for the image displayed when no connection can  be made to the target module
DISCONNECTED_IMAGE = 'disconnected.jpg'


    
class TargetDisplay():
    # Creates a window to display the images and GUI for modifying the image update mode
    # also contains functions to grab the new image from the target module

    # Possibility of adding the ability to save the image of the target to a flash drive?

    def __init__(self,root):
        self.root = root
        self.img_path = TARGET_IMAGE_PATH
        self.disconnected = 0 #no connection if 1
        

        # create a canvas for the image to be displayed on
        self.canvas = Canvas(root, width = 600, height = 480)
        self.canvas.pack(side = LEFT)

        # display the disconnected image in this canvas
        self.current_image = ImageTk.PhotoImage(Image.open(DISCONNECTED_IMAGE))
        self.displayed_image = self.canvas.create_image(0,0, anchor = NW, image = self.current_image)
        self.previous_image = self.current_image

        # Checkbox for enabling automatic updates
        self.auto_update = BooleanVar()
        self.auto_update_toggle = Checkbutton(root, text = 'Auto \nUpdate \nimage?', variable = self.auto_update, command = self.update_image)
        self.auto_update_toggle.pack(side=RIGHT)
        self.auto_update_toggle.select()# checks the checkbox to have it start at auto downloading


        # Button to manually update the image or force an image update
        self.update_button = Button(root, text = 'Update', command=self.update_image)
        self.update_button.pack(side = RIGHT)
        self.check_toggle()
        self.url = 'http://192.168.42.1/image.jpg'
        self.update_image()



    def display_disconnected(self):
        self.disconnected = 1
        self.current_image = ImageTk.PhotoImage(Image.open(DISCONNECTED_IMAGE))
        self.canvas.itemconfig(self.displayed_image, image = self.current_image)
        return
            


    def download_new_image(self):
        #downloads new image from the web server
        try:
            new_image = urllib.request.urlopen(self.url,timeout = 3, )
            open(TARGET_IMAGE_PATH,'wb').write(new_image.read())
            
        except urllib.error.URLError:
            # if it can't find the URL it throws an error and there is no connection to the target
            # keep trying to redownload until connection is reestablished
            print('urlerror')
            self.display_disconnected()
        except timeout:
            #Connection timed out
            print('Timeout')
            self.display_disconnected()

        except:
            
             #downloaded a partial image file. 
            print('incompleteread')
            

        
            
        

    def update_image(self):
        #updates the display with a new image
        self.disconnected=0
        self.download_new_image()
        try:
            if(self.disconnected==0):
                self.current_image = ImageTk.PhotoImage(Image.open(self.img_path))
                self.canvas.itemconfig(self.displayed_image, image = self.current_image)
                self.previous_image = self.current_image
                print('New Image Downloaded')
        except OSError:
            print('OSError')
            

      


    def check_toggle(self):
        if (self.auto_update.get()==True):
            print("auto")
            self.update_image()
        self.canvas.after(1000, self.check_toggle)

    def change_target(self):
        # commands the target module to run a python script that will send a
        # command to the down range arduino to change targets
        try:
            ssh = paramiko.SSHClient()
            ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
            ssh.connect('192.168.42.1',username = 'pi', password='raspberry')
            ssh.exec_command('sudo python change_target.py')
        except:
            print('Err sending target command')
                
        


root = Tk()
TargetDisplay(root)
root.mainloop()
            
    
        
