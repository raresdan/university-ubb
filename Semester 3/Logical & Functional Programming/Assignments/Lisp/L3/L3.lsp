; 4. Write a function that returns the product of numeric atoms in a list, at any leve

(defun product-of-numeric-atoms (lst)
  (if (atom lst)
      (if (numberp lst)
          lst
          1)
      (apply #'*(mapcar #'product-of-numeric-atoms lst))))

(print (product-of-numeric-atoms '(1 2 (A 4) ((B 5) 6))))

