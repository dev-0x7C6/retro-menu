#pragma once

class QDir;
class QDirIterator;
class QFile;
class QFileInfo;
class QIcon;
class QSettings;
class QString;
class QStringList;

template<class key_t, class value_t>
class QMap;

template<class key_t, class value_t>
using map = QMap<key_t, value_t>;

template<class key_t>
class QSet;

template<class key_t>
using set = QSet<key_t>;

using dir = QDir;
using dir_iterator = QDirIterator;
using file = QFile;
using file_info = QFileInfo;
using icon = QIcon;
using settings = QSettings;
using string = QString;
using string_list = QStringList;
