//========================================
// OperationHistory.h
//
//  Created on: 2013/12/11
//      Author: you
//========================================

#ifndef OPERATIONHISTORY_H_
#define OPERATIONHISTORY_H_

#include <vector>

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

#endif /* OPERATIONHISTORY_H_ */
