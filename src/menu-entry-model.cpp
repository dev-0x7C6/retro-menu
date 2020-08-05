#include "menu-entry-model.hpp"

QVariant MenuEntryModel::data(int i, int role) const {
	return data(index(i, 0), role);
}

int MenuEntryModel::rowCount(const QModelIndex &) const {
	return static_cast<int>(m_games.size());
}

QVariant MenuEntryModel::data(const QModelIndex &index, int role) const {
	const auto &entry = m_games.at(static_cast<std::size_t>(index.row()));

	switch (role) {
		case EntryRole::ExecuteRole: return entry.exec;
		case EntryRole::NameRole: return entry.name;
		case EntryRole::PlatformRole: return entry.platform;
		case EntryRole::FileCoverRole: return entry.icon;
		case EntryRole::UsageCountRole: return entry.usage_count;
	}

	return {};
}

QHash<int, QByteArray> MenuEntryModel::roleNames() const {
	return {{PlatformRole, "platform"}, {ExecuteRole, "exec"}, {FilePathRole, "rom"}, {FileCoverRole, "cover"}, {NameRole, "name"}, {UsageCountRole, "usageCount"}};
}

bool MenuEntryModel::setData(const QModelIndex &index, const QVariant &value, int role) {
	if (EntryRole::UsageCountRole == role) {
		m_games[static_cast<std::size_t>(index.row())].usage_count++;
		return true;
	}

	return false;
}

void MenuEntryModel::emplace(menu_entry &&game) {
	m_games.emplace_back(std::move(game));
}
