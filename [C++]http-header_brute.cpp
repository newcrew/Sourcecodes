// Screenshot: http://s1.directupload.net/images/131220/a2sh3abz.png

/*                       #                 
                        ###                   
                       ## ##                  
                      ### ###                 
                     ###   ###                
               ######################         
              ########################        
               ###  ###    ####  ####         
                ## ###      ### ####          
                 #####      #######           
         ###     ######     ######   ###      
        ######  ########   #######  #######   
       ######   ######### #########  #######  
      #####    ####  ######### #####    ####  
      #####   #####   #######   #####   ####  
       ###########     #####     ###########  
        #########       ##        #########   
         #####                      #####
       http-header brute - script by unnex
               visit: www.unnex.de
*/

//link with ws2_32.lib

#include <winsock2.h>
#include <windows.h>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) { cout<<"\n"; string help="################################################\n###http-header brute - script by www.unnex.de###\n################################################\n\nusage: *.exe [addr] [port] [header.txt] [search string] [dic.txt] [dic line] [search string found 0, 1] [output.txt] [hex (optional)]\n\n[addr]=address destination\n~127.0.0.1\n[port]=port destination\n-80\n[header.txt]=http-header file within [brute] as replacement for dictionary\n~header.txt\nGET /[brute]/index.html HTTP/1.1\nHost: 127.0.0.1\nConnection: close\n[search string]=string to found or not found in response.\n~\"welcome\"\n[dic.txt]=dictionary file\n~dic.txt\n[dic line]=start dictionary list from line number x\n~1\n[search string found 0, 1]=note \"found\" by found or not found search string (0=found, 1=not found)\n~1\n[output.txt]=output file to note all founds\n~output.txt\n[hex (optional)]=encode dictionary lines to hex (optional type \"hex\" or type nothing)\n~hex\n\n---test examples---\nexample 1: http-header_brute.exe blacknet.me 80 header.txt \"HTTP/1.1 404 Not Found\" folders.txt 1 1 output.txt hex\n^---folders.txt\ntest\nunnex\n123\n^---header.txt\nGET /[brute]/index.php HTTP/1.1\nHost: blacknet.me\nConnection: close\n\nexample 2: http-header_brute.exe 81.169.145.161 80 header.txt \"HTTP/1.1 200 OK\" hosts.txt 1 0 output.txt\n^---hosts.txt\ngoogle.de\nblacknet.me\nsoso.com\n^---header.txt\nGET / HTTP/1.1\nHost: [brute]\nConnection: close\n";
if (!argv[1] or !argv[2] or !argv[3] or !argv[4] or !argv[5] or !argv[6] or !argv[7] or !argv[8]) { cout<<help; exit(0); } const char * addr=argv[1]; int port; port=atoi(argv[2]); int ii; ii=atoi(argv[6]); if (ii<1) { ii=1; }
const char * yes=argv[7]; string no=yes; string ania=""; if (argv[9]) { const char * ani=argv[9]; ania=ani; }

string source=""; string sourcea; ifstream fin(argv[3]); if (fin.is_open()) { while (!fin.eof()) { getline(fin, sourcea);source+=sourcea+"\r\n"; } fin.close(); } else { cout<<"Could not open "<<argv[3]<<"\n"; exit(0); } source+="\r\n"; string oldsource=source;
string hexy="off"; if (argv[9]) { if (ania=="hex") { hexy="on"; } } cout<<"Address: "<<argv[1]<<"\nPort: "<<argv[2]<<"\nHeader Filename: "<<argv[3]<<"\nSearch String: "<<argv[4]<<"\nDictionary Filename: "<<argv[5]<<"\nStart Dictionary from:"<<argv[6]<<"\nNote by Search String (0=found, 1=not found): "<<argv[7]<<"\nOutput Filename: "<<argv[8]<<"\nEncode String to Hex: "<<hexy<<"\n\n";
ofstream finb; string path=""; ifstream fina(argv[5]); int iii=1; int iiii=0; if (fina.is_open()) { while (!fina.eof()) { if (iii<ii and iiii==0) { while (iii<ii && !fina.eof()) { getline(fina, sourcea); iii++; } ii=iii; }

path=""; string hexstring; int yi; while (path.length()<1 && !fina.eof()) { getline(fina, sourcea); path=sourcea; } if  (path.length()<1) { cout<<"\nfin!\n"; return 0; } source=oldsource;
hexstring=""; yi=0; if (ania=="hex") { int ipath; while (path[yi]) { ipath=(int)path[yi]; std::ostringstream oss; oss<<std::hex<<ipath; hexstring+="%"+oss.str(); yi++; } }
if (hexstring.length()<1) { hexstring=path; } while (source.find("[brute]")!=string::npos) { source.replace(source.find("[brute]"), 7, hexstring); } const char * header=source.c_str();

string out; WSADATA wsaData; if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) { cout<<"WSAStartup failed.\n"; return 1; }
SOCKET Socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP); struct hostent *host; host = gethostbyname(addr); if (host==0) { cout<<"Could not open "<<addr<<"\n"; return 1; }
SOCKADDR_IN SockAddr; SockAddr.sin_port=htons(port); SockAddr.sin_family=AF_INET; SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

char buffer[10000]; int nDataLength; string fullbuffer=""; string qla=""; while (connect(Socket,(SOCKADDR*)(&SockAddr),sizeof(SockAddr))!=0) { }
send(Socket, header, strlen(header), 0); while ((nDataLength = recv(Socket,buffer,10000,0)) > 0){ qla=buffer; fullbuffer+=""+qla; }
closesocket(Socket); WSACleanup(); out="a"; if (fullbuffer.length()>0) { if (no=="0" and fullbuffer.length()>0) { if (fullbuffer.find(argv[4])>fullbuffer.length()) { if (path==hexstring) { cout<<"Found: "<<path<<"\n"; } else { cout<<"Found: "<<path<<" ("<<hexstring<<")"<<"\n"; } finb.open(argv[8], ios::app); if (!finb.is_open()) { cout<<"Could not open "<<argv[8]<<"\n"; return 1; } finb<<path<<"\n"; finb.close(); out="b"; } }
if (no=="1") { if (fullbuffer.find(argv[4])<=fullbuffer.length()) { if (path==hexstring) { cout<<"Found: "<<path<<"\n"; } else { cout<<"Found: "<<path<<" ("<<hexstring<<")"<<"\n"; } finb.open(argv[8], ios::app); if (!finb.is_open()) { cout<<"Could not open "<<argv[8]<<"\n"; return 1; } finb<<path<<"\n"; finb.close(); out="b"; } }
if (out=="a") { if (path==hexstring) { cout<<ii<<": "<<path<<"\n"; } else { cout<<ii<<": "<<path<<" ("<<hexstring<<")"<<"\n"; } } ii++; } iiii=1; } } else { cout<<"Could not open "<<argv[5]<<"\n"; return 1; } fina.close(); cout<<"\nFin!\n"; return 0; }
