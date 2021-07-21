import math

from OpenGL.raw.GL.VERSION.GL_1_0 import GL_FILL, GL_LINE
from setup import WINDOW_HEIGHT, WINDOW_WIDTH

import glm
import numpy as np


class Camera:
    def __init__(self):
        self.yaw_angle = 0
        self.pitch_angle = 0
        self.camera_speed = 0.1
        self.camera_up = glm.vec3(0.0, 1.0, 0.0)
        self.camera_pos = glm.vec3(0.0, 0.5, -15.0)
        self.camera_front = glm.vec3(1.0, 0.0, 0.0)
        self.sensitivity = 0.05
        self.render_type = GL_FILL
        self.fov_angle = 90

    def update_camera(self):
        self.camera_front.x = math.cos(glm.radians(self.yaw_angle)) * math.cos(glm.radians(self.pitch_angle))
        self.camera_front.y = math.sin(glm.radians(self.pitch_angle))
        self.camera_front.z = math.sin(glm.radians(self.yaw_angle)) * math.cos(glm.radians(self.pitch_angle))
        self.camera_front = glm.normalize(self.camera_front)
    
    def clip_pos(self):
        '''clip_pos ensures the player does not leave the map'''
        self.camera_pos.x = np.clip(self.camera_pos.x, -19.5, 19.5)
        self.camera_pos.y = np.clip(self.camera_pos.y, 0.5, 19.5)
        self.camera_pos.z = np.clip(self.camera_pos.z, -19.5, 19.5)

    def move(self, direction):
        if direction == 'W':
            self.camera_pos += self.camera_speed * self.camera_front
        elif direction == 'A':
            self.camera_pos -= glm.normalize(glm.cross(self.camera_front, self.camera_up)) * self.camera_speed
        elif direction == 'S':
            self.camera_pos -= self.camera_speed * self.camera_front
        elif direction == 'D':
            self.camera_pos += glm.normalize(glm.cross(self.camera_front, self.camera_up)) * self.camera_speed
        
        self.clip_pos()
    
    def change_fov(self, delta):
        self.fov_angle += delta
        self.fov_angle = np.clip(self.fov_angle, 60, 120)

    def yaw(self, angle):
        self.yaw_angle += angle
        self.update_camera()

    def pitch(self, angle):
        self.pitch_angle += angle
        self.pitch_angle = np.clip(self.pitch_angle, -89.9, 89.9) # prevent from looking inward
        self.update_camera()
    
    def view(self):
        return np.array(glm.lookAt(self.camera_pos, self.camera_pos + self.camera_front, self.camera_up), dtype=np.float32)
    
    def projection(self):
        return np.array(glm.perspective(glm.radians(self.fov_angle), WINDOW_WIDTH / WINDOW_HEIGHT, .1, 1000.0), dtype=np.float32)
