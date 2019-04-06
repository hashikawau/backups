//========================================
// ModelRoot.h
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#ifndef MODELROOT_H_
#define MODELROOT_H_

#include <vector>
#include <list>
#include <memory>

#include "IShape.h"

namespace geoedit {

/*
 *
 */
class ModelRoot {
public:
    ModelRoot();
    ~ModelRoot();

    int size() const {
        return m_shapes.size();
    }
    IShape* get(int index) const {
        auto it = m_shapes.begin();
        for(int i=0; i< index; ++i){
            ++it;
        }
        return (*it).get();
    }
    void add(IShape* value) {
        m_shapes.push_front(std::unique_ptr<IShape>(value));
    }
    int remove(IShape* value) {
        int i = 0;
        for (auto it = m_shapes.begin(); it != m_shapes.end(); ++it) {
            if ((*it).get() == value) {
                m_shapes.erase(it);
                break;
            }
            ++i;
        }
        return i;
    }

    std::list<std::unique_ptr<IShape>>& getShapes() {
        return m_shapes;
    }

    void addModelChangeListner(std::function<void()> listener){
        m_modelChangeListners.push_back(listener);
    }
    void addSelectionChangeListner(std::function<void(const std::vector<IShape*>&)> listener){
        m_selectionChangeListners.push_back(listener);
    }
    void setSelection(const std::vector<IShape*>& selection){
        for(auto it: m_selectionChangeListners){
            it(selection);
        }
    }

    void load(std::ifstream& fstream);
    void save(std::ofstream& fstream);

private:
    void modelChanged(){
        for(auto& it: m_modelChangeListners){
            it();
        }
    }

private:
    std::list<std::unique_ptr<IShape> > m_shapes;

    std::vector<std::function<void()> > m_modelChangeListners;
    std::vector<std::function<void(const std::vector<IShape*>&)> > m_selectionChangeListners;

};

} /* namespace geoedit */

#endif /* MODELROOT_H_ */
