//========================================
// IconEditor.cpp
//
//  Created on: 2013/12/07
//      Author: you
//========================================

#include "IconEditor.h"
#include <QtWidgets/qapplication.h>
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>

#include <iostream>

#include "ICommand.h"

//---> FillRectCommand
class FillRectCommand: public ICommand {
public:
    virtual ~FillRectCommand();
    virtual bool canExecute() override;
    virtual bool canUndo() override;
    virtual void execute() override;
    virtual void undo() override;
    virtual void redo() override;

    static FillRectCommand* create(QImage* image, const QPoint& pos, QRgb rgb);

private:
    FillRectCommand(QImage* image, const QPoint& pos, QRgb rgb);
    QImage* m_image;
    QPoint m_pos;
    QRgb m_newRgb;
    QRgb m_oldRgb;

};

FillRectCommand* FillRectCommand::create(QImage* image, const QPoint& pos, QRgb rgb) {
    FillRectCommand* result = nullptr;
    if (image->pixel(pos) != rgb) {
        result = new FillRectCommand(image, pos, rgb);
    }
    return result;
}

FillRectCommand::FillRectCommand(QImage* image, const QPoint& pos, QRgb rgb)
        : m_image(image),
                m_pos(pos),
                m_newRgb(rgb),
                m_oldRgb(m_image->pixel(m_pos))
{
    std::cout << "new: " << this << std::endl;
}

FillRectCommand::~FillRectCommand() {
    std::cout << "delete: " << this << std::endl;
}

bool FillRectCommand::canExecute() {
    return m_image->pixel(m_pos) != m_newRgb;
}

bool FillRectCommand::canUndo() {
    return true;
}

void FillRectCommand::execute() {
    m_image->setPixel(m_pos, m_newRgb);
}

void FillRectCommand::undo() {
    m_image->setPixel(m_pos, m_oldRgb);
}

void FillRectCommand::redo() {
    m_image->setPixel(m_pos, m_newRgb);
}
//<--- FillRectCommand

IconEditor::IconEditor(QWidget* parent)
        : QWidget(parent),
                m_filepath(""),
                m_image(16, 16, QImage::Format_RGB32),
                m_zoom(16)
//                m_historyIndex(0)
{
    for (int i = 0; i < m_image.width(); ++i) {
        for (int j = 0; j < m_image.height(); ++j) {
            m_image.setPixel(i, j, 0x00FFFFFF);
        }
    }

    m_color[0].setRgb(qRgb(0, 0, 0));
    m_color[1].setRgb(qRgb(255, 255, 255));

    QBoxLayout* layout_0 = new QHBoxLayout();
    setLayout(layout_0);
    {
        layout_0->addStretch(300);

        QBoxLayout* layout_1 = new QVBoxLayout();
        layout_0->addLayout(layout_1);
        {
            for (int i = 0; i < 2; ++i) {
                QBoxLayout* layout_2 = new QHBoxLayout();
                layout_1->addLayout(layout_2);
                {
                    for (int j = 0; j < 3; ++j) {
                        m_rgbs[i][j] = new QSpinBox();
                        layout_2->addWidget(m_rgbs[i][j]);

                        m_rgbs[i][j]->setRange(0, 255);
                        m_rgbs[i][j]->setValue(i == 0 ? 0 : 255);
                        connect(m_rgbs[i][j], SIGNAL(valueChanged(int)), this, SLOT(setColor(int)));
                    }
                }
            }
        }
    }
}

IconEditor::~IconEditor()
{
}

void IconEditor::load(const QString& filepath) {
    m_image.load(filepath);
//    QSize size = m_image.size();
//    std::cout << size.width() << ", " << size.height() << std::endl;
//    for (int i = 0; i < size.width(); ++i) {
//        for (int j = 0; j < size.height(); ++j) {
//                std::cout << m_image.pixel(i, j) << " ";
//                m_image.setPixel(i, j, 0x00FFFFFF);
//        }
//            std::cout << std::endl;
//    }
}

void IconEditor::save(const QString& filepath, const char* format, int quality) {
    m_image.save(filepath, format, quality);
}

void IconEditor::undo() {
    m_commandHistory.undo();
    update();
}

void IconEditor::redo() {
    m_commandHistory.redo();
    update();
}

