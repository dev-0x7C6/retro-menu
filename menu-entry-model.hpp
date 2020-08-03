#pragma once

#include <QAbstractListModel>
#include <menu-entry.hpp>

class MenuEntryModel final : public QAbstractListModel {
	Q_OBJECT
	Q_ENUMS(EntryRole)
public:
	explicit MenuEntryModel() = default;
	virtual ~MenuEntryModel() = default;

	enum EntryRole {
		PlatformRole = Qt::UserRole,
		ExecuteRole,
		FilePathRole,
		FileCoverRole,
		NameRole,
		UsageCountRole
	};

	Q_INVOKABLE QVariant data(int i, int role) const;

	virtual int rowCount(const QModelIndex &) const override final;
	virtual QVariant data(const QModelIndex &index, int role) const override final;
	virtual QHash<int, QByteArray> roleNames() const override;

	virtual bool setData(const QModelIndex &index, const QVariant &value, int role) override;

	void emplace(menu_entry &&game);

private:
	std::vector<menu_entry> m_games;
};
