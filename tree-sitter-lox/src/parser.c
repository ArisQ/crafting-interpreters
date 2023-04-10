#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 45
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 52
#define ALIAS_COUNT 0
#define TOKEN_COUNT 26
#define EXTERNAL_TOKEN_COUNT 0
#define FIELD_COUNT 0
#define MAX_ALIAS_SEQUENCE_LENGTH 5
#define PRODUCTION_ID_COUNT 1

enum {
  anon_sym_var = 1,
  anon_sym_EQ = 2,
  anon_sym_SEMI = 3,
  anon_sym_print = 4,
  anon_sym_BANG_EQ = 5,
  anon_sym_EQ_EQ = 6,
  anon_sym_GT = 7,
  anon_sym_GT_EQ = 8,
  anon_sym_LT = 9,
  anon_sym_LT_EQ = 10,
  anon_sym_DASH = 11,
  anon_sym_PLUS = 12,
  anon_sym_SLASH = 13,
  anon_sym_STAR = 14,
  anon_sym_BANG = 15,
  sym_nil = 16,
  anon_sym_true = 17,
  anon_sym_false = 18,
  anon_sym_LPAREN = 19,
  anon_sym_RPAREN = 20,
  sym_number = 21,
  sym_identifier = 22,
  anon_sym_DQUOTE = 23,
  aux_sym_string_token1 = 24,
  sym_comment = 25,
  sym_program = 26,
  sym__declaration = 27,
  sym_var_decl = 28,
  sym__statement = 29,
  sym_expr_stmt = 30,
  sym_print_stmt = 31,
  sym__expression = 32,
  sym__equality = 33,
  sym_equality = 34,
  sym__comparision = 35,
  sym_comparision = 36,
  sym__term = 37,
  sym_term = 38,
  sym__factor = 39,
  sym_factor = 40,
  sym__unary = 41,
  sym_unary = 42,
  sym__primary = 43,
  sym_bool = 44,
  sym_group = 45,
  sym_string = 46,
  aux_sym_program_repeat1 = 47,
  aux_sym_equality_repeat1 = 48,
  aux_sym_comparision_repeat1 = 49,
  aux_sym_term_repeat1 = 50,
  aux_sym_factor_repeat1 = 51,
};

static const char * const ts_symbol_names[] = {
  [ts_builtin_sym_end] = "end",
  [anon_sym_var] = "var",
  [anon_sym_EQ] = "=",
  [anon_sym_SEMI] = ";",
  [anon_sym_print] = "print",
  [anon_sym_BANG_EQ] = "!=",
  [anon_sym_EQ_EQ] = "==",
  [anon_sym_GT] = ">",
  [anon_sym_GT_EQ] = ">=",
  [anon_sym_LT] = "<",
  [anon_sym_LT_EQ] = "<=",
  [anon_sym_DASH] = "-",
  [anon_sym_PLUS] = "+",
  [anon_sym_SLASH] = "/",
  [anon_sym_STAR] = "*",
  [anon_sym_BANG] = "!",
  [sym_nil] = "nil",
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_number] = "number",
  [sym_identifier] = "identifier",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_token1] = "string_token1",
  [sym_comment] = "comment",
  [sym_program] = "program",
  [sym__declaration] = "_declaration",
  [sym_var_decl] = "var_decl",
  [sym__statement] = "_statement",
  [sym_expr_stmt] = "expr_stmt",
  [sym_print_stmt] = "print_stmt",
  [sym__expression] = "_expression",
  [sym__equality] = "_equality",
  [sym_equality] = "equality",
  [sym__comparision] = "_comparision",
  [sym_comparision] = "comparision",
  [sym__term] = "_term",
  [sym_term] = "term",
  [sym__factor] = "_factor",
  [sym_factor] = "factor",
  [sym__unary] = "_unary",
  [sym_unary] = "unary",
  [sym__primary] = "_primary",
  [sym_bool] = "bool",
  [sym_group] = "group",
  [sym_string] = "string",
  [aux_sym_program_repeat1] = "program_repeat1",
  [aux_sym_equality_repeat1] = "equality_repeat1",
  [aux_sym_comparision_repeat1] = "comparision_repeat1",
  [aux_sym_term_repeat1] = "term_repeat1",
  [aux_sym_factor_repeat1] = "factor_repeat1",
};

