#Compilation

lcc -o main.gb ./src/main.c

#What I have learned

## Commands

```whereis grep```
Display the location of the command location

##Gameboy specific

###Waitpad
```waitpad(<TOUCH>)```

where TOUCH is one of the following commands:

- J_UP
- J_DOWN
- J_LEFT
- J_RIGHT
- J_A
- J_B
- J_START
- J_SELECT

lets us wait for a user input of a specific command

###JOYPAD

Same as waitpad but non-blocking

```        if (!(keys & J_B) && (prev_keys & J_B)){}```

can therefore help us to know when the user release a command
