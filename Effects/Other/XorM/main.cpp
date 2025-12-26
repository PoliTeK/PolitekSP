#include "daisy_seed.h"
#include "daisysp.h"
#include "XorM.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
XorM glitch;
Oscillator tone;
Oscillator mangle;
Oscillator carrier;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    // Process mangle: output is -1.0 to 1.0
    // Map it to 0.0 to 1.0 for the mangle parameter
    float automation = (mangle.Process() + 1.0f) * 0.5f;
    glitch.setMangle(automation);

    for(size_t i = 0; i < size; i++)
    {
        // Generate audio signal
        float sig = tone.Process();
        float car = carrier.Process();
        float man = mangle.Process();
        glitch.setMangle(man);
        // Apply effect (Self-modulation for testing)
        float wet = glitch.process(sig, 0.0f);

        // Stereo Output
        out[0][i] = wet;
        out[1][i] = wet;
    }
}

int main(void)
{
    // Hardware Setup
    hw.Init();
    hw.SetAudioBlockSize(4);
    float sample_rate = hw.AudioSampleRate();

    // Effect Init
    glitch.init();

    // Audio Oscillator Setup (Sine, 110Hz, 50% vol)
    tone.Init(sample_rate);
    tone.SetWaveform(Oscillator::WAVE_SIN);
    tone.SetFreq(440.0f); 
    tone.SetAmp(0.5f);

    // Automation mangle Setup (Triangle, 0.1Hz)
    mangle.Init(sample_rate);
    mangle.SetWaveform(Oscillator::WAVE_TRI);
    mangle.SetFreq(0.1f); 
    mangle.SetAmp(1.0f);
    

    carrier.Init(sample_rate);
    carrier.SetWaveform(Oscillator::WAVE_SIN);
    carrier.SetFreq(50.0f); 
    carrier.SetAmp(1.0f);

    // Start
    hw.StartAudio(AudioCallback);

    while(1) {}
}