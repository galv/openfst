// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// See www.openfst.org for extensive documentation on this weighted
// finite-state transducer library.
//
// Google-style logging declarations and inline definitions.

#ifndef FST_LIB_LOG_H_
#define FST_LIB_LOG_H_

#include <cassert>
#include <iostream>
#include <string>

#include <fst/types.h>
#include <fst/flags.h>

using std::string;

DECLARE_int32(v);

class LogMessage {
 public:
  LogMessage(const string &type) : fatal_(type == "FATAL") {
    std::cerr << type << ": ";
  }
  ~LogMessage() {
    std::cerr << std::endl;
    if(fatal_)
      exit(1);
  }
  std::ostream &stream() { return std::cerr; }

 private:
  bool fatal_;
};

#define FST_LOG(type) LogMessage(#type).stream()
#define VFST_LOG(level) if ((level) <= FLAGS_v) FST_LOG(INFO)

// Checks
inline void FstCheck(bool x, const char* expr,
                const char *file, int line) {
  if (!x) {
    FST_LOG(FATAL) << "Check failed: \"" << expr
               << "\" file: " << file
               << " line: " << line;
  }
}

#define FST_CHECK(x) FstCheck(static_cast<bool>(x), #x, __FILE__, __LINE__)
#define FST_CHECK_EQ(x, y) FST_CHECK((x) == (y))
#define FST_CHECK_LT(x, y) FST_CHECK((x) < (y))
#define FST_CHECK_GT(x, y) FST_CHECK((x) > (y))
#define FST_CHECK_LE(x, y) FST_CHECK((x) <= (y))
#define FST_CHECK_GE(x, y) FST_CHECK((x) >= (y))
#define FST_CHECK_NE(x, y) FST_CHECK((x) != (y))

// Debug checks
#define FST_DCHECK(x) assert(x)
#define FST_DCHECK_EQ(x, y) FST_DCHECK((x) == (y))
#define FST_DCHECK_LT(x, y) FST_DCHECK((x) < (y))
#define FST_DCHECK_GT(x, y) FST_DCHECK((x) > (y))
#define FST_DCHECK_LE(x, y) FST_DCHECK((x) <= (y))
#define FST_DCHECK_GE(x, y) FST_DCHECK((x) >= (y))
#define FST_DCHECK_NE(x, y) FST_DCHECK((x) != (y))


// Ports
#define ATTRIBUTE_DEPRECATED __attribute__((deprecated))

#endif  // FST_LIB_LOG_H_
