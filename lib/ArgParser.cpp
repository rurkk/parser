#include "ArgParser.h"

void ArgumentParser::ArgParser::StoreString(StringArgument* string_argument, std::string& value) {
  if (string_argument->multi_value == -1) {
    string_argument->str_value = value;
    string_argument->flag_string_value = true;
    if (string_argument->store_str_value != nullptr) {
      *string_argument->store_str_value = string_argument->str_value;
    }
  } else {
    string_argument->vec_str_values.push_back(value);
    string_argument->flag_string_vec_values = true;
    if (string_argument->store_vec_str_values != nullptr) {
      *string_argument->store_vec_str_values = string_argument->vec_str_values;
    }
  }
}

void ArgumentParser::ArgParser::StoreInt(ArgumentParser::IntArgument* int_argument, std::string& value) {
  if (int_argument->multi_value == -1) {
    int_argument->int_value = std::stoi(value);
    int_argument->flag_int_value = true;
    if (int_argument->store_int_value != nullptr) {
      *int_argument->store_int_value = int_argument->int_value;
    }
  } else {
    int_argument->vec_int_values.push_back(std::stoi(value));
    int_argument->flag_int_vec_values = true;
    if (int_argument->store_vec_int_values != nullptr) {
      *int_argument->store_vec_int_values = int_argument->vec_int_values;
    }
  }
}

void ArgumentParser::ArgParser::StoreBool(ArgumentParser::BoolArgument* bool_argument, std::string& value) {
  if (bool_argument->multi_value == -1) {
    bool_argument->bool_value = std::stoi(value);
    bool_argument->flag_bool_value = true;
    if (bool_argument->store_bool_value != nullptr) {
      *bool_argument->store_bool_value = bool_argument->bool_value;
    }
  } else {
    bool_argument->vec_bool_values.push_back(std::stoi(value));
    bool_argument->flag_bool_vec_values = true;
    if (bool_argument->store_vec_bool_values != nullptr) {
      *bool_argument->store_vec_bool_values = bool_argument->vec_bool_values;
    }
  }
}

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& argv) {
  for (int i = 1; i < argv.size(); i++) {
    if (argv[i] == long_help_ or argv[i] == short_help_) {
      return true;
    } else if (argv[i][0] != '-') {
      std::string value;
      value = argv[i];
      for (StringArgument* string_argument : StringArguments_) {
        if (string_argument->positional) {
          ArgumentParser::ArgParser::StoreString(string_argument, value);
        }
      }
      for (IntArgument* int_argument : IntArguments_) {
        if (int_argument->positional) {
          ArgumentParser::ArgParser::StoreInt(int_argument, value);
        }
      }
      for (BoolArgument* bool_argument : BoolArguments_) {
        if (bool_argument->positional) {
          ArgumentParser::ArgParser::StoreBool(bool_argument, value);
        }
      }
    } else if (argv[i][0] == '-' and argv[i][1] == '-') {
      uint64_t border = argv[i].find('=');
      if (border != std::string::npos) {
        std::string value;
        value = argv[i].substr(border + 1, argv[i].size() - border - 1);
        for (StringArgument* string_argument : StringArguments_) {
          if (string_argument->long_name == ((std::string_view) argv[i]).substr(2, border - 2)) {
            ArgumentParser::ArgParser::StoreString(string_argument, value);
          }
        }
        for (IntArgument* int_argument : IntArguments_) {
          if (int_argument->long_name == ((std::string_view) argv[i]).substr(2, border - 2)) {
            ArgumentParser::ArgParser::StoreInt(int_argument, value);
          }
        }
      } else {
        std::string value;
        value = "1";
        for (BoolArgument* bool_argument : BoolArguments_) {
          if (bool_argument->long_name == ((std::string_view) argv[i]).substr(2, border - 2)) {
            ArgumentParser::ArgParser::StoreBool(bool_argument, value);
          }
        }
      }
    } else if (argv[i][0] == '-') {
      if (argv[i].find('=') != std::string::npos) {
        std::string value;
        value = argv[i].substr(3, argv[i].size() - 3);
        for (StringArgument* string_argument : StringArguments_) {
          if (string_argument->short_name == argv[i][1]) {
            ArgumentParser::ArgParser::StoreString(string_argument, value);
          }
        }
        for (IntArgument* int_argument : IntArguments_) {
          if (int_argument->short_name == argv[i][1]) {
            ArgumentParser::ArgParser::StoreInt(int_argument, value);
          }
        }
      } else {
        for (int j = 1; j < argv[i].length(); j++) {
          std::string value;
          value = "1";
          for (BoolArgument* bool_argument : BoolArguments_) {
            if (bool_argument->short_name == argv[i][j]) {
              ArgumentParser::ArgParser::StoreBool(bool_argument, value);
            }
          }
        }
      }
    }
  }
  for (StringArgument* string_argument : StringArguments_) {
    if (!string_argument->flag_string_value and !string_argument->flag_string_vec_values) {
      return false;
    }
    if (string_argument->multi_value != -1) {
      if (string_argument->vec_str_values.size() < string_argument->multi_value) {
        return false;
      }
    }
  }
  for (IntArgument* int_argument : IntArguments_) {
    if (!int_argument->flag_int_value and !int_argument->flag_int_vec_values) {
      return false;
    }
    if (int_argument->multi_value != -1) {
      if (int_argument->vec_int_values.size() < int_argument->multi_value) {
        return false;
      }
    }
  }
  for (BoolArgument* bool_argument : BoolArguments_) {
    if (bool_argument->multi_value != -1) {
      if (bool_argument->vec_bool_values.size() < bool_argument->multi_value) {
        return false;
      }
    }
  }

  return true;
}

