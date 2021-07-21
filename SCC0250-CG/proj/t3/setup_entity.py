from moon import Moon
from walle import Walle
from OpenGL.GL import *
from PIL import Image
from entity import Entity
import numpy as np

def load_model_from_file(filename):
    """Loads a Wavefront OBJ file. """
    vertices = []
    texture_coords = []
    faces = []
    normals = []

    material = None

    for line in open(filename, 'r'):
        if line.startswith('#'):
            continue
        values = line.split()
        if not values:
            continue

        if values[0] == 'v':
            vertices.append(values[1:4])
        elif values[0] == 'vt':
            texture_coords.append(values[1:3])
        elif values[0] == 'vn':
            normals.append(values[1:4])
        elif values[0] in ('usemtl', 'usemat'):
            material = values[1]
        elif values[0] == 'f':
            face = []
            face_texture = []
            face_normals = []
            for v in values[1:]:
                w = v.split('/')
                face.append(int(w[0]))
                if len(w) >= 2 and len(w[1]) > 0:
                    face_texture.append(int(w[1]))
                else:
                    face_texture.append(1)
                    
                if len(w) >= 3 and len(w[2]) > 0:
                    face_normals.append(int(w[2]))
                else:
                    face_normals.append(1)

            faces.append((face, face_texture, face_normals, material))

    if len(normals) == 0:
        normals.append([0, 1, 0])

    model = {
        'vertices': vertices,
        'texture': texture_coords,
        'normals': normals,
        'faces': faces,
    }

    return model

def load_texture_from_file(texture_id, texture_img):
    glBindTexture(GL_TEXTURE_2D, texture_id)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST)
    img = Image.open(texture_img)
    img_width, img_height = img.size[0], img.size[1]
    image_data = img.tobytes('raw', 'RGB', 0, -1)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data)


def setup_entities():
    glEnable(GL_TEXTURE_2D)
    info = [
        # inside
        {'name': 'house', 'obj': 'assets/obj/cottage.obj', 'texture': 'assets/texture/cottage.png'}, 
        {'name': 'floor', 'obj': 'assets/obj/cottage_floor.obj', 'texture': 'assets/texture/floor.jpg'}, 
        {'name': 'pool_table', 'obj': 'assets/obj/pool_table.obj', 'texture': 'assets/texture/pool_table.jpg'}, 
        {'name': 'pizza', 'obj': 'assets/obj/pizza.obj', 'texture': 'assets/texture/pizza.jpg'}, 
        {'name': 'table', 'obj': 'assets/obj/table.obj', 'texture': 'assets/texture/table.jpg'},

        # outside
        {'name': 'walle', 'obj': 'assets/obj/walle.obj', 'texture': 'assets/texture/walle.jpg', 'type': Walle},
        {'name': 'ground', 'obj': 'assets/obj/ground.obj', 'texture': 'assets/texture/ground.jpg'},
        {'name': 'wood', 'obj': 'assets/obj/wood.obj', 'texture': 'assets/texture/wood.png'},
        {'name': 'sky', 'obj': 'assets/obj/box.obj', 'texture': 'assets/texture/sky.jpg'},
        {'name': 'road', 'obj': 'assets/obj/road.obj', 'texture': 'assets/texture/road.jpg'},
        {'name': 'cat', 'obj': 'assets/obj/cat.obj', 'texture': 'assets/texture/cat.jpg'},
        {'name': 'moon', 'obj': 'assets/obj/moon.obj', 'texture': 'assets/texture/moon_bump.png', 'type': Moon},
    ]
    textures_ids = glGenTextures(len(info))

    entities, vertices, texture_coords, normals = {}, [], [], []

    for entity_info, tex_id in zip(info, textures_ids):
        model = load_model_from_file(entity_info['obj'])
        first = len(vertices)
        
        for face in model['faces']:
            for vertex_id in face[0]:
                vertices.append(model['vertices'][vertex_id - 1])
            for texture_coord_id in face[1]:
                texture_coords.append(model['texture'][texture_coord_id - 1])
            for normal_id in face[2]:
                normals.append(model['normals'][normal_id - 1])

        last = len(vertices)
        load_texture_from_file(tex_id, entity_info['texture'])
        if 'type' in entity_info:
            entities[entity_info['name']] = entity_info['type'](first, last, tex_id)
        else:
            entities[entity_info['name']] = Entity(first, last, tex_id)

    entities['pool_table'].scale(1 / 100, 1 / 100, 1 / 100)
    entities['pool_table'].rotate(-np.pi / 2, 0, 0)
    entities['pool_table'].translate(-250, 0, 0)
    entities['pool_table'].set_light(kd=2)

    entities['table'].scale(1 / 90, 1 / 90, 1 / 90)
    entities['table'].translate(270, 0, 0)
    entities['table'].set_light(ks=2, ns=2)

    entities['house'].translate(0, -0.3, 0)

    entities['pizza'].scale(1 / 4, 1 / 4, 1 / 4)
    entities['pizza'].translate(12, 2.4, 0)
    entities['pizza'].set_light(kd=5)

    entities['walle'].scale(1 / 8, 1 / 8, 1 / 8)
    entities['walle'].translate(10, -4.5, -100)
    entities['walle'].set_light(kd=50, ks=25)

    entities['ground'].translate(0, -0.3, 0)
    entities['ground'].scale(5, 1, 5)
    entities['ground'].set_light(kd=0.5)

    entities['wood'].scale(1 / 3, 1 / 3, 1 / 3)
    entities['wood'].translate(40, 0, 0)
    entities['wood'].set_light(kd=5)

    entities['sky'].scale(20, 20, 20)

    entities['road'].scale(1 / 3, 1, 3)
    entities['road'].translate(0, -0.25, -8)

    entities['cat'].scale(1 / 65, 1 / 65, 1 / 65)
    entities['cat'].rotate(-np.pi / 2, 0, np.pi)
    entities['cat'].translate(250, -300, 15)

    entities['moon'].translate(-15, 15, 0)
    entities['moon'].set_light(kd=2, ks=2, ns=2)
    
    return entities, np.array(vertices, dtype=np.float32), np.array(texture_coords, dtype=np.float32), np.array(normals, dtype=np.float32)