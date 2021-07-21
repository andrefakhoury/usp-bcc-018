"""
 * Prof. Lizeth Andrea Castellanos Beltran
 * Aluna PAE: Leo Sampaio Ferraz Ribeiro
 * Integrantes:
   - Andre Luis Mendes Fakhoury - 4482145
   - Gustavo Vinicius Vieira Soares - 10734428
 * SCC0251 - Processamento de Imagens
 * Trabalho 01: geração de imagens
 * 1o Semestre de 2021
"""

import numpy as np
import random
import imageio

# reading input data
ref = input().rstrip() # reference filename
img_size = int(input()) # image size
f = int(input()) # id of function to be used
q = int(input()) # parameter used on image generation
sample_size = int(input()) # sample will be sample_size x sample_size
bits = int(input()) # number of bits per pixel
seed = int(input()) # seed for random number generation

# set random seed
random.seed(seed)

# generating x and y indices
x = np.repeat(np.arange(img_size), img_size).reshape(img_size, -1)
y = np.tile(np.arange(img_size), img_size).reshape(img_size, -1)

### defining each function as specified

# f(x, y) = (xy + 2y)
def f1():
    return x * y + 2 * y

# f(x, y) = |cos(x/q) + 2sin(y/q)|
def f2():
    return np.abs(np.cos(x / q) + 2 * np.sin(y / q))

# f(x, y) = |3(x/q) - (y/q)^(1/3)|
def f3():
    return np.abs(3 * x / q - (y / q) ** (1 / 3))

# f(x, y) = rand(0, 1, S)
def f4():
    img = np.zeros((img_size, img_size))
    for y in range(img_size):
    	for x in range(img_size):
    		img[x, y] = random.random();
    return img

# f(x, y) = randomwalk(S)
def f5():
    img = np.zeros((img_size, img_size))
    x, y = 0, 0
    img[x, y] = 1
    for it in range(1 + img_size ** 2):
        dx = random.randint(-1, 1)
        dy = random.randint(-1, 1)
        x = (x + dx) % img_size
        y = (y + dy) % img_size
        img[x, y] = 1
    return img

# generate image with specified function
img = [f1, f2, f3, f4, f5][f - 1]() # call function with each id
img = (img - img.min()) / (img.max() - img.min()) * 65535 # normalize values to range [0, 65535]

# downsample image

# just take the indices where x % floor(img_size / sample_size) and y % (img_size / sample_size) are 0
sample = img[((x % (img_size // sample_size)) == 0) & ((y % (img_size // sample_size)) == 0)].reshape(sample_size, -1)
sample = (sample - sample.min()) / (sample.max() - sample.min()) * 255  # normalize values to range [0, 255]
sample = sample.astype(np.uint8) # change type

# left and right shift to use the "bits" most significant bits
sample = np.left_shift(np.right_shift(sample, 8 - bits), 8 - bits)

# load reference image
img_ref = np.load(ref)

# compare both using RSE
error = ((sample.astype(np.float64) - img_ref.astype(np.float64)) ** 2).sum() ** (1 / 2)

# print with 4 decimal places precision
print("%.4f" % error)