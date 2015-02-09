#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

class SDLGameObject;

enum MessageType {
	CollisionEnter,
	TriggerEnter
};

class Message {
public:
	Message(int destId, MessageType type, SDLGameObject* caller) : destinationObjectId_(destId), messageType_(type), caller_(caller) {}
	int getDestinationObjectId() { return destinationObjectId_; }
	MessageType getMessageType() { return messageType_; }
	SDLGameObject* getCaller() { return caller_; }
private: 
    int destinationObjectId_;
    MessageType messageType_;
	SDLGameObject* caller_;
};

#endif