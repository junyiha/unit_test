@echo off

:: check params num
set argC=0
for %%x in (%*) do Set /A argC+=1

if %argC% == 2 (
  echo Device  IP  = %2
  echo Install calib = %1
) else (
  echo usage: %~nx0 calib_file device_ip
  pause
  exit
)

:: get basename of *.deb
set basename=%~nx1
set device_ip=%2

:: remove ssh-key of host
echo;
echo  Clear Signature..
ssh-keygen -f %USERPROFILE%\.ssh\known_hosts -R %device_ip%
echo y | plink -ssh -noagent -l xyz -pw 736767 %device_ip% echo -e '\n Login successful.\n'

:: transmit file by scp
echo;
echo  Transport calib..
pscp -noagent -l xyz -pw 736767 %1 %device_ip%:/home/xyz/

echo y | plink -ssh -noagent -l xyz -pw 736767 %device_ip% sudo cp %basename% /usr/local/share/config

echo;
echo  Update calibration done.
