#pragma once

#include <string>
#include <vector>
#include <variant>

namespace ArgumentParser {

struct StringArgument {
  char short_name = ' ';
  std::string long_name = " ";
  std::string description = " ";

  std::string str_value;
  std::vector<std::string> vec_str_values;

  std::string* store_str_value = nullptr;
  std::vector<std::string>* store_vec_str_values = nullptr;

  bool flag_string_value = false;
  bool flag_string_vec_values = false;

  bool positional = false;
  int multi_value = -1;

  ArgumentParser::StringArgument& Default(const char* tmp);
  ArgumentParser::StringArgument& StoreValue(std::string& tmp);
  ArgumentParser::StringArgument& StoreValues(std::vector<std::string>& tmp);
  ArgumentParser::StringArgument& MultiValue(int min_args_count = 0);
  ArgumentParser::StringArgument& Positional();
};

struct IntArgument {
  char short_name = ' ';
  std::string long_name = " ";
  std::string description = " ";

  int int_value;
  std::vector<int> vec_int_values;

  int* store_int_value = nullptr;
  std::vector<int>* store_vec_int_values = nullptr;

  bool flag_int_value = false;
  bool flag_int_vec_values = false;

  bool positional = false;
  int multi_value = -1;

  ArgumentParser::IntArgument& Default(int tmp);
  ArgumentParser::IntArgument& StoreValue(int& tmp);
  ArgumentParser::IntArgument& StoreValues(std::vector<int>& tmp);
  ArgumentParser::IntArgument& MultiValue(int min_args_count = 0);
  ArgumentParser::IntArgument& Positional();
};

struct BoolArgument {
  char short_name = ' ';
  std::string long_name = " ";
  std::string description = " ";

  bool bool_value = true;
  std::vector<bool> vec_bool_values;

  bool* store_bool_value = nullptr;
  std::vector<bool>* store_vec_bool_values = nullptr;

  bool flag_bool_value = false;
  bool flag_bool_vec_values = false;

  bool positional = false;
  int multi_value = -1;

  ArgumentParser::BoolArgument& Default(bool tmp);
  ArgumentParser::BoolArgument& StoreValue(bool& tmp);
  ArgumentParser::BoolArgument& StoreValues(std::vector<bool>& tmp);
  ArgumentParser::BoolArgument& MultiValue(int min_args_count = 0);
  ArgumentParser::BoolArgument& Positional();
};

class ArgParser {
 private:
  std::vector<StringArgument*> StringArguments_;
  std::vector<IntArgument*> IntArguments_;
  std::vector<BoolArgument*> BoolArguments_;
  std::string name_parser_;
  std::string short_help_;
  std::string long_help_;
  std::string parser_description_;
  bool help_ = false;
 public:
  explicit ArgParser(const std::string& name) {
    name_parser_ = name;
  }
  bool Parse(const std::vector<std::string>& parse_vec);
  bool Parse(int argc, char** argv);
  static void StoreString(StringArgument* string_argument, std::string& value);
  static void StoreInt(IntArgument* int_argument, std::string& value);
  static void StoreBool(BoolArgument* bool_argument, std::string& value);

  StringArgument& AddStringArgument(const char* long_name, const char* description = "");
  StringArgument& AddStringArgument(char short_name, const char* long_name, const char* description = "");
  std::string GetStringValue(const char* long_name, int i = -1);

  IntArgument& AddIntArgument(const char* long_name, const char* description = "");
  IntArgument& AddIntArgument(char short_name, const char* long_name, const char* description = "");
  int GetIntValue(const char* long_name, int i = -1);

  BoolArgument& AddFlag(const char* long_name, const char* description = "");
  BoolArgument& AddFlag(char short_name, const char* long_name, const char* description = "");
  bool GetFlag(const char* long_name, int i = -1);

  void AddHelp(char short_name, const char* long_name, const char* description = "");
  void AddHelp(const char* long_name, const char* description = "");
  [[nodiscard]] bool Help() const;

  std::string HelpDescription();
};

} // namespace ArgumentParser