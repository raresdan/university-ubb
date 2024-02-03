(DEFUN INS (E N L)
  (COND
    ((= N 1) (CONS E L))
    (T (CONS (CAR L) (INS E (- N 1) (CDR L))))
  )
)
