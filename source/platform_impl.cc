#include "thread_impl.h"
#include "filesystem_impl.h"
#include "platform_impl.h"

namespace Runtime {
PlatformImpl::PlatformImpl()
	: thread_factory_(std::make_unique<Thread::ThreadFactoryImplPosix>()),
	: file_system_(std::make_unique<Filesystem::InstanceImplPosix()) { };

PlatformImpl::~PlatformImpl() = default;
}
