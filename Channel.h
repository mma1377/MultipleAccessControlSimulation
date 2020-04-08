#pragma once
#include "SenderNode.h";

class Channel {
private:
	SenderNode* _nodes;
	int _numOfNodes;
	int* _tdmaChannel;
	int* _cdmaChannel;
	int _channelCapacity;
	int _walshCodeSize;
	int _virtualTime;

public:
	Channel(SenderNode* nodes, int numOfNodes, int channelCap);
	void generate_and_assign_walsh_code_to_nodes();
	void tdma();
	void dtdma();
	void cdma();
	void cdma_decode_and_print(int nodeIndx);

};