static const TSSymbol ts_symbol_map[] = {
  [ts_builtin_sym_end] = ts_builtin_sym_end,
  [anon_sym_var] = anon_sym_var,
  [anon_sym_EQ] = anon_sym_EQ,
  [anon_sym_SEMI] = anon_sym_SEMI,
  [anon_sym_print] = anon_sym_print,
  [anon_sym_BANG_EQ] = anon_sym_BANG_EQ,
  [anon_sym_EQ_EQ] = anon_sym_EQ_EQ,
  [anon_sym_GT] = anon_sym_GT,
  [anon_sym_GT_EQ] = anon_sym_GT_EQ,
  [anon_sym_LT] = anon_sym_LT,
  [anon_sym_LT_EQ] = anon_sym_LT_EQ,
  [anon_sym_DASH] = anon_sym_DASH,
  [anon_sym_PLUS] = anon_sym_PLUS,
  [anon_sym_SLASH] = anon_sym_SLASH,
  [anon_sym_STAR] = anon_sym_STAR,
  [anon_sym_BANG] = anon_sym_BANG,
  [sym_nil] = sym_nil,
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_number] = sym_number,
  [sym_identifier] = sym_identifier,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_token1] = aux_sym_string_token1,
  [sym_comment] = sym_comment,
  [sym_program] = sym_program,
  [sym__declaration] = sym__declaration,
  [sym_var_decl] = sym_var_decl,
  [sym__statement] = sym__statement,
  [sym_expr_stmt] = sym_expr_stmt,
  [sym_print_stmt] = sym_print_stmt,
  [sym__expression] = sym__expression,
  [sym__equality] = sym__equality,
  [sym_equality] = sym_equality,
  [sym__comparision] = sym__comparision,
  [sym_comparision] = sym_comparision,
  [sym__term] = sym__term,
  [sym_term] = sym_term,
  [sym__factor] = sym__factor,
  [sym_factor] = sym_factor,
  [sym__unary] = sym__unary,
  [sym_unary] = sym_unary,
  [sym__primary] = sym__primary,
  [sym_bool] = sym_bool,
  [sym_group] = sym_group,
  [sym_string] = sym_string,
  [aux_sym_program_repeat1] = aux_sym_program_repeat1,
  [aux_sym_equality_repeat1] = aux_sym_equality_repeat1,
  [aux_sym_comparision_repeat1] = aux_sym_comparision_repeat1,
  [aux_sym_term_repeat1] = aux_sym_term_repeat1,
  [aux_sym_factor_repeat1] = aux_sym_factor_repeat1,
};

static const TSSymbolMetadata ts_symbol_metadata[] = {
  [ts_builtin_sym_end] = {
    .visible = false,
    .named = true,
  },
  [anon_sym_var] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SEMI] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_print] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_EQ_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_GT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LT_EQ] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_DASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_PLUS] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_SLASH] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_STAR] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_BANG] = {
    .visible = true,
    .named = false,
  },
  [sym_nil] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_LPAREN] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_RPAREN] = {
    .visible = true,
    .named = false,
  },
  [sym_number] = {
    .visible = true,
    .named = true,
  },
  [sym_identifier] = {
    .visible = true,
    .named = true,
  },
  [anon_sym_DQUOTE] = {
    .visible = true,
    .named = false,
  },
  [aux_sym_string_token1] = {
    .visible = false,
    .named = false,
  },
  [sym_comment] = {
    .visible = true,
    .named = true,
  },
  [sym_program] = {
    .visible = true,
    .named = true,
  },
  [sym__declaration] = {
    .visible = false,
    .named = true,
  },
  [sym_var_decl] = {
    .visible = true,
    .named = true,
  },
  [sym__statement] = {
    .visible = false,
    .named = true,
  },
  [sym_expr_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym_print_stmt] = {
    .visible = true,
    .named = true,
  },
  [sym__expression] = {
    .visible = false,
    .named = true,
  },
  [sym__equality] = {
    .visible = false,
    .named = true,
  },
  [sym_equality] = {
    .visible = true,
    .named = true,
  },
  [sym__comparision] = {
    .visible = false,
    .named = true,
  },
  [sym_comparision] = {
    .visible = true,
    .named = true,
  },
  [sym__term] = {
    .visible = false,
    .named = true,
  },
  [sym_term] = {
    .visible = true,
    .named = true,
  },
  [sym__factor] = {
    .visible = false,
    .named = true,
  },
  [sym_factor] = {
    .visible = true,
    .named = true,
  },
  [sym__unary] = {
    .visible = false,
    .named = true,
  },
  [sym_unary] = {
    .visible = true,
    .named = true,
  },
  [sym__primary] = {
    .visible = false,
    .named = true,
  },
  [sym_bool] = {
    .visible = true,
    .named = true,
  },
  [sym_group] = {
    .visible = true,
    .named = true,
  },
  [sym_string] = {
    .visible = true,
    .named = true,
  },
  [aux_sym_program_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_equality_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_comparision_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_term_repeat1] = {
    .visible = false,
    .named = false,
  },
  [aux_sym_factor_repeat1] = {
    .visible = false,
    .named = false,
  },
};

