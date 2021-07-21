from entity import Entity

import event
import numpy as np

class Moon(Entity):
    def __init__(self, first_vertex, last_vertex, texture_id):
        super().__init__(first_vertex, last_vertex, texture_id)

    def tick(self):
        # Make moon (light source) move in circular motion
        s = np.sin(event.total_frame_time / 1.0) * 0.25
        c = np.cos(event.total_frame_time / 1.0) * 0.25
        self.translate(s, 0, c)