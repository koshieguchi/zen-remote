#pragma once

#include "core/common.h"
#include "zen-remote/server/gl-buffer.h"

namespace zen::remote::server {

class Session;

class GlBuffer final : public IGlBuffer {
 public:
  DISABLE_MOVE_AND_COPY(GlBuffer);
  GlBuffer() = delete;
  GlBuffer(std::shared_ptr<Session> session);
  ~GlBuffer();

  void Init();

  void GlBufferData(std::unique_ptr<IBuffer> buffer, uint32_t target,
      size_t size, uint32_t usage) override;

  uint64_t id() override;

 private:
  uint64_t id_;
  std::weak_ptr<Session> session_;
};

}  // namespace zen::remote::server
