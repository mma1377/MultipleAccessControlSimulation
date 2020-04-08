#include "SenderNode.h"

SenderNode::SenderNode()
{
	_data = nullptr;
	_walshCode = nullptr;
}

SenderNode::SenderNode(const char* data, int dataSize, int dataRate)
{
	_dataSize = dataSize;
	_dataRate = dataRate;
	_data = new bool[_dataSize];
	for (int i = 0; i < _dataSize; ++i) {
		_data[i] = data[i] == '1';
	}
}

SenderNode::~SenderNode()
{
	if(_walshCode != nullptr)
		delete[] _walshCode;
	if(_data != nullptr)
		delete[] _data;
}

SenderNode::SenderNode(SenderNode& other)
{
	_dataSize = other._dataSize;
	_dataRate = other._dataRate;
	_walshCodeSize = other._walshCodeSize;
	_data = new bool[_dataSize];
	_walshCode = new bool[_walshCodeSize];
	for (int i = 0; i < _dataSize; ++i) {
		_data[i] = other._data[i];
	}
	for (int i = 0; i < _walshCodeSize; ++i) {
		_walshCode[i] = other._walshCode[i];
	}
}

SenderNode::SenderNode(SenderNode&& other)
{
	_dataSize = other._dataSize;
	_dataRate = other._dataRate;
	_walshCodeSize = other._walshCodeSize;
	_data = other._data;
	_walshCode = other._walshCode;
	other._data = nullptr;
	other._walshCode = nullptr;
}

SenderNode& SenderNode::operator=(SenderNode& other)
{
	if (this != &other) {
		this->~SenderNode();
		_dataSize = other._dataSize;
		_dataRate = other._dataRate;
		_walshCodeSize = other._walshCodeSize;
		_data = new bool[_dataSize];
		_walshCode = new bool[_walshCodeSize];
		for (int i = 0; i < _dataSize; ++i) {
			_data[i] = other._data[i];
		}
		for (int i = 0; i < _walshCodeSize; ++i) {
			_walshCode[i] = other._walshCode[i];
		}
	}
	return *this;
}

SenderNode& SenderNode::operator=(SenderNode&& other)
{
	if (this != &other) {
		this->~SenderNode();
		_dataSize = other._dataSize;
		_dataRate = other._dataRate;
		_walshCodeSize = other._walshCodeSize;
		_data = other._data;
		_walshCode = other._walshCode;
		other._data = nullptr;
		other._walshCode = nullptr;
	}
	return *this;
}

bool SenderNode::tdma_send(int* channel, int& virtualTime)
{
	bool retVal = false;

	bool randFlag = rand() % 2;

	if (randFlag) {
		for (int i = 0; i < _dataRate; ++i) {
			if (i < _dataSize) {
				channel[i] = _data[i] ? -1 : 1;
			}
		}

		for (int i = _dataRate; i < _dataSize; ++i) {
			_data[i - _dataRate] = _data[i];
		}

		_dataSize -= _dataRate;
		if (_dataSize < 0)
			_dataSize = 0;
	}

	if (_dataSize <= 0)
		retVal = true;

	virtualTime += timeSlot;


	return retVal;
}


int* SenderNode::cdma_encode(int len)
{
	int* encodedData = new int[len * _walshCodeSize];
	for (int i = 0; i < len * _walshCodeSize; ++i) {
		encodedData[i] = 0;
	}

	bool randFlag = rand() % 2;

	if (randFlag) {

		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < _walshCodeSize; ++j) {
				if (i < _dataSize && i < _dataRate)
					encodedData[i * _walshCodeSize + j] = _data[i] ^ _walshCode[j] ? -1 : 1;
				else
					encodedData[i * _walshCodeSize + j] = 0;
			}
		}

		for (int i = _dataRate; i < _dataSize; ++i) {
			_data[i - _dataRate] = _data[i];
		}

		_dataSize -= _dataRate;
		if (_dataSize < 0)
			_dataSize = 0;
	}
	return encodedData;
}

void SenderNode::set_walsh_code(bool* code, int size)
{
	_walshCode = code;
	_walshCodeSize = size;
}

bool* SenderNode::get_walsh_code()
{
	return _walshCode;
}

int SenderNode::get_date_size()
{
	return _dataSize;
}
