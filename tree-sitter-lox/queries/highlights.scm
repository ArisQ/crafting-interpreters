; highlights.scm

; [
;  "print",
;  "var",
;  "if",
;  "else"
; ] @keyword
"print" @keyword
"var" @keyword
"if" @keyword
"else" @keyword

"!=" @operator
"==" @operator

">" @operator
">=" @operator
"<" @operator
"<=" @operator

"+" @operator
"-" @operator
"*" @operator
"/" @operator

"!" @operator
; "-" @operator

"=" @operator

; "nil" @keyword
(nil) @constant

; "true" @boolean
; "false" @boolean
(bool) @boolean

(number) @number
(string) @string

; (identifier) @identifier
(identifier) @variable
(comment) @comment

; module
; constructor
; variable.parameter
; type
; number
; string
; constant
; embedded
; punctuation.delimiter
; property
; comment
; keyword
; attribute
; constant.builtin
; type.builtin
; tag
; string.special
; function.builtin
; variable.builtin
; operator
; function
; punctuation.bracket
