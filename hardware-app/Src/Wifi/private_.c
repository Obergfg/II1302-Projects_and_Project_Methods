//Make a copy of this file and remove the "_" in the name, so you get a file called "private.c"
//This file will not get pushed to github because it is included in the .gitignore file in the repository's main directory.

#define ATCWJAP "AT+CWJAP=\"SSID\",\"PASSWORD\"\r\n"
#define CIPSTART "AT+CIPSTART=\"SSL\",\"DATABASEHOST\",443\r\n";
#define POSTLIGHT "POST /Plants/HARDWAREID/LightLevel.json HTTP/1.1\r\nHost: DATABASEHOST\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%d\r\n\r\n\r\n"
#define POSTMOISTURE "POST /Plants/HARDWAREID/MoistureLevel.json HTTP/1.1\r\nHost: DATABASEHOST\r\nContent-Type: text/plain\r\nContent-Length: %d\r\n\r\n%d\r\n\r\n\r\n";
