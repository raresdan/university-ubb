(DEFUN MYREMOVE (e l)
  (COND
    ((ATOM l) l)
    ((EQL (CAR l) e) (MYREMOVE e (CDR l)))
    (T (CONS (CAR l) (MYREMOVE e (CDR l))))
  )
)
