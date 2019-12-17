/*
 * This file is part of WebEngine Greeter
 * Copyright (C) 2019  Matija Skala <mskala@gmx.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef THEMEUTILS_H
#define THEMEUTILS_H

#include <QVariant>

class ThemeUtils : public QObject
{
    Q_OBJECT

public Q_SLOTS:
    QVariant dirlist(QString dirPath, bool onlyImages);
};

#endif // THEMEUTILS_H
