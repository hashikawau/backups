//========================================
// WaveEditor.cpp
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#include "WaveEditor.h"
#include <QtWidgets/qapplication.h>
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qscrollbar.h>

#include <QtCore/qabstracteventdispatcher.h>
#include <QtCore/qabstractnativeeventfilter.h>

#include <memory>
#include <iterator>
#include <iostream>
#include "IWaveIterator.h"

namespace wavedit {

class A: public QAbstractNativeEventFilter {
public:
    A(WaveDevice* wave);
    ~A();

public:
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message,
        long *result) override;

private:
    WaveDevice* m_wave;
};

A::A(WaveDevice* wave)
        : m_wave(wave) {
}
A::~A() {
}
bool A::nativeEventFilter(
    const QByteArray& /*eventType*/,
    void* message,
    long* /*result*/) {

//#ifdef WIN32
    MSG* msg = (MSG*) message;
    if (msg->message == MM_WOM_DONE) {
//        std::cout << "winEvent(): " << MM_WOM_DONE << ", " << std::endl;
//        *result =
        m_wave->waveOutProc_WOM_DONE((HWAVEOUT) msg->wParam, (LPWAVEHDR) msg->lParam);
        return true;
    }
//#endif

    return false;
}
std::unique_ptr<A> m_a;

//CoordinateConverter::PointD GeometryEditor::m_mousePosition;
WaveEditor::WaveEditor(/*ModelRoot* modelRoot,*/QWidget* parent)
    //        : QWidget(parent)
    {
    setMouseTracking(true);

//    setBackgroundRole(QPalette::BrightText);

    m_waveDevice.reset(new WaveDevice(winId()));
//    initWave((HWND) winId());
//    m_a.reset(new A(m_waveDevice.get()));
    QAbstractEventDispatcher::instance(0)->installNativeEventFilter(new A(m_waveDevice.get()));

    m_waveInfo.reset(new WaveInfo());
//    m_waveInfo->load("waves/first.wav");

    m_waveInfo->setData(
        200000,
        SineWaveIterator<short>(100, 440),
        SineWaveIterator<short>(100, 440));
    m_waveInfo->save("waves/sine440.wav");

    m_waveInfo->setData(
        200000,
        TriangularWaveIterator<short>(100, 440),
        TriangularWaveIterator<short>(100, 440));
    m_waveInfo->save("waves/triangular440.wav");

    m_waveInfo->setData(
        200000,
        SawWaveIterator<short>(100, 440),
        SawWaveIterator<short>(100, 440));
    m_waveInfo->save("waves/saw440.wav");

    m_waveInfo->setData(
        200000,
        SquareWaveIterator<short>(100, 440),
        SquareWaveIterator<short>(100, 440));
    m_waveInfo->save("waves/square440.wav");

    m_waveInfo->setData(
        200000,
        PulseWaveIterator<short>(100, 440),
        PulseWaveIterator<short>(100, 440));
    m_waveInfo->save("waves/pulse440.wav");

    auto addIt = new AddWaveIterator<short>();
    addIt->add(new SineWaveIterator<short>(10, 55));
    addIt->add(new SineWaveIterator<short>(20, 110));
    addIt->add(new SineWaveIterator<short>(20, 220));
    addIt->add(new SineWaveIterator<short>(20, 440));
    addIt->add(new SineWaveIterator<short>(100, 880));
    addIt->add(new SineWaveIterator<short>(100, 1860));
    m_waveInfo->setData(
        200000,
        *addIt,
        *addIt);
    m_waveInfo->save("waves/temp.wav");

    MultWaveIterator<short> multIt;
    multIt.add(addIt);
//    multIt.add(new SineWaveIterator<short>(100, 1000));
    multIt.add(new SineWaveIterator<short>(100, 2, 441000));
    m_waveInfo->setData(
        200000,
        multIt,
        multIt);
    m_waveInfo->save("waves/temp.wav");
//    m_waveInfo->show();

//    m_waveInfo->setData(
//        200000,
//        SineWaveIterator<short>(50, 1860),
//        SineWaveIterator<short>(50, 880));

    m_waveInfo->load("waves/Mozart Alla Turca.wav");
    m_waveDevice->open(*m_waveInfo);

    setWidget(new GraphCanvas(this));
    widget()->resize(2000, 1000);

    std::cout << "\t" << horizontalScrollBar()->minimum()
        << " -> " << horizontalScrollBar()->maximum() << std::endl;
    std::cout << "\t" << verticalScrollBar()->minimum()
        << " -> " << verticalScrollBar()->maximum() << std::endl;
    std::cout << "\t" << horizontalScrollBar()->value()
        << ", " << verticalScrollBar()->value() << std::endl;
}

WaveEditor::~WaveEditor() {
}

void WaveEditor::load(const std::string& file) {
//    m_modelRoot->load(fstream);
//    parentWidget()->parentWidget()->update();
//    QSound s(file.c_str());
//    s.play();
//    QSound::play(file.c_str());
//    QThread::sleep(1000);
//    Sleep(1000);
//    WaveDevice w;
    m_waveInfo->load(file);

    int dx = 1;
    horizontalScrollBar()->setValue(0);
    widget()->resize(dx * m_waveInfo->size() / 4, height());
//    m_waveDevice->open(*m_waveInfo);
//    m_waveDevice->load(file);
}

void WaveEditor::save(const std::string& file) {
    m_waveInfo->save(file);
}

void WaveEditor::undo() {
//    m_commandHistory.undo();
}

void WaveEditor::redo() {
//    m_commandHistory.redo();
    update();
}

