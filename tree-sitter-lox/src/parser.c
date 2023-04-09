#include <tree_sitter/parser.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#endif

#define LANGUAGE_VERSION 14
#define STATE_COUNT 49
#define LARGE_STATE_COUNT 4
#define SYMBOL_COUNT 44
#define ALIAS_COUNT 0
#define TOKEN_COUNT 25
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
  anon_sym_true = 16,
  anon_sym_false = 17,
  anon_sym_nil = 18,
  anon_sym_LPAREN = 19,
  anon_sym_RPAREN = 20,
  sym_number = 21,
  sym_identifier = 22,
  anon_sym_DQUOTE = 23,
  aux_sym_string_token1 = 24,
  sym_program = 25,
  sym_declaration = 26,
  sym_var_decl = 27,
  sym_statement = 28,
  sym_expr_stmt = 29,
  sym_print_stmt = 30,
  sym_expression = 31,
  sym_equality = 32,
  sym_comparision = 33,
  sym_term = 34,
  sym_factor = 35,
  sym_unary = 36,
  sym_primary = 37,
  sym_string = 38,
  aux_sym_program_repeat1 = 39,
  aux_sym_equality_repeat1 = 40,
  aux_sym_comparision_repeat1 = 41,
  aux_sym_term_repeat1 = 42,
  aux_sym_factor_repeat1 = 43,
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
  [anon_sym_true] = "true",
  [anon_sym_false] = "false",
  [anon_sym_nil] = "nil",
  [anon_sym_LPAREN] = "(",
  [anon_sym_RPAREN] = ")",
  [sym_number] = "number",
  [sym_identifier] = "identifier",
  [anon_sym_DQUOTE] = "\"",
  [aux_sym_string_token1] = "string_token1",
  [sym_program] = "program",
  [sym_declaration] = "declaration",
  [sym_var_decl] = "var_decl",
  [sym_statement] = "statement",
  [sym_expr_stmt] = "expr_stmt",
  [sym_print_stmt] = "print_stmt",
  [sym_expression] = "expression",
  [sym_equality] = "equality",
  [sym_comparision] = "comparision",
  [sym_term] = "term",
  [sym_factor] = "factor",
  [sym_unary] = "unary",
  [sym_primary] = "primary",
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
  [anon_sym_true] = anon_sym_true,
  [anon_sym_false] = anon_sym_false,
  [anon_sym_nil] = anon_sym_nil,
  [anon_sym_LPAREN] = anon_sym_LPAREN,
  [anon_sym_RPAREN] = anon_sym_RPAREN,
  [sym_number] = sym_number,
  [sym_identifier] = sym_identifier,
  [anon_sym_DQUOTE] = anon_sym_DQUOTE,
  [aux_sym_string_token1] = aux_sym_string_token1,
  [sym_program] = sym_program,
  [sym_declaration] = sym_declaration,
  [sym_var_decl] = sym_var_decl,
  [sym_statement] = sym_statement,
  [sym_expr_stmt] = sym_expr_stmt,
  [sym_print_stmt] = sym_print_stmt,
  [sym_expression] = sym_expression,
  [sym_equality] = sym_equality,
  [sym_comparision] = sym_comparision,
  [sym_term] = sym_term,
  [sym_factor] = sym_factor,
  [sym_unary] = sym_unary,
  [sym_primary] = sym_primary,
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
  [anon_sym_true] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_false] = {
    .visible = true,
    .named = false,
  },
  [anon_sym_nil] = {
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
  [sym_program] = {
    .visible = true,
    .named = true,
  },
  [sym_declaration] = {
    .visible = true,
    .named = true,
  },
  [sym_var_decl] = {
    .visible = true,
    .named = true,
  },
  [sym_statement] = {
    .visible = true,
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
  [sym_expression] = {
    .visible = true,
    .named = true,
  },
  [sym_equality] = {
    .visible = true,
    .named = true,
  },
  [sym_comparision] = {
    .visible = true,
    .named = true,
  },
  [sym_term] = {
    .visible = true,
    .named = true,
  },
  [sym_factor] = {
    .visible = true,
    .named = true,
  },
  [sym_unary] = {
    .visible = true,
    .named = true,
  },
  [sym_primary] = {
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
  [45] = 45,
  [46] = 46,
  [47] = 47,
  [48] = 48,
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
  START_LEXER();
  eof = lexer->eof(lexer);
  switch (state) {
    case 0:
      if (eof) ADVANCE(24);
      if (lookahead == '!') ADVANCE(41);
      if (lookahead == '"') ADVANCE(49);
      if (lookahead == '(') ADVANCE(45);
      if (lookahead == ')') ADVANCE(46);
      if (lookahead == '*') ADVANCE(39);
      if (lookahead == '+') ADVANCE(37);
      if (lookahead == '-') ADVANCE(36);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ';') ADVANCE(28);
      if (lookahead == '<') ADVANCE(34);
      if (lookahead == '=') ADVANCE(27);
      if (lookahead == '>') ADVANCE(32);
      if (lookahead == 'f') ADVANCE(4);
      if (lookahead == 'h') ADVANCE(8);
      if (lookahead == 'n') ADVANCE(10);
      if (lookahead == 'p') ADVANCE(19);
      if (lookahead == 't') ADVANCE(17);
      if (lookahead == 'v') ADVANCE(5);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(0)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 1:
      if (lookahead == '!') ADVANCE(2);
      if (lookahead == ')') ADVANCE(46);
      if (lookahead == '*') ADVANCE(39);
      if (lookahead == '+') ADVANCE(37);
      if (lookahead == '-') ADVANCE(36);
      if (lookahead == '/') ADVANCE(38);
      if (lookahead == ';') ADVANCE(28);
      if (lookahead == '<') ADVANCE(34);
      if (lookahead == '=') ADVANCE(3);
      if (lookahead == '>') ADVANCE(32);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(1)
      END_STATE();
    case 2:
      if (lookahead == '=') ADVANCE(30);
      END_STATE();
    case 3:
      if (lookahead == '=') ADVANCE(31);
      END_STATE();
    case 4:
      if (lookahead == 'a') ADVANCE(11);
      END_STATE();
    case 5:
      if (lookahead == 'a') ADVANCE(18);
      END_STATE();
    case 6:
      if (lookahead == 'e') ADVANCE(42);
      END_STATE();
    case 7:
      if (lookahead == 'e') ADVANCE(43);
      END_STATE();
    case 8:
      if (lookahead == 'e') ADVANCE(14);
      END_STATE();
    case 9:
      if (lookahead == 'i') ADVANCE(15);
      END_STATE();
    case 10:
      if (lookahead == 'i') ADVANCE(12);
      END_STATE();
    case 11:
      if (lookahead == 'l') ADVANCE(20);
      END_STATE();
    case 12:
      if (lookahead == 'l') ADVANCE(44);
      END_STATE();
    case 13:
      if (lookahead == 'l') ADVANCE(16);
      END_STATE();
    case 14:
      if (lookahead == 'l') ADVANCE(13);
      END_STATE();
    case 15:
      if (lookahead == 'n') ADVANCE(21);
      END_STATE();
    case 16:
      if (lookahead == 'o') ADVANCE(48);
      END_STATE();
    case 17:
      if (lookahead == 'r') ADVANCE(22);
      END_STATE();
    case 18:
      if (lookahead == 'r') ADVANCE(25);
      END_STATE();
    case 19:
      if (lookahead == 'r') ADVANCE(9);
      END_STATE();
    case 20:
      if (lookahead == 's') ADVANCE(7);
      END_STATE();
    case 21:
      if (lookahead == 't') ADVANCE(29);
      END_STATE();
    case 22:
      if (lookahead == 'u') ADVANCE(6);
      END_STATE();
    case 23:
      if (eof) ADVANCE(24);
      if (lookahead == '!') ADVANCE(40);
      if (lookahead == '"') ADVANCE(49);
      if (lookahead == '(') ADVANCE(45);
      if (lookahead == '-') ADVANCE(36);
      if (lookahead == ';') ADVANCE(28);
      if (lookahead == '=') ADVANCE(26);
      if (lookahead == 'f') ADVANCE(4);
      if (lookahead == 'h') ADVANCE(8);
      if (lookahead == 'n') ADVANCE(10);
      if (lookahead == 'p') ADVANCE(19);
      if (lookahead == 't') ADVANCE(17);
      if (lookahead == 'v') ADVANCE(5);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') SKIP(23)
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 24:
      ACCEPT_TOKEN(ts_builtin_sym_end);
      END_STATE();
    case 25:
      ACCEPT_TOKEN(anon_sym_var);
      END_STATE();
    case 26:
      ACCEPT_TOKEN(anon_sym_EQ);
      END_STATE();
    case 27:
      ACCEPT_TOKEN(anon_sym_EQ);
      if (lookahead == '=') ADVANCE(31);
      END_STATE();
    case 28:
      ACCEPT_TOKEN(anon_sym_SEMI);
      END_STATE();
    case 29:
      ACCEPT_TOKEN(anon_sym_print);
      END_STATE();
    case 30:
      ACCEPT_TOKEN(anon_sym_BANG_EQ);
      END_STATE();
    case 31:
      ACCEPT_TOKEN(anon_sym_EQ_EQ);
      END_STATE();
    case 32:
      ACCEPT_TOKEN(anon_sym_GT);
      if (lookahead == '=') ADVANCE(33);
      END_STATE();
    case 33:
      ACCEPT_TOKEN(anon_sym_GT_EQ);
      END_STATE();
    case 34:
      ACCEPT_TOKEN(anon_sym_LT);
      if (lookahead == '=') ADVANCE(35);
      END_STATE();
    case 35:
      ACCEPT_TOKEN(anon_sym_LT_EQ);
      END_STATE();
    case 36:
      ACCEPT_TOKEN(anon_sym_DASH);
      END_STATE();
    case 37:
      ACCEPT_TOKEN(anon_sym_PLUS);
      END_STATE();
    case 38:
      ACCEPT_TOKEN(anon_sym_SLASH);
      END_STATE();
    case 39:
      ACCEPT_TOKEN(anon_sym_STAR);
      END_STATE();
    case 40:
      ACCEPT_TOKEN(anon_sym_BANG);
      END_STATE();
    case 41:
      ACCEPT_TOKEN(anon_sym_BANG);
      if (lookahead == '=') ADVANCE(30);
      END_STATE();
    case 42:
      ACCEPT_TOKEN(anon_sym_true);
      END_STATE();
    case 43:
      ACCEPT_TOKEN(anon_sym_false);
      END_STATE();
    case 44:
      ACCEPT_TOKEN(anon_sym_nil);
      END_STATE();
    case 45:
      ACCEPT_TOKEN(anon_sym_LPAREN);
      END_STATE();
    case 46:
      ACCEPT_TOKEN(anon_sym_RPAREN);
      END_STATE();
    case 47:
      ACCEPT_TOKEN(sym_number);
      if (('0' <= lookahead && lookahead <= '9')) ADVANCE(47);
      END_STATE();
    case 48:
      ACCEPT_TOKEN(sym_identifier);
      END_STATE();
    case 49:
      ACCEPT_TOKEN(anon_sym_DQUOTE);
      END_STATE();
    case 50:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead == '\t' ||
          lookahead == '\n' ||
          lookahead == '\r' ||
          lookahead == ' ') ADVANCE(50);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(51);
      END_STATE();
    case 51:
      ACCEPT_TOKEN(aux_sym_string_token1);
      if (lookahead != 0 &&
          lookahead != '"') ADVANCE(51);
      END_STATE();
    default:
      return false;
  }
}

