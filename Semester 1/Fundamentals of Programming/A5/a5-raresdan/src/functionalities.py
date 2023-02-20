import random
from math import sqrt

# Set A: Length and elements of the longest subarray of numbers where both their real
# and imaginary parts can be written using the same base 10 digits (e.g. 1+3i, 31i, 33+i, 111, 11-313i)

# Set B: The length and elements of the longest increasing subsequence, when considering each number's modulus


# Write below this comment
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

def create_complex(a, b):
    """
    Creates a list containing 2 integers
    :param a: real part
    :param b: imaginary part
    :return: list of type [real, imaginary]
    """
    z = [a, b]
    return z


def generate_random():
    a = random.randint(0, 100)
    b = random.randint(0, 100)
    z = create_complex(a, b)
    return z


def get_real(z):
    return int(z[0])


def get_imaginary(z):
    return int(z[1])


def to_str(z):
    """
    Returns to string representation of complex number z
    :param z: Given list z = [re, img]
    :return: String representation of z
    """

    if z[1] == 0:
        return str(z[0])
    if z[0] == 0:
        return str(z[1]) + "i"
    if z[1] > 0:
        return str(z[0]) + "+" + str(z[1]) + "i"
    if z[1] < 0:
        return str(z[0]) + str(z[1]) + "i"



#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#

'''
def create_complex(a, b):
    """
    Creates a dictionary containing 2 components, one referencing the real part of the 
    complex number and one referencing the imaginary part of it
    :param a: real part
    :param b: imaginary part
    :return: dictionary of type (real, imaginary)
    """
    z = dict(real=a, imaginary=b)
    return z


def generate_random():
    a = random.randint(0, 100)
    b = random.randint(0, 100)
    z = create_complex(a, b)
    return z


def get_real(z):
    return int(z['real'])


def get_imaginary(z):
    return int(z['imaginary'])


def to_str(z):
    """
    Returns to string representation of complex number z
    :param z: Given dictionary z = (real, imaginary)
    :return: String representation of z
    """

    if z['imaginary'] == 0:
        return str(z['real'])
    if z['real'] == 0:
        return str(z['imaginary']) + "i"
    if z['imaginary'] > 0:
        return str(z['real']) + "+" + str(z['imaginary']) + "i"
    if z['imaginary'] < 0:
        return str(z['real']) + str(z['imaginary']) + "i"
'''

#
# Write below this comment
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
def frequency(z):
    """
    :param z: the complex number
    :return: frequency vector of the digits of the complex number
    """
    v = [0] * 10
    a = abs(get_real(z))
    if a != 0:
        while a != 0:
            ld = a % 10
            v[ld] = 1
            a = a // 10
    b = abs(get_imaginary(z))
    if b != 0:
        while b != 0:
            ld = b % 10
            v[ld] = 1
            b = b // 10
    return v


def verify_frequency(z1, z2):
    """
    :param z1: a complex number
    :param z2: another complex number
    :return: true if the numbers are represented with the same base 10 digits
             false otherwise
    """

    a = frequency(z1)
    b = frequency(z2)
    for i in range(1, 10):
        if a[i] != b[i]:
            return False
    return True


def len_longest_subarray(arr: list, n: int) -> int:
    """
    :param arr: the list of complex numbers in which we search
    :param n: the length of the list
    :return: the length of the longest subarray with the propriety
    """
    # 'm' will be the length of the maximum subarray
    m = 1
    # 'length' is used for intermediary lengths
    length = 1
    # we go through the array trying to find the length of the longest subarray
    for i in range(1, n):
        if verify_frequency(arr[i - 1], arr[i]):
            length = length + 1
        else:
            if m < length:
                m = length
            length = 1
    if m < length:
        m = length
    return m


def return_longest_subarray(arr: list, n: int) -> list:
    """
    :param arr: The list of complex numbers
    :param n: length of the list
    :return: the longest subarray with the propriety
    """
    # 'm' will be the length of the maximum subarray
    m = 1
    # 'length' is used for intermediary lengths
    length = 1
    max_index = 0
    # we go through the array trying to find the length of the longest subarray
    for i in range(1, n):
        if verify_frequency(arr[i - 1], arr[i]):
            length = length + 1
        else:
            if m < length:
                m = length
                max_index = i - m
            length = 1
    if m < length:
        m = length
        max_index = n - m
    v = []
    # append all terms in the longest subarray, so we can return the subarray
    for i in range(max_index, (m + max_index)):
        v.append(to_str(arr[i]))
    return v


def modulus(z):
    """
    :param z: the complex number
    :return: the modulus calculated using the mathematical formula
    """
    a = get_real(z)
    b = get_imaginary(z)
    mod = sqrt(a * a + b * b)
    return mod


def modules_list(v):
    """
    Converts a list of complex numbers to a list of their modules
    :param v: the list of complex numbers given
    :return: a list of the modules of each number
    """

    n = len(v)
    modules = []
    for i in range(0, n):
        modules.append(round(modulus(v[i]), 3))
    return modules


def longest_increasing_subsequence(arr):
    """
    :param arr: The list in which we search for the longest increasing sequence
    :return: the longest increasing sequence
    """
    if not arr:
        return []
    # longest[i] stores the longest increasing subsequence of sublist `arr[0…i]` that ends with `arr[i]`
    longest = [[] for _ in range(len(arr))]
    # longest[0] denotes the longest increasing subsequence ending at `arr[0]`
    longest[0].append(to_str(arr[0]))
    # start from the second element in the list
    for i in range(1, len(arr)):
        for j in range(i):
            # find the longest increasing subsequence that ends with `arr[j]`
            # where `arr[j]` is less than the current element `arr[i]`
            if modulus(arr[j]) < modulus(arr[i]) and len(longest[j]) > len(longest[i]):
                longest[i] = longest[j].copy()
        longest[i].append(to_str(arr[i]))
    # `j` will store the index of longest
    j = 0
    for i in range(len(arr)):
        if len(longest[j]) < len(longest[i]):
            j = i
    return longest[j]
