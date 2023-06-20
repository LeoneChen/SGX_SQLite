#include <filesystem>
#include <string.h>
#include <string>

namespace fs = std::filesystem;

#define WORK_DIR "/tmp/OCallWorkDir"

extern "C" void sgxfuzz_log(int ll, bool with_prefix, const char *fmt, ...);
extern "C" int SGXFuzzerEnvClearBeforeTest() {
  // Clean WORK_DIR
  std::error_code ec;
  fs::path work_dir(WORK_DIR);
  fs::remove_all(work_dir, ec);
  if (ec) {
    sgxfuzz_log(1, true, "rm %s: %s\n", WORK_DIR, ec.message().c_str());
  }
  fs::create_directory(work_dir);
  return 0;
}