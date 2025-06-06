/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "HWDevice.h"

#include <EGL/eglplatform.h>
#include <igl/opengl/egl/Context.h>
#include <igl/opengl/egl/Device.h>

namespace igl::opengl::egl {

std::unique_ptr<IContext> HWDevice::createContext(Result* outResult) const {
  Result::setOk(outResult);
  return std::make_unique<Context>(IGL_EGL_NULL_WINDOW);
}

std::unique_ptr<IContext> HWDevice::createContext(EGLNativeWindowType nativeWindow,
                                                  Result* outResult) const {
  return std::make_unique<Context>(nativeWindow);
}

std::unique_ptr<IContext> HWDevice::createContext(RenderingAPI /*api*/,
                                                  EGLNativeWindowType nativeWindow,
                                                  Result* outResult) const {
  return createContext(nativeWindow, outResult);
}

std::unique_ptr<IContext> HWDevice::createOffscreenContext(size_t width,
                                                           size_t height,
                                                           Result* outResult) const {
  Result::setOk(outResult);
  return std::make_unique<Context>(width, height);
}

std::unique_ptr<opengl::Device> HWDevice::createWithContext(std::unique_ptr<IContext> context,
                                                            Result* outResult) const {
  Result::setOk(outResult);
  if (context == nullptr) {
    Result::setResult(outResult, Result::Code::ArgumentInvalid, "context is null");
    return nullptr;
  }
  return std::make_unique<opengl::egl::Device>(std::move(context));
}

std::unique_ptr<IDevice> HWDevice::create(EGLNativeWindowType nativeWindow,
                                          Result* outResult) const {
  auto context = createContext(nativeWindow, outResult);
  if (context == nullptr) {
    return nullptr;
  }
  return createWithContext(std::move(context), outResult);
}

} // namespace igl::opengl::egl
