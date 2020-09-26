#include "icon-provider.hpp"

#include <QDirIterator>

auto preferred_ext_icon(const string_list &paths, const string_list &exts) -> std::optional<icon> {
	for (const auto &path : paths) {
		for (const auto &ext : exts)
			if (path.contains("." + ext))
				return QIcon(path);
	}

	return std::nullopt;
}

auto preferred_size_icon(const string_list &paths, std::initializer_list<int> sizes) -> std::optional<icon> {
	for (const auto &size : sizes)
		for (const auto &path : paths)
			if (path.contains(string::number(size) + "x" + string::number(size)))
				return QIcon(path);

	if (!paths.isEmpty())
		return QIcon(paths.last());

	return std::nullopt;
}

IconProvider::IconProvider(const string_list &search_paths) {
	for (const auto &path : search_paths) {
		dir_iterator it(path, QDir::Files, QDirIterator::Subdirectories);
		while (it.hasNext()) {
			file_info info(it.next());
			m_iconMap[info.baseName()] += info.absoluteFilePath();
		}
	}
}

auto IconProvider::getIcon(const string &id) -> icon {
	if (!m_iconMap.contains(id))
		return {};

	const auto &paths = m_iconMap[id];

	if (auto icon = preferred_ext_icon(paths, {"svg"}); icon.has_value())
		return icon.value();

	if (auto icon = preferred_size_icon(paths, {256, 128, 96, 64, 48, 32, 24, 22, 16}); icon.has_value())
		return icon.value();

	return {};
}
