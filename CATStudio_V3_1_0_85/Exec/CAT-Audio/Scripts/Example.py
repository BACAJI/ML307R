import sys
import time
regacc = RegAccessor.Init()
sys.stdout = regacc
sys.stderr = regacc
BusId = 0x2
SlaveAddr = 0x38
Addr = 0x1
Mask = 0x1
"""
Following code is Used to power up codec
"""
value = regacc.GetReg(BusId ,SlaveAddr ,Addr,Mask) #STBY_B
res = regacc.SetReg(BusId ,SlaveAddr ,Addr,0x1,0x1) #STBY_B
