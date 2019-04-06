//========================================
// WaveEditor.h
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#ifndef WAVEEDITOR_H_
#define WAVEEDITOR_H_

#include <QtWidgets/qscrollarea.h>

//#include <fstream>
#include <memory>

#include "WaveDevice.h"

//#include "model/ModelRoot.h"
//#include "util/CoordinateConverter.h"
//#include "util/OperationHistory.h"

namespace wavedit {

/*
 *
 */
class WaveEditor: public QScrollArea {
Q_OBJECT

private:
    class GraphCanvas: public QWidget {
    public:
        GraphCanvas(WaveEditor* outer);
        virtual ~GraphCanvas() ;
    protected:
        virtual void resizeEvent(QResizeEvent* event);
        virtual void paintEvent(QPaintEvent* event);

    private:
        WaveEditor* m_outer;

    };

public:
    explicit WaveEditor(/*ModelRoot* modelRoot,*/QWidget* parent = 0);
    virtual ~WaveEditor();

    void load(const std::string& file);
    void save(const std::string& file);
    void undo();
    void redo();

public slots:
    void playButtonClicked();
    void stopButtonClicked();

protected:
//    virtual void resizeEvent(QResizeEvent *event);
//    virtual void paintEvent(QPaintEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    //    virtual void mouseReleaseEvent(QMouseEvent* event);
//    //virtual void mouseDoubleClickEvent(QMouseEvent* event);
//    virtual void mouseMoveEvent(QMouseEvent* event);
//    virtual void wheelEvent(QWheelEvent* event);
    virtual void closeEvent(QCloseEvent* event);

private:
//    static CoordinateConverter::PointD m_mousePosition;
//
//    ModelRoot* m_modelRoot;
//    CoordinateConverter m_converter;
//    std::vector<IShape*> m_selection;
//
//    util::OperationHistory m_commandHistory;

    std::unique_ptr<WaveDevice> m_waveDevice;

    std::unique_ptr<WaveInfo> m_waveInfo;

};

} /* namespace wavedit */

#endif /* WAVEEDITOR_H_ */
