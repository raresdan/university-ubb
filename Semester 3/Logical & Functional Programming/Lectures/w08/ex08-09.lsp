(DEFUN MYFIRST (X)
  (COND
    ((ATOM X) X)
    ((NULL X) NIL) ; useless
    (T (CAR X))
  )
)

(DEFUN MYMAX (X Y)
	(COND
		((> X Y) X)
		(T Y)
	)
)

(DEFUN MYLAST (X)
	(COND
		((ATOM X) X)
		((NULL (CDR X)) (CAR X))
		(T (MYLAST (CDR X)))
	)
)

(DEFUN XCAR (X)
	(COND
		((ATOM X) NIL)
		(T (CAR X))
	)
)

