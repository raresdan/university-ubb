(DEFUN TEST (L)
  (COND
    ((NULL L) T)
    ((LABELS
      (
        (TEST1 (L)
          (COND
            ((NULL L) T)
            ((NUMBERP (CAR L)) (TEST1 (CDR L)))
            (T NIL)
          )
        )
      )
      (TEST1 (CAR L))
     ) (TEST (CDR L)))
    (T NIL)
  )
)
