#pragma once
#include <iostream>

#define timeSlot 500;
#define channelSize 30;

class SenderNode {
private:
	bool* _data;
	int _dataSize;
	int _dataRate;
	bool* _walshCode;
	int _walshCodeSize;

public:
	SenderNode();
	SenderNode(const char* data, int dataSize, int dataRate);
	SenderNode(int dataSize, int dataRate);
	~SenderNode();
	SenderNode(SenderNode& other);
	SenderNode(SenderNode&& other);
	SenderNode& operator=(SenderNode& other);
	SenderNode& operator=(SenderNode&& other);

	bool tdma_send(int* channel, int& virtualTime);
	int* cdma_encode(int len);
	void set_walsh_code(bool* code, int size);
	bool* get_walsh_code();
	int get_date_size();
};
