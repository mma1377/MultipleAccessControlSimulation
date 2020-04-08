#include <iostream>
#include <ctime>
#include "Channel.h"

void a_cdma() {
	srand((unsigned)time(0));

	SenderNode* nodes = new SenderNode[4];
	nodes[0] = SenderNode("10001011110000110111110110000111110001100011101010000111111011011101011010111010101010101011111111011101111010", 110, 5);
	nodes[1] = SenderNode("1110110111011010111111000011111111001101011111101110111111011101111011110111", 75, 3);
	nodes[2] = SenderNode("1000101111000011011111011000011111000110001110101000011111101101110101101011000011001110101000", 94, 2);
	nodes[3] = SenderNode("000100100001111110111010100001001011110101000011000110100100", 60, 4);

	Channel channel(nodes, 4, 30);
	channel.generate_and_assign_walsh_code_to_nodes();
	channel.cdma();
}

void a_tdma() {
	srand((unsigned)time(0));

	SenderNode* nodes = new SenderNode[4];
	nodes[0] = SenderNode("10001011110000110111110110000111110001100011101010000111111011011101011010111010101010101011111111011101111010", 110, 5);
	nodes[1] = SenderNode("1110110111011010111111000011111111001101011111101110111111011101111011110111", 75, 3);
	nodes[2] = SenderNode("1000101111000011011111011000011111000110001110101000011111101101110101101011000011001110101000", 94, 2);
	nodes[3] = SenderNode("000100100001111110111010100001001011110101000011000110100100", 60, 4);

	Channel channel(nodes, 4, 30);
	channel.tdma();
}

void a_dtdma() {
	srand((unsigned)time(0));

	SenderNode* nodes = new SenderNode[4];
	nodes[0] = SenderNode("10001011110000110111110110000111110001100011101010000111111011011101011010111010101010101011111111011101111010", 110, 5);
	nodes[1] = SenderNode("1110110111011010111111000011111111001101011111101110111111011101111011110111", 75, 3);
	nodes[2] = SenderNode("1000101111000011011111011000011111000110001110101000011111101101110101101011000011001110101000", 94, 2);
	nodes[3] = SenderNode("000100100001111110111010100001001011110101000011000110100100", 60, 4);

	Channel channel(nodes, 4, 30);
	channel.dtdma();
}

void b_cdma() {
	srand((unsigned)time(0));

	SenderNode* nodes = new SenderNode[400];
	for (int i = 0; i < 100; i++) {
		nodes[i] = SenderNode(110, 5);
	}
	for (int i = 100; i < 200; i++) {
		nodes[i] = SenderNode(75, 3);
	}
	for (int i = 200; i < 300; i++) {
		nodes[i] = SenderNode(94, 2);
	}
	for (int i = 300; i < 400; i++) {
		nodes[i] = SenderNode(60, 4);
	}

	Channel channel(nodes, 400, 30);
	channel.generate_and_assign_walsh_code_to_nodes();
	channel.cdma();
}

void b_tdma() {
	srand((unsigned)time(0));

	SenderNode* nodes = new SenderNode[400];
	for (int i = 0; i < 100; i++) {
		nodes[i] = SenderNode(110, 5);
	}
	for (int i = 100; i < 200; i++) {
		nodes[i] = SenderNode(75, 3);
	}
	for (int i = 200; i < 300; i++) {
		nodes[i] = SenderNode(94, 2);
	}
	for (int i = 300; i < 400; i++) {
		nodes[i] = SenderNode(60, 4);
	}

	Channel channel(nodes, 400, 30);
	channel.tdma();
}

void b_dtdma() {
	srand((unsigned)time(0));

	SenderNode* nodes = new SenderNode[400];
	for (int i = 0; i < 100; i++) {
		nodes[i] = SenderNode(110, 5);
	}
	for (int i = 100; i < 200; i++) {
		nodes[i] = SenderNode(75, 3);
	}
	for (int i = 200; i < 300; i++) {
		nodes[i] = SenderNode(94, 2);
	}
	for (int i = 300; i < 400; i++) {
		nodes[i] = SenderNode(60, 4);
	}

	Channel channel(nodes, 400, 30);
	channel.dtdma();
}


int main() {
	b_dtdma();
	return 0;
}