static const TSSymbol ts_alias_sequences[PRODUCTION_ID_COUNT][MAX_ALIAS_SEQUENCE_LENGTH] = {
  [0] = {0},
};

static const uint16_t ts_non_terminal_alias_map[] = {
  0,
};

static const TSStateId ts_primary_state_ids[STATE_COUNT] = {
  [0] = 0,
  [1] = 1,
  [2] = 2,
  [3] = 3,
  [4] = 4,
  [5] = 5,
  [6] = 6,
  [7] = 7,
  [8] = 8,
  [9] = 9,
  [10] = 10,
  [11] = 11,
  [12] = 12,
  [13] = 13,
  [14] = 14,
  [15] = 15,
  [16] = 16,
  [17] = 17,
  [18] = 18,
  [19] = 19,
  [20] = 20,
  [21] = 21,
  [22] = 22,
  [23] = 23,
  [24] = 24,
  [25] = 25,
  [26] = 26,
  [27] = 27,
  [28] = 28,
  [29] = 29,
  [30] = 30,
  [31] = 31,
  [32] = 32,
  [33] = 33,
  [34] = 34,
  [35] = 35,
  [36] = 36,
  [37] = 37,
  [38] = 38,
  [39] = 39,
  [40] = 40,
  [41] = 41,
  [42] = 42,
  [43] = 43,
  [44] = 44,
};

