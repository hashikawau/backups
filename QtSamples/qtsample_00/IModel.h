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

class QWidget;

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

#endif /* IMODEL_H_ */
