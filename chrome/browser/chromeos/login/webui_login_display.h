// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_WEBUI_LOGIN_DISPLAY_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_WEBUI_LOGIN_DISPLAY_H_
#pragma once

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/login/login_display.h"
#include "chrome/browser/chromeos/login/user_manager.h"
#include "chrome/browser/ui/webui/chromeos/login/signin_screen_handler.h"
#include "views/widget/widget.h"

namespace gfx {
class Rect;
}  // namespace gfx

namespace chromeos {
// WebUI-based login UI implementation.
class WebUILoginDisplay : public LoginDisplay,
                          public SigninScreenHandlerDelegate {
 public:
  explicit WebUILoginDisplay(LoginDisplay::Delegate* delegate);
  virtual ~WebUILoginDisplay();

  // LoginDisplay implementation:
  virtual void Init(const std::vector<UserManager::User>& users,
                    bool show_guest,
                    bool show_new_user) OVERRIDE;
  virtual void OnBeforeUserRemoved(const std::string& username) OVERRIDE;
  virtual void OnUserImageChanged(UserManager::User* user) OVERRIDE;
  virtual void OnUserRemoved(const std::string& username) OVERRIDE;
  virtual void OnFadeOut() OVERRIDE;
  virtual void OnLoginSuccess(const std::string& username) OVERRIDE;
  virtual void SetUIEnabled(bool is_enabled) OVERRIDE;
  virtual void SelectPod(int index) OVERRIDE;
  virtual void ShowError(int error_msg_id,
                         int login_attempts,
                         HelpAppLauncher::HelpTopic help_topic_id) OVERRIDE;

  // SigninScreenHandlerDelegate implementation:
  virtual void CompleteLogin(const std::string& username,
                             const std::string& password) OVERRIDE;
  virtual void Login(const std::string& username,
                     const std::string& password) OVERRIDE;
  virtual void LoginAsGuest() OVERRIDE;
  virtual void FixCaptivePortal() OVERRIDE;
  virtual void CreateAccount() OVERRIDE;
  virtual void RemoveUser(const std::string& username) OVERRIDE;
  virtual void ShowEnterpriseEnrollmentScreen() OVERRIDE;
  virtual void SetWebUIHandler(
      LoginDisplayWebUIHandler* webui_handler) OVERRIDE;
  virtual void ShowSigninScreenForCreds(const std::string& username,
                                        const std::string& password);
  virtual const std::vector<UserManager::User>& GetUsers() const OVERRIDE;
  virtual bool IsShowGuest() const OVERRIDE;
  virtual bool IsShowNewUser() const OVERRIDE;

 private:
  // Set of Users that are visible.
  std::vector<UserManager::User> users_;

  // Whether to show guest login.
  bool show_guest_;

  // Whether to show add new user.
  bool show_new_user_;

  // Reference to the WebUI handling layer for the login screen
  LoginDisplayWebUIHandler* webui_handler_;

  DISALLOW_COPY_AND_ASSIGN(WebUILoginDisplay);
};

}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_LOGIN_WEBUI_LOGIN_DISPLAY_H_
