#! /bin/sh

comf=`ls /dev/tty.wchusbserial*`
cosf=`ls *.elf`

#stm32prog -c port=$comf br=115200 P=EVEN db=8 sb=1 -e all -d $cosf -s
stm32prog -c port=$comf br=115200 P=EVEN db=8 sb=1 -d $cosf -s

stm32prog -c port=$comf br=115200 P=NONE db=8 sb=1 console

