#include "Maad.h"
#include <AsstCaller.h>
#include <cstdint>

static Json::StreamWriterBuilder writerBuilder;

JSON_ITEM JsonHandler::deserialize(const std::string Str) {
  Json::CharReaderBuilder readerBuilder;
  Json::Value root;
  std::string errs;
  std::istringstream iss(Str);
  if (!Json::parseFromStream(readerBuilder, iss, &root, &errs)) {
    Logger::toConsole("Failed to parse JSON: ", Logger::warn);
  }
  return root;
}

AsstBool
JsonHandler::deserializeFile(JSON_ITEM &json,
                             std::string path) { // 将json文件转换为json对象
  std::ifstream file(path);
  std::string jsonStr;

  if (file.is_open()) {
    std::stringstream buffer;
    buffer << file.rdbuf();
    jsonStr = buffer.str();
    file.close();
  } else {
    return 1;
  }
  json = deserialize(jsonStr);
  return 0;
}

std::string JsonHandler::serialize(const JSON_ITEM json) {
  Json::StreamWriterBuilder writerBuilder;
  std::ostringstream oss;
  Json::StreamWriter *writer = writerBuilder.newStreamWriter();
  writer->write(json, &oss);
  delete writer;
  return oss.str();
}

std::string JsonHandler::returnValue(JSON_ITEM *json, std::string key) {
  return (*json)[key].asString();
}