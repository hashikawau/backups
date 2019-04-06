//========================================
// WaveDevice.cpp
//
//  Created on: 2014/01/02
//      Author: you
//========================================

#include "WaveDevice.h"

#include <QtCore/qabstractnativeeventfilter.h>

#include <cmath>

#include <fstream>
#include <cmath>
#include <iostream>

namespace wavedit {

//static int sine_func(short *data, int strt_count, int n_data, int fs, double amp, double f);

//===============================================
struct WaveFormat {
    char RIFF[4];
    long riff_size;
    char riff_kind[4];
    char fmt[4];
    long fmt_chnk;
    PCMWAVEFORMAT pcm;
    char data_chnk[4];
    long Nbyte;
};
//===============================================
WaveBufferIterator::WaveBufferIterator(std::shared_ptr<char> data, int length)
        : m_data(data),
            m_size(length),
            m_position(0)
{
}
WaveBufferIterator::~WaveBufferIterator() {
}
//===============================================
static void error(const std::string& message) {
    std::cout << "failed to open file: " << message << std::endl;
}
//===============================================
WaveInfo::WaveInfo()
        : m_numChannels(2),
            m_numBitsPerSample(16),
            m_numSamplesPerSec(44000),
            m_data(),
            m_size(0)
{
}
WaveInfo::~WaveInfo() {
}
void WaveInfo::load(const std::string& filepath) {
    std::ifstream stream(filepath, std::ios::binary);
    if (!stream) {
        error("stream()");
    }
    typedef struct {
        char riff[4];
        int riff_size;
        char riff_kind[4];
        char fmt[4];
        int fmt_size;
        PCMWAVEFORMAT pcm;
    } WaveFormat;
    WaveFormat waveFormat;
    stream.read((char*) &waveFormat, sizeof(waveFormat));

    {
        char array[] = {
            waveFormat.riff[0],
            waveFormat.riff[1],
            waveFormat.riff[2],
            waveFormat.riff[3],
            '\0'
        };
        std::string str(array);
        if ("RIFF" != str) {
            error("file format not RIFF" + str);
        }
    }
    {
        char array[] = {
            waveFormat.riff_kind[0],
            waveFormat.riff_kind[1],
            waveFormat.riff_kind[2],
            waveFormat.riff_kind[3],
            '\0'
        };
        std::string str(array);
        if ("WAVE" != str) {
            error("RIFF kind not WAVE" + str);
        }
    }
    {
        char array[] = {
            waveFormat.fmt[0],
            waveFormat.fmt[1],
            waveFormat.fmt[2],
            waveFormat.fmt[3],
            '\0'
        };
        std::string str(array);
        if ("fmt " != str) {
            error("WAVE format not fmt" + str);
        }
    }
    {
        if (waveFormat.pcm.wf.wFormatTag != WAVE_FORMAT_PCM) {
            error("WAVE format not PCM" + waveFormat.pcm.wf.wFormatTag);
        }
    }

    typedef struct {
        char format[4];
        int size;
    } WaveDataInfo;
    WaveDataInfo waveDataInfo;
    stream.read((char*) &waveDataInfo, sizeof(WaveDataInfo));
    {
        char array[] = {
            waveDataInfo.format[0],
            waveDataInfo.format[1],
            waveDataInfo.format[2],
            waveDataInfo.format[3],
            '\0'
        };
        std::string str(array);
        if ("data" != str) {
            error("WAVE data format not data" + str);
        }
    }

    m_numChannels = waveFormat.pcm.wf.nChannels;
    m_numSamplesPerSec = waveFormat.pcm.wf.nSamplesPerSec;
    m_numBitsPerSample = waveFormat.pcm.wBitsPerSample;
    m_size = waveDataInfo.size;
    auto data = new char[m_size];
    stream.read(data, waveDataInfo.size);
//    m_data.reset(data);
    m_data = std::shared_ptr<char>(data, std::default_delete<char[]>());

    std::cout << "data size: " << m_size << std::endl;
    std::cout << "fmt size: " << waveFormat.fmt_size << std::endl;
    std::cout << "riff size: " << waveFormat.riff_size << std::endl;
}
void WaveInfo::save(const std::string& filepath) const {
    std::ofstream stream(filepath, std::ios::binary);

    typedef struct {
        char riff[4];
        int riff_size;
        char riff_kind[4];
        char fmt[4];
        int fmt_chnk;
        PCMWAVEFORMAT pcm;
        char format[4];
        int data_size;
    } WaveFormat;
    WaveFormat
    waveFormat {
        { 'R', 'I', 'F', 'F' },
        (m_size + 8) + (16 + 12),
        { 'W', 'A', 'V', 'E' },
        { 'f', 'm', 't', ' ' },
        16,
        WAVE_FORMAT_PCM,
        getNumChannels(),
        getNumSamplesPerSec(),
        getNumAvgBytesPerSec(),
        getNumBlockAlign(),
        getNumBitsPerSample(),
        { 'd', 'a', 't', 'a' },
        m_size
    };
    stream.write((char*) &waveFormat, sizeof(waveFormat));
    stream.write(m_data.get(), m_size);
}
//===============================================
WaveDevice::WaveDevice(WId hwnd/*, double f*/)
        : m_hwnd((HWND) hwnd),
            m_hWaveOut(0),
            // m_whdr({0, 0})
            m_maxBufferLength(0),
            m_iterator(0, 0) //,
//            m_currentPos(0),
//            m_length(0),
//            m_data(0)
{
}
WaveDevice::~WaveDevice() {
    std::cout << "close()" << std::endl;

    waveOutReset(m_hWaveOut);
    for (WAVEHDR it : m_whdr) {
        waveOutUnprepareHeader(m_hWaveOut, &it, sizeof(WAVEHDR));
    }
    waveOutClose(m_hWaveOut);
}

void WaveDevice::open(const WaveInfo& waveInfo) {
    m_maxBufferLength = waveInfo.getNumBlockAlign() * NUM_DATA_BLOCK;
    m_iterator = waveInfo.iterator();

    WAVEFORMATEX wfe;
    wfe.wFormatTag = WAVE_FORMAT_PCM;
    wfe.nChannels = waveInfo.getNumChannels();
    wfe.nSamplesPerSec = waveInfo.getNumSamplesPerSec();
    wfe.nAvgBytesPerSec = waveInfo.getNumAvgBytesPerSec();
    wfe.nBlockAlign = waveInfo.getNumBlockAlign();
    wfe.wBitsPerSample = waveInfo.getNumBitsPerSample();
    wfe.cbSize = 0;
    waveOutOpen(&m_hWaveOut,
    WAVE_MAPPER,
        &wfe,
        (DWORD) m_hwnd,
        0,
        CALLBACK_WINDOW);

    for (auto& it : m_whdr) {
        it.dwUser = 0; //State::STOP;
    }

    std::cout << "channels: " << wfe.nChannels << std::endl;
    std::cout << "frequency: " << wfe.nSamplesPerSec / 1000.0 << std::endl;
    std::cout << "bits: " << wfe.wBitsPerSample << std::endl;

}

void WaveDevice::start() {
    m_iterator.move(0);
    for (auto& it : m_whdr) {
        it.lpData = m_iterator.get();
        it.dwBufferLength = m_iterator.advace(m_maxBufferLength);
        it.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
        it.dwLoops = 1;
        it.dwUser ^= State::PLAY;

        waveOutPrepareHeader(m_hWaveOut, &it, sizeof(WAVEHDR));
        auto result = waveOutWrite(m_hWaveOut, &it, sizeof(WAVEHDR));

        std::cout << "start(): " << &it;
        if (result != 0) {
            std::cout << " error -> " << result;
        }
        std::cout << std::endl;
    }
}
void WaveDevice::stop() {
    for (auto& it : m_whdr) {
        it.dwUser = State::STOP;
    }
    waveOutReset(m_hWaveOut);
}

int WaveDevice::waveOutProc_WOM_DONE(HWAVEOUT hwo, LPWAVEHDR pwhdr) {
    if (pwhdr->dwUser & State::STOP) {
        pwhdr->dwUser ^= State::STOP;
        std::cout << "stoped(): " << &pwhdr << std::endl;
    } else
    if (pwhdr->dwUser & State::PLAY) {
        if (m_iterator.hasNext()) {
            int pos = m_iterator.position();

            pwhdr->lpData = m_iterator.get();
            pwhdr->dwBufferLength = m_iterator.advace(m_maxBufferLength);

            waveOutWrite(hwo,
                pwhdr,
                sizeof(WAVEHDR));

            std::cout << "current pos: " << pos
                << " / " << m_iterator.size()
                << " [+" << pwhdr->dwBufferLength << "]"
                << " - " << pwhdr
                << std::endl;
        } else {
            std::cout << "end: " << std::endl;
        }
    }

    return 0;
}

} /* namespace wavedit */

