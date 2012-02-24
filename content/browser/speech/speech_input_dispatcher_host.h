// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SPEECH_SPEECH_INPUT_DISPATCHER_HOST_H_
#define CONTENT_BROWSER_SPEECH_SPEECH_INPUT_DISPATCHER_HOST_H_

#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "content/public/browser/browser_message_filter.h"
#include "net/url_request/url_request_context_getter.h"

class AudioManager;
struct SpeechInputHostMsg_StartRecognition_Params;

namespace content {
class SpeechInputPreferences;
struct SpeechInputResult;
}

namespace speech_input {

class SpeechInputManagerImpl;

// SpeechInputDispatcherHost is a delegate for Speech API messages used by
// RenderMessageFilter.
// It's the complement of SpeechInputDispatcher (owned by RenderView).
class CONTENT_EXPORT SpeechInputDispatcherHost
    : public content::BrowserMessageFilter {
 public:
  class SpeechInputCallers;

  SpeechInputDispatcherHost(
      int render_process_id,
      net::URLRequestContextGetter* context_getter,
      content::SpeechInputPreferences* speech_input_preferences,
      AudioManager* audio_manager);

  // Methods called by SpeechInputManagerImpl.
  void SetRecognitionResult(int caller_id,
                            const content::SpeechInputResult& result);
  void DidCompleteRecording(int caller_id);
  void DidCompleteRecognition(int caller_id);

  // content::BrowserMessageFilter implementation.
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 bool* message_was_ok) OVERRIDE;

  // Singleton manager setter useful for tests.
  static void set_manager(SpeechInputManagerImpl* manager);

 private:
  virtual ~SpeechInputDispatcherHost();

  void OnStartRecognition(
      const SpeechInputHostMsg_StartRecognition_Params &params);
  void OnCancelRecognition(int render_view_id, int request_id);
  void OnStopRecording(int render_view_id, int request_id);

  // Returns the speech input manager to forward events to, creating one if
  // needed.
  SpeechInputManagerImpl* manager();

  int render_process_id_;
  bool may_have_pending_requests_;  // Set if we received any speech IPC request

  scoped_refptr<net::URLRequestContextGetter> context_getter_;
  scoped_refptr<content::SpeechInputPreferences> speech_input_preferences_;
  AudioManager* audio_manager_;

  static SpeechInputManagerImpl* manager_;

  DISALLOW_COPY_AND_ASSIGN(SpeechInputDispatcherHost);
};

}  // namespace speech_input

#endif  // CONTENT_BROWSER_SPEECH_SPEECH_INPUT_DISPATCHER_HOST_H_
