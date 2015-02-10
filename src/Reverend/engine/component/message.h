#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

class GameObject;

enum MessageType {
	CollisionEnter,
	TriggerEnter
};

class Message {
public:
	Message(int destId, MessageType type, GameObject* caller) : destinationObjectId_(destId), messageType_(type), caller_(caller) {}
	int getDestinationObjectId() { return destinationObjectId_; }
	MessageType getMessageType() { return messageType_; }
	GameObject* getCaller() { return caller_; }
private: 
    int destinationObjectId_;
    MessageType messageType_;
	GameObject* caller_;
};

#endif