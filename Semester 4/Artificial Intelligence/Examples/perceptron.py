from numpy import random, dot, array
import matplotlib as mpl

def threshold(x):
    if x < 0.2 :
        return 0
    return 1

class Perceptron:
    def __init__(self, noInputs, activationFunction, learningRate):
        self.noInputs = noInputs
        self.weights = random.rand(self.noInputs)
        self.activationFunction = activationFunction
        self.output = 0
        self.learningRate = learningRate
        self.errorVariation = []
    
    def fire(self, inputs):
        self.output = self.activationFunction(
                dot(array(inputs), self.weights))
        return self.output
    
    def trainPerceptronRule(self, inputs, output):
        totalError = 0
        for i in range(len(inputs)):
            error = output[i] - self.fire(inputs[i])
            delta = self.learningRate*error*array(inputs[i])
            self.weights += delta
            totalError += error**2
        self.errorVariation.append(totalError)
        
def test1():
    # AND logic
    p = Perceptron(2, threshold, 0.1)
    x = [[1,1],[1,0],[0,1],[0,0]]
    t = [1,0,0,0]
    noIterations = 10
    for i in range(noIterations):
        p.trainPerceptronRule(x,t)
    print(p.weights)
    for j in range(len(x)):
        print(x[j], p.fire(x[j]))
    
    mpl.pyplot.plot(range(noIterations), p.errorVariation,
                    label = 'Total error vs Iteration')
    mpl.pyplot.xlabel('Iterations')
    mpl.pyplot.ylabel('Total error')
    mpl.pyplot.legend()
    mpl.pyplot.title('AND logic')
    mpl.pyplot.show()
        
def test2():
    # OR logic
    p = Perceptron(2, threshold, 0.1)
    x = [[1,1],[1,0],[0,1],[0,0]]
    t = [1,1,1,0]
    noIterations = 10
    for i in range(noIterations):
        p.trainPerceptronRule(x,t)
    print(p.weights)
    for j in range(len(x)):
        print(x[j], p.fire(x[j]))
    
    mpl.pyplot.plot(range(noIterations), p.errorVariation, 
                    label = 'Total error vs Iteration')
    mpl.pyplot.xlabel('Iterations')
    mpl.pyplot.ylabel('Total error')
    mpl.pyplot.legend()
    mpl.pyplot.title('OR logic')
    mpl.pyplot.show()    

def test3():
    # XOR 
    p = Perceptron(2, threshold, 0.1)
    x = [[1,1],[1,0],[0,1],[0,0]]
    t = [0,1,1,0]
    noIterations = 10000
    # no matter how many iterations you put 
    # the perceptron will not be able to learn
    for i in range(noIterations):
        p.trainPerceptronRule(x,t)
    print(p.weights)
    for j in range(len(x)):
        print(x[j], p.fire(x[j]))
    
    mpl.pyplot.plot(range(noIterations), p.errorVariation, 
                    label='Total error vs Iteration')
    mpl.pyplot.xlabel('Iterations')
    mpl.pyplot.ylabel('Total error')
    mpl.pyplot.legend()
    mpl.pyplot.title('XOR')
    mpl.pyplot.show()
    
test1()
#test2()
#test3()