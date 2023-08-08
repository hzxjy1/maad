#include "Maad.h"

static Json::StreamWriterBuilder writerBuilder;

JSON_ITEM JsonHandler::deserialize(const std::string Str) {
  Json::CharReaderBuilder readerBuilder;
  Json::Value root;
  std::string errs;
  std::istringstream iss(Str);
  if (!Json::parseFromStream(readerBuilder, iss, &root, &errs)) {
    std::cerr << "Failed to parse JSON: " << errs << std::endl;
  }
  return root;
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

bool JsonHandler::isRealEmpty(JSON_ITEM *json) {
  bool isEmpty = true;

  // 遍历 JSON 的键值对
  for (Json::ValueIterator itr = json->begin(); itr != json->end(); ++itr) {
    const Json::Value &value = *itr;

    // 检查当前值是否为空
    if (!value.isNull()) {
      isEmpty = false;
      break;
    }
  }

  return isEmpty;
}