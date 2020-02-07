;	mytrans.scm - Jon Crawford
;	COP4020 Spring 2019 - Assigment 5
;	Micro-p to scheme converter
;
;	(eval (convert "filename") (the-environment))

(define test
	(lambda (filename)
		(let ((s-expr (convert filename)))
			(display s-expr)
			(newline)
			(eval s-expr)
			(newline))))

(define file2list
	(lambda (filename)
		(begin	(set-current-input-port! (open-input-file filename))
			(read-list))))

(define read-list
	(lambda ()
		(let ((token (read)))
			(cond	((eof-object? token) '())
				(else (cons token (read-list)))))))

(define convert
	(lambda (filename)
		(begin (set-current-input-port! (open-input-file filename))
			(statement (read)))))

(define statements
	(lambda ()
		(let ((token (read)))
		(cond	((eof-object? token) '())
			((eq? token 'end) '())
			(else	(let* ((s (statement token))
					(r (statements)))
				(cons s r)))))))

(define statement
	(lambda (token)
		(cond	((eq? token 'declare) (declare_statement))
			((eq? token 'begin) (begin_statement))
			((eq? token 'for) (for_statement))
			((eq? token 'if) (if_statement))
			((eq? token 'set) (set_statement))
			(else (expression token)))))

;; student template for begin_statement used in declarations
(define begin_statement
	(lambda ()
		(let* ((s(statements)))
			(cons 'begin s))))

;; student template for declare_statement
(define declare_statement
	(lambda ()
		(let* ((d (declarations))
			(s (statements)))
		(cons 'let* (cons d s)))))

;; student template for for_statement
(define for_statement
	(lambda ()
		(let* ((i (expression (read))) 
        (equals (expression (read-after '=)))
        (to (expression (read-after 'to)))
        (stmt (statement (read))))
      (list 'do (list (list i equals (list '+ i 1))) (list (list '> i to ) i) stmt))))
				
;; student template for if_statement needs if-then-else
(define if_statement
	(lambda ()
		(let* ((iff ( expression (read)))
		    (thn (statement (read-after 'then)))
		    (els (statement (read-after 'else))))
						(list 'if iff thn els))))

(define declarations
	(lambda ()
		(let ((token (read)))
		(cond	((eof-object? token) '(eof))
			((eq? token 'begin) '())
			(else	(let* ((d (declaration token)) (r (declarations)))
				(cons d r)))))))

(define declaration
	(lambda (token)
		(list token (expression (read-after '=)))))

(define read-after
	(lambda (token)
		(if (eq? (read) token)
			(read)
			(display "Syntax error"))))

;; called by expression same recursive logic as delcarations or statements
(define call_expression
	(lambda ()
		(let ((token (read)))
			(cond	((eof-object? token) '()) ((eq? token '$) '()) 
		(else	(let* ((ex (expression token)) (ce (call_expression)))
				(cons ex ce)))))))
					
;; student template for expression
(define expression
  (lambda (token)
    (if (eq? token 'call)
			(call_expression) token)))
					
;; student template for expression
(define set_statement
	(lambda ()
    (let ((token (read)))
			(list 'set! token (expression (read-after '=))))))