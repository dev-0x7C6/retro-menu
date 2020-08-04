#pragma once

#include <QObject>
#include <QStringList>

#include <common.hpp>

class ProcessSchedule : public QObject {
	Q_OBJECT
public:
	ProcessSchedule(const char *argc, QObject *parent = nullptr);
	virtual ~ProcessSchedule();

	Q_INVOKABLE void schedule(const QString &);

private:
	QStringList m_scheduledCommands;
	const char *m_program;
};
