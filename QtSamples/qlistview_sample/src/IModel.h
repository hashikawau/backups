//========================================
// IModel.h
//
//  Created on: 2013/12/19
//      Author: you
//========================================

#ifndef IMODEL_H_
#define IMODEL_H_

#include <string>
#include <vector>
#include <functional>

//class QWidget;
#include <QtWidgets/qwidget.h>

class QLineEdit;

namespace sample {

class IModel;
class EditPage4ModelA;

class ModelRoot {
public:
    ModelRoot();
    ~ModelRoot();

    int size() const;
    IModel* get(int index) const;
    void add(IModel* model);
    void remove(IModel* model);

private:
    std::vector<IModel*> m_models;
};

/*
 *
 */
class IModel {
public:
//    IModel();
    virtual ~IModel() =0;

    virtual void process() =0;

    virtual const std::string toString() =0;
    virtual QWidget* getEditPage() =0;
};

class ModelA: public IModel {
public:
    ModelA(double x);
    virtual ~ModelA();
    virtual void process() override;

    virtual const std::string toString() override;
    virtual QWidget* getEditPage() override;

    double x() {
        return m_x;
    }
    void setX(double value) {
        m_x = value;
    }

private:
    double m_x;
};

class ModelB: public IModel {
public:
    ModelB(double x, double y);
    virtual ~ModelB();
    virtual void process() override;

    virtual const std::string toString() override;
    virtual QWidget* getEditPage() override;

    double x() {
        return m_x;
    }
    void setX(double value) {
        m_x = value;
    }
    double y() {
        return m_y;
    }
    void setY(double value) {
        m_y = value;
    }

private:
    double m_x;
    double m_y;
};

class EditPage4ModelA: public QWidget {
Q_OBJECT

public:
    static EditPage4ModelA* getInstance(ModelA* model);
    virtual ~EditPage4ModelA();

public slots:
    void setX(const QString& text);

private:
    EditPage4ModelA(QWidget* parent = 0);
    void setModel(ModelA* model);

private:
    static EditPage4ModelA* s_instance;
    ModelA* m_model;
    QLineEdit* m_textX;

};

class EditPage4ModelB: public QWidget {
Q_OBJECT

public:
    static EditPage4ModelB* getInstance(ModelB* model);
    static void setUpdateFunctor();
    virtual ~EditPage4ModelB();

public slots:
    void setX(const QString& text);
    void setY(const QString& text);

private:
    EditPage4ModelB(QWidget* parent = 0);
    void setModel(ModelB* model);

private:
    static EditPage4ModelB* s_instance;
    ModelB* m_model;
    QLineEdit* m_textX;
    QLineEdit* m_textY;
    std::function<void()> m_updateFunctor;

};

} /* namespace sample */

#endif /* IMODEL_H_ */
