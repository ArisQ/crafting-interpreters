module.exports = grammar({
    name: 'lox',
    rules: {
        program: $ => repeat1($.declaration), // EOF
        declaration: $ => choice(
            // $.class_decl,
            // $.fun_decl,
            $.var_decl,
            $.statement,
        ),
        var_decl: $ => seq('var', $.identifier, optional(seq('=', $.expression)), ';'),
        statement: $ => choice(
            $.expr_stmt,
            $.print_stmt,
        ),
        expr_stmt: $ => seq($.expression, ';'),
        print_stmt: $ => seq('print', $.expression, ';'),

        // page 80
        expression: $ => $.equality,
        equality: $ => seq($.comparision, repeat(seq(choice('!=', '=='), $.comparision))),
        comparision: $ => seq($.term, repeat(seq(choice('>', '>=', '<', '<='), $.term))),
        term: $ => seq($.factor, repeat(seq(choice('-', '+'), $.factor))),
        factor: $ => seq($.unary, repeat(seq(choice('/', '*'), $.unary))),
        unary: $ => choice(
            seq(choice('!', '-'), $.unary),
            $.primary,
        ),
        primary: $ => choice(
            $.number, $.string,
            'true', 'false', 'nil',
            seq('(', $.expression, ')'),
            $.identifier,
        ),

        number: $ => /\d+/,
        identifier: $ => 'hello',
        string: $ => seq('"', /[^"]*/, '"'),
    }
});

