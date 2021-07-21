import glfw
from OpenGL.GL import *

import event
import setup
from setup_entity import setup_entities

from entity import Entity

from time import time
from typing import List

def render(camera, entities: List[Entity], program):
    for _, entity in entities.items():
        entity.set_light(ka=event.ambient / 10)

    loc_view = glGetUniformLocation(program, 'view')
    loc_projection = glGetUniformLocation(program, 'projection')

    # update camera and light source position
    loc_view_pos = glGetUniformLocation(program, 'view_pos')
    glUniform3f(loc_view_pos, camera.camera_pos.x, camera.camera_pos.y, camera.camera_pos.z)
    loc_light_pos = glGetUniformLocation(program, 'light_pos')
    glUniform3f(loc_light_pos, entities['moon'].cx, entities['moon'].cy, entities['moon'].cz)

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
        obj.draw(program)

    glfw.swap_buffers(window)


if __name__ == "__main__":
    # initialize window
    window = setup.setup_glfw()
    program = setup.setup_program()

    # initialize entities
    entities, vertices, texture_coords, normals = setup_entities()
    setup.setup_buffer(program, vertices, 'position')
    setup.setup_textures(program, texture_coords)
    setup.setup_buffer(program, normals, 'normal')
    
    camera = event.camera
    event.setup_callbacks(window)

    glEnable(GL_DEPTH_TEST)
    # Loop rendering
    while not glfw.window_should_close(window):
        before = time()
        render(camera, entities, program)

        event.last_frame_time = time() - before
        event.total_frame_time += event.last_frame_time

    glfw.terminate()
