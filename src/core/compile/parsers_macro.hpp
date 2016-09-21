#pragma once

// Read next token and execute associated parser
#define PARSE_NEXT \
  goto *parsers__[static_cast<int>($input.read<Token>())]

// Open parser declaration block
#define BEGIN_PARSERS \
  static const int count__ = static_cast<int>(Token::NIL); \
  static bool initialized__ = false; \
  static void* parsers__[count__]; \
  int i__ = 0

// Parser that recognized END_OF_INPUT token and
// breaks from compiletion.
// #NOTE: must be a 1 parser in a list
#define TERMINATING_PARSER(NAME) \
  if (initialized__) { \
    PARSE_NEXT; \
  } \
  parsers__[i__++] = &&NAME; \
  goto after_##NAME; \
  end_of_input: return get_result(); \
  after_##NAME:

// Declare regular parser which handles Nth token
#define PARSER(NAME) \
  parsers__[i__++] = &&NAME##_label; \
  goto after_##NAME; \
  NAME##_label: \
    parse_##NAME(); \
    PARSE_NEXT; \
  after_##NAME:

// Close parser declaration block
#define END_PARSERS \
  initialized__ = true; \
  PARSE_NEXT

