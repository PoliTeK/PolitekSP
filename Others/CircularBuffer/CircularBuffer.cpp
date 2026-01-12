#include "CircularBuffer.h"

void CircularBuffer::Init(float* buffer_array, size_t size, float fs) {
    _buffer = buffer_array;
    _MAX_SIZE = size;
    _buff_dim = _MAX_SIZE; 

    _h = _buff_dim -1;
    _mode = 0;
    _fs = fs;

    _write_block = false;
}
// TODO trovare un modo sicuro per avere variazioni di tempo -- decimazione / interpolazioni per allargare ciò che c'era e metterlo a tempo
void CircularBuffer::SetBuffSize(float bpm, uint8_t steps, float scale){
    _bpm = bpm;
    _steps = steps;
    _scale = scale;

    _buff_time = (15.0f * ((float)steps/scale) / bpm ) ;
    _buff_dim = (size_t)(_buff_time * _fs);

    if (_buff_dim > _MAX_SIZE) {
        _buff_dim = _MAX_SIZE;
    } 
    if (_buff_dim < 10) {
        _buff_dim = 10;
    }

    if (_h >= _buff_dim) {
        _h = _h % _buff_dim;
    }

}

void CircularBuffer::Write(float input) {
   if (_write_block == false) {
        if (_h < _buff_dim - 1 )
        {   
            _h = (_h + 1);
        } else {
            _h = 0;
        }
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

    if (_h > 0 || _mode == 0)
    {   
        output = _buffer[_h];
        _h = (_h + _mode);
    } else {
        output = _buffer[_h];
        _h = _buff_dim - 1;
    }

    return output;
    
}
