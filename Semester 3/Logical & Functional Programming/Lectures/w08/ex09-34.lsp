(DEFUN LIS1 (L)
  (COND
    ((NULL L) NIL)
    ((NUMBERP (CAR L)) (LIS1 (CDR L)))
    ((ATOM (CAR L)) (CONS (CAR L) (LIS1 (CDR L))))
    (T (APPEND (LIS1 (CAR L)) (LIS1 (CDR L))))
  )
)

(DEFUN LIS2 (L)
  (COND
    ((NULL L) NIL)
    ((NUMBERP (CAR L)) (LIS2 (CDR L)))
    ((ATOM (CAR L)) (CONS (CAR L) (LIS2 (CDR L))))
    (T (CONS (LIS2 (CAR L)) (LIS2 (CDR L))))
  )
)
