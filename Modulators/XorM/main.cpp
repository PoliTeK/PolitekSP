#include "daisy_seed.h"
#include "daisysp.h"
#include "XorM.h"

using namespace daisy;
using namespace daisysp;

DaisySeed hw;
XorM glitch;
Oscillator tone;
Oscillator mask;
Oscillator carrier;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
    // Process mask: output is -1.0 to 1.0
    // Map it to 0.0 to 1.0 for the mask parameter
    float automation = (mask.Process() + 1.0f) * 0.5f;
    glitch.setMask(automation);

    for(size_t i = 0; i < size; i++)
    {
        // Generate audio signal
        float sig = tone.Process();
        float car = carrier.Process();
        float man = mask.Process();
        glitch.setMask(man);
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

    // Automation mask Setup (Triask, 0.1Hz)
    mask.Init(sample_rate);
    mask.SetWaveform(Oscillator::WAVE_TRI);
    mask.SetFreq(0.1f); 
    mask.SetAmp(1.0f);
    

    carrier.Init(sample_rate);
    carrier.SetWaveform(Oscillator::WAVE_SIN);
    carrier.SetFreq(50.0f); 
    carrier.SetAmp(1.0f);

    // Start
    hw.StartAudio(AudioCallback);

    while(1) {}
}