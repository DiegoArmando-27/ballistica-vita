// Released under the MIT License. See LICENSE for details.

#ifndef BALLISTICA_ASSETS_ASSETS_SERVER_H_
#define BALLISTICA_ASSETS_ASSETS_SERVER_H_

#include <list>
#include <vector>

#include "ballistica/core/object.h"

namespace ballistica {

class AssetsServer {
 public:
  explicit AssetsServer(Thread* thread);
  ~AssetsServer();
  void PushBeginWriteReplayCall();
  void PushEndWriteReplayCall();
  void PushAddMessageToReplayCall(const std::vector<uint8_t>& data);
  auto thread() const -> Thread* { return thread_; }

 private:
  void Process();
  void WriteReplayMessages();
  Thread* thread_{};
  FILE* replay_out_file_{};
  size_t replay_bytes_written_{};
  bool writing_replay_{};
  bool replays_broken_{};
  std::list<std::vector<uint8_t> > replay_messages_;
  size_t replay_message_bytes_{};
  Timer* process_timer_{};
  std::vector<Object::Ref<AssetComponentData>*> pending_preloads_;
  std::vector<Object::Ref<AssetComponentData>*> pending_preloads_audio_;
  friend struct PreloadRunnable;
  friend class Assets;
};

}  // namespace ballistica

#endif  // BALLISTICA_ASSETS_ASSETS_SERVER_H_