#!/bin/bash

if [ $# -ne 2 ]; then
  echo "usage: ./update_calib.sh calib_file camera_ip"
  exit
fi

echo 'Device  IP   =' $2
echo 'Install calib =' $1

echo -e '\n Clear Signature..'
ssh-keygen -f ~/.ssh/known_hosts -R $2
# trigger an output warning
sshpass -p 736767 ssh -o StrictHostKeyChecking=no xyz@$2 echo -e '\\n Login successful.\\n'

echo -e '\n Transport calib..'
sshpass -p 736767 scp -o StrictHostKeyChecking=no $1 xyz@$2:~

sshpass -p 736767 ssh -o StrictHostKeyChecking=no xyz@$2 sudo cp $(basename $1) /usr/local/share/config
echo -e '\n Update calibration done.'
