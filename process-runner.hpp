#pragma once

#include <QObject>

#include <common.hpp>

class ProcessRunner : public QObject {
	Q_OBJECT
public:
	ProcessRunner(QObject *parent = nullptr)
			: QObject(parent){};
	virtual ~ProcessRunner() = default;

	Q_INVOKABLE void start(const QString &);
};
