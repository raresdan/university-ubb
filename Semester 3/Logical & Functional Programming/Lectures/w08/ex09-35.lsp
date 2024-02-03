(DEFUN LPAIR (E L)
  (COND
    ((NULL L) NIL)
    (T (CONS (LIST E (CAR L)) (LPAIR E (CDR L))))
  )
)
