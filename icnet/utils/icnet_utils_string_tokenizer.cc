/*
 * Copyright (c) 2017 Cisco and/or its affiliates.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <icnet_errors_tokenizer_exception.h>
#include "icnet_utils_string_tokenizer.h"
#include "icnet_errors.h"

namespace utils {

StringTokenizer::StringTokenizer(const std::string &str)
    : str_(str), delimiter_(" ") {
}

StringTokenizer::StringTokenizer(const std::string &str, const std::string &delim)
    : str_(str), delimiter_(delim) {
}

bool StringTokenizer::hasMoreTokens() {
  return str_.find(delimiter_) != std::string::npos && !str_.empty();
}

std::string StringTokenizer::nextToken() {
  unsigned long pos = str_.find(delimiter_);

  bool token_found = std::string::npos != pos;

  if (!token_found && str_.empty()) {
    throw errors::TokenizerException();
  }

  std::string token = str_.substr(0, pos);
  str_.erase(0, token_found ? pos + delimiter_.length() : pos);

  return token;
}

}