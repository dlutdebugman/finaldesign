#ifndef PUBLICENUM
#define PUBLICENUM
enum ChosseResult
{
    ID_OK = 0,						// 确定;
    ID_CANCEL						// 取消;
};

enum MessageType
{
    MESSAGE_INFORMATION = 0,		// 提示信息;
    MESSAGE_WARNNING,				// 提示警告;
    MESSAGE_QUESTION,				// 提示询问;
    MESSAGE_INPUT					// 提示输入框;
};

enum MessageButtonType
{
    BUTTON_OK = 0,					// 只有确定按钮;
    BUTTON_OK_AND_CANCEL,			// 确定、取消按钮;
    BUTTON_CLOSE					// 关闭按钮;
};
#endif // PUBLICENUM

