#include "process-schedule.hpp"

#include <QCoreApplication>
#include <QProcess>
#include <utility>

ProcessSchedule::ProcessSchedule(string program, QObject *parent)
		: QObject(parent)
		, m_program(std::move(program)) {}

void ProcessSchedule::schedule(const string &proc) {
	m_scheduledCommands << proc;
}

ProcessSchedule::~ProcessSchedule() {
	for (auto &&proc : m_scheduledCommands) {
		QProcess process;
		process.setProgram("/bin/sh");
		process.setArguments({"-c", QString("%1; %2").arg(proc, m_program)});
		process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
		qint64 pid{};
		process.startDetached(&pid);
	}
}
