import glfw
from OpenGL.raw.GL.VERSION.GL_1_0 import GL_FILL, GL_LINE
from setup import WINDOW_HEIGHT, WINDOW_WIDTH

from camera import Camera

last_frame_time = 0
total_frame_time = 0

last_x, last_y = WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2

camera = Camera()
ambient = 2

def key_event(window, key, scancode, action, mods):
    global ambient
    if action == glfw.RELEASE:
        return

    if key == glfw.KEY_PERIOD:
        camera.change_fov(0.25)
    elif key == glfw.KEY_COMMA:
        camera.change_fov(-0.25)
        
    move_keys = {glfw.KEY_W: 'W', glfw.KEY_S: 'S', glfw.KEY_A: 'A', glfw.KEY_D: 'D'}
    angle_keys = {glfw.KEY_Q: -10, glfw.KEY_E: 10}
    if key in move_keys:
        camera.move(move_keys[key])
    elif key in angle_keys:
        camera.yaw(angle_keys[key])
    elif key == glfw.KEY_U:
        ambient = max(ambient - 1, 0)
    elif key == glfw.KEY_P:
        ambient = min(ambient + 1, 10)
    elif key == glfw.KEY_K:
        camera.render_type = GL_FILL if camera.render_type == GL_LINE else GL_LINE
    elif key == glfw.KEY_ESCAPE:
        glfw.set_window_should_close(window, True)

def mouse_event(window, xpos, ypos):
    global last_x, last_y
    xoffset = xpos - last_x
    yoffset = last_y - ypos
    last_x = xpos
    last_y = ypos

    camera.yaw(xoffset * camera.sensitivity)
    camera.pitch(yoffset * camera.sensitivity)
    camera.update_camera()

    # fixate cursor position so that it does not leave the screen
    last_x, last_y = WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2
    glfw.set_cursor_pos(window, last_x, last_y)

def setup_callbacks(window):
    glfw.set_key_callback(window, key_event)
    glfw.set_cursor_pos_callback(window, mouse_event)
