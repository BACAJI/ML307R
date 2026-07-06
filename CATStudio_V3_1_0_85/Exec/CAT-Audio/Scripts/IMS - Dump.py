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
print 'Current working directory: ', os.getcwd()

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

#pull dump file
EE_Hbuf_file_name = os.path.join(temp_dir, 'com_EE_Hbuf.bin')
cmd = '.\\adb.exe wait-for-device pull /NVM/com_EE_Hbuf.bin ' + EE_Hbuf_file_name
print cmd
subprocess.Popen(cmd)

DTCM_file_name = os.path.join(temp_dir, 'com_DTCM.bin')
cmd = '.\\adb.exe wait-for-device pull /NVM/com_DTCM.bin ' + DTCM_file_name
print cmd
subprocess.Popen(cmd)

DDR_RW_file_name = os.path.join(temp_dir, 'com_DDR_RW.bin')
cmd = '.\\adb.exe wait-for-device pull /NVM/com_DDR_RW.bin ' + DDR_RW_file_name
print cmd
subprocess.Popen(cmd)

#zip file
default_file_name = filename_prefix + '_IMS_dump.zip'
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
zipFile.write(os.path.basename(EE_Hbuf_file_name))
zipFile.write(os.path.basename(DTCM_file_name))
zipFile.write(os.path.basename(DDR_RW_file_name))
zipFile.close()
print 'Zipped file is ' + zip_file_name

#restore the working directory
os.chdir('..')
print 'Change working directory!'
print 'Current working directory : ', os.getcwd()