//========================================
// ICommand.h
//
//  Created on: 2013/12/11
//      Author: you
//========================================

#ifndef ICOMMAND_H_
#define ICOMMAND_H_

namespace util{

/*
 *
 */
class ICommand {
public:
    virtual ~ICommand() =0;

    virtual bool canExecute() =0;
    virtual bool canUndo() =0;
    virtual void execute() =0;
    virtual void undo() =0;
    virtual void redo() =0;
};

} /* namespace util */

#endif /* ICOMMAND_H_ */
