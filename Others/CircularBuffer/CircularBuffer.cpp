#include "CircularBuffer.h"

void CircularBuffer::Init(float* buffer_array, size_t size) {
    _buffer = buffer_array;
    _size = size  ;
    _mask = size - 1; 
    _h = _mask;
    _mode = 0;

    _write_block = false;
}

void CircularBuffer::Write(float input) {
   if (_write_block == false) {
        _h = (_h + 1) & _mask;
        _buffer[_h] = input;
    }
    
}
void CircularBuffer::SetMode(ReadMode mode)
{
    _mode = mode;
    if(mode == -1){
        _write_block = true;

    }else {
        _write_block = false;
    }
        
}
float CircularBuffer::Read() 
{
    float output = 0.0f;
    output = _buffer[_h];
    _h  = (_h + _mode) & _mask;
    return output;
    
}
