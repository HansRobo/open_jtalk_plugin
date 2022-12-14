// Copyright 2022 Kotaro Yoshimoto All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "open_jtalk_plugin/open_jtalk_plugin.hpp"

std::filesystem::path open_jtalk_plugin::OpenJTalkPlugin::generateSoundFile(
  const std::string input_text, const std::filesystem::path output_directory,
  const std::string file_name)
{
  std::string generated_file_path = output_directory / (file_name + ".wav");
  std::stringstream command_ss;
  // clang-format off
  command_ss << "echo " << input_text
             << " | open_jtalk"
             << " -x "  << dictionary_path
             << " -m "  << hts_voice_path
             << " -ow " << generated_file_path
             << " -r "  << speed_rate;
  // clang-format on
  system(command_ss.str().c_str());

  return std::filesystem::path(generated_file_path);
}

std::vector<speak_ros::Parameter> open_jtalk_plugin::OpenJTalkPlugin::getParametersDefault() const
{
  return {
    // clang-format off
      {"dictionary_path", "dictionary path", "/var/lib/mecab/dic/open-jtalk/naist-jdic"},
      {"hts_voice_path", "hts voice file path", "/usr/share/hts-voice/nitech-jp-atr503-m001/nitech_jp_atr503_m001.htsvoice"},
      {"speed_rate", "speed rate", "1.0"}
    // clang-format on
  };
}

void open_jtalk_plugin::OpenJTalkPlugin::importParameters(
  const std::unordered_map<std::string, std::string> & parameters)
{
  dictionary_path = parameters.at("dictionary_path");
  hts_voice_path = parameters.at("hts_voice_path");
  speed_rate = parameters.at("speed_rate");
}
