;*=====================================================================*/
;*    serrano/prgm/project/bigloo/cigloo/Parser/lexer.scm              */
;*    -------------------------------------------------------------    */
;*    Author      :  Manuel Serrano                                    */
;*    Creation    :  Fri Nov 24 11:36:25 1995                          */
;*    Last change :  Sun Aug 31 16:05:12 2008 (serrano)                */
;*    -------------------------------------------------------------    */
;*    The C lexer                                                      */
;*=====================================================================*/

;*---------------------------------------------------------------------*/
;*    The module                                                       */
;*---------------------------------------------------------------------*/
(module parser_lexer
   (import  parser_tools
	    parser_cpp
	    engine_param)
   (export  (init-lexer!)
	    lexer
	    (define-type-id <string>)))

;*---------------------------------------------------------------------*/
;*    define-type-id ...                                               */
;*---------------------------------------------------------------------*/
(define (define-type-id string)
   (putprop! (string->symbol string) 'typedef #t))

;*---------------------------------------------------------------------*/
;*    *keyword-list*                                                   */
;*---------------------------------------------------------------------*/
(define *keyword-list*
   '("asm"
     "auto"
     "break"
     "case"
     "char"
     "const"
     "__const"
     "continue"
     "default"
     "do"
     "double"
     "else"
     "enum"
     "extern"
     "float"
     "for"
     "fortran"
     "goto"
     "if"
     "int"
     "long"
     "register"
     "restrict"
     "__restrict"
     "__restrict__"
     "return"
     "short"
     "signed"
     "sizeof"
     "static"
     "struct"
     "switch"
     "typedef"
     "union"
     "unsigned"
     "void"
     "volatile"
     "while"
     "FILE"
     "obj_t"))

(define *gcc-keyword-list*
   '("__attribute__" "inline" "__inline__" "__inline" "__extension__" "__gnuc_va_list"))

;*---------------------------------------------------------------------*/
;*    lexer initialization                                             */
;*---------------------------------------------------------------------*/
(define (init-lexer!)
   (for-each (lambda (word)
		(putprop! (string->symbol word) 'reserved #t))
	     *keyword-list*)
   (if *gcc-extensions?*
       (for-each (lambda (word)
		    (putprop! (string->symbol word) 'reserved #t))
		 *gcc-keyword-list*)))

;*---------------------------------------------------------------------*/
;*    lexer ...                                                        */
;*---------------------------------------------------------------------*/
(define lexer
   (regular-grammar ((nonzero-digit   (in ("19")))
		     (odigit          (in ("07")))
		     (long-suffix     (or #\l #\L))
		     (unsigned-suffix (or #\u #\U)))

      ;; blank
      ((+ (in #\space #\newline #\tab #a012))
       (ignore))

      ;; comment
      ((: "/*" (* (or (out #\*) (: (+ #\*) (out #\/ #\*)))) (+ #\*) "/")
       (ignore))

      ;; __extension__
      ("__extension__"
        (ignore))

      ;; cpp rules
      ((bol (: #\# (* (or all
			  (: #\\ #\Newline)
			  (: "/*" (* (or (out #\*) (: (+ #\*) (out #\/ #\*))))
				  (+ #\*) "/")))))
       (let ((coord  (the-coord input-port))
	     (string (the-string))
	     (ctx (make-cell 'noctx)))
	  (set-cpp-coord! coord)
	  (try (read/lalrp cpp-parser
			   (lambda (port _)
			      (read/rp cpp-lexer port ctx))
			   (open-input-string string))
	       (lambda (escape proc mes obj)
		  (error "cigloo" "cpp parser" (list 'cpp coord mes))))
	  (set-cpp-coord! #f)
	  (ignore)))

      ;; comma
      (#\,
       (list 'COMMA (the-coord input-port)))

      ;; semi-comma
      (#\;
       (list 'SEMI-COMMA (the-coord input-port)))

      ;; dots
      (#\.
       (list 'DOT (the-coord input-port)))
      
      ;; bracket
      (#\{
       (list 'BRA-OPEN (the-coord input-port)))
      (#\}
       (list 'BRA-CLO (the-coord input-port)))

      ;; angle
      (#\[
       (list 'ANGLE-OPEN (the-coord input-port)))
      (#\]
       (list 'ANGLE-CLO (the-coord input-port)))

      ;; parenthesis
      (#\(
       (list 'PAR-OPEN (the-coord input-port)))
      (#\)
       (list 'PAR-CLO (the-coord input-port)))

      ;; ldots
      ("..."
       (list 'LDOTS (the-coord input-port)))
      
      ;; integer constant
      ((: (or (: nonzero-digit (* digit))
	      (: #\0 (* odigit))
	      (: (uncase "0x") (+ xdigit)))
	  (? (or long-suffix
		 (: long-suffix unsigned-suffix)
		 unsigned-suffix
		 (: unsigned-suffix long-suffix))))
       (list 'CONSTANT (the-coord input-port) (the-string)))

      ;; floating-point constant
      ((or (: (+ digit)
	      (: (in #\e #\E) (? (in #\- #\+)) (+ digit))
	      (? (in #\f #\F #\l #\L)))
	   (: (or (: (+ digit) #\. (* digit)) (: #\. (+ digit)))
	      (? (: (in #\e #\E) (? (in #\- #\+)) (+ digit)))
	      (? (in #\f #\F #\l #\L))))
       (list 'CONSTANT (the-coord input-port) (the-string)))

      ;; character constant
      ((: (? #\L) #\' (+ all) #\')
       (list 'CONSTANT (the-coord input-port) (the-string)))

      ;; string constant
      ((: (? #\L) #\" (* (out #\")) #\")
       (list 'CONSTANT (the-coord input-port) (the-string)))

      ;; operators
      ((in #\* #\+ #\- #\/ #\% #\& #\~ #\! #\/ #\% #\= #\< #\> #\? #\^ #\:)
       (list (the-symbol) (the-coord input-port)))
      (#\|
       (list 'BOR (the-coord input-port)))

      ((or "&&" "<<" ">>" "<=" ">=" "==" "!=" "->" "++" "--" "+="
	   "-=" "*=" "/=" "%=" "<<=" ">>=" "&=" "^=")
       (list (the-symbol) (the-coord input-port)))
      ("||"
       (list 'OR (the-coord input-port)))
      ("|="
       (list 'OR= (the-coord input-port)))

      ;; identifier
      ((: (or #\_ alpha) (* (or #\_ alpha digit)))
       (let* ((string   (the-string))
	      (symbol   (string->symbol string)))
	  (cond
	     ((getprop symbol 'reserved)
	      (list symbol (the-coord input-port)))
	     ((getprop symbol 'typedef)
	      ;; see the `declaration' rule in the grammar to
	      ;; discover where the `typedef' property is set.
	      (list 'TYPE-ID (the-coord input-port) string))
	     (else
	      (list 'ID (the-coord input-port) string)))))

      ;; error
      (else
       (let ((c (the-failure)))
	  (if (eof-object? c)
	      c
	      (list 'ERROR
		    (the-coord input-port)
		    c))))))

