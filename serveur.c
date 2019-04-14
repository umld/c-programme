#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#include<arpa/inet.h>

void *connection_handler(void*);  

int main(int argc ,char*argv[])
{ 

 int socket_desc,client_sock,c,read_size;  
 struct sockaddr_in server,client;  
 int *new_sock;  

//creation socket  
socket_desc=socket(AF_INET,SOCK_STREAM,0); 
if(socket_desc==-1)  
{

   printf("création de socket a échouer");  
}
puts("socket créer avec succes");  
  
//preparer socket adresse en structure  
server.sin_family=AF_INET; 
server.sin_addr.s_addr=INADDR_ANY; 
server.sin_port=htons(atoi(argv[1])); 

//bind
if(bind(socket_desc,(struct sockaddr*)&server,sizeof(server))<0)
{
 
 //message d'erreur
 perror("bind a echouer" ) ;  
 return 1 ; 

}
puts("bind avec succes ");  

//ecouter  
listen(socket_desc,3);  

//acceptation et client arrivé 
puts("attend pour une nouvelle connexion .....");  
c=sizeof(struct sockaddr_in);  

//acceptation connexion d'un client 
while(client_sock=accept(socket_desc,(struct sockaddr *)&client,(socklen_t*)&c))
{
puts("connexion accepter") ; 
pthread_t sniff; 
new_sock=malloc(1);  
*new_sock=client_sock; 
if(pthread_create(&sniff,NULL,connection_handler,(void *)new_sock)<0) 
{

 perror("création du thread a echouer ");  
 return  1; 

}
puts("handler assigned"); 
}

	if(client_sock<0)
	{
	 perror("acceptation a echouer ");  
	 return 1 ;  
	}
return 0 ;  

}

void *connection_handler(void*socket_desc)
{
 
 int sock=*(int*)socket_desc;  
 int read_size; 
 char client_message[2000];  
//recevoire les messages du client   
while((read_size=recv(sock,client_message,2000,0))>0)
{
  
  
  //envoie du message au client
 
   write(sock,client_message,strlen(client_message));  
}
  
if(read_size ==0)
{
puts("client déconnecter ")  ;
fflush(stdout);  
}
else if(read_size==-1)
{
perror("recevoie du message a échouer") ; 
}
}







