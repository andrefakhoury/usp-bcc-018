"""
 * Prof. Dr. Moacir Ponti
 * Aluna PAE: Leo Sampaio Ferraz Ribeiro
 * Monitor: Flavio Salles
 * Integrantes:
   - Andre Luis Mendes Fakhoury - 4482145
   - Gustavo Vinicius Vieira Soares - 10734428
 * SCC0251 - Processamento de Imagens
 * Trabalho 04 - Recovery and Fourier
 * 1o Semestre de 2021
"""

import numpy as np
import imageio
from scipy.fft import rfft2, irfft2, fftshift

# read input data
f_name = input().strip()
g_name = input().strip()
filter_type = int(input().strip())
gamma = float(input().strip())

# reads weights of methods 1 and 2
if filter_type == 1:
    i1, i2, j1, j2 = [int(x) for x in input().strip().split()]
    n = int(input().strip())
    denoising = input().strip()
else:
    gauss_size = int(input().strip())
    sigma = float(input().strip())

# Return the dispesion measure for the array a
def dispersion(a):
    if denoising == 'average':
        x = np.std(a)
    else:
        q75, q25 = np.percentile(a, [75 ,25])
        x = q75 - q25
    return 1 if np.abs(x) < 1e-7 else x

# Return the centrality measure for the array a
def centrality(a):
    return np.mean(a) if denoising == 'average' else np.median(a)

# Applies the adaptative denoising filter on g
def adaptative_denoising(g):
    f = np.empty_like(g, dtype=float)
    g_pad = np.pad(g, n // 2, mode='symmetric')
    d = dispersion(g[i1:i2, j1:j2])
    for i in range(f.shape[0]):
        for j in range(f.shape[1]):
            d_l = dispersion(g_pad[i:i + n, j:j + n])
            c_l = centrality(g_pad[i:i + n, j:j + n])
            f[i, j] = g[i, j] - gamma * d / d_l * (g[i, j] - c_l)
    return f

# Returns a gaussian filter of size k and given sigma
def gaussian_filter(k = 3, sigma = 1.0):
    arx = np.arange((-k//2) + 1.0, (k//2) + 1.0)
    x, y = np.meshgrid(arx, arx)
    filt = np.exp(-1/2 * (x ** 2 + y ** 2) / sigma ** 2)
    return filt / np.sum(filt)

# Pad a image with zeros, centering the initial values. Considers that everything is a square matrix.
def pad_center(a, shape):
    pad_len = shape[0] - a.shape[0]
    return np.pad(a, ((pad_len - pad_len // 2, pad_len // 2), ))

# Applies constrained least squares filtering on image img
def constrained_least_squares(img):
    used_filter = gaussian_filter(gauss_size, sigma)
    laplacian = np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]])

    G = rfft2(img)
    P = rfft2(pad_center(laplacian, img.shape))
    H = rfft2(pad_center(used_filter, img.shape))
    H_conj = np.conjugate(H)
    rec_fun = H_conj / (np.abs(H) ** 2 + gamma * np.abs(P) ** 2)
    img_rec = irfft2(rec_fun * G)

    return fftshift(img_rec)

# returns RMSE of img1 and img2
def get_error(img1, img2):
    return (((img1.astype(np.int32) - img2.astype(np.int32)) ** 2).sum() / img1.shape[0] / img1.shape[1]) ** (1 / 2)

# read image and apply filtering
img = imageio.imread(g_name)
img_rec = adaptative_denoising(img) if filter_type == 1 else constrained_least_squares(img)
img_rec = np.clip(img_rec, 0, 255)

# calculate and print RMSE
img_ori = imageio.imread(f_name)
print(f'{get_error(img_ori, img_rec):.4f}')