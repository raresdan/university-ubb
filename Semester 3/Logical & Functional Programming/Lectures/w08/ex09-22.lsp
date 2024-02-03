(DEFUN MYSUBST (e1 e2 e3)
  (COND
    ((EQUAL e2 e3) e1)
    ((ATOM e3) e3)
    (T (CONS (MYSUBST e1 e2 (CAR e3)) (MYSUBST e1 e2 (CDR e3))))
  )
)
