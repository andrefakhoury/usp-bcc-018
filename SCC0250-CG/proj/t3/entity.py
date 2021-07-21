import utils
from OpenGL.GL import *

class Entity:
    def __init__(self, first_vertex, last_vertex, texture_id):
        self.first_vertex = first_vertex
        self.last_vertex = last_vertex
        self.texture_id = texture_id
        self.cx, self.cy, self.cz = 0, 0, 0 # object center
        self.rx, self.ry, self.rz = 0, 0, 0 # object rotation
        self.sx, self.sy, self.sz = 1, 1, 1 # object scale
        self.ka = self.kd = self.ks = self.ns = 1.0

    def translate(self, tx: float, ty: float, tz: float):
        self.cx += tx
        self.cy += ty
        self.cz += tz

    def rotate(self, rx: float, ry: float, rz: float):
        self.rx += rx
        self.ry += ry
        self.rz += rz

    def scale(self, sx: float, sy: float, sz: float):
        self.sx *= sx
        self.sy *= sy
        self.sz *= sz
    
    def set_light(self, ka=None, kd=None, ks=None, ns=None):
        self.ka = ka if ka is not None else self.ka
        self.kd = kd if kd is not None else self.kd
        self.ks = ks if ks is not None else self.ks
        self.ns = ns if ns is not None else self.ns

    def model(self):
        return utils.model(
            self.rx, self.ry, self.rz,
            self.cx, self.cy, self.cz,
            self.sx, self.sy, self.sz
        )

    def draw(self, program):
        loc_model = glGetUniformLocation(program, 'model')
        loc_ns = glGetUniformLocation(program, 'ns')
        loc_ks = glGetUniformLocation(program, 'ks')
        loc_kd = glGetUniformLocation(program, 'kd')
        loc_ka = glGetUniformLocation(program, 'ka')
        
        glUniformMatrix4fv(loc_model, 1, GL_TRUE, self.model())
        glUniform1f(loc_ka, self.ka)
        glUniform1f(loc_kd, self.kd)
        glUniform1f(loc_ks, self.ks)
        glUniform1f(loc_ns, self.ns)

        glBindTexture(GL_TEXTURE_2D, self.texture_id)
        glDrawArrays(GL_TRIANGLES, self.first_vertex, self.last_vertex - self.first_vertex)

    def tick(self):
        '''Perform animations attached to the entity. Should be overwritten by child objects'''
        pass
