"""
 * Prof. Lizeth Andrea Castellanos Beltran
 * Aluna PAE: Leo Sampaio Ferraz Ribeiro
 * Integrantes:
   - Andre Luis Mendes Fakhoury - 4482145
   - Gustavo Vinicius Vieira Soares - 10734428
 * SCC0251 - Processamento de Imagens
 * Trabalho 03: filtragem
 * 1o Semestre de 2021
"""

import numpy as np
import imageio

def filter_1d(img, w):
    n, orig_shape = w.shape[0], img.shape
    p = n // 2
    out = np.empty_like(img.flatten(), dtype=float)
    img = np.pad(img.flatten(), p, 'wrap')
    # applies the filter to get output[i]
    for i in range(out.shape[0]):
        out[i] = np.dot(img[i : i + n], w)
    return out.reshape(orig_shape)

def filter_2d(img, w):
    n = w.shape[0]
    p = n // 2
    out = np.empty_like(img, dtype=float)
    img = np.pad(img, p, 'symmetric')
    # applies the filter to get output[i, j]
    for i in range(out.shape[0]):
        for j in range(out.shape[1]):
            out[i, j] = np.sum(img[i : i + n, j : j + n] * w)
    return out

def filter_median(img, n):
    p = n // 2
    img = np.pad(img, p)
    img_ret = np.copy(img)
    # computes the median of each submatrix
    for i in range(p, img.shape[0] - p):
        for j in range(p, img.shape[1] - p):
            base_matrix = np.array(img[i-p:i+p+1, j-p:j+p+1])
            img_ret[i, j] = np.floor(np.median(base_matrix))
    return img_ret[p:img.shape[0]-p, p:img.shape[1]-p]

# applies min max normalization on image img, with values in range [0, max_value]
def min_max_normalize(img, max_value):
    return (img - img.min()) / (img.max() - img.min()) * max_value

# returns RMSE of img and img_gen
def get_error(img, img_gen):
    return (((img.astype(np.int32) - img_gen.astype(np.int32)) ** 2).sum() / img.shape[0] / img.shape[1]) ** (1 / 2)
    
# read input data
img_ref = input().strip() # filename of image
method_id = int(input().strip()) # id of filtering method
n_filter = int(input().strip()) # size of filter
    
# reads weights of methods 1 and 2
if method_id == 1:
    weights = np.array([float(w) for w in input().split()]).astype(float)
elif method_id == 2:
    weights = np.array([[float(w) for w in input().split()] for i in range(n_filter)]).astype(float)

img = imageio.imread(img_ref)
if method_id == 1:
    img_out = filter_1d(img, weights)
elif method_id == 2:
    img_out = filter_2d(img, weights)
else:
    img_out = filter_median(img, n_filter)

print(get_error(img, min_max_normalize(img_out, 255)))
