(DEFUN GEN (F L)
  (COND 
    ((NULL L) T)
    ((FUNCALL F (CAR L)) (GEN F (CDR L)))
    (T NIL)
  )
)

(DEFUN LIN (L)
  (GEN #'(LAMBDA (L)
      (GEN #'NUMBERP L)
    )
    L
  )
)
