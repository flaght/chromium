// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_TRAY_SYSTEM_TRAY_ITEM_H_
#define ASH_SYSTEM_TRAY_SYSTEM_TRAY_ITEM_H_
#pragma once

#include "ash/ash_export.h"
#include "ash/system/user/login_status.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"

namespace views {
class View;
}

namespace ash {

class ASH_EXPORT SystemTrayItem {
 public:
  SystemTrayItem();
  virtual ~SystemTrayItem();

  // Returns a view to be displayed in the system tray. If this returns NULL,
  // then this item is not displayed in the tray.
  virtual views::View* CreateTrayView(user::LoginStatus status) = 0;

  // Returns a view for the item to be displayed in the list. This view can be
  // displayed with a number of other tray items, so this should not be too
  // big.
  virtual views::View* CreateDefaultView(user::LoginStatus status) = 0;

  // Returns a detailed view for the item. This view is displayed standalone.
  virtual views::View* CreateDetailedView(user::LoginStatus status) = 0;

  // These functions are called when the corresponding view item is about to be
  // removed. An item should do appropriate cleanup in these functions.
  virtual void DestroyTrayView() = 0;
  virtual void DestroyDefaultView() = 0;
  virtual void DestroyDetailedView() = 0;

  // Pops up the detailed view for this item. An item can request to show its
  // detailed view using this function (e.g. from an observer callback when
  // something, e.g. volume, network availability etc. changes).
  void PopupDetailedView();

 private:

  DISALLOW_COPY_AND_ASSIGN(SystemTrayItem);
};

}  // namespace ash

#endif  // ASH_SYSTEM_TRAY_SYSTEM_TRAY_ITEM_H_
