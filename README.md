## KEYLOGGER
---
### About

This keylogger uses Reverse Shell and Sockets to enable a connection with the kali machine. 
Reverse Shell is used in order to retrieve the log.txt which stores the keystroke rather than sending it via the email which reduces the privacy.
This is carried out using socket programming and connecting using netcat.

### Requirement
- C++17 or greater
- Linux System or Subsystem

### How to use

First Open your desired linux system(here kali) with netcat and run the command
```
nc -lnvp 8001
```

To compile the program:
```
g++ -o <executable name> main.cpp -lws2_32
```

After running, in the linux system enter any key to enter the reverse shell. The reverse shell is soley used to extract the log file.
