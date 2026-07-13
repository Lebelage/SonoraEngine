export module sonora.engine.core.logger;
import std;

import sonora.engine.core.engine_definitions;
export namespace sonora::engine::core {

enum class LogType { Error, Warning, Success, Info };

class Logger {
public:
  static void Log(LogType log_type, const std::string &message) {
    std::string_view type;

    switch (log_type) {
    case LogType::Error:
      type = "Error";
      break;
    case LogType::Warning:
      type = "Warning";
      break;
    case LogType::Success:
      type = "Success";
      break;
    case LogType::Info:
      type = "Info";
      break;
    }
    const auto text = std::format("{}: {}", type, message);

    std::cout << text << "\n";
  }

  static void LogCollection(LogType log_type, const std::string &message,
                     const std::vector<const char *> &collection) {
    std::string_view type;

    switch (log_type) {
    case LogType::Error:
      type = "Error";
      break;
    case LogType::Warning:
      type = "Warning";
      break;
    case LogType::Success:
      type = "Success";
      break;
    }

    std::string text = std::format("{}: {} \n", type, message);

    text.reserve(text.size() + collection.size() * 32);

    for (const auto *c : collection) {
      if (c == nullptr) {
        text += "  - [nullptr]\n";
        continue;
      }

      text += std::format("  - {}\n", std::string_view(c));
    }

    std::cout << text << "\n";
  }
};
} // namespace sonora::engine::core