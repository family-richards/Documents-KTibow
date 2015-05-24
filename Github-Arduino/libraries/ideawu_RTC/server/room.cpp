#include "base/log.h"
#include "room.h"

int Room::join(Client *client){
	clients_[client->id] = client;
	return 0;
}

int Room::quit(Client *client){
	mixer.free_channel(client->id);
	clients_.erase(client->id);
	return 0;
}

int Room::publish(Client *client, Packet *req){
	const std::vector<Bytes> *params = req->params();
	if(params->size() < 2){
		log_error("missing arguments");
		return -1;
	}
	int room_id = params->at(0).Int();
	if(room_id != this->id){
		log_error("invalid room_id: %d, should be: %d", room_id, this->id);
		return -1;
	}
	const Bytes &data = params->at(1);

	voice::Frame frame;
	frame.seq = req->seq();
	frame.buf.assign(data.data(), data.size());
	mixer.process_frame(client->id, frame);

	return 0;
}
	
void Room::tick(){
	// TODO: 如果所有的通道的缓冲区都溢出(超过BUF_SIZE), 则说明时钟周期误差扩大了,
	// 那么应该再进行第二次混音, 而不必等待下一次的时钟周期.
	voice::Frame *mixed_frame = mixer.mix();
	if(mixed_frame == NULL){
		return;
	}
	if(mixed_frame->buf.size() == 0){
		return;
	}
	//this->broadcast(frame->buf.data(), frame->buf.size());
	Packet resp;
	resp.set_type(Packet::DATA);
	resp.set_seq(data_seq_next);
	// TODO: room_id, data
	resp.set_data(mixed_frame->buf.data(), mixed_frame->buf.size());
	
	std::map<int, Client*>::const_iterator it;
	for(it = clients_.begin(); it!=clients_.end(); it++){
		const Client *client = (*it).second;
		voice::Channel *channel = mixer.get_channel(client->id);
		if(!channel || channel->last_frame()->empty()){
			int ret = client->link->send(resp);
			if(ret <= 0){
				log_error("error: %s", strerror(errno));
			}
			log_trace("client: %d, send %d byte(s) to: %s",
				client->id, ret, client->addr.repr().c_str());
		}else{
			voice::Frame *frame = channel->last_frame();
			frame->unmix_from(*mixed_frame);
			
			Packet p;
			p.set_type(Packet::DATA);
			p.set_seq(data_seq_next);
			// TODO: room_id, data
			p.set_data(frame->buf.data(), frame->buf.size());
			
			int ret = client->link->send(p);
			if(ret <= 0){
				log_error("error: %s", strerror(errno));
			}
			log_trace("client: %d, send %d byte(s) to: %s",
				client->id, ret, client->addr.repr().c_str());
		}
	}

	data_seq_next ++;
}
