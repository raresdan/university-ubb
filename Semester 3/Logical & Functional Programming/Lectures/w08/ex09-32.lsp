(DEFUN SUM (N L)
  (COND
    ((NULL L) 0)
    ((= N 0) 0)
    (T (+ (CAR L) (SUM (- N 1) (CDR L)))
  )
)
