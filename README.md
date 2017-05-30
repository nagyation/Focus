# Focus
A very simple program that runs as a daemon reminds you -by a notification- of what you are currently doing periodically to keep focus <br> <br>

## Build:
**Make sure you already have libnotify** <br>
-> git clone https://github.com/nagyation/Focus <br>
-> cd Focus<br>
-> make <br>

## Use:
-p {period in mins} : time between each notification <br>
-d {duration in hours} : the total run duration of the program afterwhich it will exit <br>
-t {title} : the title of the notification to recieve <br>
-b {body} : the text body of the notification <br>
-h {help} : show arguments <br>

./focus -h for help <br>
./focus -p {period} -d {duration of the run} -t {title} -b {text to be notified with}<br>

### Example:
./focus -p 10 -d 2 -t "Hello world" -b "Hey"<br>
