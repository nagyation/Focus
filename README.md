# Focus
A very simple program that runs as a daemon reminds you -by a notification- of what you are currently doing periodically to keep focus <br> <br>

## Build:
**Make sure you already have gtk+2 and libnotify** <br>
you can install it by: <br>
**Ubuntu:** <br>
`sudo apt-get install libnotify-dev`

`sudo apt-get install gtk2.0`


**Arch:** <br>
`sudo pacman -S gtk2`

 `sudo pacman -S libnotify` 
 <br><br>

**Focus build** <br>
`$ git clone https://github.com/nagyation/Focus`

`$ cd Focus `

`$ make `

`$ sudo make install `

## Use:
-p {period in mins} : time between each notification <br>
-d {duration in hours} : the total run duration of the program afterwhich it will exit <br>
-t {title} : the title of the notification to recieve <br>
-b {body} : the text body of the notification <br>
-h {help} : show arguments <br>

focus -h    For help <br>
focus -p {period} -d {duration of the run} -t {title} -b {text to be notified with}<br>

### Example:
`focus -p 10 -d 2 -t "Hello world" -b "Hey"`<br>
