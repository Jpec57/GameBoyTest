#!/bin/bash
PATH="/Users/jpec/Library/Application Support/OpenEmu/Game Library/roms/Game Boy/"
FILE="main.gb"
EMULATOR=OpenEmu
/bin/rm -rf "$PATH/$FILE" 
/bin/cp $FILE "$PATH/$FILE"
PID="/usr/bin/pgrep $EMULATOR"
#if [ ! -z "$PID" -a "$PID" != " " ]; then
#    /bin/kill $(/usr/bin/pgrep $EMULATOR)
#fi
#/bin/sleep 1
#/usr/bin/open $FILE