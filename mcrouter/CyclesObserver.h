/*
 *  Copyright (c) 2015, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

#include <folly/experimental/ExecutionObserver.h>

#include "mcrouter/lib/cycles/Cycles.h"

namespace facebook { namespace memcache { namespace mcrouter {

class CyclesObserver : public folly::ExecutionObserver {
 public:
  void starting(uintptr_t id) noexcept override {
    if (!cycles::start()) {
      // Should never happen
      DCHECK(false) << "There is already one cycles interval "
                       "active in this thread";
    }
  }
  void runnable(uintptr_t id) noexcept override {}
  void stopped(uintptr_t id) noexcept override {
    cycles::finish();
  }
};

}}} // facebook::memcache::mcrouter
