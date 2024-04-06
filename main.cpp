#include "widget.h"
#include "api.h"
#include <QApplication>
#include <QFileOpenEvent>
#ifdef Q_OS_WIN
#if _MSC_VER
#include <mindumpdef.h>
#include <minidumpapiset.h>
long  __stdcall CrashInfocallback(_EXCEPTION_POINTERS *pexcp)
{
#if QT_NO_DEBUG
    QString mode = "release";
#else
    QString mode = "debug";
#endif
    QString dirpath;
    QString filepath;
    dirpath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/"+QApplication::applicationName()+"/dmp";
    filepath = dirpath + "/" + QApplication::applicationName() + "_" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + "_" + mode +"_crash_dump.dmp";
    if(!QFileInfo(dirpath).isDir())
        QDir().mkpath(dirpath);
    HANDLE hDumpFile = ::CreateFile(
        (LPCWSTR)filepath.utf16(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if(hDumpFile != INVALID_HANDLE_VALUE)
    {
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pexcp;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        ::MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            hDumpFile,
            MiniDumpNormal,
            &dumpInfo,
            NULL,
            NULL
        );
    }
    QMessageBox box = QMessageBox(QMessageBox::Critical,"错误","应用无响应",QMessageBox::NoButton);
    QPushButton* b1 = box.addButton("等待响应",QMessageBox::RejectRole);
    QPushButton* b2 = box.addButton("终止进程",QMessageBox::AcceptRole);
    QPushButton* b3 = box.addButton("终止进程并定位到崩溃文件",QMessageBox::HelpRole);
    QObject::connect(b3,QOverload<bool>::of(&QPushButton::clicked),[filepath](){
        QString s = filepath;
        s.replace("/","\\");
        ShellExecuteW(NULL, L"open", L"explorer", QString("/select, \"%1\"").arg(s).toStdWString().c_str(), NULL, SW_SHOW);
        QApplication::exit(-1);
        Windows::killExecute(QFileInfo(QApplication::applicationFilePath()).fileName());

    });
    QObject::connect(b2,QOverload<bool>::of(&QPushButton::clicked),[filepath](){
        QApplication::exit(-1);
        Windows::killExecute(QFileInfo(QApplication::applicationFilePath()).fileName());
    });
    box.exec();
    return 0;
}
#endif
#endif
int main(int argc, char *argv[])
{
    //QJniObject::callStaticMethod<void>(javaPackage,"setFullScreen","()V");
#ifdef Q_OS_WIN
#if _MSC_VER
    ::SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)CrashInfocallback);
#endif
#endif
    QApplication a(argc, argv);
    a.setApplicationName("MediaPlayer");
    Widget w;
    w.show();
    return a.exec();
}
