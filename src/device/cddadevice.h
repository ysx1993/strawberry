/*
 * Strawberry Music Player
 * This file was part of Clementine.
 * Copyright 2010, David Sansome <me@davidsansome.com>
 *
 * Strawberry is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Strawberry is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Strawberry.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#ifndef CDDADEVICE_H
#define CDDADEVICE_H

#include "config.h"

#include <QMutex>

// These must come after Qt includes
#include <cdio/cdio.h>
#include <gst/audio/gstaudiocdsrc.h>

#include "cddasongloader.h"
#include "connecteddevice.h"
#include "core/song.h"
#include "musicbrainz/musicbrainzclient.h"

class CddaDevice : public ConnectedDevice {
  Q_OBJECT

 public:
  Q_INVOKABLE CddaDevice(const QUrl &url, DeviceLister *lister, const QString &unique_id, DeviceManager *manager, Application *app, int database_id, bool first_time);
  ~CddaDevice();

  void Init();
  void Refresh();
  bool CopyToStorage(const MusicStorage::CopyJob&) { return false; }
  bool DeleteFromStorage(const MusicStorage::DeleteJob&) { return false; }

  static QStringList url_schemes() { return QStringList() << "cdda"; }

signals:
  void SongsDiscovered(const SongList &songs);

 private slots:
  void SongsLoaded(const SongList &songs);

 private:
  CddaSongLoader cdda_song_loader_;
};

#endif
