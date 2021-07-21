import glfw
from OpenGL.GL import *

WINDOW_HEIGHT = 720
WINDOW_WIDTH = 1280

def setup_glfw():
    glfw.init()
    glfw.window_hint(glfw.VISIBLE, glfw.FALSE)

    window = glfw.create_window(WINDOW_WIDTH, WINDOW_HEIGHT, 'MarcaTour 2k21', None, None)
    glfw.make_context_current(window)
    glfw.show_window(window)
    glfw.set_cursor_pos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2)
    glfw.set_input_mode(window, glfw.CURSOR, glfw.CURSOR_HIDDEN)
    return window

def setup_shader(program, shader_code, shader_type):
    shader = None
    if shader_type == 'vertex':
        shader   = glCreateShader(GL_VERTEX_SHADER)
    elif shader_type == 'fragment':
        shader = glCreateShader(GL_FRAGMENT_SHADER)
    else:
        raise RuntimeError('shader_type must be either vertex or fragment')
    
    glShaderSource(shader, shader_code)
    
    glCompileShader(shader)
    if not glGetShaderiv(shader, GL_COMPILE_STATUS):
        error = glGetShaderInfoLog(shader).decode()
        print(error)
        raise RuntimeError('Could not compile shader')
        
    glAttachShader(program, shader)


def setup_program():
    program = glCreateProgram()

    with open('shader/shader.vert', 'r') as f:
        vertex_code = '\n'.join(f.readlines())

    with open('shader/shader.frag', 'r') as f:
        fragment_code = '\n'.join(f.readlines())

    setup_shader(program, vertex_code, 'vertex')
    setup_shader(program, fragment_code, 'fragment')

    glLinkProgram(program)
    if not glGetProgramiv(program, GL_LINK_STATUS):
        print(glGetProgramInfoLog(program))
        raise RuntimeError('Linking error')

    glUseProgram(program)

    return program

def setup_vertices(program, vertices):
    buffer = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, buffer)
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_DYNAMIC_DRAW)
    stride = vertices.strides[0]
    offset = ctypes.c_void_p(0)
    loc = glGetAttribLocation(program, 'position')
    glEnableVertexAttribArray(loc)
    glVertexAttribPointer(loc, 3, GL_FLOAT, False, stride, offset)

def setup_textures(program, textures):
    buffer = glGenBuffers(1)
    glBindBuffer(GL_ARRAY_BUFFER, buffer)
    glBufferData(GL_ARRAY_BUFFER, textures.nbytes, textures, GL_STATIC_DRAW)
    stride = textures.strides[0]
    offset = ctypes.c_void_p(0)
    loc = glGetAttribLocation(program, 'texture_coord')
    glEnableVertexAttribArray(loc)
    glVertexAttribPointer(loc, 2, GL_FLOAT, False, stride, offset)
