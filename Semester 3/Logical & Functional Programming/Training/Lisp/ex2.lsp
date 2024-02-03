; Define a function to remove all occureneces of an element from a nonlinear list

(defun remove-all (l e)
    (cond
        ((null l) nil)
        ((listp (car l)) (cons (remove-all (car l) e) (remove-all (cdr l) e)))
        ((equal (car l) e) (remove-all (cdr l) e))
        (T (cons (car l) (remove-all (cdr l) e)))
    ))

(print (remove-all '(1 2 (3 8 1) 1 2 7 (3 4 (1 2 1)) 2 7 1 6) 1))