//public slots
void IconEditor::setColor(int value) {
    QObject* sender = QObject::sender();
    if (sender == m_rgbs[0][0]) {
        m_color[0].setRed(value);
        update();
    } else if (sender == m_rgbs[0][1]) {
        m_color[0].setGreen(value);
        update();
    } else if (sender == m_rgbs[0][2]) {
        m_color[0].setBlue(value);
        update();
    } else if (sender == m_rgbs[1][0]) {
        m_color[1].setRed(value);
        update();
    } else if (sender == m_rgbs[1][1]) {
        m_color[1].setGreen(value);
        update();
    } else if (sender == m_rgbs[1][2]) {
        m_color[1].setBlue(value);
        update();
    }
}

//protected
void IconEditor::paintEvent(QPaintEvent* event) {
    int imageWidth = m_image.width();
    int imageHeight = m_image.height();

    QPainter painter(this);
    for (int i = 0; i < m_image.width(); ++i) {
        for (int j = 0; j < m_image.height(); ++j) {
            //std::cout << i << ", " << j << ": " << m_image.pixel(i, j) << std::endl;
            QRect rect(m_zoom * i, m_zoom * j, m_zoom, m_zoom);
            //painter.fillRect(rect, Qt::white);
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgb(m_image.pixel(i, j));
                painter.fillRect(rect, color);
            }
        }
    }
    if (m_zoom > 3) {
        painter.setPen(Qt::black);
        for (int i = 0; i <= imageWidth; ++i) {
            painter.drawLine(m_zoom * i, 0, m_zoom * i, m_zoom * imageHeight);
        }
        for (int i = 0; i <= imageHeight; ++i) {
            painter.drawLine(0, m_zoom * i, m_zoom * imageWidth, m_zoom * i);
        }
    }

    int size = 64;
    painter.fillRect(QRect(m_zoom * imageWidth + 10, 0 * (size + 2), size, size), m_color[0]);
    painter.fillRect(QRect(m_zoom * imageWidth + 10, 1 * (size + 2), size, size), m_color[1]);
}

void IconEditor::mousePressEvent(QMouseEvent* event) {
    QPoint mousePos = event->pos();
    QPoint pos(mousePos.x() / m_zoom, mousePos.y() / m_zoom);

    if (pos.x() >= 0
            && pos.y() >= 0
            && pos.x() < m_image.width()
            && pos.y() < m_image.height()) {

        std::cout << pos.x() << ", " << pos.y() << ": " << m_image.pixel(pos) << std::endl;

        if (Qt::LeftButton == event->button()) {
            if (Qt::CTRL & QApplication::keyboardModifiers()) {
                m_color[0].setRgb(m_image.pixel(pos));
            } else {
                ICommand* fillRectCommand = FillRectCommand::create(&m_image, pos, m_color[0].rgb());
                if (fillRectCommand != nullptr) {
//                    operateCommand(fillRectCommand);
                    m_commandHistory.execute(fillRectCommand);
                }
            }
        } else
        if (Qt::RightButton == event->button()) {
            if (Qt::CTRL & QApplication::keyboardModifiers()) {
                m_color[1].setRgb(m_image.pixel(pos));
            } else {
                ICommand* fillRectCommand = FillRectCommand::create(&m_image, pos, m_color[1].rgb());
                if (fillRectCommand != nullptr) {
//                    operateCommand(fillRectCommand);
                    m_commandHistory.execute(fillRectCommand);
                }
            }
        }

        setFocus();
        update();
    }
}

void IconEditor::mouseReleaseEvent(QMouseEvent*) {
}

void IconEditor::mouseMoveEvent(QMouseEvent* event) {
    QPoint mousePos = event->pos();
    QPoint pos(mousePos.x() / m_zoom, mousePos.y() / m_zoom);

    if (pos.x() >= 0
            && pos.y() >= 0
            && pos.x() < m_image.width()
            && pos.y() < m_image.height()) {

//        std::cout << pos.x() << ", " << pos.y() << ": " << m_image.pixel(pos) << std::endl;

        if (Qt::LeftButton & event->buttons()) {
            ICommand* fillRectCommand = FillRectCommand::create(&m_image, pos, m_color[0].rgb());
            if (fillRectCommand != nullptr) {
//                operateCommand(fillRectCommand);
                m_commandHistory.execute(fillRectCommand);
            }
        } else
        if (Qt::RightButton & event->buttons()) {
            ICommand* fillRectCommand = FillRectCommand::create(&m_image, pos, m_color[1].rgb());
            if (fillRectCommand != nullptr) {
//                operateCommand(fillRectCommand);
                m_commandHistory.execute(fillRectCommand);
            }
        }
        update();
    }
}

void IconEditor::wheelEvent(QWheelEvent* event) {
    int newZoom = m_zoom + event->delta() / 120;
    if (newZoom > 0) {
        m_zoom = newZoom;
        update();
    }
}

