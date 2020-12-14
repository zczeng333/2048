Documentation
=============
**General Description:**

This project is a 2048 mini game programmed with C

Project mainly includes two parts:
1. core logic (front-end & back-end) of 2048 game
2. user interface

Dependencies
-------------
**Language:**  C

Project Architecture
-------------
```buildoutcfg
│  2048 3.0i.c      // graphic front-end & back-end system
│  2048 3.0i.o
│  drawfield.c      // code for game interface
│  graphics.dev
│  graphics.exe     // start game
│  graphics.layout
│  huaji.o
│  Makefile.win
│  menu.c           // menu for game
│  menu.o
│  README.md        // help
│
├─include           // dependencies
│      exception.h
│      extgraph.h
│      gcalloc.h
│      genlib.h
│      graphics.h
│      random.h
│      simpio.h
│      strlib.h
│
└─libgraphics       // garphics dependencies
        exceptio.c
        exceptio.o
        genlib.c
        genlib.o
        graphics.c
        graphics.o
        random.c
        random.o
        simpio.c
        simpio.o
        strlib.c
        strlib.o
```

Usage
-------------
click graphics.exe to start