static const TSLexMode ts_lex_modes[STATE_COUNT] = {
  [0] = {.lex_state = 0},
  [1] = {.lex_state = 23},
  [2] = {.lex_state = 23},
  [3] = {.lex_state = 23},
  [4] = {.lex_state = 23},
  [5] = {.lex_state = 23},
  [6] = {.lex_state = 23},
  [7] = {.lex_state = 23},
  [8] = {.lex_state = 23},
  [9] = {.lex_state = 1},
  [10] = {.lex_state = 1},
  [11] = {.lex_state = 23},
  [12] = {.lex_state = 1},
  [13] = {.lex_state = 23},
  [14] = {.lex_state = 23},
  [15] = {.lex_state = 23},
  [16] = {.lex_state = 23},
  [17] = {.lex_state = 1},
  [18] = {.lex_state = 1},
  [19] = {.lex_state = 1},
  [20] = {.lex_state = 1},
  [21] = {.lex_state = 1},
  [22] = {.lex_state = 1},
  [23] = {.lex_state = 23},
  [24] = {.lex_state = 23},
  [25] = {.lex_state = 23},
  [26] = {.lex_state = 23},
  [27] = {.lex_state = 1},
  [28] = {.lex_state = 1},
  [29] = {.lex_state = 1},
  [30] = {.lex_state = 1},
  [31] = {.lex_state = 1},
  [32] = {.lex_state = 1},
  [33] = {.lex_state = 1},
  [34] = {.lex_state = 1},
  [35] = {.lex_state = 1},
  [36] = {.lex_state = 1},
  [37] = {.lex_state = 1},
  [38] = {.lex_state = 1},
  [39] = {.lex_state = 0},
  [40] = {.lex_state = 23},
  [41] = {.lex_state = 0},
  [42] = {.lex_state = 0},
  [43] = {.lex_state = 0},
  [44] = {.lex_state = 0},
  [45] = {.lex_state = 0},
  [46] = {.lex_state = 0},
  [47] = {.lex_state = 0},
  [48] = {.lex_state = 50},
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
    [anon_sym_true] = ACTIONS(1),
    [anon_sym_false] = ACTIONS(1),
    [anon_sym_nil] = ACTIONS(1),
    [anon_sym_LPAREN] = ACTIONS(1),
    [anon_sym_RPAREN] = ACTIONS(1),
    [sym_number] = ACTIONS(1),
    [sym_identifier] = ACTIONS(1),
    [anon_sym_DQUOTE] = ACTIONS(1),
  },
  [1] = {
    [sym_program] = STATE(41),
    [sym_declaration] = STATE(2),
    [sym_var_decl] = STATE(25),
    [sym_statement] = STATE(25),
    [sym_expr_stmt] = STATE(14),
    [sym_print_stmt] = STATE(14),
    [sym_expression] = STATE(42),
    [sym_equality] = STATE(39),
    [sym_comparision] = STATE(35),
    [sym_term] = STATE(31),
    [sym_factor] = STATE(28),
    [sym_unary] = STATE(12),
    [sym_primary] = STATE(18),
    [sym_string] = STATE(22),
    [aux_sym_program_repeat1] = STATE(2),
    [anon_sym_var] = ACTIONS(3),
    [anon_sym_print] = ACTIONS(5),
    [anon_sym_DASH] = ACTIONS(7),
    [anon_sym_BANG] = ACTIONS(7),
    [anon_sym_true] = ACTIONS(9),
    [anon_sym_false] = ACTIONS(9),
    [anon_sym_nil] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [sym_number] = ACTIONS(9),
    [sym_identifier] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(13),
  },
  [2] = {
    [sym_declaration] = STATE(3),
    [sym_var_decl] = STATE(25),
    [sym_statement] = STATE(25),
    [sym_expr_stmt] = STATE(14),
    [sym_print_stmt] = STATE(14),
    [sym_expression] = STATE(42),
    [sym_equality] = STATE(39),
    [sym_comparision] = STATE(35),
    [sym_term] = STATE(31),
    [sym_factor] = STATE(28),
    [sym_unary] = STATE(12),
    [sym_primary] = STATE(18),
    [sym_string] = STATE(22),
    [aux_sym_program_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(15),
    [anon_sym_var] = ACTIONS(3),
    [anon_sym_print] = ACTIONS(5),
    [anon_sym_DASH] = ACTIONS(7),
    [anon_sym_BANG] = ACTIONS(7),
    [anon_sym_true] = ACTIONS(9),
    [anon_sym_false] = ACTIONS(9),
    [anon_sym_nil] = ACTIONS(9),
    [anon_sym_LPAREN] = ACTIONS(11),
    [sym_number] = ACTIONS(9),
    [sym_identifier] = ACTIONS(9),
    [anon_sym_DQUOTE] = ACTIONS(13),
  },
  [3] = {
    [sym_declaration] = STATE(3),
    [sym_var_decl] = STATE(25),
    [sym_statement] = STATE(25),
    [sym_expr_stmt] = STATE(14),
    [sym_print_stmt] = STATE(14),
    [sym_expression] = STATE(42),
    [sym_equality] = STATE(39),
    [sym_comparision] = STATE(35),
    [sym_term] = STATE(31),
    [sym_factor] = STATE(28),
    [sym_unary] = STATE(12),
    [sym_primary] = STATE(18),
    [sym_string] = STATE(22),
    [aux_sym_program_repeat1] = STATE(3),
    [ts_builtin_sym_end] = ACTIONS(17),
    [anon_sym_var] = ACTIONS(19),
    [anon_sym_print] = ACTIONS(22),
    [anon_sym_DASH] = ACTIONS(25),
    [anon_sym_BANG] = ACTIONS(25),
    [anon_sym_true] = ACTIONS(28),
    [anon_sym_false] = ACTIONS(28),
    [anon_sym_nil] = ACTIONS(28),
    [anon_sym_LPAREN] = ACTIONS(31),
    [sym_number] = ACTIONS(28),
    [sym_identifier] = ACTIONS(28),
    [anon_sym_DQUOTE] = ACTIONS(34),
  },
};