bool ArgumentParser::ArgParser::Parse(int argc, char** argv) {
  std::vector<std::string> vec_argv(argc);
  for (int i = 0; i < argc; i++) {
    vec_argv[i] = argv[i];
  }

  return ArgumentParser::ArgParser::Parse(vec_argv);
}

ArgumentParser::StringArgument&
ArgumentParser::ArgParser::AddStringArgument(const char* long_name, const char* description) {
  ArgumentParser::StringArgument* Argument = new ArgumentParser::StringArgument;
  Argument->long_name = long_name;
  Argument->description = description;
  StringArguments_.push_back(Argument);

  return *Argument;
}
ArgumentParser::StringArgument&
ArgumentParser::ArgParser::AddStringArgument(char short_name, const char* long_name, const char* description) {
  ArgumentParser::StringArgument* Argument = new ArgumentParser::StringArgument;
  Argument->long_name = long_name;
  Argument->short_name = short_name;
  Argument->description = description;
  StringArguments_.push_back(Argument);

  return *Argument;
}

ArgumentParser::IntArgument&
ArgumentParser::ArgParser::AddIntArgument(const char* long_name, const char* description) {
  ArgumentParser::IntArgument* Argument = new ArgumentParser::IntArgument;
  Argument->long_name = long_name;
  Argument->description = description;
  IntArguments_.push_back(Argument);

  return *Argument;
}
ArgumentParser::IntArgument&
ArgumentParser::ArgParser::AddIntArgument(char short_name, const char* long_name, const char* description) {
  ArgumentParser::IntArgument* Argument = new ArgumentParser::IntArgument;
  Argument->long_name = long_name;
  Argument->short_name = short_name;
  Argument->description = description;
  IntArguments_.push_back(Argument);

  return *Argument;
}

ArgumentParser::BoolArgument&
ArgumentParser::ArgParser::AddFlag(const char* long_name, const char* description) {
  ArgumentParser::BoolArgument* Argument = new ArgumentParser::BoolArgument;
  Argument->long_name = long_name;
  Argument->description = description;
  BoolArguments_.push_back(Argument);

  return *Argument;
}
ArgumentParser::BoolArgument&
ArgumentParser::ArgParser::AddFlag(char short_name, const char* long_name, const char* description) {
  ArgumentParser::BoolArgument* Argument = new ArgumentParser::BoolArgument;
  Argument->long_name = long_name;
  Argument->short_name = short_name;
  Argument->description = description;
  BoolArguments_.push_back(Argument);

  return *Argument;
}

void ArgumentParser::ArgParser::AddHelp(char short_name, const char* long_name, const char* description) {
  help_ = true;
  short_help_ = short_name;
  long_help_ = long_name;
  parser_description_ = description;
}
void ArgumentParser::ArgParser::AddHelp(const char* long_name, const char* description) {
  help_ = true;
  long_help_ = long_name;
  parser_description_ = description;
}

