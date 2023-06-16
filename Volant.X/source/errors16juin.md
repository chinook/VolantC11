# Compilation errors left (to fix)

1. Incompatible implicit declaration of built-in function powf and logf <br />
`source/Display.c: In function 'PrintFloat':`<br />
`source/Display.c:125:20: warning: incompatible implicit declaration of built-in function 'powf' [enabled by default]`<br />
`source/Display.c:125:33: warning: incompatible implicit declaration of built-in function 'logf' [enabled by default]`<br />
`source/Display.c: In function 'PrintFloatFixed':`<br />
`source/Display.c:166:20: warning: incompatible implicit declaration of built-in function 'powf' [enabled by default]`<br />
`source/Display.c: In function 'PrintInt':`<br />
`source/Display.c:201:18: warning: incompatible implicit declaration of built-in function 'pow' [enabled by default]`

2. Initializer element is not constant (idk what this is)
`source/main.c:80:2: error: initializer element is not constant`<br />
`SW1, SW2, SW3, SW4, SW5, SW6, SW7, SW8, SW9, SW10, SW11, SW12`<br />
`source/main.c:80:2: error: (near initialization for 'swi_to_sw[0]')`<br />
`source/main.c:80:2: error: initializer element is not constant`<br />
`source/main.c:80:2: error: (near initialization for 'swi_to_sw[1]')`<br />
etc.

BUILD FAILED (exit value 2, total time: 1s)
