#pragma once

#include <QObject>
#include <QStringList>

#include <common.hpp>

class ProcessSchedule : public QObject {
	Q_OBJECT
public:
	ProcessSchedule(string program, QObject *parent = nullptr);
	virtual ~ProcessSchedule();

	Q_INVOKABLE void schedule(const QString &);

private:
	string_list m_scheduledCommands;
	const string m_program;
};
