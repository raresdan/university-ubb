(DEFUN SUM1 (L)
  (COND
    ((NULL L) 0)
    ((NUMBERP (CAR L)) (+ (CAR L) (SUM1 (CDR L))))
    (T (SUM1 (CDR L)))
  )
)

(DEFUN SUM2 (L)
  (COND
    ((NULL L) 0)
    ((NUMBERP (CAR L)) (+ (CAR L) (SUM2 (CDR L))))
    ((ATOM (CAR L)) (SUM2 (CDR L)))
    (T (+ (SUM2 (CAR L)) (SUM2 (CDR L))))
  )
)

(DEFUN SUM2a (L)
  (COND
    ((NUMBERP L) L)
    ((ATOM L) 0)
    (T (+ (SUM2a (CAR L)) (SUM2a (CDR L))))
  )
)

