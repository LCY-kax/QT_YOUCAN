#include "openfile.h"

void showFileInFolder(const QString &filePath) {
    QStringList param;
#if defined(Q_OS_WIN)
    param << "/select"
          << "," << QDir::toNativeSeparators(filePath);
    QProcess::startDetached("explorer.exe", param);
#elif defined(Q_OS_MAC)
    param << "-e"
          << QString("tell application \"Finder\" to reveal POSIX file \"%1\"")
                 .arg(filePath);
    QProcess::execute(QLatin1String("/usr/bin/osascript"), param);
    param.clear();
    param << "-e"
          << "tell application \"Finder\" to activate";
    QProcess::execute("/usr/bin/osascript", param);
#else
    QFileInfo finfo(filePath);
    QString dest = "array:string:'" + QUrl::fromLocalFile(filePath).url() + "'\t";
    QString tmpfile(/*DirHandler::GetLogPath()*/QDir::currentPath() + "open_folder.sh");
    QString targetType = finfo.isDir()
                             ? "org.freedesktop.FileManager1.ShowFolders\t"
                             : "org.freedesktop.FileManager1.ShowItems\t";
    QFile openfd(tmpfile);
    if (openfd.open(QFile::WriteOnly)) {
        QTextStream out(&openfd);
        out << "#!/bin/bash\n\n"
            << "dbus-send\t"
            << "--session\t"
            << "--print-reply\t"
            << "--dest=org.freedesktop.FileManager1\t"
            << "--type=method_call\t"
            << "/org/freedesktop/FileManager1\t" << targetType << dest
            << "string:''\n";
        openfd.close();
    }
    openfd.setPermissions(QFileDevice::ExeOwner | QFileDevice::ExeUser |
                          QFileDevice::ExeGroup | QFileDevice::ExeOther |
                          QFileDevice::ReadOwner | QFileDevice::WriteGroup |
                          QFileDevice::WriteOwner);
    QProcess pro;
    pro.execute(tmpfile);
    pro.waitForFinished();
    openfd.remove();
#endif
}
