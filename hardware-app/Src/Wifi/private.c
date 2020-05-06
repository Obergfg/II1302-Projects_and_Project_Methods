//Make a copy of this file and remove the "_" in the name, so you get a file called "private.c"
//This file will not get pushed to github because it is included in the .gitignore file in the repository's main directory.

#define ATCWJAP "AT+CWJAP=\"TN24GHz_1E73C3\",\"AWD3HUC376\"\r\n";
#define CIPSTART "AT+CIPSTART=\"SSL\",\"farmtesting-cbe6a.firebaseio.com\",443\r\n";
#define POSTLIGHT "POST /Plants/a7bv5shj3/LightLevel.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%d\r\n\r\n\r\n"
#define POSTMOISTURE "POST /Plants/a7bv5shj3/MoistureLevel.json HTTP/1.1\r\nHost: farmtesting-cbe6a.firebaseio.com\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%d\r\n\r\n\r\n";
