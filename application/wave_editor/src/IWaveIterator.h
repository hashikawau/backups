//========================================
// IWaveIterator.h
//
//  Created on: 2014/01/13
//      Author: you
//========================================

#ifndef IWAVEITERATOR_H_
#define IWAVEITERATOR_H_

#include <memory>
#include <vector>
#include <iterator>

#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace wavedit {

/*
 *
 */
template<class T>
class IWaveIterator: public std::iterator<std::input_iterator_tag, T> {
public:
    typedef T value_type;

public:
    virtual ~IWaveIterator() =0;

    virtual T operator*() const =0;
    virtual IWaveIterator& operator++() =0;

    virtual T amplitude() {
        return 1;
    }
};
template<class T>
IWaveIterator<T>::~IWaveIterator() {
}

template<class T>
class SineWaveIterator: public IWaveIterator<T> {
public:
    SineWaveIterator(T amplitude, int frequency, int numSamplePerSec = 44100)
            : m_amplitude(amplitude),
                m_theta(0.0),
                m_delta(2 * M_PI * frequency / numSamplePerSec)
    {
    }
    virtual ~SineWaveIterator() {
    }

    virtual T operator*() const override {
        return m_amplitude * std::sin(m_theta);
    }
    virtual SineWaveIterator& operator++() override {
        m_theta += m_delta;
        while (m_theta >= 2 * M_PI) {
            m_theta -= 2 * M_PI;
        }
        return *this;
    }
    virtual T amplitude() {
        return m_amplitude;
    }

private:
    T m_amplitude;
    double m_theta;
    double m_delta;

};

template<class T>
class TriangularWaveIterator: public std::iterator<std::input_iterator_tag, T> {
public:
    typedef T value_type;

public:
    TriangularWaveIterator(T amplitude, int frequency, int numSamplePerSec = 44100)
            : m_amplitude(amplitude),
                m_x(0.0),
                m_delta((double) frequency / numSamplePerSec)
    {
    }
    ~TriangularWaveIterator() {
    }

    T operator*() const {
        return m_amplitude * ((std::signbit(m_x) ? -1 : 1) * 4.0 * m_x - 1.0);
    }
    TriangularWaveIterator& operator++() {
        m_x += m_delta;
        while (m_x >= 0.5) {
            m_x -= 1.0;
        }
        return *this;
    }

private:
    T m_amplitude;
    double m_x;
    double m_delta;

};

template<class T>
class SawWaveIterator: public std::iterator<std::input_iterator_tag, T> {
public:
    typedef T value_type;

public:
    SawWaveIterator(T amplitude, int frequency, int numSamplePerSec = 44100)
            : m_amplitude(amplitude),
                m_x(0.0),
                m_delta((double) frequency / numSamplePerSec)
    {
    }
    ~SawWaveIterator() {
    }

    T operator*() const {
        return m_amplitude * 2.0 * m_x;
    }
    SawWaveIterator& operator++() {
        m_x += m_delta;
        while (m_x >= 0.5) {
            m_x -= 1.0;
        }
        return *this;
    }

private:
    T m_amplitude;
    double m_x;
    double m_delta;

};

template<class T>
class SquareWaveIterator: public std::iterator<std::input_iterator_tag, T> {
public:
    typedef T value_type;

public:
    SquareWaveIterator(T amplitude, int frequency, int numSamplePerSec = 44100)
            : m_amplitude(amplitude),
                m_x(0.0),
                m_delta((double) frequency / numSamplePerSec)
    {
    }
    ~SquareWaveIterator() {
    }

    T operator*() const {
        return m_amplitude * (std::signbit(m_x) ? -1.0 : 1.0);
    }
    SquareWaveIterator& operator++() {
        m_x += m_delta;
        while (m_x >= 0.5) {
            m_x -= 1.0;
        }
        return *this;
    }

private:
    T m_amplitude;
    double m_x;
    double m_delta;

};

template<class T>
class PulseWaveIterator: public std::iterator<std::input_iterator_tag, T> {
public:
    typedef T value_type;

public:
    PulseWaveIterator(T amplitude, int frequency, int numSamplePerSec = 44100)
            : m_amplitude(amplitude),
                m_x(0.0),
                m_delta((double) frequency / numSamplePerSec)
    {
    }
    ~PulseWaveIterator() {
    }

    T operator*() const {
        return m_amplitude * (m_x >= 0 && m_x < m_delta ? 1.0 : 0.0);
    }
    PulseWaveIterator& operator++() {
        m_x += m_delta;
        while (m_x >= 0.5) {
            m_x -= 1.0;
        }
        return *this;
    }

private:
    T m_amplitude;
    double m_x;
    double m_delta;

};

template<class T>
class AddWaveIterator: public IWaveIterator<T> {
public:
    AddWaveIterator()
    {
    }
    virtual ~AddWaveIterator() {
    }

    virtual T operator*() const override {
        T result = 0;
        for (auto& it : m_iterators) {
            result += *(*it);
        }
        return result;
    }
    virtual IWaveIterator<T>& operator++() override {
        for (auto& it : m_iterators) {
            ++(*it);
        }
        return *this;
    }

    void add(IWaveIterator<T>* iterator) {
        m_iterators.push_back(std::shared_ptr<IWaveIterator<T> >(iterator));
    }

private:
    std::vector<std::shared_ptr<IWaveIterator<T> > > m_iterators;

};

template<class T>
class MultWaveIterator: public IWaveIterator<T> {
public:
    MultWaveIterator()
    {
    }
    virtual ~MultWaveIterator() {
    }

    virtual T operator*() const override {
        T result = 1;
        for (auto& it : m_iterators) {
            result *= *(*it);
        }
        return result;
    }
    virtual IWaveIterator<T>& operator++() override {
        for (auto& it : m_iterators) {
            ++(*it);
        }
        return *this;
    }

    void add(IWaveIterator<T>* iterator) {
        m_iterators.push_back(std::shared_ptr<IWaveIterator<T> >(iterator));
    }

private:
    std::vector<std::shared_ptr<IWaveIterator<T> > > m_iterators;

};

} /* namespace wavedit */

#endif /* IWAVEITERATOR_H_ */