std::string ArgumentParser::ArgParser::GetStringValue(const char* long_name, int i) {
  for (StringArgument* string_argument : StringArguments_) {
    if (string_argument->long_name == long_name) {
      if (i == -1) return string_argument->str_value;
      else return string_argument->vec_str_values[i];
    }
  }

  return "";
}
int ArgumentParser::ArgParser::GetIntValue(const char* long_name, int i) {
  for (IntArgument* int_argument : IntArguments_) {
    if (int_argument->long_name == long_name) {
      if (i == -1) return int_argument->int_value;
      else return int_argument->vec_int_values[i];
    }
  }

  return 0;
}
bool ArgumentParser::ArgParser::GetFlag(const char* long_name, int i) {
  for (BoolArgument* bool_argument : BoolArguments_) {
    if (bool_argument->long_name == long_name) {
      if (i == -1) return bool_argument->bool_value;
      else return bool_argument->vec_bool_values[i];
    }
  }

  return false;
}
bool ArgumentParser::ArgParser::Help() const {
  return help_;
}
std::string ArgumentParser::ArgParser::HelpDescription() {
  std::string help_description;
  help_description = name_parser_ + '\n' + parser_description_ + '\n' + '\n';
  std::string argument_description;
  argument_description = "";
  for (StringArgument* string_argument : StringArguments_) {
    if (string_argument->short_name != ' ') {
      std::string s(1, string_argument->short_name);
      argument_description += s + ", ";
    }
    if (string_argument->long_name != " ") {
      argument_description += string_argument->long_name + ", ";
    }
    if (string_argument->description != " ") {
      argument_description += string_argument->description + '\n';
    }
  }
  help_description += argument_description;
  argument_description = "";
  for (IntArgument* int_argument : IntArguments_) {
    if (int_argument->short_name != ' ') {
      std::string s(1, int_argument->short_name);
      argument_description += s + ", ";
    }
    if (int_argument->long_name != " ") {
      argument_description += int_argument->long_name + ", ";
    }
    if (int_argument->description != " ") {
      argument_description += int_argument->description + '\n';
    }
  }
  help_description += argument_description;
  argument_description = "";
  for (BoolArgument* bool_argument : BoolArguments_) {
    if (bool_argument->short_name != ' ') {
      std::string s(1, bool_argument->short_name);
      argument_description += s + ", ";
    }
    if (bool_argument->long_name != " ") {
      argument_description += bool_argument->long_name + ", ";
    }
    if (bool_argument->description != " ") {
      argument_description += bool_argument->description + '\n';
    }
  }
  help_description += argument_description;

  return help_description;
}

ArgumentParser::StringArgument& ArgumentParser::StringArgument::Default(const char* tmp) {
  this->flag_string_value = true;
  this->str_value = tmp;
  if (store_str_value != nullptr) {
    *this->store_str_value = this->str_value;
  }
  flag_string_value = true;

  return *this;
}
ArgumentParser::StringArgument& ArgumentParser::StringArgument::StoreValue(std::string& tmp) {
  store_str_value = &tmp;
  *store_str_value = str_value;

  return *this;
}
ArgumentParser::StringArgument& ArgumentParser::StringArgument::MultiValue(int min_args_count) {
  multi_value = min_args_count;

  return *this;
}
ArgumentParser::StringArgument& ArgumentParser::StringArgument::StoreValues(std::vector<std::string>& tmp) {
  store_vec_str_values = &tmp;
  *store_vec_str_values = vec_str_values;

  return *this;
}
ArgumentParser::StringArgument& ArgumentParser::StringArgument::Positional() {
  positional = true;

  return *this;
}

ArgumentParser::IntArgument& ArgumentParser::IntArgument::Default(int tmp) {
  this->flag_int_value = true;
  this->int_value = tmp;
  if (store_int_value != nullptr) {
    *this->store_int_value = this->int_value;
  }
  flag_int_value = true;

  return *this;
}
ArgumentParser::IntArgument& ArgumentParser::IntArgument::StoreValue(int& tmp) {
  store_int_value = &tmp;
  *store_int_value = int_value;

  return *this;
}
ArgumentParser::IntArgument& ArgumentParser::IntArgument::MultiValue(int min_args_count) {
  multi_value = min_args_count;

  return *this;
}
ArgumentParser::IntArgument& ArgumentParser::IntArgument::StoreValues(std::vector<int>& tmp) {
  store_vec_int_values = &tmp;
  *store_vec_int_values = vec_int_values;

  return *this;
}
ArgumentParser::IntArgument& ArgumentParser::IntArgument::Positional() {
  positional = true;

  return *this;
}

ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::Default(bool tmp) {
  this->flag_bool_value = true;
  this->bool_value = tmp;
  if (store_bool_value != nullptr) {
    *this->store_bool_value = this->bool_value;
  }

  return *this;
}
ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::StoreValue(bool& tmp) {
  store_bool_value = &tmp;
  *store_bool_value = bool_value;

  return *this;
}
ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::MultiValue(int min_args_count) {
  multi_value = min_args_count;

  return *this;
}
ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::StoreValues(std::vector<bool>& tmp) {
  store_vec_bool_values = &tmp;
  *store_vec_bool_values = vec_bool_values;

  return *this;
}
ArgumentParser::BoolArgument& ArgumentParser::BoolArgument::Positional() {
  positional = true;

  return *this;
}