static const uint16_t ts_small_parse_table[] = {
  [0] = 12,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    STATE(28), 1,
      sym_factor,
    STATE(31), 1,
      sym_term,
    STATE(35), 1,
      sym_comparision,
    STATE(39), 1,
      sym_equality,
    STATE(43), 1,
      sym_expression,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [42] = 12,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    STATE(28), 1,
      sym_factor,
    STATE(31), 1,
      sym_term,
    STATE(35), 1,
      sym_comparision,
    STATE(39), 1,
      sym_equality,
    STATE(47), 1,
      sym_expression,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [84] = 12,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    STATE(28), 1,
      sym_factor,
    STATE(31), 1,
      sym_term,
    STATE(35), 1,
      sym_comparision,
    STATE(39), 1,
      sym_equality,
    STATE(44), 1,
      sym_expression,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [126] = 10,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    STATE(28), 1,
      sym_factor,
    STATE(31), 1,
      sym_term,
    STATE(38), 1,
      sym_comparision,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [162] = 9,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    STATE(28), 1,
      sym_factor,
    STATE(34), 1,
      sym_term,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [195] = 4,
    STATE(9), 1,
      aux_sym_factor_repeat1,
    ACTIONS(39), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(41), 2,
      anon_sym_SLASH,
      anon_sym_STAR,
    ACTIONS(37), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [217] = 4,
    STATE(9), 1,
      aux_sym_factor_repeat1,
    ACTIONS(46), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(48), 2,
      anon_sym_SLASH,
      anon_sym_STAR,
    ACTIONS(44), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [239] = 8,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(12), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    STATE(30), 1,
      sym_factor,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [269] = 4,
    STATE(10), 1,
      aux_sym_factor_repeat1,
    ACTIONS(48), 2,
      anon_sym_SLASH,
      anon_sym_STAR,
    ACTIONS(52), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(50), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [291] = 1,
    ACTIONS(54), 12,
      ts_builtin_sym_end,
      anon_sym_var,
      anon_sym_print,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      anon_sym_LPAREN,
      sym_number,
      sym_identifier,
      anon_sym_DQUOTE,
  [306] = 1,
    ACTIONS(56), 12,
      ts_builtin_sym_end,
      anon_sym_var,
      anon_sym_print,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      anon_sym_LPAREN,
      sym_number,
      sym_identifier,
      anon_sym_DQUOTE,
  [321] = 1,
    ACTIONS(58), 12,
      ts_builtin_sym_end,
      anon_sym_var,
      anon_sym_print,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      anon_sym_LPAREN,
      sym_number,
      sym_identifier,
      anon_sym_DQUOTE,
  [336] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(18), 1,
      sym_primary,
    STATE(21), 1,
      sym_unary,
    STATE(22), 1,
      sym_string,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [363] = 2,
    ACTIONS(39), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(37), 10,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_SLASH,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [380] = 2,
    ACTIONS(62), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(60), 10,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_SLASH,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [397] = 2,
    ACTIONS(66), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(64), 10,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_SLASH,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [414] = 2,
    ACTIONS(70), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(68), 10,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_SLASH,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [431] = 2,
    ACTIONS(74), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(72), 10,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_SLASH,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [448] = 2,
    ACTIONS(78), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(76), 10,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_SLASH,
      anon_sym_STAR,
      anon_sym_RPAREN,
  [465] = 1,
    ACTIONS(80), 12,
      ts_builtin_sym_end,
      anon_sym_var,
      anon_sym_print,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      anon_sym_LPAREN,
      sym_number,
      sym_identifier,
      anon_sym_DQUOTE,
  [480] = 1,
    ACTIONS(82), 12,
      ts_builtin_sym_end,
      anon_sym_var,
      anon_sym_print,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      anon_sym_LPAREN,
      sym_number,
      sym_identifier,
      anon_sym_DQUOTE,
  [495] = 1,
    ACTIONS(84), 12,
      ts_builtin_sym_end,
      anon_sym_var,
      anon_sym_print,
      anon_sym_DASH,
      anon_sym_BANG,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      anon_sym_LPAREN,
      sym_number,
      sym_identifier,
      anon_sym_DQUOTE,
  [510] = 7,
    ACTIONS(11), 1,
      anon_sym_LPAREN,
    ACTIONS(13), 1,
      anon_sym_DQUOTE,
    STATE(17), 1,
      sym_unary,
    STATE(18), 1,
      sym_primary,
    STATE(22), 1,
      sym_string,
    ACTIONS(7), 2,
      anon_sym_DASH,
      anon_sym_BANG,
    ACTIONS(9), 5,
      anon_sym_true,
      anon_sym_false,
      anon_sym_nil,
      sym_number,
      sym_identifier,
  [537] = 4,
    STATE(29), 1,
      aux_sym_term_repeat1,
    ACTIONS(88), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(90), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(86), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [557] = 4,
    STATE(27), 1,
      aux_sym_term_repeat1,
    ACTIONS(90), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(94), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(92), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [577] = 4,
    STATE(29), 1,
      aux_sym_term_repeat1,
    ACTIONS(98), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(100), 2,
      anon_sym_DASH,
      anon_sym_PLUS,
    ACTIONS(96), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [597] = 2,
    ACTIONS(98), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(96), 8,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_DASH,
      anon_sym_PLUS,
      anon_sym_RPAREN,
  [612] = 4,
    STATE(32), 1,
      aux_sym_comparision_repeat1,
    ACTIONS(105), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(107), 2,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(103), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [630] = 4,
    STATE(33), 1,
      aux_sym_comparision_repeat1,
    ACTIONS(105), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(107), 2,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(109), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [648] = 4,
    STATE(33), 1,
      aux_sym_comparision_repeat1,
    ACTIONS(113), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(116), 2,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
    ACTIONS(111), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [666] = 2,
    ACTIONS(119), 2,
      anon_sym_GT,
      anon_sym_LT,
    ACTIONS(111), 6,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_GT_EQ,
      anon_sym_LT_EQ,
      anon_sym_RPAREN,
  [679] = 3,
    STATE(36), 1,
      aux_sym_equality_repeat1,
    ACTIONS(121), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
    ACTIONS(123), 2,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
  [691] = 3,
    STATE(37), 1,
      aux_sym_equality_repeat1,
    ACTIONS(123), 2,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
    ACTIONS(125), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [703] = 3,
    STATE(37), 1,
      aux_sym_equality_repeat1,
    ACTIONS(127), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
    ACTIONS(129), 2,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
  [715] = 1,
    ACTIONS(127), 4,
      anon_sym_SEMI,
      anon_sym_BANG_EQ,
      anon_sym_EQ_EQ,
      anon_sym_RPAREN,
  [722] = 1,
    ACTIONS(132), 2,
      anon_sym_SEMI,
      anon_sym_RPAREN,
  [727] = 2,
    ACTIONS(134), 1,
      anon_sym_EQ,
    ACTIONS(136), 1,
      anon_sym_SEMI,
  [734] = 1,
    ACTIONS(138), 1,
      ts_builtin_sym_end,
  [738] = 1,
    ACTIONS(140), 1,
      anon_sym_SEMI,
  [742] = 1,
    ACTIONS(142), 1,
      anon_sym_SEMI,
  [746] = 1,
    ACTIONS(144), 1,
      anon_sym_RPAREN,
  [750] = 1,
    ACTIONS(146), 1,
      anon_sym_DQUOTE,
  [754] = 1,
    ACTIONS(148), 1,
      sym_identifier,
  [758] = 1,
    ACTIONS(150), 1,
      anon_sym_SEMI,
  [762] = 1,
    ACTIONS(152), 1,
      aux_sym_string_token1,
};

