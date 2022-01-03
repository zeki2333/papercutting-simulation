#include"Python.h"
#include"QDebug"

//int initPython()
//{
//    Py_SetPythonHome(L"E:/APP/anaconda3");
//    Py_Initialize();
//    if(Py_IsInitialized())
//    {
//        qDebug("python 初始化成功");
//    }
//    PyObject* pModule = PyImport_ImportModule("hello");//.py文件名
//    if(!pModule)
//    {
//        qDebug()<<"cant open python file\n";
//    }
//    PyObject* pFunhello = PyObject_GetAttrString(pModule,"hello");//函数名
//    if(!pFunhello)
//    {
//        qDebug()<<"Get function hello failed\n";
//    }
//    PyObject_CallFunction(pFunhello,NULL);
//    Py_Finalize();
//}


