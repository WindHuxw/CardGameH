#include "UndoModel.h"
#include "./views/CardView.h"





bool UndoModel::stackPush(ActionData a)
{
    _undoStack.push(a);
    return true;
}


bool UndoModel::stackPop()
{
    if (!_undoStack.empty())
    {
        _undoStack.pop();
        return true;
    }
    return false;
}


bool UndoModel::isEmpty()
{
    return _undoStack.empty();
}

ActionData UndoModel::undo()
{
    if (_undoStack.empty())
    {
        ActionData tmp;
        tmp.area = -1;
            return tmp;
    }
    
    auto reverse = _undoStack.top();
    _undoStack.pop();
    return reverse;
}