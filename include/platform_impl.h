#pragma once

#include "runtime/filesystem.h"
#include "runtime/thread.h"

namespace runtime {

class PlatformImpl {
public:
    PlatformImpl();
    ~PlatformImpl();
    Thread::ThreadFactory& threadFactory() { return *thread_factory_; }
    Filesystem::Instance& fileSystem() { return *file_system_; }

private:
    Thread::ThreadFactoryPtr thread_factory_;
    Filesystem::InstancePtr file_system_;
};
}
