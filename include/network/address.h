#pragma once

#include <sys/types.h>

#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace Runtime {
namespace Network {

class SocketInterface;

namespace Address {

class Ipv4 {
public:
    virtual ~Ipv4() = default;

    virtual uint32_t address() const = 0;
};

enum class IpVersion { v4, v6 };

class Ip {
public:
    virtual ~Ip() = default;

    virtual const std::string& addressAsString() const = 0;
    virtual bool isAnyAddress() const = 0;
    virtual bool isUnicastAddress() const = 0;
    virtual const Ipv4* ipv4() const = 0;
    // virtual const Ipv6* ipv6() const = 0;
    virtual uint32_t port() const = 0;
    virtual IpVersion version() const = 0;
};

class Pipe {
public:
    virtual ~Pipe() = default;

    virtual bool abstractNamespace() const = 0;

    virtual mode_t mode() const = 0;
};

class EnvoyInternalAddress {
public:
    virtual ~EnvoyInternalAddress() = default;

    virtual const std::string& addressId() const = 0;
};

enum class Type { Ip, Pipe, EnvoyInternal};

class Instance {
public:
    virtual ~Instance() = default;

    virtual bool operator==(const Instance& rhs) const = 0;
    bool operator!=(const Instance& rhs) const { return !operator==(rhs); }
    virtual const std::string& asString() const = 0;
    virtual std::string_view asStringView() const = 0;
    virtual const std::string& logicalName() const = 0;
    virtual const Ip* ip() const = 0;
    virtual const Pipe* pipe() const = 0;
    virtual const EnvoyInternalAddress* envoyInternalAddress() const = 0;
    virtual const sockaddr* sockAddr() const = 0;
    virtual socklen_t sockAddrLen() const = 0;
    virtual Type type() const = 0;
    virtual const Network::SocketInterface& socketInterface() const = 0;
};

using InstanceConstSharedPtr = std::shared_ptr<const Instance>;

}
}
}