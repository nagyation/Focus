# Focus
A very simple program reminds you -by a notification- of what you are currently doing periodically to keep focus <br> <br>

## Build and Use:
**Make sure you already have libnotify** <br>
-> git clone https://github.com/nagyation/Focus <br>
-> cd Focus<br>
-> gcc -o focus \`pkg-config --cflags --libs libnotify\` focus.c <br>
-> ./focus {duration} {title} {text to be notified with}<br>
-> ex: ./focus 1 "Hello world" "Hey" &<br>
