
import os
import subprocess

def get_files():
    file_paths = []
    for root, dir, files in os.walk('res/images'):
        for filename in files:
            file_paths.append(os.path.join(root, filename))

    return file_paths

arguments = [
    'spritebaker',
    '-width', '1024',
    '-height', '1024',
    '-padding', '4',
    '-bg_color', '255 0 255 0',
    '-trim_images',
    '-sprite_format',
    '-output', 'res/sprite_atlas.png'
]

arguments.append('-input')

for file in get_files():
    arguments.append(file)

# print " ".join(arguments)
subprocess.call(arguments)
