from entity import Entity

import numpy as np

total_frame_time = 0
last_frame_time = 0

class Walle(Entity):
    def __init__(self, first_vertex, last_vertex, texture_id):
        super().__init__(first_vertex, last_vertex, texture_id)

    def tick(self):
        # make walle go back and forth
        s = np.sin(total_frame_time / 5)
        self.translate(3 * last_frame_time * (1 if s > 0 else -1), 0, 0)