static inline bool anon_sym_BANG_character_set_1(int32_t c) {
  return (c < 8192
    ? (c < ' '
      ? (c < '\r'
        ? (c >= '\t' && c <= '\n')
        : c <= '\r')
      : (c <= ' ' || (c < 5760
        ? c == 160
        : c <= 5760)))
    : (c <= 8203 || (c < 12288
      ? (c < 8287
        ? c == 8239
        : c <= 8288)
      : (c <= 12288 || c == 65279))));
}

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(7);
      if (lookahead == '!') ADVANCE(24);
      if (lookahead == '"') ADVANCE(47);
      if (lookahead == '(') ADVANCE(28);
      if (lookahead == ')') ADVANCE(29);
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == '+') ADVANCE(20);
      if (lookahead == '-') ADVANCE(19);
      if (lookahead == '/') ADVANCE(21);
      if (lookahead == ';') ADVANCE(11);
      if (lookahead == '<') ADVANCE(17);
      if (lookahead == '=') ADVANCE(10);
      if (lookahead == '>') ADVANCE(15);
      if (lookahead == 'f') ADVANCE(31);
      if (lookahead == 'n') ADVANCE(36);
      if (lookahead == 'p') ADVANCE(42);
      if (lookahead == 't') ADVANCE(40);
      if (lookahead == 'v') ADVANCE(32);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(30);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      if (anon_sym_BANG_character_set_1(lookahead)) SKIP(0)
      END_STATE();
    case 1:
      if (lookahead == '!') ADVANCE(23);
      if (lookahead == '"') ADVANCE(47);
      if (lookahead == '(') ADVANCE(28);
      if (lookahead == '-') ADVANCE(19);
      if (lookahead == '/') ADVANCE(3);
      if (lookahead == 'f') ADVANCE(31);
      if (lookahead == 'n') ADVANCE(36);
      if (lookahead == 't') ADVANCE(40);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(30);
      if (anon_sym_BANG_character_set_1(lookahead)) SKIP(1)
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 2:
      if (lookahead == '!') ADVANCE(4);
      if (lookahead == ')') ADVANCE(29);
      if (lookahead == '*') ADVANCE(22);
      if (lookahead == '+') ADVANCE(20);
      if (lookahead == '-') ADVANCE(19);
      if (lookahead == '/') ADVANCE(21);
      if (lookahead == ';') ADVANCE(11);
      if (lookahead == '<') ADVANCE(17);
      if (lookahead == '=') ADVANCE(5);
      if (lookahead == '>') ADVANCE(15);
      if (anon_sym_BANG_character_set_1(lookahead)) SKIP(2)
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 3:
      if (lookahead == '/') ADVANCE(52);
      END_STATE();
    case 4:
      if (lookahead == '=') ADVANCE(13);
      END_STATE();
    case 5:
      if (lookahead == '=') ADVANCE(14);
      END_STATE();
    case 6:
      if (eof) ADVANCE(7);
      if (lookahead == '!') ADVANCE(23);
      if (lookahead == '"') ADVANCE(47);
      if (lookahead == '(') ADVANCE(28);
      if (lookahead == '-') ADVANCE(19);
      if (lookahead == '/') ADVANCE(3);
      if (lookahead == ';') ADVANCE(11);
      if (lookahead == '=') ADVANCE(9);
      if (lookahead == 'f') ADVANCE(31);
      if (lookahead == 'n') ADVANCE(36);
      if (lookahead == 'p') ADVANCE(42);
      if (lookahead == 't') ADVANCE(40);
      if (lookahead == 'v') ADVANCE(32);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(30);
      if (('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      if (anon_sym_BANG_character_set_1(lookahead)) SKIP(6)
      END_STATE();
    case 7:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 8:
      ACCEPT_TOKEN(anon_sym_var);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 9:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 10:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(14);
      END_STATE();
    case 11:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 12:
      ACCEPT_TOKEN(anon_sym_print);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 13:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 14:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 15:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(16);
      END_STATE();
    case 16:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 17:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(18);
      END_STATE();
    case 18:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 19:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 20:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 21:
      ACCEPT_TOKEN(anon_sym_SLASH);
      if (lookahead == '/') ADVANCE(52);
      END_STATE();
    case 22:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 23:
      ACCEPT_TOKEN(anon_sym_BANG);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(anon_sym_BANG);
      if (lookahead == '=') ADVANCE(13);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(sym_nil);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_true);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_false);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(30);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(37);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'a') ADVANCE(41);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('b' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(26);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'e') ADVANCE(27);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(39);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'i') ADVANCE(38);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(43);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'l') ADVANCE(25);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'n') ADVANCE(44);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(45);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(8);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'r') ADVANCE(35);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 's') ADVANCE(34);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 't') ADVANCE(12);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(sym_identifier);
      if (lookahead == 'u') ADVANCE(33);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(sym_identifier);
      if (('0' <= lookahead && lookahead <= '9') ||
          ('a' <= lookahead && lookahead <= 'z')) ADVANCE(46);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\n') ADVANCE(51);
      if (lookahead == '"') ADVANCE(52);
      if (lookahead != 0) ADVANCE(48);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '/') ADVANCE(50);
      if (anon_sym_BANG_character_set_1(lookahead)) ADVANCE(49);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(51);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '/') ADVANCE(48);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(51);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(51);
      END_STATE();
    case 52:
      ACCEPT_TOKEN(sym_comment);
      if (lookahead != 0 &&
          lookahead != '\n') ADVANCE(52);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 6},
  [2] = {.lex_state = 6},
  [3] = {.lex_state = 6},
  [4] = {.lex_state = 1},
  [5] = {.lex_state = 1},
  [6] = {.lex_state = 1},
  [7] = {.lex_state = 1},
  [8] = {.lex_state = 1},
  [9] = {.lex_state = 1},
  [10] = {.lex_state = 1},
  [11] = {.lex_state = 1},
  [12] = {.lex_state = 2},
  [13] = {.lex_state = 2},
  [14] = {.lex_state = 2},
  [15] = {.lex_state = 2},
  [16] = {.lex_state = 6},
  [17] = {.lex_state = 2},
  [18] = {.lex_state = 2},
  [19] = {.lex_state = 2},
  [20] = {.lex_state = 6},
  [21] = {.lex_state = 6},
  [22] = {.lex_state = 6},
  [23] = {.lex_state = 2},
  [24] = {.lex_state = 2},
  [25] = {.lex_state = 2},
  [26] = {.lex_state = 2},
  [27] = {.lex_state = 2},
  [28] = {.lex_state = 2},
  [29] = {.lex_state = 2},
  [30] = {.lex_state = 2},
  [31] = {.lex_state = 2},
  [32] = {.lex_state = 2},
  [33] = {.lex_state = 2},
  [34] = {.lex_state = 2},
  [35] = {.lex_state = 2},
  [36] = {.lex_state = 6},
  [37] = {.lex_state = 2},
  [38] = {.lex_state = 0},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 0},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 49},
};

