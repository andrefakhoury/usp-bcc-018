import math

from OpenGL.raw.GL.VERSION.GL_1_0 import GL_FILL, GL_LINE
from setup import WINDOW_HEIGHT, WINDOW_WIDTH
import glfw

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
        self.last_x, self.last_y = WINDOW_HEIGHT/2, WINDOW_WIDTH/2
        self.render_type = GL_FILL

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
        return np.array(glm.perspective(glm.radians(90.0), WINDOW_WIDTH / WINDOW_HEIGHT, .1, 1000.0), dtype=np.float32)

    def key_event(self, window, key, scancode, action, mods):
        if action == glfw.RELEASE:
            return
            
        move_keys = {glfw.KEY_W: 'W', glfw.KEY_S: 'S', glfw.KEY_A: 'A', glfw.KEY_D: 'D'}
        angle_keys = {glfw.KEY_Q: -10, glfw.KEY_E: 10}
        if key in move_keys:
            self.move(move_keys[key])
        elif key in angle_keys:
            self.yaw(angle_keys[key])
        elif key == glfw.KEY_P:
            self.render_type = GL_FILL if self.render_type == GL_LINE else GL_LINE
        elif key == glfw.KEY_ESCAPE:
            glfw.set_window_should_close(window, True)

    def mouse_event(self, window, xpos, ypos):
        xoffset = xpos - self.last_x
        yoffset = self.last_y - ypos
        self.last_x = xpos
        self.last_y = ypos

        self.yaw(xoffset * self.sensitivity)
        self.pitch(yoffset * self.sensitivity)
        self.update_camera()

        # fixate cursor position so that it does not leave the screen
        self.last_x, self.last_y = WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2
        glfw.set_cursor_pos(window, self.last_x, self.last_y)

    def setup_callbacks(self, window):
        glfw.set_key_callback(window, self.key_event)
        glfw.set_cursor_pos_callback(window, self.mouse_event)