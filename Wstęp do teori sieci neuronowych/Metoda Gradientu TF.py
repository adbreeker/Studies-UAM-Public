import random
import tensorflow as tf
import numpy as np

np.random.seed(50)

def init1():
    X = tf.Variable(np.random.uniform(-10,10), trainable=True)
    Y = tf.Variable(np.random.uniform(-10,10), trainable=True)
    Z = tf.Variable(np.random.uniform(-10, 10), trainable=True)
    return X, Y , Z

def init2():
    X = tf.Variable(np.random.uniform(-10,10), trainable=True)
    Y = tf.Variable(np.random.uniform(-10,10), trainable=True)
    return X, Y

def function2(X,Y):
    return (3*X**4+4*X**3-12*X**2+12*Y**2-24*Y)

def function1(X,Y,Z):
    return (2*X**2+2*Y**2+Z**2-2*X*Y-2*Y*Z-2*X+3)


X , Y, Z = init1()
min=function1(X.numpy(),Y.numpy(), Z.numpy())
for i in range(3):
    optimizer = tf.optimizers.SGD(learning_rate=0.01, momentum=0)
    for epoch in range(1000):
        optimizer.minimize(lambda: function1(X,Y,Z), var_list=[X, Y, Z])
        print((function1(X, Y, Z)).numpy(), X.numpy(), Y.numpy(), Z.numpy(), end="\r")
    print(X.numpy(), Y.numpy(), Z.numpy(), function1(X,Y,Z).numpy())
    X, Y, Z = init1()

print(" -------------------------------------------- ")

X , Y= init2()
min=function2(X.numpy(),Y.numpy())
for i in range(3):
    optimizer = tf.optimizers.SGD(learning_rate=0.01, momentum=0)
    for epoch in range(1000):
        optimizer.minimize(lambda: function2(X,Y), var_list=[X, Y])
        print((function2(X, Y)).numpy(), X.numpy(), Y.numpy(), end="\r")
    print(X.numpy(), Y.numpy(), function2(X,Y).numpy())
    X, Y = init2()