static const uint16_t ts_parse_table[LARGE_STATE_COUNT][SYMBOL_COUNT] = {
  [0] = {
    [ts_builtin_sym_end] = ACTIONS(1),
    [anon_sym_var] = ACTIONS(1),
    [anon_sym_EQ] = ACTIONS(1),
    [anon_sym_SEMI] = ACTIONS(1),
    [anon_sym_print] = ACTIONS(1),
    [anon_sym_BANG_EQ] = ACTIONS(1),
    [anon_sym_EQ_EQ] = ACTIONS(1),
    [anon_sym_GT] = ACTIONS(1),
    [anon_sym_GT_EQ] = ACTIONS(1),
    [anon_sym_LT] = ACTIONS(1),
    [anon_sym_LT_EQ] = ACTIONS(1),
    [anon_sym_DASH] = ACTIONS(1),
    [anon_sym_PLUS] = ACTIONS(1),
    [anon_sym_SLASH] = ACTIONS(1),
    [anon_sym_STAR] = ACTIONS(1),
    [anon_sym_BANG] = ACTIONS(1),
    [sym_nil] = ACTIONS(1),
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
    [sym_comment] = ACTIONS(3),
  },
  [1] = {
    [sym_program] = STATE(42),
    [sym__declaration] = STATE(3),
    [sym_var_decl] = STATE(3),
    [sym__statement] = STATE(3),
    [sym_expr_stmt] = STATE(3),
    [sym_print_stmt] = STATE(3),
    [sym__expression] = STATE(41),
    [sym__equality] = STATE(41),
    [sym_equality] = STATE(41),
    [sym__comparision] = STATE(34),
    [sym_comparision] = STATE(34),
    [sym__term] = STATE(28),
    [sym_term] = STATE(28),
    [sym__factor] = STATE(25),
    [sym_factor] = STATE(25),
    [sym__unary] = STATE(13),
    [sym_unary] = STATE(13),
    [sym__primary] = STATE(13),
    [sym_bool] = STATE(13),
    [sym_group] = STATE(13),
    [sym_string] = STATE(13),
    [aux_sym_program_repeat1] = STATE(3),
    [anon_sym_var] = ACTIONS(5),
    [anon_sym_print] = ACTIONS(7),
    [anon_sym_DASH] = ACTIONS(9),
    [anon_sym_BANG] = ACTIONS(9),
    [sym_nil] = ACTIONS(11),
    [anon_sym_true] = ACTIONS(13),
    [anon_sym_false] = ACTIONS(13),
    [anon_sym_LPAREN] = ACTIONS(15),
    [sym_number] = ACTIONS(17),
    [sym_identifier] = ACTIONS(11),
    [anon_sym_DQUOTE] = ACTIONS(19),
    [sym_comment] = ACTIONS(3),
  },
  [2] = {
    [sym__declaration] = STATE(2),
    [sym_var_decl] = STATE(2),
    [sym__statement] = STATE(2),
    [sym_expr_stmt] = STATE(2),
    [sym_print_stmt] = STATE(2),
    [sym__expression] = STATE(41),
    [sym__equality] = STATE(41),
    [sym_equality] = STATE(41),
    [sym__comparision] = STATE(34),
    [sym_comparision] = STATE(34),
    [sym__term] = STATE(28),
    [sym_term] = STATE(28),
    [sym__factor] = STATE(25),
    [sym_factor] = STATE(25),
    [sym__unary] = STATE(13),
    [sym_unary] = STATE(13),
    [sym__primary] = STATE(13),
    [sym_bool] = STATE(13),
    [sym_group] = STATE(13),
    [sym_string] = STATE(13),
    [aux_sym_program_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(21),
    [anon_sym_var] = ACTIONS(23),
    [anon_sym_print] = ACTIONS(26),
    [anon_sym_DASH] = ACTIONS(29),
    [anon_sym_BANG] = ACTIONS(29),
    [sym_nil] = ACTIONS(32),
    [anon_sym_true] = ACTIONS(35),
    [anon_sym_false] = ACTIONS(35),
    [anon_sym_LPAREN] = ACTIONS(38),
    [sym_number] = ACTIONS(41),
    [sym_identifier] = ACTIONS(32),
    [anon_sym_DQUOTE] = ACTIONS(44),
    [sym_comment] = ACTIONS(3),
  },
  [3] = {
    [sym__declaration] = STATE(2),
    [sym_var_decl] = STATE(2),
    [sym__statement] = STATE(2),
    [sym_expr_stmt] = STATE(2),
    [sym_print_stmt] = STATE(2),
    [sym__expression] = STATE(41),
    [sym__equality] = STATE(41),
    [sym_equality] = STATE(41),
    [sym__comparision] = STATE(34),
    [sym_comparision] = STATE(34),
    [sym__term] = STATE(28),
    [sym_term] = STATE(28),
    [sym__factor] = STATE(25),
    [sym_factor] = STATE(25),
    [sym__unary] = STATE(13),
    [sym_unary] = STATE(13),
    [sym__primary] = STATE(13),
    [sym_bool] = STATE(13),
    [sym_group] = STATE(13),
    [sym_string] = STATE(13),
    [aux_sym_program_repeat1] = STATE(2),
    [ts_builtin_sym_end] = ACTIONS(47),
    [anon_sym_var] = ACTIONS(5),
    [anon_sym_print] = ACTIONS(7),
    [anon_sym_DASH] = ACTIONS(9),
    [anon_sym_BANG] = ACTIONS(9),
    [sym_nil] = ACTIONS(11),
    [anon_sym_true] = ACTIONS(13),
    [anon_sym_false] = ACTIONS(13),
    [anon_sym_LPAREN] = ACTIONS(15),
    [sym_number] = ACTIONS(17),
    [sym_identifier] = ACTIONS(11),
    [anon_sym_DQUOTE] = ACTIONS(19),
    [sym_comment] = ACTIONS(3),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(17), 1,
      sym_number,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(11), 2,
      sym_nil,
      sym_identifier,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(25), 2,
      sym__factor,
      sym_factor,
    STATE(28), 2,
      sym__term,
      sym_term,
    STATE(34), 2,
      sym__comparision,
      sym_comparision,
    STATE(43), 3,
      sym__expression,
      sym__equality,
      sym_equality,
    STATE(13), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [50] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(17), 1,
      sym_number,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(11), 2,
      sym_nil,
      sym_identifier,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(25), 2,
      sym__factor,
      sym_factor,
    STATE(28), 2,
      sym__term,
      sym_term,
    STATE(34), 2,
      sym__comparision,
      sym_comparision,
    STATE(40), 3,
      sym__expression,
      sym__equality,
      sym_equality,
    STATE(13), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [100] = 12,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(17), 1,
      sym_number,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(11), 2,
      sym_nil,
      sym_identifier,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(25), 2,
      sym__factor,
      sym_factor,
    STATE(28), 2,
      sym__term,
      sym_term,
    STATE(34), 2,
      sym__comparision,
      sym_comparision,
    STATE(39), 3,
      sym__expression,
      sym__equality,
      sym_equality,
    STATE(13), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [150] = 11,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(17), 1,
      sym_number,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(11), 2,
      sym_nil,
      sym_identifier,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(25), 2,
      sym__factor,
      sym_factor,
    STATE(28), 2,
      sym__term,
      sym_term,
    STATE(35), 2,
      sym__comparision,
      sym_comparision,
    STATE(13), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [195] = 10,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(17), 1,
      sym_number,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(11), 2,
      sym_nil,
      sym_identifier,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(25), 2,
      sym__factor,
      sym_factor,
    STATE(31), 2,
      sym__term,
      sym_term,
    STATE(13), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [236] = 9,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(17), 1,
      sym_number,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(11), 2,
      sym_nil,
      sym_identifier,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    STATE(27), 2,
      sym__factor,
      sym_factor,
    STATE(13), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [273] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(51), 1,
      sym_number,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(49), 2,
      sym_nil,
      sym_identifier,
    STATE(19), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [306] = 8,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(15), 1,
      anon_sym_LPAREN,
    ACTIONS(19), 1,
      anon_sym_DQUOTE,
    ACTIONS(55), 1,
      sym_number,
    ACTIONS(9), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(13), 2,
      anon_sym_true,
      anon_sym_false,
    ACTIONS(53), 2,
      sym_nil,
      sym_identifier,
    STATE(15), 6,
      sym__unary,
      sym_unary,
      sym__primary,
      sym_bool,
      sym_group,
      sym_string,
  [339] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(61), 1,
      anon_sym_SLASH,
    ACTIONS(64), 1,
      anon_sym_STAR,
    STATE(12), 1,
      aux_sym_factor_repeat1,
    ACTIONS(59), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(57), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [366] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_SLASH,
    ACTIONS(73), 1,
      anon_sym_STAR,
    STATE(14), 1,
      aux_sym_factor_repeat1,
    ACTIONS(69), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(67), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [393] = 6,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(71), 1,
      anon_sym_SLASH,
    ACTIONS(73), 1,
      anon_sym_STAR,
    STATE(12), 1,
      aux_sym_factor_repeat1,
    ACTIONS(77), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(75), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [420] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(59), 3,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_SLASH,
    ACTIONS(57), 9,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [440] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(79), 6,
      ts_builtin_sym_end,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_LPAREN,
      sym_number,
      anon_sym_DQUOTE,
    ACTIONS(81), 6,
      anon_sym_var,
      anon_sym_print,
      sym_nil,
      anon_sym_true,
      anon_sym_false,
      sym_identifier,
  [460] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(85), 3,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_SLASH,
    ACTIONS(83), 9,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [480] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(89), 3,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_SLASH,
    ACTIONS(87), 9,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [500] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(93), 3,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_SLASH,
    ACTIONS(91), 9,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [520] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(95), 6,
      ts_builtin_sym_end,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_LPAREN,
      sym_number,
      anon_sym_DQUOTE,
    ACTIONS(97), 6,
      anon_sym_var,
      anon_sym_print,
      sym_nil,
      anon_sym_true,
      anon_sym_false,
      sym_identifier,
  [540] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(99), 6,
      ts_builtin_sym_end,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_LPAREN,
      sym_number,
      anon_sym_DQUOTE,
    ACTIONS(101), 6,
      anon_sym_var,
      anon_sym_print,
      sym_nil,
      anon_sym_true,
      anon_sym_false,
      sym_identifier,
  [560] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(103), 6,
      ts_builtin_sym_end,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_LPAREN,
      sym_number,
      anon_sym_DQUOTE,
    ACTIONS(105), 6,
      anon_sym_var,
      anon_sym_print,
      sym_nil,
      anon_sym_true,
      anon_sym_false,
      sym_identifier,
  [580] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(109), 3,
      anon_sym_GT,
      anon_sym_LT,
      anon_sym_SLASH,
    ACTIONS(107), 9,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [600] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(24), 1,
      aux_sym_term_repeat1,
    ACTIONS(113), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(115), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(111), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [623] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(26), 1,
      aux_sym_term_repeat1,
    ACTIONS(120), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(122), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(118), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [646] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(24), 1,
      aux_sym_term_repeat1,
    ACTIONS(122), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(126), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(124), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [669] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(113), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(111), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [687] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(29), 1,
      aux_sym_comparision_repeat1,
    ACTIONS(130), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(132), 2,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(128), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [708] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(30), 1,
      aux_sym_comparision_repeat1,
    ACTIONS(130), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(132), 2,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(134), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [729] = 5,
    ACTIONS(3), 1,
      sym_comment,
    STATE(30), 1,
      aux_sym_comparision_repeat1,
    ACTIONS(138), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(141), 2,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(136), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [750] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(144), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(136), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [766] = 4,
    ACTIONS(3), 1,
      sym_comment,
    STATE(33), 1,
      aux_sym_equality_repeat1,
    ACTIONS(146), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
    ACTIONS(148), 2,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
  [781] = 4,
    ACTIONS(3), 1,
      sym_comment,
    STATE(33), 1,
      aux_sym_equality_repeat1,
    ACTIONS(150), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
    ACTIONS(152), 2,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
  [796] = 4,
    ACTIONS(3), 1,
      sym_comment,
    STATE(32), 1,
      aux_sym_equality_repeat1,
    ACTIONS(148), 2,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
    ACTIONS(155), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [811] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(150), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [821] = 3,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(157), 1,
      anon_sym_EQ,
    ACTIONS(159), 1,
      anon_sym_SEMI,
  [831] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(161), 1,
      sym_identifier,
  [838] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(163), 1,
      anon_sym_DQUOTE,
  [845] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(165), 1,
      anon_sym_RPAREN,
  [852] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(167), 1,
      anon_sym_SEMI,
  [859] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(169), 1,
      anon_sym_SEMI,
  [866] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(171), 1,
      ts_builtin_sym_end,
  [873] = 2,
    ACTIONS(3), 1,
      sym_comment,
    ACTIONS(173), 1,
      anon_sym_SEMI,
  [880] = 2,
    ACTIONS(175), 1,
      aux_sym_string_token1,
    ACTIONS(177), 1,
      sym_comment,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 50,
  [SMALL_STATE(6)] = 100,
  [SMALL_STATE(7)] = 150,
  [SMALL_STATE(8)] = 195,
  [SMALL_STATE(9)] = 236,
  [SMALL_STATE(10)] = 273,
  [SMALL_STATE(11)] = 306,
  [SMALL_STATE(12)] = 339,
  [SMALL_STATE(13)] = 366,
  [SMALL_STATE(14)] = 393,
  [SMALL_STATE(15)] = 420,
  [SMALL_STATE(16)] = 440,
  [SMALL_STATE(17)] = 460,
  [SMALL_STATE(18)] = 480,
  [SMALL_STATE(19)] = 500,
  [SMALL_STATE(20)] = 520,
  [SMALL_STATE(21)] = 540,
  [SMALL_STATE(22)] = 560,
  [SMALL_STATE(23)] = 580,
  [SMALL_STATE(24)] = 600,
  [SMALL_STATE(25)] = 623,
  [SMALL_STATE(26)] = 646,
  [SMALL_STATE(27)] = 669,
  [SMALL_STATE(28)] = 687,
  [SMALL_STATE(29)] = 708,
  [SMALL_STATE(30)] = 729,
  [SMALL_STATE(31)] = 750,
  [SMALL_STATE(32)] = 766,
  [SMALL_STATE(33)] = 781,
  [SMALL_STATE(34)] = 796,
  [SMALL_STATE(35)] = 811,
  [SMALL_STATE(36)] = 821,
  [SMALL_STATE(37)] = 831,
  [SMALL_STATE(38)] = 838,
  [SMALL_STATE(39)] = 845,
  [SMALL_STATE(40)] = 852,
  [SMALL_STATE(41)] = 859,
  [SMALL_STATE(42)] = 866,
  [SMALL_STATE(43)] = 873,
  [SMALL_STATE(44)] = 880,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT_EXTRA(),
  [5] = {.entry = {.count = 1, .reusable = false}}, SHIFT(37),
  [7] = {.entry = {.count = 1, .reusable = false}}, SHIFT(5),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(10),
  [11] = {.entry = {.count = 1, .reusable = false}}, SHIFT(13),
  [13] = {.entry = {.count = 1, .reusable = false}}, SHIFT(23),
  [15] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [17] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [19] = {.entry = {.count = 1, .reusable = true}}, SHIFT(44),
  [21] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2),
  [23] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(37),
  [26] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(5),
  [29] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(10),
  [32] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(13),
  [35] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(23),
  [38] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(6),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(13),
  [44] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(44),
  [47] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program, 1),
  [49] = {.entry = {.count = 1, .reusable = false}}, SHIFT(19),
  [51] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [53] = {.entry = {.count = 1, .reusable = false}}, SHIFT(15),
  [55] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [57] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_factor_repeat1, 2),
  [59] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_factor_repeat1, 2),
  [61] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_factor_repeat1, 2), SHIFT_REPEAT(11),
  [64] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_factor_repeat1, 2), SHIFT_REPEAT(11),
  [67] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__factor, 1),
  [69] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__factor, 1),
  [71] = {.entry = {.count = 1, .reusable = false}}, SHIFT(11),
  [73] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [75] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_factor, 2),
  [77] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_factor, 2),
  [79] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_var_decl, 5),
  [81] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_var_decl, 5),
  [83] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [85] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3),
  [87] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_group, 3),
  [89] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_group, 3),
  [91] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary, 2),
  [93] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_unary, 2),
  [95] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_print_stmt, 3),
  [97] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_print_stmt, 3),
  [99] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_var_decl, 3),
  [101] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_var_decl, 3),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expr_stmt, 2),
  [105] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_expr_stmt, 2),
  [107] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_bool, 1),
  [109] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_bool, 1),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_term_repeat1, 2),
  [113] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_term_repeat1, 2),
  [115] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_term_repeat1, 2), SHIFT_REPEAT(9),
  [118] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__term, 1),
  [120] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym__term, 1),
  [122] = {.entry = {.count = 1, .reusable = true}}, SHIFT(9),
  [124] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 2),
  [126] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_term, 2),
  [128] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__comparision, 1),
  [130] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [132] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [134] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparision, 2),
  [136] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_comparision_repeat1, 2),
  [138] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_comparision_repeat1, 2), SHIFT_REPEAT(8),
  [141] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_comparision_repeat1, 2), SHIFT_REPEAT(8),
  [144] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_comparision_repeat1, 2),
  [146] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_equality, 2),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [150] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_equality_repeat1, 2),
  [152] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_equality_repeat1, 2), SHIFT_REPEAT(7),
  [155] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym__equality, 1),
  [157] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [159] = {.entry = {.count = 1, .reusable = true}}, SHIFT(21),
  [161] = {.entry = {.count = 1, .reusable = true}}, SHIFT(36),
  [163] = {.entry = {.count = 1, .reusable = true}}, SHIFT(17),
  [165] = {.entry = {.count = 1, .reusable = true}}, SHIFT(18),
  [167] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [169] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [171] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [173] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [175] = {.entry = {.count = 1, .reusable = false}}, SHIFT(38),
  [177] = {.entry = {.count = 1, .reusable = false}}, SHIFT_EXTRA(),
};