static const uint32_t ts_small_parse_table_map[] = {
  [SMALL_STATE(4)] = 0,
  [SMALL_STATE(5)] = 42,
  [SMALL_STATE(6)] = 84,
  [SMALL_STATE(7)] = 126,
  [SMALL_STATE(8)] = 162,
  [SMALL_STATE(9)] = 195,
  [SMALL_STATE(10)] = 217,
  [SMALL_STATE(11)] = 239,
  [SMALL_STATE(12)] = 269,
  [SMALL_STATE(13)] = 291,
  [SMALL_STATE(14)] = 306,
  [SMALL_STATE(15)] = 321,
  [SMALL_STATE(16)] = 336,
  [SMALL_STATE(17)] = 363,
  [SMALL_STATE(18)] = 380,
  [SMALL_STATE(19)] = 397,
  [SMALL_STATE(20)] = 414,
  [SMALL_STATE(21)] = 431,
  [SMALL_STATE(22)] = 448,
  [SMALL_STATE(23)] = 465,
  [SMALL_STATE(24)] = 480,
  [SMALL_STATE(25)] = 495,
  [SMALL_STATE(26)] = 510,
  [SMALL_STATE(27)] = 537,
  [SMALL_STATE(28)] = 557,
  [SMALL_STATE(29)] = 577,
  [SMALL_STATE(30)] = 597,
  [SMALL_STATE(31)] = 612,
  [SMALL_STATE(32)] = 630,
  [SMALL_STATE(33)] = 648,
  [SMALL_STATE(34)] = 666,
  [SMALL_STATE(35)] = 679,
  [SMALL_STATE(36)] = 691,
  [SMALL_STATE(37)] = 703,
  [SMALL_STATE(38)] = 715,
  [SMALL_STATE(39)] = 722,
  [SMALL_STATE(40)] = 727,
  [SMALL_STATE(41)] = 734,
  [SMALL_STATE(42)] = 738,
  [SMALL_STATE(43)] = 742,
  [SMALL_STATE(44)] = 746,
  [SMALL_STATE(45)] = 750,
  [SMALL_STATE(46)] = 754,
  [SMALL_STATE(47)] = 758,
  [SMALL_STATE(48)] = 762,
};

