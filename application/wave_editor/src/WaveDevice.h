//========================================
// WaveDevice.h
//
//  Created on: 2014/01/02
//      Author: you
//========================================

#ifndef WAVEDEVICE_H_
#define WAVEDEVICE_H_

//#include <windows.h>
#include <windef.h>
#include <winnt.h>
#include <mmsystem.h>
typedef struct tagMSG {
    HWND hwnd;
    UINT message;
    WPARAM wParam;
    LPARAM lParam;
    DWORD time;
    POINT pt;
} MSG, *LPMSG, *PMSG;

#include <QtGui/qwindowdefs.h>

#include <string>
#include <memory>
#include <iostream>

namespace wavedit {

class WaveBufferIterator {
public:
    WaveBufferIterator(std::shared_ptr<char> data, int length);
    ~WaveBufferIterator();

    LPSTR get() const {
        return m_data.get() + m_position;
    }
    DWORD advace(int distance) {
        int advancedDistance = std::min(distance, m_size - m_position);
        m_position += advancedDistance;
        return advancedDistance;
    }
    bool hasNext() const {
        return m_size - m_position > 0;
    }
    void move(int index) {
        m_position = index;
    }
    int size() const {
        return m_size;
    }
    int position() const {
        return m_position;
    }

private:
    std::shared_ptr<char> m_data;
    int m_size;
    int m_position;

};

/*
 *
 */
class WaveInfo {
public:
    WaveInfo();
    ~WaveInfo();

    void load(const std::string& filepath);
    void save(const std::string& filepath) const;

    unsigned short getNumChannels() const {
        return m_numChannels;
    }
    unsigned short getNumBitsPerSample() const {
        return m_numBitsPerSample;
    }
    unsigned short getNumBlockAlign() const {
        return getNumChannels() * getNumBitsPerSample() / 8;
    }
    unsigned int getNumSamplesPerSec() const {
        return m_numSamplesPerSec;
    }
    unsigned int getNumAvgBytesPerSec() const {
        return getNumSamplesPerSec() * getNumBlockAlign();
    }
    std::shared_ptr<char> data() const {
        return m_data;
    }
    int size() const {
        return m_size;
    }
    WaveBufferIterator iterator() const {
        return WaveBufferIterator(m_data, m_size);
    }

    template<class Iterator>
    void setData(int size, const Iterator& begin, int numSamplesPerSec = 44100) {
        m_numChannels = 1;
        m_numBitsPerSample = sizeof(typename Iterator::value_type) * 8;
        m_numSamplesPerSec = numSamplesPerSec;
        m_size = size * getNumBlockAlign();
        m_data = std::shared_ptr<char>(new char[m_size], std::default_delete<char[]>());
        auto data = reinterpret_cast<typename Iterator::value_type*>(m_data.get());
        auto it = begin;
        for (int i = 0; i < size; ++i) {
            data[i] = *it;
            ++it;
        }
    }
    template<class Iterator>
    void setData(int size, const Iterator& leftBegin, const Iterator& rightBegin, int numSamplesPerSec = 44100) {
        m_numChannels = 2;
        m_numBitsPerSample = sizeof(typename Iterator::value_type) * 8;
        m_numSamplesPerSec = numSamplesPerSec;
        m_size = size * getNumBlockAlign();
        m_data = std::shared_ptr<char>(new char[m_size], std::default_delete<char[]>());
        auto data = reinterpret_cast<typename Iterator::value_type*>(m_data.get());
        auto left = leftBegin;
        auto right = rightBegin;
        for (int i = 0; i < size; ++i) {
            data[2 * i + 0] = *left;
            data[2 * i + 1] = *right;
            ++left;
            ++right;
        }
    }

    void show() const {
        for (int i = 0; i < size(); ++i) {
            std::cout << i << ": " << (int) data().get()[i] << std::endl;
        }
    }

private:
    WaveInfo(const WaveInfo&);
    WaveInfo operator=(const WaveInfo&);

private:
    unsigned short m_numChannels;
    unsigned short m_numBitsPerSample;
    unsigned int m_numSamplesPerSec;
    std::shared_ptr<char> m_data;
    int m_size;

}
;

/*
 *
 */
class WaveDevice {
public:
    WaveDevice(WId hwnd/*, double f = 440*/);
    ~WaveDevice();

//    void load(const std::string& filepath);

    void open(const WaveInfo& waveInfo);

    void start();
    void stop();

    void pause();
    void resume();

    int waveOutProc_WOM_DONE(HWAVEOUT hwo, LPWAVEHDR pwhdr);

public:
    enum State
            : DWORD {
            STOP = 0x01,
            PLAY = 0x02,
            PAUSE = 0x04,
            LOOP = 0x08,
    };

private:
    WaveDevice(const WaveDevice&);
    WaveDevice& operator=(const WaveDevice&);

private:
    static const int NUM_BUFFERS = 4;
    static const int NUM_DATA_BLOCK = 5000;

    HWND m_hwnd;

    HWAVEOUT m_hWaveOut;
    std::array<WAVEHDR, NUM_BUFFERS> m_whdr;
    int m_maxBufferLength;
    WaveBufferIterator m_iterator;

//    int m_currentPos;
//    int m_length;
//    std::shared_ptr<char> m_data;

//    int m_fs; //sampling frequency [Hz]
//    double m_f; //frequency [Hz]
//    int m_idur; //time [s]
//    double m_amp; //amplitude

//    WaveInfo* m_waveInfo;
};

} /* namespace wavedit */

#endif /* WAVEDEVICE_H_ */
