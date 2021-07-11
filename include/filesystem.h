#pragma once

#include <bitset>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

namespace Runtime {
namespace Filesystem {

using FlagSet = std::bitset<4>;

class File {
public:
    virtual ~File() = default;

    enum Operation {
        Read,
        Write,
        Create,
        Append,
    };

    virtual bool open(FlagSet flags) = 0;

    virtual ssize_t write(std::string_view buffer) = 0;

    virtual bool close() = 0;

    virtual bool isOpen() const = 0;

    virtual std::string path() const = 0;
};

using FilePtr = std::unique_ptr<File>;

struct PathSplitResult {
    std::string_view directory_;
    std::string_view file_;
};

class Instance {
public:
    virtual ~Instance() = default;

    virtual FilePtr createFile(const std::string& path) = 0;
    virtual bool fileExists(const std::string& path) = 0;
    virtual bool directoryExists(const std::string& path) = 0;
    virtual ssize_t fileSize(const std::string& path) = 0;
    virtual std::string fileReadToEnd(const std::string& path) = 0;

    virtual PathSplitResult splitPathFromFilename(std::string_view path) = 0;

    virtual bool illegalPath(const std::string& path) = 0;
};

using InstancePtr = std::unique_ptr<Instance>;

enum class FileType { Regular, Directory, Other };


struct DirectoryEntry {
    std::string name_;
    FileType type_;

    bool operator==(const DirectoryEntry& rhs) const {
        return name_ == rhs.name_ && type_ == rhs.type_;
    }
};

class DirectoryIteratorImpl;
class DirectoryInterator {
public:
    DirectoryIterator() : entry_({"", FileType::Other}) {}
    virtual ~DirectoryIterator() = default;
    const DirectoryEntry& operator*() const { return entry_; }
    bool operator!=(const DirectoryIterator& rhs) const { return !(entry_ == *rhs); }

    virtual DirectoryIteratorImpl& operator++() = 0;

protected:
    DirectoryEntry entry_;
};

}
}
