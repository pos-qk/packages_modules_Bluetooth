/*
 * Copyright 2021 HIMSA II K/S - www.himsa.com.
 * Represented by EHIMA - www.ehima.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <array>
#include <optional>
#include <vector>

#include "bta/include/bta_le_audio_api.h"

/* Interface class */
class LeAudioBroadcaster {
 public:
  enum class AudioProfile {
    SONIFICATION = 0,
    MEDIA = 1,
  };

  static constexpr uint8_t kInstanceIdUndefined = 0xFF;
  static constexpr AudioProfile kDefaultAudioProfile = AudioProfile::MEDIA;

  virtual ~LeAudioBroadcaster(void) = default;

  static void Initialize(
      bluetooth::le_audio::LeAudioBroadcasterCallbacks* callbacks,
      base::Callback<bool()> hal_2_1_verifier);
  static void Stop(void);
  static void Cleanup(void);
  static LeAudioBroadcaster* Get(void);
  static bool IsLeAudioBroadcasterRunning(void);
  static void DebugDump(int fd);

  virtual void CreateAudioBroadcast(
      std::vector<uint8_t> metadata, AudioProfile profile,
      std::optional<bluetooth::le_audio::BroadcastCode> broadcast_code =
          std::nullopt) = 0;
  virtual void SuspendAudioBroadcast(uint8_t instance_id) = 0;
  virtual void StartAudioBroadcast(uint8_t instance_id) = 0;
  virtual void StopAudioBroadcast(uint8_t instance_id) = 0;
  virtual void DestroyAudioBroadcast(uint8_t instance_id) = 0;
  virtual void GetBroadcastId(uint8_t instance_id) = 0;
  virtual void GetAllBroadcastStates(void) = 0;
  virtual void UpdateMetadata(uint8_t instance_id,
                              std::vector<uint8_t> metadata) = 0;
  virtual void IsValidBroadcast(
      uint8_t instance_id, uint8_t addr_type, RawAddress addr,
      base::Callback<void(uint8_t /* instance_id */, uint8_t /* addr_type */,
                          RawAddress /* addr */, bool /* is_valid */)>
          cb) = 0;

  virtual void SetNumRetransmit(uint8_t count) = 0;
  virtual uint8_t GetNumRetransmit(void) const = 0;
  virtual void SetStreamingPhy(uint8_t phy) = 0;
  virtual uint8_t GetStreamingPhy(void) const = 0;
};
