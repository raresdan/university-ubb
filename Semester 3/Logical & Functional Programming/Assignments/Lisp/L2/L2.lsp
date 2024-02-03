; 4. Convert a tree of type (2) to type (1).

(defun transform(l)
    (cond 
        ((null l) nil)
        ((null (cadr l)) (append (list (car l)) (list 0) ))
        ((null (caddr l)) (append (list (car l)) (list 1) (transform (cadr l))))
        (t (append (list (car l)) (list 2) (transform (cadr l)) (transform (caddr l))))))

(print (transform '(A (B) (C (D) (E)))))