static const TSParseActionEntry ts_parse_actions[] = {
  [0] = {.entry = {.count = 0, .reusable = false}},
  [1] = {.entry = {.count = 1, .reusable = false}}, RECOVER(),
  [3] = {.entry = {.count = 1, .reusable = true}}, SHIFT(46),
  [5] = {.entry = {.count = 1, .reusable = true}}, SHIFT(4),
  [7] = {.entry = {.count = 1, .reusable = true}}, SHIFT(16),
  [9] = {.entry = {.count = 1, .reusable = true}}, SHIFT(22),
  [11] = {.entry = {.count = 1, .reusable = true}}, SHIFT(6),
  [13] = {.entry = {.count = 1, .reusable = true}}, SHIFT(48),
  [15] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_program, 1),
  [17] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2),
  [19] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(46),
  [22] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(4),
  [25] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(16),
  [28] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(22),
  [31] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(6),
  [34] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_program_repeat1, 2), SHIFT_REPEAT(48),
  [37] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_factor_repeat1, 2),
  [39] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_factor_repeat1, 2),
  [41] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_factor_repeat1, 2), SHIFT_REPEAT(26),
  [44] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_factor, 2),
  [46] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_factor, 2),
  [48] = {.entry = {.count = 1, .reusable = true}}, SHIFT(26),
  [50] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_factor, 1),
  [52] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_factor, 1),
  [54] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_print_stmt, 3),
  [56] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_statement, 1),
  [58] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_var_decl, 5),
  [60] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary, 1),
  [62] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_unary, 1),
  [64] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_string, 3),
  [66] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_string, 3),
  [68] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primary, 3),
  [70] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_primary, 3),
  [72] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_unary, 2),
  [74] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_unary, 2),
  [76] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_primary, 1),
  [78] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_primary, 1),
  [80] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_var_decl, 3),
  [82] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expr_stmt, 2),
  [84] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_declaration, 1),
  [86] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 2),
  [88] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_term, 2),
  [90] = {.entry = {.count = 1, .reusable = true}}, SHIFT(11),
  [92] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_term, 1),
  [94] = {.entry = {.count = 1, .reusable = false}}, REDUCE(sym_term, 1),
  [96] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_term_repeat1, 2),
  [98] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_term_repeat1, 2),
  [100] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_term_repeat1, 2), SHIFT_REPEAT(11),
  [103] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparision, 1),
  [105] = {.entry = {.count = 1, .reusable = false}}, SHIFT(8),
  [107] = {.entry = {.count = 1, .reusable = true}}, SHIFT(8),
  [109] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_comparision, 2),
  [111] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_comparision_repeat1, 2),
  [113] = {.entry = {.count = 2, .reusable = false}}, REDUCE(aux_sym_comparision_repeat1, 2), SHIFT_REPEAT(8),
  [116] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_comparision_repeat1, 2), SHIFT_REPEAT(8),
  [119] = {.entry = {.count = 1, .reusable = false}}, REDUCE(aux_sym_comparision_repeat1, 2),
  [121] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_equality, 1),
  [123] = {.entry = {.count = 1, .reusable = true}}, SHIFT(7),
  [125] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_equality, 2),
  [127] = {.entry = {.count = 1, .reusable = true}}, REDUCE(aux_sym_equality_repeat1, 2),
  [129] = {.entry = {.count = 2, .reusable = true}}, REDUCE(aux_sym_equality_repeat1, 2), SHIFT_REPEAT(7),
  [132] = {.entry = {.count = 1, .reusable = true}}, REDUCE(sym_expression, 1),
  [134] = {.entry = {.count = 1, .reusable = true}}, SHIFT(5),
  [136] = {.entry = {.count = 1, .reusable = true}}, SHIFT(23),
  [138] = {.entry = {.count = 1, .reusable = true}},  ACCEPT_INPUT(),
  [140] = {.entry = {.count = 1, .reusable = true}}, SHIFT(24),
  [142] = {.entry = {.count = 1, .reusable = true}}, SHIFT(13),
  [144] = {.entry = {.count = 1, .reusable = true}}, SHIFT(20),
  [146] = {.entry = {.count = 1, .reusable = true}}, SHIFT(19),
  [148] = {.entry = {.count = 1, .reusable = true}}, SHIFT(40),
  [150] = {.entry = {.count = 1, .reusable = true}}, SHIFT(15),
  [152] = {.entry = {.count = 1, .reusable = true}}, SHIFT(45),
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
