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

#include <QDirIterator>

#include "themeutils.h"

QVariant ThemeUtils::dirlist(QString dirPath, bool onlyImages)
{
    if (dirPath.isEmpty() || dirPath == "/")
        return QVariantList{};
    bool allowed = false;
    for (auto allowedDir: {
        DATADIR "/lightdm-webengine-greeter/themes",
        "/usr/share/backgrounds",
        "/usr/share/wallpapers",
        "/tmp"})
        if (QDir{dirPath}.canonicalPath().startsWith(allowedDir))
            allowed = true;
    if (!allowed)
        return QVariantList{};
    QStringList l;
    if (onlyImages)
    {
        QDirIterator it{dirPath, {"*.jpg", "*.jpeg", "*.png", "*.gif", "*.bmp", "*.webp"}, QDir::Files, QDirIterator::Subdirectories};
        while (it.hasNext())
            l << it.next();
    }
    else
    {
        QDirIterator it{dirPath};
        while (it.hasNext())
            l << it.next();
    }
    QStringList r;
    for (auto path: l)
    {
        int index = path.lastIndexOf("/contents/");
        if (index != -1)
        {
            auto d = path;
            d.chop(d.length() - index);
            QFileInfo f{d + "/metadata.desktop"};
            if (f.exists() && f.isFile())
            {
                QDir dir{d + "/contents/images"};
                if (path != dir.path() + "/" + dir.entryList(QDir::Files, QDir::Name).last())
                    continue;
            }
        }
        r << path;
    }
    return r;
}
