#ifndef RTC_SERVER_SERVER_H
#define RTC_SERVER_SERVER_H

#include "base/log.h"
#include "fde.h"
#include "room.h"
#include "token.h"
#include "client.h"

class UdpLink;
class Packet;
class Address;

/*
Room types:
	Audio Conferencing
	Non-reliable Broacasting
		One-on-One Audio Chat
		Audio Broacasting
	Reliable Broacasting
		One-on-One Text Chat
		Group Text Chat
*/

class Server
{
public:
	RoomSvc rooms;
	ClientSvc clients;
	TokenSvc tokens;

	Server();
	~Server();
	
	void tick(){
		RoomSvc::iterator it;
		for(it=rooms.begin(); it!=rooms.end(); it++){
			Room *room = it->second;
			room->tick();
		}
	}
	
	UdpLink* proc_listen_link(UdpLink *listen_link, Fdevents *fdes);
	int proc_client_link(UdpLink *link, Fdevents *fdes);
	int proc_admin_listen_link(UdpLink *serv_link, Fdevents *fdes);
	int proc_admin_link(UdpLink *link, Fdevents *fdes);

private:
	int proc_open(UdpLink *admin_link, Packet *req, Address *addr);
	int proc_sign(UdpLink *admin_link, Packet *req, Address *addr);
	int proc_close(UdpLink *link, Packet *req, Address *addr);
	Client* proc_join(UdpLink *serv_link, Packet *req, Address *addr);
	int proc_quit(UdpLink *link, Packet *req, Address *addr);
	int proc_pub(Client *client, Packet *req);
};

#endif
