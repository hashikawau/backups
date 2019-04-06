//========================================
// OperationHistory.h
//
//  Created on: 2013/12/11
//      Author: you
//========================================

#ifndef OPERATIONHISTORY_H_
#define OPERATIONHISTORY_H_

#include <vector>

namespace util {

class ICommand;

/*
 *
 */
class OperationHistory {
public:
    OperationHistory();
    ~OperationHistory();

    void execute(ICommand* command);
    void undo();
    void redo();

private:
    std::vector<ICommand*> m_historyList;
    int m_historyIndex;

};

} /* namespace util */

#endif /* OPERATIONHISTORY_H_ */
