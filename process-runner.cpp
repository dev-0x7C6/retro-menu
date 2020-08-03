#include "process-runner.hpp"

#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

void ProcessRunner::start(const string &proc) {
	QProcess process;
	process.setProgram("/bin/sh");
	process.setArguments({"-c", QString("%1; %2").arg(proc, QCoreApplication::applicationFilePath())});
	process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
	qint64 pid{};
	process.startDetached(&pid);
}
