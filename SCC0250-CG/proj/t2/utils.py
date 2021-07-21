import glm
import numpy as np

def model(rx, ry, rz, tx, ty, tz, sx, sy, sz):
    mat = glm.mat4(1.0)
    mat = glm.scale(mat, glm.vec3(sx, sy, sz))
    mat = glm.rotate(mat, rx, glm.vec3(1, 0, 0))
    mat = glm.rotate(mat, ry, glm.vec3(0, 1, 0))
    mat = glm.rotate(mat, rz, glm.vec3(0, 0, 1))
    mat = glm.translate(mat, glm.vec3(tx, ty, tz))
    return np.array(mat, dtype=np.float32)
