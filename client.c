#include<stdio.h> //printf
#include<string.h>//strlen
#include<sys/socket.h>//socket
#include<arpa/inet.h>//inet_adress
#include<stdlib.h>
#include<unistd.h>


int main(int argc , char *argv[])
{
 int sock;  
 struct sockaddr_in server;  
 char message[2000],server_reply[1000];

//creation socket 
 sock=socket(AF_INET,SOCK_STREAM,0); 
 if(sock==-1)
 {
  printf("socket non créer ");  
 }
puts("socket créer avec succes"); 
server.sin_addr.s_addr=inet_addr("127.0.0.1");  //inet serveur 
server.sin_family=AF_INET;  
server.sin_port=htons(atoi(argv[1]));  

//connection au serveur

if(connect(sock,(struct sockaddr*)&server,sizeof(server))<0)
{
 perror("connexion echouer"); 
return 1; 
}
puts("connexion avec succes"); 

//communication avec le serveur 

while(1)
{
 printf("entrer votre message") ; 
 scanf("%s",message);  

//envoie des donnée  
 if(send(sock,message,strlen(message),0)<0)
 {
 puts("envoie echouer ");  
 return 1 ; 

 }

//reception et répitition de serveur
 if(recv(sock,server_reply,2000,0)<0)
 {
 puts("reception a échouer !! ");  
 break ;   
 }
puts("perroquet re-parler  :\n ");  
puts(server_reply); 

}
close(sock);  
return 0 ;  
}
