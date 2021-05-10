"""
 * Prof. Lizeth Andrea Castellanos Beltran
 * Aluna PAE: Leo Sampaio Ferraz Ribeiro
 * Integrantes:
   - Andre Luis Mendes Fakhoury - 4482145
   - Gustavo Vinicius Vieira Soares - 10734428
 * SCC0251 - Processamento de Imagens
 * Trabalho 02: realce e superresolução
 * 1o Semestre de 2021
"""

import numpy as np
import imageio

# reading input
img_low = input().strip()
img_high = input().strip()
f = int(input())
gamma = float(input())

# array with every image
imgs = [imageio.imread(f'{img_low}{i}.png') for i in range(4)]

"""
Enhancement functions.
Each function receive an array of images and return them enhanced.
"""

# no enhancement
def enh_none(imgs):
    return imgs

# Histogram Equalization of an image with cumulative histogram hc and no_levels levels
def histogram_equalization(img, hc, no_levels):
    N, M = img.shape
    img_eq = np.zeros((N, M)).astype(np.uint8)
    for z in range(no_levels):
        s = (no_levels - 1) * hc[z] / hc[-1]
        img_eq[np.where(img == z)] = s
    return img_eq

# Cumulative histogram (considering each image individually)
def enh_cumulative_histogram_single(imgs):
    for i, img in enumerate(imgs):
        hc = np.cumsum(np.histogram(img, bins=np.arange(257))[0])
        imgs[i] = histogram_equalization(img, hc, 256)
    return imgs

# Cumulative histogram (considering every image histogram)
def enh_cumulative_histogram_group(imgs):
    hc = np.cumsum(np.histogram(imgs, bins=np.arange(257))[0])
    for i, img in enumerate(imgs):
        imgs[i] = histogram_equalization(img, hc, 256)
    return imgs

# Gamma correction function
def enh_gamma_correction(imgs):
    for i, img in enumerate(imgs):
        imgs[i] = np.floor(255 * ((img / 255.0) ** (1 / gamma)))
    return imgs

# array to index functions
enh_functions = [enh_none,
                enh_cumulative_histogram_single,
                enh_cumulative_histogram_group,
                enh_gamma_correction]

# Apply enhancement
imgs = enh_functions[f](imgs)

# apply super resolution technique in every image in imgs array
def super_resolution(imgs):
    orig_shape = imgs[0].shape
    large_shape = (orig_shape[0] * 2, orig_shape[1] * 2)
    # row and column indices
    x = np.repeat(np.arange(large_shape[0]), large_shape[1]).reshape(large_shape[0], -1)
    y = np.tile(np.arange(large_shape[1]), large_shape[0]).reshape(large_shape[0], -1)

    img_large = np.zeros((large_shape[0] * large_shape[1]))
    img_large[((x % 2 == 0) & (y % 2 == 0)).reshape(-1)] = imgs[0].reshape(-1)
    img_large[((x % 2 == 0) & (y % 2 == 1)).reshape(-1)] = imgs[1].reshape(-1)
    img_large[((x % 2 == 1) & (y % 2 == 0)).reshape(-1)] = imgs[2].reshape(-1)
    img_large[((x % 2 == 1) & (y % 2 == 1)).reshape(-1)] = imgs[3].reshape(-1)
    return img_large.reshape(large_shape)

# apply super resolution
img_large = super_resolution(imgs)

# image to check correctness
img_check = imageio.imread(img_high)

# print error
err = (((img_check.astype(np.int32) - img_large.astype(np.int32)) ** 2).sum() / img_large.shape[0] / img_large.shape[1]) ** (1 / 2)
print(f'{err:.4f}')
