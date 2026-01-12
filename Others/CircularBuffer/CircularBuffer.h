#pragma once
#include <stdint.h>
#include <stddef.h> // Per size_t



class CircularBuffer {

public:
    CircularBuffer() {}
    ~CircularBuffer() {}

    enum ReadMode { 
        FORWARD = 0, 
        BACKWARD = -1
        };

    void Init(float* buffer_array, size_t size, float fs);

    void SetBuffSize(float bpm, uint8_t steps, float scale = 1); // TODO Scl

    void Write(float input);

    void SetMode(ReadMode mode);

    float Read();


private:
    float* _buffer;      // Puntatore all'array vero
    size_t _MAX_SIZE;        // Grandezza totale
    float _fs;

    size_t _buff_dim;
    float _buff_time;

    float _bpm, _scale;
    uint8_t _steps;
    

    size_t _h;  // testina 

    int8_t _mode;
    bool _write_block = false;
    
};