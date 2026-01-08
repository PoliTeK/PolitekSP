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

    // Inizializza passando il puntatore all'array in SDRAM e la sua grandezza
    void Init(float* buffer_array, size_t size);

    // Scrive un campione e avanza la testina
    void Write(float input);

    void SetMode(ReadMode mode);

    float Read();


private:
    float* _buffer;      // Puntatore all'array vero
    size_t _size;        // Grandezza totale
    size_t _mask; // Maschera per wrap around
    size_t _h;  // testina 

    int8_t _mode;
    bool _write_block = false;
    
};