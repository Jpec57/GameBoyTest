#Compilation

lcc -o main.gb ./src/main.c

#What I have learned

## Commands

```whereis grep```
Display the location of the command location

##Gameboy specific

###Limitation

The Gameboy's memory cannot keep more than 255 different tiles for background and 128 sprite tiles

###Screen size

The size of the screen is 160 x 144 pixels

```            set_bkg_tiles(0, 0, 20, 18, blankScreen);```

Full white screen because 8 * 20 = 160 and 8 * 18 = 144

###Sprite size 

Two different formats are available:

- 8 * 8
- 8 * 16

But no more than 10 sprites on the same line and no more than 40 on screen. 

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

#Sources

https://blog.flozz.fr/2019/02/05/developpement-gameboy-7-les-sprites/