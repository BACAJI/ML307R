import sys
import time
import os
import subprocess
import ctypes
import time
import shutil
import zipfile
import repr
cats = CATSProxy.Init()
sys.stdout = cats
sys.stderr = cats
#get current working directory
print 'Current working directory : ', os.getcwd()

############################# Delete Old Logs #########################################
#delete old local files and create temp directory
temp_dir = 'temp'
shutil.rmtree(temp_dir,ignore_errors=True)
os.mkdir(temp_dir)


filename_prefix = time.strftime('%Y-%m-%d-%H-%M-%S', time.localtime(time.time()))
#print current_time

#require for root
cmd = '.\\adb.exe wait-for-device root'
print cmd
p = subprocess.Popen(cmd)

#clear previous log
cmd = '.\\adb.exe wait-for-device shell logcat -c'
print cmd
p = subprocess.Popen(cmd)

#delete old files
cmd = '.\\adb.exe wait-for-device shell rm -rf /data/DKBx_x.cap'
print cmd
p = subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(output, err) = p.communicate()
p_status = p.wait()
#print output
#print p_status

cmd = '.\\adb.exe wait-for-device shell rm -rf /data/DKBx_x.txt'
print cmd
p = subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(output, err) = p.communicate()
p_status = p.wait()
#print output
#print p_status

cmd = '.\\adb.exe wait-for-device shell rm -rf /data/DKBx_x_radio.txt'
print cmd
p = subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(output, err) = p.communicate()
p_status = p.wait()
#print output
#print p_status

cmd = '.\\adb.exe wait-for-device shell rm -rf /data/DKBx_x_kernel.txt'
print cmd
p = subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(output, err) = p.communicate()
p_status = p.wait()
#print output
#print p_status

cmd = '.\\adb.exe wait-for-device shell rm -rf /data/screenshot.png'
print cmd
p = subprocess.Popen(cmd,stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(output, err) = p.communicate()
p_status = p.wait()

############################# Capture Logs #########################################

startup_info = subprocess.STARTUPINFO()
startup_info.dwFlags |= subprocess.STARTF_USESHOWWINDOW 

#capture radio log on UE
cmd = '.\\adb.exe wait-for-device shell logcat -b radio -v threadtime -f /data/DKBx_x_radio.txt'
print cmd
p_radio = subprocess.Popen(cmd, startupinfo=startup_info)

#capture kernel log on UE
cmd = '.\\adb.exe wait-for-device shell logcat -k -f /data/DKBx_x_kernel.txt'
print cmd
p_kernel = subprocess.Popen(cmd, startupinfo=startup_info)

#capture main log on PC
main_file_name = os.path.join(temp_dir, filename_prefix + '_main.txt')
f_main = open(main_file_name,"w")
cmd = '.\\adb.exe wait-for-device shell logcat -b main -b events -v threadtime'
print cmd
p_main = subprocess.Popen(cmd, startupinfo=startup_info, stdout=f_main)

#Wait for the "Stop" button to be pressed by user
print 'Press stop button to end capturing!!!'
cats.WaitForStop()

############################# Stop Logs #########################################
#the "Stop" button is pressed, close the 3 running process on UE
subprocess.Popen("taskkill /F /PID {pid} /T".format(pid=p_radio.pid))
subprocess.Popen("taskkill /F /PID {pid} /T".format(pid=p_kernel.pid))
subprocess.Popen("taskkill /F /PID {pid} /T".format(pid=p_main.pid))

#close the file which is used to write main log into
f_main.close()

#pull radio log 
radio_file_name = os.path.join(temp_dir, filename_prefix + '_radio.txt')
cmd = '.\\adb.exe wait-for-device pull /data/DKBx_x_radio.txt ' + radio_file_name
print cmd
subprocess.Popen(cmd)

#pull kernel log
kernel_file_name = os.path.join(temp_dir, filename_prefix + '_kernel.txt')
cmd = '.\\adb.exe wait-for-device pull /data/DKBx_x_kernel.txt ' + kernel_file_name
print cmd
subprocess.Popen(cmd)


#get the current screenshot of the phone
cmd = '.\\adb.exe wait-for-device shell screencap -p /data/screenshot.png'
print cmd
p = subprocess.Popen(cmd, stdout=subprocess.PIPE,stderr=subprocess.PIPE)
(output, err) = p.communicate()
p_status = p.wait()
screenshot_file_name = os.path.join(temp_dir, filename_prefix + '.png')
cmd = '.\\adb.exe wait-for-device pull /data/screenshot.png ' + screenshot_file_name
print cmd
subprocess.Popen(cmd)

#zip file
default_file_name = filename_prefix + '_IMS_radio_no_tcpdump.zip'
cats.SetDefaultZipName(default_file_name)
input_file_name = cats.GetSavedZipName()
bDefault = not input_file_name

#change working directory to prepare for zipping
os.chdir(temp_dir)
print 'Change working directory!'
print 'Current working directory : ', os.getcwd()

#start to zip
zip_file_name = default_file_name if bDefault else input_file_name
zipFile = zipfile.ZipFile(zip_file_name, 'w', zipfile.ZIP_DEFLATED)
zipFile.write(os.path.basename(radio_file_name))
zipFile.write(os.path.basename(kernel_file_name))
zipFile.write(os.path.basename(main_file_name))
zipFile.write(os.path.basename(screenshot_file_name))
zipFile.close()
print 'Zipped file is ' + zip_file_name

#restore the working directory
os.chdir('..')
print 'Change working directory!'
print 'Current working directory : ', os.getcwd()