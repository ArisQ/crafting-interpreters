module.exports = grammar({
    name: 'lox',
    rules: {
        program: $ => repeat1($._declaration), // EOF
        _declaration: $ => choice(
            // $.class_decl,
            // $.fun_decl,
            $.var_decl,
            $._statement,
        ),
        var_decl: $ => seq('var', $.identifier, optional(seq('=', $._expression)), ';'),
        _statement: $ => choice(
            $.expr_stmt,
            $.print_stmt,
            $.if_stmt,
            $.block,
        ),
        expr_stmt: $ => seq($._expression, ';'),
        print_stmt: $ => seq('print', $._expression, ';'),
        block: $ => seq('{', repeat($._declaration) ,'}'),
        if_stmt: $ => prec.left(1, seq(
            'if', '(', $._expression, ')', $._statement,
            optional(seq('else', $._statement)),
        )),

        // page 80
        _expression: $ => $._assignment,

        _assignment: $ => choice($._equality, $.assignment),
        assignment: $ => seq($.identifier, '=', $._assignment),

        _equality: $ => choice($._comparision, $.equality),
        equality: $ => seq($._comparision, repeat1(seq(choice('!=', '=='), $._comparision))),

        _comparision: $ => choice($._term, $.comparision),
        comparision: $ => seq($._term, repeat1(seq(choice('>', '>=', '<', '<='), $._term))),

        _term: $ => choice($._factor, $.term),
        term: $ => seq($._factor, repeat1(seq(choice('-', '+'), $._factor))),

        _factor: $ => choice($._unary, $.factor),
        factor: $ => seq($._unary, repeat1(seq(choice('/', '*'), $._unary))),

        _unary: $ => choice($._primary, $.unary),
        unary: $ => seq(choice('!', '-'), $._unary),

        _primary: $ => choice(
            $.nil,
            $.bool,
            $.number,
            $.string,
            $.group,
            $.identifier,
        ),

        nil: $ => 'nil',
        bool: $ => choice('true', 'false'),
        group: $ => seq('(', $._expression, ')'),
        number: $ => /\d+(\.\d+)?/,
        identifier: $ => /[a-z][a-z0-9]*/,
        string: $ => seq('"', /[^"]*/, '"'),

        comment: $ => token(seq('//', /.*/)),
    },
    extras: $ => [$.comment, /[\s\p{Zs}\uFEFF\u2060\u200B]/],
});

