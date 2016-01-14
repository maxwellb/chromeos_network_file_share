// Copyright 2015 Google Inc.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <string>

namespace pp {
class VarDictionary;
}

namespace NaclFsp {

class BaseOptions {
 protected:
  BaseOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);

 public:
  std::string fileSystemId;

 private:
  // Prevent copy and assignment.
  BaseOptions(const BaseOptions&);
  BaseOptions& operator=(const BaseOptions&);
};

class TrackedOperationOptions : public BaseOptions {
 protected:
  TrackedOperationOptions() : requestId(-1) {}
  virtual void Set(const pp::VarDictionary& optionsDict);

 public:
  int requestId;
};

class DirectoryOperationOptions : public TrackedOperationOptions {
 protected:
  DirectoryOperationOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);

 public:
  std::string directoryPath;
};

class OpenFileOperationOptions : public TrackedOperationOptions {
 protected:
  OpenFileOperationOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);

 public:
  int openRequestId;
};

class FileIOOperationOptions : public OpenFileOperationOptions {
 protected:
  FileIOOperationOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);

 public:
  double offset;
  double length;
};

class MountOptions : public BaseOptions {
 public:
  MountOptions() : writable(false), openedFilesLimit(0) {}
  virtual void Set(const pp::VarDictionary& optionsDict);

  std::string displayName;
  bool writable;
  int openedFilesLimit;
};

class UnmountOptions : public BaseOptions {
 public:
  UnmountOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
};

class GetMetadataOptions : public TrackedOperationOptions {
 public:
  GetMetadataOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string entryPath;
  bool thumbnail;
};

class ReadDirectoryOptions : public DirectoryOperationOptions {
 public:
  ReadDirectoryOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
};

class CreateDirectoryOptions : public DirectoryOperationOptions {
 public:
  CreateDirectoryOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  bool recursive;
};

enum OpenFileMode { FILE_MODE_READ = 0, FILE_MODE_WRITE = 1 };

class OpenFileOptions : public TrackedOperationOptions {
 public:
  OpenFileOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string filePath;
  OpenFileMode mode;
};

class CreateFileOptions : public TrackedOperationOptions {
 public:
  CreateFileOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string filePath;
};

class CloseFileOptions : public OpenFileOperationOptions {
 public:
  CloseFileOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
};

class ReadFileOptions : public FileIOOperationOptions {
 public:
  ReadFileOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
};

class WriteFileOptions : public FileIOOperationOptions {
 public:
  WriteFileOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  const void* data;
};

class DeleteEntryOptions : public TrackedOperationOptions {
 public:
  DeleteEntryOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string entryPath;
  bool recursive;
};

class CopyEntryOptions : public TrackedOperationOptions {
 public:
  CopyEntryOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string sourcePath;
  std::string targetPath;
};

class MoveEntryOptions : public TrackedOperationOptions {
 public:
  MoveEntryOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string sourcePath;
  std::string targetPath;
};

class TruncateOptions : public TrackedOperationOptions {
 public:
  TruncateOptions() {}
  virtual void Set(const pp::VarDictionary& optionsDict);
  std::string filePath;
  double length;
};

}  // namespace NaclFsp