# Focus
A very simple program that notifies you of a certain sentence every amount of time, it helps me to keep focus <br> <br>

## Build and Use:
**Make sure you already have libnotify** <br>
-> git clone https://github.com/nagyation/Focus <br>
-> cd Focus<br>
-> gcc -o focus 'pkg-config --cflags --libs libnotify' focus.c
-> ./focus {duration} {text to be notified with}<br>
-> ex: ./focus 1 "Hello world" &<br>
