"""
 * Prof. Dr. Moacir Ponti
 * Aluna PAE: Leo Sampaio Ferraz Ribeiro
 * Monitor: Flavio Salles
 * Integrantes:
   - Andre Luis Mendes Fakhoury - 4482145
   - Gustavo Vinicius Vieira Soares - 10734428
 * SCC0251 - Processamento de Imagens
 * Trabalho 05 - Image Descriptors
 * 1o Semestre de 2021
"""

import numpy as np
import imageio
from scipy import ndimage

# Ignoring numpy errors or warnings
np.seterr(divide='ignore', invalid='ignore')

# Returns the Luminance of the image, quantised to use only an amount of bits
def preprocess(img):
    B, G, R = img[:,:,0], img[:,:,1], img[:,:,2]
    f = np.floor(0.299 * R + 0.587 * G + 0.114 * B).astype(np.int32)
    f = np.right_shift(f, 8 - bits)
    return f

# Returns the normalised histogram
def norm_hist(img):
    p = np.zeros(1 << bits)
    np.add.at(p, img.reshape(-1), 1)
    p /= np.sum(p)
    p /= np.linalg.norm(p)
    return p

# Calculates intensity-level co-ocurrence matrix
def cc_mat(img):
    i = img[:-1, :-1].reshape(-1)
    j = img[1:, 1:].reshape(-1)
    c = np.zeros((1 << bits, 1 << bits))
    np.add.at(c, (i, j), 1)
    c /= np.sum(c)
    return c

# Calculates energy metric of matrix c
def energy(c):
    return np.sum(c ** 2)

# Calculates entropy metric of matrix c
def entropy(c):
    return -np.sum(c * np.log(c + 0.001))

# Calculates contrast metric of matrix c
def contrast(c):
    n = c.shape[0]
    i = np.repeat(np.arange(n), n).reshape(n, -1)
    j = np.tile(np.arange(n), n).reshape(n, -1)
    return np.sum((i - j) ** 2 * c) / (n ** 2)

# Calculates correlation metric of matrix c
def correlation(c):
    n = c.shape[0]
    u_i = np.sum(np.arange(n) * np.sum(c, axis=1))
    u_j = np.sum(np.arange(n) * np.sum(c, axis=0))
    d_i = np.sum((np.arange(n) - u_i) ** 2 * np.sum(c, axis=1))
    d_j = np.sum((np.arange(n) - u_j) ** 2 * np.sum(c, axis=0))
    if d_i > 0 and d_j > 0:
        i = np.repeat(np.arange(n), n).reshape(n, -1)
        j = np.tile(np.arange(n), n).reshape(n, -1)
        return np.sum(i * j * c - u_i * u_j) / d_i / d_j
    return 0

# Calculates homogeneity metric of matrix c
def homogeneity(c):
    n = c.shape[0]
    i = np.repeat(np.arange(n), n).reshape(n, -1)
    j = np.tile(np.arange(n), n).reshape(n, -1)
    return np.sum(c / (np.abs(i - j) + 1))

# Calculate Haralick descriptor using pre-defined texture metrics
def haralick(img):
    c = cc_mat(img)
    d = np.array([
        energy(c),
        entropy(c),
        contrast(c),
        correlation(c),
        homogeneity(c)
    ])
    d /= np.linalg.norm(d)
    return d

# Calculate Histogram of Oriented Gradients of image img
def hist_grad(img):
    img = img.astype(np.float64)
    ws_x = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])
    ws_y = ws_x.T

    gx = ndimage.convolve(img, ws_x)
    gy = ndimage.convolve(img, ws_y)

    M = np.sqrt(gx ** 2 + gy ** 2) / np.sum(np.sqrt(gx ** 2 + gy ** 2))
    M[np.isnan(M)] = 0
    phi = np.arctan(gy / gx) + np.pi / 2
    phi = np.degrees(phi)
    phi[np.isnan(phi)] = 179
    phi[phi > 179] = 0

    d = np.zeros(9)
    np.add.at(d, np.floor(phi // 20).astype(np.int32), M)
    if np.linalg.norm(d) > 0:
        d /= np.linalg.norm(d)
    return d

# Returns the descriptors of image img
def descriptor(img):
    return np.concatenate((
        norm_hist(img),
        haralick(img),
        hist_grad(img)
    ))

# distance between descriptors
def dist(d, di):
    return np.sqrt(np.sum((d - di) ** 2))

##########################################################

# read input data
f_name = 'images/' + input().strip()
g_name = 'images/' + input().strip()
bits = int(input().strip())

# load input images
f_img = imageio.imread(f_name)
g_img = imageio.imread(g_name)

# preprocess to get Luminance and quantise
f_img = preprocess(f_img)
g_img = preprocess(g_img)

d = descriptor(f_img)

# determine the closest window
best_score, best_i, best_j = np.inf, 0, 0
for i in range(0, g_img.shape[0], 16):
    for j in range(0, g_img.shape[1], 16):
        if i + 32 > g_img.shape[0] or j + 32 > g_img.shape[1]:
            continue
        d_ij = descriptor(g_img[i:i + 32, j:j + 32])
        score = dist(d, d_ij)
        if score < best_score:
            best_score, best_i, best_j = score, i, j

best_i //= 16
best_j //= 16

print(best_i, best_j)

## Code used to visualize (commented to submit to run.codes)
# import matplotlib.pyplot as plt
# import matplotlib.patches as patches
# fig, ax = plt.subplots()
# ax.imshow(g_img, cmap='gray')
# rect = patches.Rectangle((best_j * 16, best_i * 16), 32, 32,
#                         linewidth = 1, edgecolor='r', facecolor='none')
# ax.add_patch(rect)
# plt.show()