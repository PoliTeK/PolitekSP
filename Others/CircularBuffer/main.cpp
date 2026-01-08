#include "daisy_seed.h"
#include "daisysp.h"
#include "CircularBuffer.h"

using namespace daisy;
using namespace daisysp;


const size_t buffsize = 1048576; // 1MB
float DSY_SDRAM_BSS buff[buffsize];


volatile bool fBack = false;
DaisySeed hw;
CircularBuffer mBuff;

GPIO button;




void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    for(size_t i = 0; i < size; i++)
    {   
        float outSample = 0.0f;
        // Input
        float sig = in[0][i];
        
        // Scrittura sempre in avanti
        mBuff.Write(sig);

        // Lettura (Forward o Backward)
        if (fBack) {
          
            mBuff.SetMode(CircularBuffer::ReadMode::BACKWARD ); // CircularBuffer::ReadMode::BLOCKING_BACKWARD
        }
        else {
            mBuff.SetMode( CircularBuffer::ReadMode::FORWARD ); // CircularBuffer::ReadMode::FORWARD
        }
        outSample = mBuff.Read();
        // Output
        out[0][i] = outSample;
        out[1][i] = outSample;
    }
}

int main(void)
{
    // Hardware Setup
    hw.Init();
    hw.SetAudioBlockSize(4);
    float sample_rate = hw.AudioSampleRate();

    button.Init(daisy::seed::D28, GPIO::Mode::INPUT, GPIO::Pull::PULLUP);

    
    mBuff.Init(buff, buffsize);

    // Start
    hw.StartAudio(AudioCallback);

    while(1) {
        
        fBack = !button.Read();

        
        System::Delay(10);
    }
}