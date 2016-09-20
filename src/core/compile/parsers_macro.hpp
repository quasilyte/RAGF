#pragma once

#define BEGIN_PARSERS() \
  const int count__ = static_cast<int>(Token::REG); \
  static void* parsers__[count__]; \
  int i__ = 0
#define PARSE_NEXT \
  goto *parsers__[static_cast<int>($input.read_token())]
#define TERMINATING_PARSER(NAME) \
  parsers__[i__++] = &&NAME; \
  goto after_##NAME; \
  end_of_input: return $writer->get_buf(); \
  after_##NAME:
#define PARSER(NAME) \
  parsers__[i__++] = &&NAME##_label; \
  goto after_##NAME; \
  NAME##_label: \
    parse_##NAME(); \
    PARSE_NEXT; \
  after_##NAME:
#define END_PARSERS() \
  PARSE_NEXT