//public slots
void WaveEditor::playButtonClicked() {
    m_waveDevice->stop();
    m_waveDevice->open(*m_waveInfo);
    m_waveDevice->start();
//    resize(1000, 100);
}
void WaveEditor::stopButtonClicked() {
    m_waveDevice->stop();

    std::cout << "\t" << horizontalScrollBar()->minimum()
        << " -> " << horizontalScrollBar()->maximum() << std::endl;
    std::cout << "\t" << verticalScrollBar()->minimum()
        << " -> " << verticalScrollBar()->maximum() << std::endl;
    std::cout << "\t" << horizontalScrollBar()->value()
        << ", " << verticalScrollBar()->value() << std::endl;

    auto bar = horizontalScrollBar();
    int max = bar->maximum();
    int min = bar->minimum();
    int value = bar->value();
    std::cout << "value: " << value << std::endl;
//    bar->setMaximum(max + 100);

    auto canvas = widget();
    int width = canvas->width();
    int height = canvas->height();
    canvas->resize(width + 100, height);
    bar->setValue(value + 100);
}

//protected
//void WaveEditor::resizeEvent(QResizeEvent *event) {
//    m_converter.setSize(event->size());
//}
//void WaveEditor::paintEvent(QPaintEvent* /*event*/) {
//    std::cout << "WaveEditor::paintEvent(): " << std::endl;
//    QPainter painter(this);
//    for (auto it = m_waveInfo->iterator(); it.hasNext(); it.advace(4)) {
//        std::cout << *(short*) it.get() << std::endl;
//    }
//}

void WaveEditor::mousePressEvent(QMouseEvent* event) {
    QPoint mousePos = event->pos();
    QPoint pos(mousePos.x(), mousePos.y());

    if (Qt::LeftButton == event->button()) {
//        m_waveDevice->stop();
//        m_waveDevice->open(*m_waveInfo);
//        m_waveDevice->start();
    } else
    if (Qt::RightButton == event->button()) {
//        m_waveDevice->stop();
    }

}

//void WaveEditor::mouseReleaseEvent(QMouseEvent*) {
//}
//
//void WaveEditor::mouseMoveEvent(QMouseEvent* event) {
//    QPoint mousePos = event->pos();
//    QPoint pos(mousePos.x(), mousePos.y());
//
//    CoordinateConverter::PointD currentPos = m_converter.convert(pos);
////    std::cout << currentPos.x << ", " << currentPos.y << std::endl;
//
//    if (Qt::LeftButton & event->buttons()) {
//        double tx = currentPos.x - m_mousePosition.x;
//        double ty = currentPos.y - m_mousePosition.y;
//
//        for (auto it : m_selection) {
//            Translator::translate(it, tx, ty);
//        }
//    } else
//    if (Qt::RightButton & event->buttons()) {
//        CoordinateConverter::PointD origin = m_converter.getOrigin();
//
//        CoordinateConverter::PointD newPos {
//            origin.x - (currentPos.x - m_mousePosition.x),
//            origin.y - (currentPos.y - m_mousePosition.y) };
//        m_converter.setOrigin(newPos);
//    }
//
//    m_mousePosition = m_converter.convert(pos);
////    std::cout << currentPos.x - m_mousePosition.x << ", " << currentPos.y - m_mousePosition.y << std::endl;
//    update();
//}
//
//void WaveEditor::wheelEvent(QWheelEvent* event) {
//    m_converter.setRatio(
//            m_converter.getRatio() * (1.0 + event->delta() / 1200.0));
//    update();
//}

void WaveEditor::closeEvent(QCloseEvent* /*event*/) {
//    closeWave();
}

WaveEditor::GraphCanvas::GraphCanvas(WaveEditor* outer)
        : m_outer(outer)
{
    setBackgroundRole(QPalette::BrightText);
}
WaveEditor::GraphCanvas::~GraphCanvas() {
}

void WaveEditor::GraphCanvas::resizeEvent(QResizeEvent* event) {
    std::cout << "resizeEvent(): " << std::endl;
    std::cout << "\t" << m_outer->horizontalScrollBar()->minimum()
        << " -> " << m_outer->horizontalScrollBar()->maximum() << std::endl;
    std::cout << "\t" << m_outer->verticalScrollBar()->minimum()
        << " -> " << m_outer->verticalScrollBar()->maximum() << std::endl;
    std::cout << "\t" << m_outer->horizontalScrollBar()->value()
        << ", " << m_outer->verticalScrollBar()->value() << std::endl;
}
void WaveEditor::GraphCanvas::paintEvent(QPaintEvent* /*event*/) {
    std::cout << "paintEvent(): " << std::endl;
    QPainter painter(this);
    int x = m_outer->horizontalScrollBar()->value();
    int dx = 1;
    int centerY = height() / 2;
    int first = x / dx ;
    int num = m_outer->viewport()->width() / dx;
    std::cout << "waveInfo->size(): " << m_outer->m_waveInfo->size() << std::endl;
    std::cout << "scrollbar(): " << m_outer->horizontalScrollBar()->value()
            << " -> " << 4 * num + first << std::endl;
    std::unique_ptr<QPoint[]> points = std::unique_ptr<QPoint[]>(new QPoint[num]);
    for (int i=0; i< num; ++i) {
        points[i] = QPoint(x, -0.01 * (*(short*) (m_outer->m_waveInfo.get() + 4 * i + first)) + centerY);
        x += dx;
    }
    painter.drawPolyline(points.get(), num);
}

} /* namespace wavedit */

