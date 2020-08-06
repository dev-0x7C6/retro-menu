#pragma

#include <QIcon>
#include <QMap>

#include <common.hpp>

class IconProvider {
public:
	IconProvider(const string_list &search_paths);

	icon getIcon(const string &id);

private:
	QMap<string, string_list> m_iconMap;
};
