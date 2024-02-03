(DEFUN LISTA (E L)
  (COND
    ((NULL L) NIL)
    (T (CONS (LIST E (CAR L)) (LISTA E (CDR L))))
  )
)
