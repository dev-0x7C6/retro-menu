#include "process-schedule.hpp"

#include <QCoreApplication>
#include <QProcess>

ProcessSchedule::ProcessSchedule(const char *program, QObject *parent)
		: QObject(parent)
		, m_program(program) {}

void ProcessSchedule::schedule(const string &proc) {
	m_scheduledCommands << proc;
}

#include <QDebug>

ProcessSchedule::~ProcessSchedule() {
	for (auto &&proc : m_scheduledCommands) {
		QProcess process;
		process.setProgram("/bin/sh");
		process.setArguments({"-c", QString("%1; %2").arg(proc, m_program)});
		qDebug() << process.arguments();
		process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
		qint64 pid{};
		process.startDetached(&pid);
	}
}
