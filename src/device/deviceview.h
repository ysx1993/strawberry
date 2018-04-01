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

#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include "config.h"

#include <memory>

#include "core/song.h"
#include "collection/collectionview.h"
#include "widgets/autoexpandingtreeview.h"

class QAction;
class QMenu;
class QSortFilterProxyModel;

class Application;
class DeviceManager;
class DeviceProperties;
class CollectionModel;
class MergedProxyModel;

class DeviceItemDelegate : public CollectionItemDelegate {
 public:
  DeviceItemDelegate(QObject *parent);

  static const int kIconPadding;

  void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class DeviceView : public AutoExpandingTreeView {
  Q_OBJECT

 public:
  DeviceView(QWidget *parent = nullptr);
  ~DeviceView();

  void SetApplication(Application *app);

 protected:
  void contextMenuEvent(QContextMenuEvent*);
  void mouseDoubleClickEvent(QMouseEvent *event);

 private slots:
  // Device menu actions
  void Connect();
  void Unmount();
  void Forget();
  void Properties();

  // Collection menu actions
  void Load();
  void AddToPlaylist();
  void OpenInNewPlaylist();
#ifdef HAVE_GSTREAMER
  void Organise();
  void Delete();
#endif

  void DeviceConnected(int row);
  void DeviceDisconnected(int row);

#ifdef HAVE_GSTREAMER
  void DeleteFinished(const SongList &songs_with_errors);
#endif

  // AutoExpandingTreeView
  bool CanRecursivelyExpand(const QModelIndex &index) const;

 private:
  QModelIndex MapToDevice(const QModelIndex &merged_model_index) const;
  QModelIndex MapToCollection(const QModelIndex &merged_model_index) const;
  QModelIndex FindParentDevice(const QModelIndex &merged_model_index) const;
  SongList GetSelectedSongs() const;

 private:
  Application *app_;
  MergedProxyModel *merged_model_;
  QSortFilterProxyModel *sort_model_;

  std::unique_ptr<DeviceProperties> properties_dialog_;
#ifdef HAVE_GSTREAMER
  std::unique_ptr<OrganiseDialog> organise_dialog_;
#endif

  QMenu *device_menu_;
  QAction *eject_action_;
  QAction *forget_action_;
  QAction *properties_action_;

  QMenu *collection_menu_;
  QAction *load_action_;
  QAction *add_to_playlist_action_;
  QAction *open_in_new_playlist_;
  QAction *organise_action_;
  QAction *delete_action_;

  QModelIndex menu_index_;
};

#endif  // DEVICEVIEW_H