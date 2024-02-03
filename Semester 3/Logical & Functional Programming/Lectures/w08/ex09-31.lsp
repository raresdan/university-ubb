(DEFUN FIRST1 (L)
  (COND
    ((NULL L) NIL)
    ((ATOM (CAR L)) (CAR L))
    (T (FIRST1 (CDR L)))
  )
)

(DEFUN FIRST2 (L)
  (COND
    ((NULL L) NIL)
    ((ATOM (CAR L)) (CAR L))
    (T (FIRST2 (CAR L)))
  )
)
