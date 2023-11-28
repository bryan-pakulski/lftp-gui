#pragma once

#include <fstream>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/yaml.h>

#include "Types.h"

namespace CONFIG {

static YAML::Node configFile = YAML::LoadFile("config.yaml");

// Load config with default value if item doesn't exist
template <class T> static T loadConfig(const std::string &configPath, const T &defaultValue) {
  try {
    return configFile[configPath].as<T>();
  } catch (const YAML::Exception &) {
    return defaultValue;
  }
}

// Prompt user for config, save to file
template <class T> static void setConfig(T &variable, const std::string &configPath) {
  // TODO: Persist configuration in config.yaml file
}

// ImGui configuration
static CString PROGRAM_NAME("lftp-ui");
static CFloat HIGH_DPI_SCALE_FACTOR(loadConfig<float>("HIGH_DPI_SCALE_FACTOR", 1.0f));
static CInt WINDOW_WIDTH(loadConfig("WINDOW_WIDTH", 1280));
static CInt WINDOW_HEIGHT(loadConfig("WINDOW_HEIGHT", 720));

static CFloat IMGUI_LOG_WINDOW_HEIGHT(loadConfig("IMGUI_LOG_WINDOW_HEIGHT", 900.0f));
static CFloat IMGUI_LOG_WINDOW_WIDTH(loadConfig("IMGUI_LOG_WINDOW_WIDTH", 820.0f));

// Logging
static CInt ENABLE_TRACE_LOGGING(loadConfig<int>("ENABLE_TRACE_LOGGING", 0));
static CInt DEBUG_LEVEL(loadConfig<int>("DEBUG_LEVEL", 5));
static CString LOG_FILE(loadConfig<std::string>("LOG_FILE", "lftp-ui.log"));

} // namespace CONFIG