#ifdef __cplusplus
extern "C" {
#endif
#ifdef _WIN32
#define extern __declspec(dllexport)
#endif

extern const TSLanguage *tree_sitter_lox(void) {
  static const TSLanguage language = {
    .version = LANGUAGE_VERSION,
    .symbol_count = SYMBOL_COUNT,
    .alias_count = ALIAS_COUNT,
    .token_count = TOKEN_COUNT,
    .external_token_count = EXTERNAL_TOKEN_COUNT,
    .state_count = STATE_COUNT,
    .large_state_count = LARGE_STATE_COUNT,
    .production_id_count = PRODUCTION_ID_COUNT,
    .field_count = FIELD_COUNT,
    .max_alias_sequence_length = MAX_ALIAS_SEQUENCE_LENGTH,
    .parse_table = &ts_parse_table[0][0],
    .small_parse_table = ts_small_parse_table,
    .small_parse_table_map = ts_small_parse_table_map,
    .parse_actions = ts_parse_actions,
    .symbol_names = ts_symbol_names,
    .symbol_metadata = ts_symbol_metadata,
    .public_symbol_map = ts_symbol_map,
    .alias_map = ts_non_terminal_alias_map,
    .alias_sequences = &ts_alias_sequences[0][0],
    .lex_modes = ts_lex_modes,
    .lex_fn = ts_lex,
    .primary_state_ids = ts_primary_state_ids,
  };
  return &language;
}
#ifdef __cplusplus
}
#endif
