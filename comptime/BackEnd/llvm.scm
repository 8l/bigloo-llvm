(module backend_llvm
   (include "Engine/pass.sch"
	    "Ast/unit.sch"
	    "Tools/trace.sch")
   
   (import cc_exec
           engine_param
           engine_configure
           type_type
           tools_error
           tools_speek
           tools_shape
           object_slots
           backend_backend
           backend_cplib
           backend_bvm

           ast_var
           ast_env
	   ast_node
           ast_local

           object_class
           module_module
           type_env
           type_cache
           type_typeof

           llvm_ir
           )

   (export (class llvm::bvm)

           (wide-class sfun/integrated::sfun
              (label::bstring read-only)
              integrated::bool)))

(register-backend! 'llvm build-llvm-backend)

(define (build-llvm-backend)
  (instantiate::llvm
     (language 'llvm)
     (heap-compatible 'c)))

(define *llc* "llc")
(define *assembler* "gcc")

(define-method (backend-link me::llvm prefix)
  (verbose 1 "      Translating IR " prefix #\Newline)
  (llc prefix)
  (verbose 1 "      Assembling " prefix ".s" #\Newline)
  (assemble prefix))

(define (llc prefix)
  (let ((cmd (string-append *llc* " " "-disable-cfi " prefix ".ll")))
    (exec cmd #t "llc")))

(define (assemble prefix)
  (let ((cmd (string-append *assembler* " -c " prefix ".s")))
    (exec cmd #t "as")))

(define (emit-comment . args)
  (display (let ((p (open-output-string)))
             (display ";; " p)
             (for-each (lambda (x) (display x p)) args)
             (newline p)
             (close-output-port p)) *ir-port*))

(define-method (backend-compile me::llvm)
  (pass-prelude "LLVM IR generation"
                (lambda () (start-emission!)))

  (emit-header)
  (emit-newline)
  (emit-prototypes)
  (emit-newline)
  (emit-function-definitions me)

  (stop-emission!))

(define (emit-newline)
  (newline *ir-port*))

(define (emit-header)
  (emit-comment "From " *src-files*)
  (emit-comment *bigloo-name*)
  (emit-comment (string-append *bigloo-author* " (c) " *bigloo-date*)))

(define (emit-prototypes)
  (verbose 3 "      All types:\n")
  (for-each-global!
   (lambda (global)
     (set-variable-name! global)
       (if (require-prototype? global)
           (begin
             (emit-prototype (global-value global) global)
             (emit-newline))))))

(define (emit-ir . nodes)
  (display (line-tree->string
            (ir-node->line-tree (apply make-node-seq nodes)) -1)
           *ir-port*)
  (emit-newline))

(define-generic (emit-prototype value::value variable::variable))

(define-method (emit-prototype value::cfun variable)
  (verbose 3 "       emit-prototype ::cfun " (variable-id variable) "\n")
  (if (cfun-macro? value)         ; don't prototype "==" etc for now
      (emit-ir
       (comment "Missing prototype for macro `~s'" (variable-id variable)))
      (with-access::global variable (id type name library)
        (let* ((arity (cfun-arity value))
               (targs (cfun-args-type value)))
          (if (<fx arity 0)
              (verbose 1 "       skipping varargs fun\n")
              (begin
                (verbose 3 "        args: " (map type->ir-type targs) "\n")
                (emit-ir
                 (comment "C function `~s'" id)
                 (instantiate::ir-function-decl
                  (return-type (type->ir-type type))
                  (name name)
                  (arguments (map type->ir-type targs))))))))))
  
(define-method (emit-prototype value::sfun variable)
  (verbose 3 "       emit-prototype ::sfun " (variable-id variable)
           " " (variable-name variable) "\n")
  (with-access::global variable (id type name import)
     (let ((types (map (lambda (a)
                           (let ((t (if (type? a)
                                        a
                                        (local-type a))))
                             (type->ir-type t)))
                       (sfun-args value))))
       (verbose 3 "        args: " types "\n")
       (emit-ir
        (comment "Scheme function `~s' (~s)" id import)
        (instantiate::ir-function-decl
         (return-type (type->ir-type type))
         (name name)
         (arguments types))))))

(define-method (emit-prototype value::svar variable)
  (verbose 3 "       emit-prototype ::svar " (variable-id variable) "\n")
  (with-access::global variable (id type name import)
     (emit-ir
      (comment "Scheme variable `~s' (~s)" id import)
      (instantiate::ir-assignment
       (name (string-append "@" name))
       (node (instantiate::ir-global-variable
              (initial-value (instantiate::ir-zero-initializer
                              (value-type (type->ir-type type))))))))))

(define-method (emit-prototype value::scnst variable)
  (verbose 3 "       emit-prototype ::scnst " (variable-id variable) "\n")
  (with-access::global variable (id type name import)
     ;; TODO: do something!!
     (emit-ir
      (comment "Scheme constant `~s' (~s)" id import)
      (instantiate::ir-assignment
       (name (string-append "@" name))
       (node (instantiate::ir-global-variable
              (initial-value (instantiate::ir-zero-initializer
                              (value-type (type->ir-type type))))))))
     (verbose 3 "        class " (scnst-class value) "\n")))

(define-method (emit-prototype value::value variable)
  (verbose 3 "       emit-prototype dummy " (variable-id variable)
           " " value "\n"))

;; from c_proto, but changed
(define (require-prototype? global)
  (and (or (not (eq? (global-module global) *module*))
           (not (sfun? (global-value global))))
       (or (>fx (global-occurrence global) 0)
           (eq? (global-removable global) 'never))))

(define-method (backend-link-objects me::llvm sources)
  (verbose 1 "      backend-link-objects llvm" sources #\Newline))

;; TODO: How does this table work?
(define-method (backend-cnst-table-name me::llvm offset)
  "__cnst")

(define *dest-prefix* #f)
(define *ir-port*     #f)

(define (start-emission!)
  ;; TODO: handle *dest*
  (let* ((prefix (prefix (car *src-files*)))
         (filename (string-append prefix ".ll")))
    (set! *ir-port* (open-output-file filename))
    (set! *dest-prefix* prefix)
    (if (not (output-port? *ir-port*))
        (error *bigloo-name* "Can't open file for output" filename)
        #unspecified)))

(define (stop-emission!)
  (flush-output-port *ir-port*)
  (close-output-port *ir-port*)
  (set! *ir-port* #f)
  *dest-prefix*)

(define (emit-function-definitions llvm::llvm)
  (for-each emit-function-definition (llvm-functions llvm)))

(define (emit-function-definition global::global)
  (with-access::global global (type id name import value)
    (let ((arg-assoc
           (map (lambda (local)
                  (list local
                        (fresh-ir-variable
                         'arg (type->ir-type (local-type local)))))
                (sfun-args value))))
     (emit-comment id "(" import ")")
     (emit-ir
      (instantiate::ir-function-defn
       (return-type (type->ir-type type))
       (name name)
       (arguments (map (lambda (v)
                         (list (ir-variable-type (cadr v))
                               (ir-variable-name (cadr v))))
                       arg-assoc))
       (blocks
        (list
         (apply make-node-seq
                (map (lambda (arg)
                       (compile-allocate-formal
                        arg (cadr (assoc arg arg-assoc))))
                     (sfun-args value)))
         (node->ir-node (sfun-body value) ret-kont))))))))

(define (compile-allocate-formal local #!optional initial-value)
  (set-variable-name! local)
  (let* ((name (string-append "%" (local-name local)))
         (type (type->ir-type/ptr (local-type local)))
         (var (instantiate::ir-variable
               (name name) (value-type type)))
         (allocation (compile-local-allocation var)))
    (make-node-seq
     (comment "Parameter `~s'" (local-id local))
     (if initial-value
         (make-node-seq
          allocation
          (compile-store var initial-value))
         allocation))))
     

;;; LLVM versions of Bigloo types.

(define *llvm-object-type* (make-ir-primitive-type "i8*"))
(define *llvm-string-type* (make-ir-primitive-type "i8*"))
(define *llvm-int-type* (make-ir-primitive-type "i32"))
(define *llvm-bool-type* (make-ir-primitive-type "i1"))
(define *llvm-long-type* (make-ir-primitive-type "i32"))

(define (type->ir-type type)
  (if (ir-type? type)
      type
      (if (bigloo-type? type)
          *llvm-object-type*
          (case (type-id type)
            ((string) *llvm-string-type*)
            ((long) *llvm-long-type*)
            ((int) *llvm-int-type*)
            ((bool) *llvm-bool-type*)
            (else
             (internal-error 'type->ir-type "unhandled type"
                             (type-id type)))))))

(define (pointerify type)
  (instantiate::ir-pointer-type
   (value-type (type->ir-type type))))

(define unpointerify ir-pointer-type-value-type)

(define (type->ir-type/ptr type)
  (instantiate::ir-pointer-type
   (value-type (type->ir-type type))))


;;; Compiling AST nodes to LLVM IR nodes.

(define-generic (node->ir-node::ir-node node::node kont::procedure))

(define-method (node->ir-node node::let-var kont)
  (verbose 3 "       node->ir-node ::let-var\n")
  (with-access::let-var node (body bindings)
     (let ((assignments
            (map (lambda (x)
                   (set-variable-name! (car x))
                   (let* ((var (var->ir-node/ptr (car x)))
                          (name (ir-variable-name var))
                          (type (ir-variable-type var)))
                     (node->ir-node
                      (cdr x)
                      (lambda (v)
                        (make-node-seq
                         (comment "Local variable ~s" (variable-id (car x)))
                         (compile-local-allocation var)
                         (compile-store/aux var v))))))
                 bindings)))
       (make-node-seq assignments (node->ir-node body kont)))))

(define-method (node->ir-node node::let-fun kont)
  ;; Thankfully, the compiler has already made sure that local `labels'
  ;; functions are only called in tail position!  We compile these like the C
  ;; backend does: the first encountered application is inlined, and other
  ;; applications jump to that inlined code.
  (verbose 3 "       node->ir-node ::let-fun\n")
  (with-access::let-fun node (body locals)
    (let loop ((locals locals)
               (formals-code '()))

      (define (compile-more-functions)
        (let ((local (car locals)))
          (set-variable-name! local)
          ;; Widen the function value to store a label and a flag for whether
          ;; it has been inlined yet.  Then compile storage for its
          ;; parameters, to be reused by all invocations.
          (let* ((fun (widen!::sfun/integrated (local-value local)
                                               (label (local-name local))
                                               (integrated #f)))
                 (allocs
                  (cons
                   (comment "Parameters for local function ~s"
                            (local-id local))
                   (map compile-allocate-formal (sfun-args fun)))))
            (loop (cdr locals) (append allocs formals-code)))))

      (define (compile-body)
        (make-node-seq formals-code (node->ir-node body kont)))

      (if (null? locals)
          (compile-body)
          (compile-more-functions)))))

(define-method (node->ir-node node::app kont)
  (verbose 3 "       node->ir-node ::app\n")
  (with-access::app node (fun)
     (let* ((var (var-variable fun))
            (val (variable-value var)))
       (set-variable-name! var)

       ;; Dispatch on the function kind.
       (cond ((sfun? val)
              (if (global? var)
                  (sfun-app->ir-node node var val kont)
                  (sfun-local-app->ir-node node var val kont)))
             ((and (cfun? val)
                   (not (or (cfun-macro? val)
                            (cfun-infix? val))))
              (cfun-app->ir-node node var val kont))
             (else
              ;; TODO: Handle all kinds.
              (begin
                (verbose 3 "        skipping " (variable-id var) "\n")
                (make-node-seq
                 (comment "Skipped call to `~s'" (variable-id var))
                 (compile-undef
                  (type->ir-type (variable-type var)) kont))))))))

;; TODO: Anything special here?
(define cfun-app->ir-node sfun-app->ir-node)

;; Compile an application of a global Scheme function.
(define (sfun-app->ir-node node var sfun kont)
  (let loop ((arg-types (map arg-type (sfun-args sfun)))
             (args (app-args node))
             (arg-code '())
             (auxs '()))

    (define (compile-more-arguments)
      ;; Compile each argument expression naming each result instruction.
      (let* ((aux (fresh-ir-variable 'aux (type->ir-type (car arg-types))))
             (name (ir-variable-name aux))
             (type (ir-variable-type aux))
             (setter (node->ir-node (car args) (make-assignment-kont aux))))
        (loop (cdr arg-types) (cdr args)
              (cons setter arg-code)
              (cons aux auxs))))
    
    (define (compile-call)
      (make-node-seq
       (comment "Arguments to `~s'" (variable-id var))
       (reverse! arg-code)
       (comment "Call to `~s'" (variable-id var))
       ;; Call the function in `var' and give back its result.
       (kont (instantiate::ir-instr-call
              (function-type (var->ir-type var))
              (function (var->ir-node var))
              (args (reverse auxs))))))
    
    (if (null? args)
        (compile-call)
        (compile-more-arguments))))

;; Compile an application of a local Scheme function.  This is guaranteed to
;; be a tail call.  See the code for node->ir-node ::let-fun.
(define (sfun-local-app->ir-node node var sfun kont)
  (let loop ((args (app-args node))
             (formals (sfun-args sfun))
             (arg-code '()))

    (define (compile-more-arguments)
      ;; Variables for each formal have already been allocated by
      ;; node->ir-node ::let-fun, so just store to them.
      (let* ((formal (car formals))
             (name (local-name formal))
             (type (local-type formal))
             (aux (fresh-ir-variable (variable-id formal) type))
             (setter (node->ir-node
                      (car args)
                      (lambda (x)
                        (make-node-seq
                         (instantiate::ir-assignment
                          (name (ir-variable-name aux))
                          (node x))
                         (compile-store (var->ir-node/ptr formal) aux))))))
        (loop (cdr args) (cdr formals) (cons setter arg-code))))

    (define (compile-call)
      (let* ((label (sfun/integrated-label sfun))
             (branch (instantiate::ir-instr-br-unconditional
                      (label (instantiate::ir-label
                              (name label))))))
        (if (sfun/integrated-integrated sfun)
            ;; Local function has already been inlined somewhere in the
            ;; surrounding global function.
            (make-node-seq
             (comment "Local tail call to `~s'" (variable-id var))
             branch)
            (begin
              ;; Not inlined yet; compile the function body here.
              (sfun/integrated-integrated-set! sfun #t)
              (make-node-seq
               (comment "Inlined local function `~s'" (variable-id var))
               ;; Need a branch here to terminate the basic block.
               branch
               (make-labeled-node-seq
                label
                (node->ir-node (sfun-body sfun) kont)))))))
    
    (if (null? args)
        (make-node-seq (reverse! arg-code) (compile-call))
        (compile-more-arguments))))

(define-method (node->ir-node node::var kont)
  (verbose 3 "       node->ir-node ::var\n")
  (set-variable-name! (var-variable node))
  (kont (instantiate::ir-instr-load
         (pointer (var->ir-node/ptr (var-variable node))))))

(define-method (node->ir-node node::conditional kont)
  (verbose 3 "       node->ir-node ::conditional\n")
  (with-access::conditional node (test true false)
     (let* ((test-var (fresh-ir-variable 'test *bool*))
            (result-var
             (fresh-ir-variable 'result (pointerify (get-type node))))
            (result-kont (make-store-kont result-var))
            (true-label (make-label 'true))
            (false-label (make-label 'false))
            (done-label (make-label 'done)))

       (define (compile-branch label branch)
         (instantiate::ir-node-seq
          (label label)
          (nodes
           (list (node->ir-node branch result-kont)
                 (instantiate::ir-instr-br-unconditional
                  (label (instantiate::ir-label (name done-label))))))))

       (let ((test-code (node->ir-node test (make-assignment-kont test-var)))
             (branch-code 
              (instantiate::ir-instr-br
               (condition test-var)
               (true-label (instantiate::ir-label (name true-label)))
               (false-label (instantiate::ir-label (name false-label)))))
             (done-code
              (make-labeled-node-seq done-label
                                     (kont (compile-load result-var)))))
         (make-node-seq
          (comment "Test expression for `if' form")
          test-code
          (compile-local-allocation result-var)
          branch-code
          (comment "Positive arm of `if' form")
          (compile-branch true-label true)
          (comment "Negative arm of `if' form")
          (compile-branch false-label false)
          done-code)))))

(define-method (node->ir-node node::sequence kont)
  (verbose 3 "       node->ir-node ::sequence\n")
  (let ((throw-away-kont
         (lambda (x)
           (let ((var (fresh-ir-variable 'null
                                         (ir-value-type x))))
             (instantiate::ir-assignment
              (name (ir-variable-name var))
              (node x))))))
    (let loop ((nodes (sequence-nodes node))
               (code '()))
      (if (null? (cdr nodes))
          (apply make-node-seq
                 (reverse! (cons (node->ir-node (car nodes) kont) code)))
          (loop (cdr nodes)
                (cons (node->ir-node (car nodes) throw-away-kont) code))))))

(define-method (node->ir-node node::setq kont)
  (let* ((variable (var-variable (setq-var node)))
         (var (var->ir-node variable)))
    (verbose 3 "       node->ir-node ::setq "
             (variable-name variable) #\Newline)
    (make-node-seq
     (comment "Assignment to variable `~s'" (variable-id variable))
     (node->ir-node (setq-value node)
                    (lambda (x)
                      (compile-store var x)
                      (kont x))))))

(define-method (node->ir-node node::atom kont)
  (verbose 3 "       node->ir-node ::atom: " (atom-value node) #\Newline)
  (let ((value (atom-value node))
        (type (type->ir-type (get-type node))))
    (make-node-seq
     (comment "Atom `~s'" value)
     (cond 
      ((fixnum? value)
       (compile-lit (instantiate::ir-lit-int
                     (value-type type)
                     (value value)) kont))
      (else
       (verbose 3 "        unhandled type of atom\n")
       (make-node-seq
        (comment "(Unhandled atom type)" value)
        (compile-undef type kont)))))))
            

(define-method (node->ir-node dummy::node kont)
  (verbose 3 "       node->ir-node unhandled " dummy #\Newline)
  (make-node-seq
   (comment "Unhandled node type `~s'" dummy)
   (compile-undef (type->ir-type (get-type dummy)) kont)))


;;; IR generation helpers.

(define (compile-undef type kont)
  (let ((ptr-var (fresh-ir-variable 'undef (pointerify type))))
    (make-node-seq
     (compile-local-allocation ptr-var)
     (kont (instantiate::ir-instr-load
            (pointer ptr-var))))))

(define (compile-lit value kont)
  (let* ((type (ir-value-type value))
         (ptr-var (fresh-ir-variable 'literal (pointerify type))))
    (make-node-seq
     (compile-local-allocation ptr-var)
     (compile-store ptr-var value)
     (kont (compile-load ptr-var)))))

;; TODO: don't do it this stupid way
(define (make-label symbol)
  (variable-name (make-local-svar symbol *_*)))

(define (make-assignment-kont var)
  (lambda (x)
    (instantiate::ir-assignment
     (name (ir-variable-name var))
     (node x))))

(define (make-store-kont var)
  (lambda (x)
    (compile-store/aux var x)))

(define (ret-kont x)
  (let ((aux (fresh-ir-variable 'aux (ir-value-type x))))
    (verbose 3 "        ret-kont " (ir-value-type x) #\Newline)
    (make-node-seq
     (compile-assignment aux x)
     (instantiate::ir-instr-ret
      (value aux)))))

(define (arg-type arg)
  (if (local? arg) (local-type arg) arg))

(define (var->ir-type var)
  (let ((x (variable-value var)))
    (if (sfun? x)
        (instantiate::ir-function-type
         (return-type (type->ir-type (variable-type var)))
         (parameter-types (map (lambda (a)
                                 (type->ir-type (arg-type a)))
                               (sfun-args x))))
        (raise "make-ir-function-type sez sfun plz"))))

(define (var->ir-node var)
  (instantiate::ir-variable
   (value-type (type->ir-type (variable-type var)))
   (name (var->ir-name var))))

(define (var->ir-node/ptr var)
  (instantiate::ir-variable
   (value-type (pointerify (type->ir-type (variable-type var))))
   (name (var->ir-name var))))

(define (var->ir-name var)
  (string-append (if (global? var) "@" "%") (variable-name var)))

(define (fresh-ir-variable symbol type)
  ;; Maybe should do this without messing with the variable tables.
  (instantiate::ir-variable
   (value-type (type->ir-type type))
   (name (string-append "%" (variable-name (make-local-svar symbol *_*))))))

(define (compile-local-allocation var)
  (compile-assignment
   var (instantiate::ir-instr-alloca
        (element-type (unpointerify (ir-variable-type var))))))

(define (compile-assignment var value)
  (instantiate::ir-assignment
   (name (ir-variable-name var))
   (node value)))

(define (compile-store var value)
  (instantiate::ir-instr-store (pointer var) (value value)))

(define (compile-store/aux var value)
  (let ((aux (fresh-ir-variable 'aux (unpointerify
                                      (ir-variable-type var)))))
    (make-node-seq
     (compile-assignment aux value)
     (compile-store var aux))))

(define (compile-load var)
  (instantiate::ir-instr-load (pointer var)))

(define (make-node-seq . stuff)
  (if (null? stuff)
      (instantiate::ir-null-node)
      (if (null? (cdr stuff))
          (car stuff)
          (instantiate::ir-node-seq
           (nodes (apply append (map (lambda (x)
                                       (if (list? x)
                                           x
                                           (list x))) stuff)))))))

(define (make-labeled-node-seq label . stuff)
  (instantiate::ir-node-seq
   (label label)
   (nodes (apply append (map (lambda (x)
                               (if (list? x)
                                   x
                                   (list x))) stuff)))))

(define (comment . stuff)
  (instantiate::ir-comment (text (apply format stuff))))

(define *newline* (instantiate::ir-newline))