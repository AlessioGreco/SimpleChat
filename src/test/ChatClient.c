/****************************************************************************
* Copyright © 2017 Alessio Greco
* github: https://github.com/RootPOI
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

/*Progetto CHAT, Gestione Client -- Greco Alessio -- UniCT -- */
/*----------------------*/
/*-------Header---------*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include "HeaderCHAT.h"
/*---------Define--------*/
#define MAXCLIENT 10
#define SERVER_ON 1
/*------Variabili-----*/
conn connection;
servertoclient stoc;
/*-------Main---------*/
int main (void){
	printf("Avvio Client(fisso)...\n");
	printf("Avvio Socket Client in corso...\n");
	int socket_client;
	if ((socket_client = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		printf("Errore Creazione Socket\n");
		exit(EXIT_FAILURE);
	}
	struct sockaddr_in addresserver;
	addresserver.sin_family = AF_INET;
	addresserver.sin_port = htons(PORTLOGIN);
	addresserver.sin_addr.s_addr = inet_addr(IPSERVER);
	printf("Connessione in Corso...\n");
	if (connect (socket_client, (struct sockaddr*)&addresserver, sizeof(addresserver)) == -1){
		printf("Errore Connessione\n");
		exit(EXIT_FAILURE);
	}
	printf("Connesso\n");
	printf("Generazione della Struct di Connessione\n");
	srand(time(NULL));
	connection.CLID = (rand()%2500)+(rand()%2500);
	connection.CLGRP = USER;
	connection.STAT = ONLINE;
	printf("Invio Struct\n");
	if(write (socket_client, &connection, sizeof(conn)) == -1){
		printf("Errore Invio Struct Messaggio\n");
		exit(EXIT_FAILURE);
	}
	printf("Connessione in corso...\n");
	if (read(socket_client, &stoc, sizeof(servertoclient)) == -1){
		printf("Errore Ricezione Risposta Collegamento\n");
		exit(EXIT_FAILURE);
	}
	switch (stoc.CMD){
		case BUSY: {
			printf("Massima quantita' di client raggiunta\n");
			exit(EXIT_FAILURE);
	}
		case CONNECTED: {
			printf("Connesso\n");
			exit(EXIT_FAILURE);
		}
	}
	
	
	
	
	
}


