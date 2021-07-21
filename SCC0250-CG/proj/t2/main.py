import glfw
from OpenGL.GL import *
from setup import *
from setup_entity import setup_entities

from entity import Entity
from camera import Camera

from time import time
from typing import List

import walle

def render(camera, entities: List[Entity], loc_model, loc_view, loc_projection):
    glfw.poll_events()

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glClearColor(1.0, 1.0, 1.0, 1.0)

    glPolygonMode(GL_FRONT_AND_BACK, camera.render_type)

    mat_view = camera.view()
    mat_projection = camera.projection()

    glUniformMatrix4fv(loc_view, 1, GL_TRUE, mat_view)
    glUniformMatrix4fv(loc_projection, 1, GL_TRUE, mat_projection)

    for _, obj in entities.items():
        obj.tick()
        obj.draw(loc_model)

    glfw.swap_buffers(window)


if __name__ == "__main__":
    # initialize window
    window = setup_glfw()
    program = setup_program()

    # initialize entities
    entities, vertices, texture_coords = setup_entities()
    setup_vertices(program, vertices)
    setup_textures(program, texture_coords)
    
    camera = Camera()
    camera.setup_callbacks(window)

    glEnable(GL_DEPTH_TEST)
    # Loop rendering
    while not glfw.window_should_close(window):
        loc_model = glGetUniformLocation(program, 'model')
        loc_view = glGetUniformLocation(program, 'view')
        loc_projection = glGetUniformLocation(program, 'projection')

        before = time()
        render(camera, entities, loc_model, loc_view, loc_projection)
        walle.last_frame_time = time() - before
        walle.total_frame_time += walle.last_frame_time

    glfw.terminate()
