/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <igl/opengl/HWDevice.h>

#include <igl/opengl/IContext.h>

namespace igl::opengl {

std::unique_ptr<Device> HWDevice::create(Result* outResult) const {
  auto context = createContext(outResult);
  if (context == nullptr) {
    return nullptr;
  }
  return createWithContext(std::move(context), outResult);
}

std::unique_ptr<Device> HWDevice::create(RenderingAPI api, Result* outResult) {
  auto context = createContext(api, IGL_EGL_NULL_WINDOW, outResult);
  if (!context) {
    Result::setResult(outResult, Result::Code::RuntimeError, "context is null");
    return nullptr;
  }

  return createWithContext(std::move(context), outResult);
}

} // namespace igl::opengl
