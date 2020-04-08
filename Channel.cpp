#include "Channel.h"

Channel::Channel(SenderNode* nodes, int numOfNodes, int channelCap)
{
	_virtualTime = 0;
	_nodes = nodes;
	_numOfNodes = numOfNodes;
	_channelCapacity = channelCap;
	_walshCodeSize = std::pow(2, std::floor(std::log2(_numOfNodes)));
	_tdmaChannel = new int[_channelCapacity];
	_cdmaChannel = new int[_channelCapacity * _walshCodeSize];
	for (int i = 0; i < _channelCapacity; ++i)
		_tdmaChannel[i] = 0;
	for (int i = 0; i < _channelCapacity * _walshCodeSize; ++i)
		_cdmaChannel[i] = 0;
}

void Channel::generate_and_assign_walsh_code_to_nodes()
{ 
	bool** walshCode = new bool* [_walshCodeSize];
	for (int i = 0; i < _walshCodeSize; ++i) {
		walshCode[i] = new bool[_walshCodeSize];
	}
	int lastCol = 1;
	int lastRow = 1;
	walshCode[0][0] = 0;
	while (lastCol < _walshCodeSize) {
		for (int i = 0; i < lastRow; ++i) {
			for (int j = 0; j < lastCol; ++j) {
				walshCode[i][lastCol + j] = walshCode[i][j];
				walshCode[lastRow + i][j] = walshCode[i][j];
				walshCode[lastRow + i][lastCol + j] = !walshCode[i][j];
			}
		}
		lastCol *= 2;
		lastRow *= 2;
	}
	for (int i = 0; i < _numOfNodes; ++i)
		_nodes[i].set_walsh_code(walshCode[i], _walshCodeSize);
	for (int i = _numOfNodes; i < _walshCodeSize; ++i)
		delete[] walshCode[i];
}

void Channel::tdma()
{
	bool allDone = false;
	while (!allDone) {
		allDone = true;
		for (int i = 0; i < _numOfNodes; i++) {
			bool iDone = _nodes[i].tdma_send(_tdmaChannel, _virtualTime);
			std::cout << "Time = " << _virtualTime << "ms:\n";
			std::cout << "Node " << i << ": ";
			for (int i = 0; i < _channelCapacity; ++i) {
				if (_tdmaChannel[i])
					std::cout << (_tdmaChannel[i] == -1 ? "1" : "0");
				_tdmaChannel[i] = 0;
			}
			std::cout << "\n";
			allDone = allDone && iDone;
		}
	}
}

void Channel::dtdma()
{
	bool allDone = false;
	while (!allDone) {
		allDone = true;
		for (int i = 0; i < _numOfNodes; ++i) {
			int sumData = 0;
			for (int j = 0; j < _numOfNodes; ++j) {
				sumData += _nodes[j].get_date_size();
			}
			int timeSlots = std::ceil((double)_nodes[i].get_date_size() / (double)sumData);
			for (int j = 0; j < timeSlots; ++j) {
				bool iDone = _nodes[i].tdma_send(_tdmaChannel, _virtualTime);
				std::cout << "Time = " << _virtualTime << "ms:\n";
				std::cout << "Node " << i << ": ";
				for (int i = 0; i < _channelCapacity; ++i) {
					if (_tdmaChannel[i])
						std::cout << (_tdmaChannel[i] == -1 ? "1" : "0");
					_tdmaChannel[i] = 0;
				}
				std::cout << "\n";
				allDone = allDone && iDone;
			}
		}
	}
}

void Channel::cdma()
{
	bool AllDone = false;
	
	while (!AllDone)
	{

		for (int i = 0; i < _channelCapacity * _walshCodeSize; ++i) {
			_cdmaChannel[i] = 0;
		}

		for (int i = 0; i < _numOfNodes; ++i) {
			int* encodedData = _nodes[i].cdma_encode(_channelCapacity);
			for (int j = 0; j < _channelCapacity * _walshCodeSize; ++j) {
				_cdmaChannel[j] += encodedData[j];
			}
		}

		_virtualTime += timeSlot;

		std::cout << "Time = " << _virtualTime << "ms:\n";

		for (int i = 0; i < _numOfNodes; ++i) {
			cdma_decode_and_print(i);
		}

		std::cout << "\n";

		AllDone = true;
		for (int i = 0; i < _numOfNodes; ++i)
			AllDone = AllDone && _nodes[i].get_date_size() == 0;
	}
}

void Channel::cdma_decode_and_print(int nodeIndx)
{
	std::cout << "\tNode " << nodeIndx << ": ";
	for (int i = 0; i < _channelCapacity * _walshCodeSize; i += _walshCodeSize) {
		int data = 0;
		for (int j = 0; j < _walshCodeSize; j++) {
			data += _cdmaChannel[i + j] * (_nodes[nodeIndx].get_walsh_code()[(i + j) % _walshCodeSize] ? -1 : 1);
		}

		data /= _walshCodeSize;

		if (data)
			std::cout << (data == -1 ? "1" : "0");
	}
	std::cout << "\n";
}
