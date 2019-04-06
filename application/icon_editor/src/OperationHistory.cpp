//========================================
// OperationHistory.cpp
//
//  Created on: 2013/12/11
//      Author: you
//========================================

#include "OperationHistory.h"

#include <iostream>

#include "ICommand.h"

OperationHistory::OperationHistory()
        : m_historyList(),
                m_historyIndex(0)
{
}

OperationHistory::~OperationHistory() {
}
void OperationHistory::execute(ICommand* command) {
    for (int i = m_historyList.size() - 1; i >= m_historyIndex; --i) {
        delete m_historyList[i];
        m_historyList.pop_back();
        std::cout << "delete: " << i << " / " << m_historyList.size() << std::endl;
    }
    m_historyList.push_back(command);
    ++m_historyIndex;
    command->execute();
}

void OperationHistory::undo() {
    if (m_historyIndex > 0) {
        --m_historyIndex;
        m_historyList[m_historyIndex]->undo();

        std::cout << "undo: " << m_historyIndex << std::endl;
    }
}

void OperationHistory::redo() {
    if (m_historyIndex < m_historyList.size()) {
        m_historyList[m_historyIndex]->redo();
        ++m_historyIndex;

        std::cout << "redo: " << m_historyIndex << std::endl;
    }
}

