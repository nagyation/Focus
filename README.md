# Focus
A very simple program that runs as a daemon reminds you -by a notification- of what you are currently doing periodically to keep focus <br> <br>

## Build and Use:
**Make sure you already have libnotify** <br>
-> git clone https://github.com/nagyation/Focus <br>
-> cd Focus<br>
-> make <br>
->./focus -h for help <br>
-> ./focus -p {period} -d {duration of the run} -t {title} -b {text to be notified with}<br>
-> ex: ./focus -p 1 -t "Hello world" -b "Hey" &<br>
