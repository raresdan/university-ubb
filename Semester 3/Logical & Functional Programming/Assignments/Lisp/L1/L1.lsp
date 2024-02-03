;4.
; a) Write a function to return the sum of two vectors

(defun vector-sum (vector1 vector2)
    (if (null vector1)
        nil
        (cons (+ (car vector1) (car vector2)) (vector-sum (cdr vector1) (cdr vector2)))))
(print (vector-sum '(1 2 3) '(4 5 6)))


;b) Write a function to get from a given list the list of all atoms, on any 
; level, but on the same order. Example:
; (((A B) C) (D E)) ==> (A B C D E)

(defun flatten-list (l)
  (cond
    ((null l) nil)
    ((atom (car l)) (cons (car l) (flatten-list (cdr l))))
    (t (append (flatten-list (car l)) (flatten-list (cdr l))))))
(print (flatten-list '(((A B) C) (D E))))


;c) Write a function that, with a list given as parameter, inverts only continuous
; sequences of atoms. Example:
; (a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))

(defun inv_list (l aux)
  (cond
    ((null l) (if aux (reverse aux) nil))
    ((listp (car l))
     (let ((inner-reversed (inv_list (car l) nil)))
       (inv_list (cdr l) (if inner-reversed (cons inner-reversed aux) aux))))
    (T (inv_list (cdr l) (cons (car l) aux)))))
(print (inv_list '(a b c (d (e f) g h i)) nil))



;d) Write a list to return the maximum value of the numerical atoms from a list, at superficial level

(defun max-num-from-list (lst)
  (let ((numbers (remove-if-not #'numberp lst)))
    (if numbers
        (apply #'max numbers)
        nil)))
(print (max-num-from-list '(1 5 3 7 2)))

